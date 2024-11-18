/*A social media platform needs to search for a user by their unique username in a list of thousands of users. The system should be designed to search through a dynamic list, optimizing performance for large datasets.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform binary search for a username
int binarySearch(char** usernames, int low, int high, char* target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(usernames[mid], target);
        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Function to sort usernames alphabetically
void quickSort(char** usernames, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(usernames, low, high);
        quickSort(usernames, low, pivotIndex - 1);
        quickSort(usernames, pivotIndex + 1, high);
    }
}

int partition(char** usernames, int low, int high) {
    char* pivot = usernames[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(usernames[j], pivot) < 0) {
            i++;
            char* temp = usernames[i];
            usernames[i] = usernames[j];
            usernames[j] = temp;
        }
    }
    char* temp = usernames[i + 1];
    usernames[i + 1] = usernames[high];
    usernames[high] = temp;
    return i + 1;
}

// Main function
int main() {
    int n;
    printf("Enter the number of users: ");
    scanf("%d", &n);

    char** usernames = (char**)malloc(n * sizeof(char*));
    if (usernames == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    getchar(); // Clear newline character from input buffer
    printf("Enter the usernames:\n");
    for (int i = 0; i < n; i++) {
        usernames[i] = (char*)malloc(50 * sizeof(char));
        if (usernames[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        fgets(usernames[i], 50, stdin);
        usernames[i][strcspn(usernames[i], "\n")] = '\0'; // Remove trailing newline
    }

    quickSort(usernames, 0, n - 1);

    char target[50];
    printf("Enter the username to search: ");
    fgets(target, 50, stdin);
    target[strcspn(target, "\n")] = '\0'; // Remove trailing newline

    int result = binarySearch(usernames, 0, n - 1, target);

    if (result != -1)
        printf("User found at position: %d\n", result + 1);
    else
        printf("User not found.\n");

    for (int i = 0; i < n; i++) {
        free(usernames[i]);
    }
    free(usernames);

    return 0;
}
