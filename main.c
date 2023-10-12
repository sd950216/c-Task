#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 20

int main(void) {
    char** usernames = NULL;
    int userCount = 0;

    while (1) {
        printf("Enter 'create' to add a new user or 'access' to log in: ");
        char choice[10];
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';  // Remove the trailing newline from fgets

        if (strcmp(choice, "create") == 0) {
            char newUser[MAX_USERNAME_LENGTH];
            printf("Enter a new username: ");
            fgets(newUser, sizeof(newUser), stdin);
            newUser[strcspn(newUser, "\n")] = '\0';

            int usernameExists = 0;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(newUser, usernames[i]) == 0) {
                    printf("Username already taken. Registration unsuccessful.\n");
                    usernameExists = 1;
                    break;
                }
            }

            if (!usernameExists) {
                usernames = (char**)realloc(usernames, (userCount + 1) * sizeof(char*));
                usernames[userCount] = (char*)malloc((strlen(newUser) + 1) * sizeof(char));
                strcpy(usernames[userCount], newUser);
                userCount++;
                printf("User created successfully.\n");
            }
        } else if (strcmp(choice, "access") == 0) {
            char user[MAX_USERNAME_LENGTH];
            printf("Enter your username: ");
            fgets(user, sizeof(user), stdin);
            user[strcspn(user, "\n")] = '\0';

            int userFound = 0;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(user, usernames[i]) == 0) {
                    userFound = 1;
                    break;
                }
            }

            if (userFound) {
                printf("Access granted. Welcome, %s!\n", user);
            } else {
                printf("Access denied. User not found.\n");
            }
        } else {
            printf("Invalid choice. Please enter 'create' or 'access'.\n");
        }
    }

    // Free allocated memory before exiting
    for (int i = 0; i < userCount; i++) {
        free(usernames[i]);
    }
    free(usernames);

    return 0;
}
