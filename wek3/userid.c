#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_NOT_NULL root_user != NULL
#define TARGET_NOT_NULL target_user != NULL
#define BOTH_NOT_NULL USER_NOT_NULL && TARGET_NOT_NULL
#define SEARCH_BY_ID sptr->id == id

static int last_user_id = 0;

typedef struct User {
    int id;
    char username[50];
    struct User* next_following; 
} User;

/* Create new user account */
User* create_user(char* username) {
    User* uptr = malloc(sizeof(User));
    if (uptr == NULL) return NULL;
    
    uptr->id = ++last_user_id;
    strcpy(uptr->username, username);
    uptr->next_following = NULL;
    return uptr;
}

/* Follow another user */
void follow_user(User* root_user, User* target_user) {
    if(BOTH_NOT_NULL) {
        if (root_user->id == target_user->id) return;

        User *sptr = root_user;
        while (sptr->next_following != NULL) {
            if (sptr->id == target_user->id) return;
            sptr = sptr->next_following;
        }
        if (sptr->id == target_user->id) return;

        sptr->next_following = target_user;
    }
}

/* Unfollow user by ID */
void unfollow_by_id(int id, User* root_user) {
    if(USER_NOT_NULL) {
        User *sptr = root_user;
        User *prev = NULL;

        while (sptr != NULL) {
            if(SEARCH_BY_ID) {
                if(prev != NULL) {
                    prev->next_following = sptr->next_following;
                    printf("\n[Action] Unfollowed User ID %d (@%s) successfully!\n", id, sptr->username);
                } else {
                    printf("\n[Warning] Cannot unfollow the root user itself!\n");
                }
                return;
            }
            prev = sptr;
            sptr = sptr->next_following;
        }
    }
    printf("\nUser with ID %d not found in this following chain!\n", id);
}

/* Print specific user information by ID */
void print_user_by_id(int id, User* root_user) {
    if (USER_NOT_NULL) {
        User *sptr = root_user;
        while (sptr != NULL) {
            if (SEARCH_BY_ID) {
                printf("\n==================================\n");
                printf("  Found Account Info:\n");
                printf("  User ID: %d\n", sptr->id);
                printf("  Username: @%s\n", sptr->username);
                if (sptr->next_following != NULL) {
                    printf("  Next Following: @%s (ID: %d)\n", sptr->next_following->username, sptr->next_following->id);
                } else {
                    printf("  Next Following: None (End of chain)\n");
                }
                printf("==================================\n");
                return;
            }
            sptr = sptr->next_following;
        }
    }
    printf("\nUser with ID %d not found!\n", id);
}

/* Print the entire following chain */
void print_following_chain(User* root_user) {
    if(USER_NOT_NULL) {
        User *sptr = root_user;
        printf("\n@%s is following this chain:\n", root_user->username);
        while (sptr != NULL) {
            printf(" -> [ID: %d | Username: @%s]\n", sptr->id, sptr->username);
            sptr = sptr->next_following;
        }
        printf("\n");
    }
}

/* Main function for testing */
int main() {
    User* u1 = create_user("Alwaleed");
    User* u2 = create_user("Ahmed");
    User* u5 = create_user("Naif");
    User* u6 = create_user("Nawaf");

    printf("--- Creating  Follow Relations ---\n");
    follow_user(u1, u2); 
    follow_user(u1, u5); 
    follow_user(u1, u6); 

    print_following_chain(u1);

    printf("--- Searching for specific account ---\n");
    print_user_by_id(2, u1);

    unfollow_by_id(3, u1);

    printf("--- Chain After Unfollow ---\n");
    print_following_chain(u1);

    free(u1);
    free(u2);
    free(u5);
    free(u6);

    return 0;
}