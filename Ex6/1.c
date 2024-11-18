/*A software application for an online store needs to sort a list of product prices in ascending order to help customers easily find cheaper options. The list is stored dynamically, and the program should work efficiently even for large datasets.*/

#include <stdio.h>
#include <stdlib.h>

// Function to sort an array using quicksort
void quickSort(float* prices, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(prices, low, high);
        quickSort(prices, low, pivotIndex - 1);
        quickSort(prices, pivotIndex + 1, high);
    }
}

// Partition function for quicksort
int partition(float* prices, int low, int high) {
    float pivot = prices[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (prices[j] < pivot) {
            i++;
            float temp = prices[i];
            prices[i] = prices[j];
            prices[j] = temp;
        }
    }
    float temp = prices[i + 1];
    prices[i + 1] = prices[high];
    prices[high] = temp;
    return i + 1;
}

// Main function
int main() {
    int n;
    printf("Enter the number of products: ");
    scanf("%d", &n);

    float* prices = (float*)malloc(n * sizeof(float));
    if (prices == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the prices of the products:\n");
    for (int i = 0; i < n; i++) {
        scanf("%f", &prices[i]);
    }

    quickSort(prices, 0, n - 1);

    printf("Sorted prices in ascending order:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", prices[i]);
    }
    printf("\n");

    free(prices);
    return 0;
}
