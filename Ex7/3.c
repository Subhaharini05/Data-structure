/*A telephone directory application needs to search for a specific contact’s phone number by their name. The contact list is stored using dynamic memory allocation, and the search should be efficient and work for any list size.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store contact information
typedef struct {
    char name[50];
    char phone[15];
} Contact;

// Function to perform binary search for a contact by name

int binarySearch(Contact* contacts, int low, int high, char* target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(contacts[mid].name, target);
        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Function to sort contacts alphabetically by name using quicksort
void quickSort(Contact* contacts, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(contacts, low, high);
        quickSort(contacts, low, pivotIndex - 1);
        quickSort(contacts, pivotIndex + 1, high);
    }
}

int partition(Contact* contacts, int low, int high) {
    Contact pivot = contacts[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(contacts[j].name, pivot.name) < 0) {
            i++;
            Contact temp = contacts[i];
            contacts[i] = contacts[j];
            contacts[j] = temp;
        }
    }
    Contact temp = contacts[i + 1];
    contacts[i + 1] = contacts[high];
    contacts[high] = temp;
    return i + 1;
}

// Main function
int main() {
    int n;
    printf("Enter the number of contacts: ");
    scanf("%d", &n);

    Contact* contacts = (Contact*)malloc(n * sizeof(Contact));
    if (contacts == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    getchar(); // Clear newline character from input buffer
    printf("Enter the contact details (Name Phone):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %s", contacts[i].name, contacts[i].phone);
    }

    quickSort(contacts, 0, n - 1);

    char target[50];
    printf("Enter the name to search for: ");
    scanf("%s", target);

    int result = binarySearch(contacts, 0, n - 1, target);

    if (result != -1)
        printf("Contact Found:\nName: %s\nPhone: %s\n", contacts[result].name, contacts[result].phone);
    else
        printf("Contact not found.\n");

    free(contacts);
    return 0;
}
