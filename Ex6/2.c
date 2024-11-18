/* team of researchers needs to sort the ages of participants in a clinical trial from youngest to oldest. The list of ages is stored using pointers in dynamically allocated memory to allow flexibility in the size of the dataset. only code  alone in c*/

#include <stdio.h>
#include <stdlib.h>

// Function to sort an array using bubble sort
void bubbleSort(int* ages, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ages[j] > ages[j + 1]) {
                int temp = ages[j];
                ages[j] = ages[j + 1];
                ages[j + 1] = temp;
            }
        }
    }
}

// Main function
int main() {
    int n;
    printf("Enter the number of participants: ");
    scanf("%d", &n);

    int* ages = (int*)malloc(n * sizeof(int));
    if (ages == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the ages of the participants:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ages[i]);
    }

    bubbleSort(ages, n);

    printf("Sorted ages from youngest to oldest:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", ages[i]);
    }
    printf("\n");

    free(ages);
    return 0;
}
