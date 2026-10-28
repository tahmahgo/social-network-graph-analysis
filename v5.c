
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void setup_Matrix(int n, int **Records, char path[500]) {
     int from_node, to_node;

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    
     for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Records[i][j] = 0;
        }
    }

    while (fscanf(fp, "%d %d", &from_node, &to_node) == 2) {
        if (from_node >= 0 && from_node < n && to_node >= 0 && to_node < n) {
            Records[from_node][to_node] = 1;
            Records[to_node][from_node] = 1;
    }

	}
	
	fclose(fp);
    
}

long currentTimeMillis() {
    struct timeval time;
    gettimeofday(&time, NULL);
    long s1 = (long)(time.tv_sec) * 1000;
    long s2 = (time.tv_usec / 1000);
    return s1 + s2;
}


int mainMenu(int *choice) {
    printf("MAIN MENU\n");
    printf("[1] View friends list\n");
    printf("[2] Check connection\n");
    printf("[3] Exit\n");
    printf("Enter your choice: ");
    scanf("%d", choice);

    if (*choice >= 1 && *choice <= 3) {
        return 1;
    } else {
        return 0;
    }
}

int getfriendsList(int n, int **Records) {
    int ID, valid, nFriends;

    nFriends = 0;
    valid = 0;

    do {
        valid = 0;
        printf("Enter ID: ");
        scanf("%d", &ID);

        if (ID >= n || ID < 0) {
            printf("ID number does not exist. Try again.\n\n");
            valid = 1;
        }

    } while (valid == 1);

    printf("\nFRIENDS:\n");

    for (int i = 0; i < n; i++) {
        if (Records[ID][i] == 1) {
            printf("%d\n", i);
            nFriends++;
        }
    }

    printf("\nTotal number of friends: %d\n\n", nFriends);

    return 1;
}

int checkConnection(int n, int **Records) {
    int ID1, ID2, valid;

    valid = 0;

    printf("\nCheck connection of ID numbers:\n");

    do {
        valid = 0;
        printf("\nEnter ID 1: ");
        scanf("%d", &ID1);

        if (ID1 >= n || ID1 < 0) {
            printf("ID not in dataset. Please try again.\n\n");
            valid = 1;
        } else {
            printf("\nEnter ID 2: ");
            scanf("%d", &ID2);

            if (ID2 >= n || ID2 < 0) {
                printf("ID not in dataset. Please try again.\n\n");
                valid = 1;
            } else {
                if (ID1 == ID2) {
                    printf("Both IDs are the same. No connection is needed.\n\n");
                } else {
                    if (Records[ID1][ID2] == 1) {
                        printf("A connection was found.\n\n");
                    } else {
                        printf("A connection was not found.\n\n");
                    }
                }
            }
        }
    } while (valid);

    return 1;
}

int main() {
    char fileName[500]; // Increased the size for the file path
    int n, e, choice, valid;
    long startTime, endTime;

    valid = 0;

    printf("Enter file name: ");
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strcspn(fileName, "\n")] = '\0'; // Remove the newline character from the file name

    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    fscanf(fp, "%d %d", &n, &e);
    fclose(fp);

    int **Records = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        Records[i] = malloc(n * sizeof(int));
    }

    setup_Matrix(n, Records, fileName);

    printf("Data loaded!\n\n");

    do {
        valid = 0;
        if (mainMenu(&choice) == 1) {
            switch (choice) {
                case 1:
                    startTime = currentTimeMillis();
                    getfriendsList(n, Records);
                    endTime = currentTimeMillis();
                    printf("Execution Time: %ldms\n\n", endTime - startTime);
                    valid = 1;
                    break;

                case 2:
                    startTime = currentTimeMillis();
                    checkConnection(n, Records);
                    endTime = currentTimeMillis();
                    printf("Execution Time: %ldms\n\n", endTime - startTime);
                    valid = 1;
                    break;
            }
        } else {
            printf("Invalid input. Try again.\n\n");
            valid = 1;
        }
    } while (valid);

    // Free the dynamically allocated memory for Records
    for (int i = 0; i < n; i++) {
        free(Records[i]);
    }
    free(Records);

    return 0;
}
