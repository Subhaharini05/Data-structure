/*A library management system needs to sort the titles of books alphabetically in an efficient manner. The program should dynamically allocate memory for storing the book titles and use a suitable sorting algorithm to handle a large number of books.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to sort book titles using quicksort
void quickSort(char** titles, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(titles, low, high);
        quickSort(titles, low, pivotIndex - 1);
        quickSort(titles, pivotIndex + 1, high);
    }
}

// Partition function for quicksort
int partition(char** titles, int low, int high) {
    char* pivot = titles[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(titles[j], pivot) < 0) {
            i++;
            char* temp = titles[i];
            titles[i] = titles[j];
            titles[j] = temp;
        }
    }
    char* temp = titles[i + 1];
    titles[i + 1] = titles[high];
    titles[high] = temp;
    return i + 1;
}

// Main function
int main() {
    int n;
    printf("Enter the number of books: ");
    scanf("%d", &n);

    char** titles = (char**)malloc(n * sizeof(char*));
    if (titles == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    getchar(); // Clear newline character from input buffer
    printf("Enter the titles of the books:\n");
    for (int i = 0; i < n; i++) {
        titles[i] = (char*)malloc(100 * sizeof(char));
        if (titles[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        fgets(titles[i], 100, stdin);
        titles[i][strcspn(titles[i], "\n")] = '\0'; // Remove trailing newline
    }

    quickSort(titles, 0, n - 1);

    printf("Book titles sorted alphabetically:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", titles[i]);
        free(titles[i]);
    }
    free(titles);

    return 0;
}
