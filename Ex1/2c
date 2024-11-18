#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 100
#define ITEM_NAME_LENGTH 50

// Function prototypes
void addItem(char shoppingList[][ITEM_NAME_LENGTH], int* itemCount, const char* item);
void removeItem(char shoppingList[][ITEM_NAME_LENGTH], int* itemCount, const char* item);
void displayShoppingList(char shoppingList[][ITEM_NAME_LENGTH], int itemCount);

int main() {
    char shoppingList[MAX_ITEMS][ITEM_NAME_LENGTH]; // Array to store shopping list items
    int itemCount = 0;                              // Current number of items in the list
    int choice;
    char item[ITEM_NAME_LENGTH];

    while (1) {
        printf("\nShopping List Menu:\n");
        printf("1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. Display Shopping List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter item to add: ");
                fgets(item, sizeof(item), stdin);
                item[strcspn(item, "\n")] = 0; // Remove newline character
                addItem(shoppingList, &itemCount, item);
                break;
            case 2:
                printf("Enter item to remove: ");
                fgets(item, sizeof(item), stdin);
                item[strcspn(item, "\n")] = 0; // Remove newline character
                removeItem(shoppingList, &itemCount, item);
                break;
            case 3:
                displayShoppingList(shoppingList, itemCount);
                break;
            case 4:
                printf("Exiting the application.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add an item to the shopping list
void addItem(char shoppingList[][ITEM_NAME_LENGTH], int* itemCount, const char* item) {
    if (*itemCount >= MAX_ITEMS) {
        printf("Shopping list is full. Cannot add more items.\n");
        return;
    }

    // Add the new item to the list
    strcpy(shoppingList[*itemCount], item);
    (*itemCount)++;
    printf("Item '%s' added successfully.\n", item);
}

// Function to remove an item from the shopping list
void removeItem(char shoppingList[][ITEM_NAME_LENGTH], int* itemCount, const char* item) {
    if (*itemCount == 0) {
        printf("Shopping list is empty. Nothing to remove.\n");
        return;
    }

    int index = -1;
    for (int i = 0; i < *itemCount; i++) {
        if (strcmp(shoppingList[i], item) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Item '%s' not found in the shopping list.\n", item);
        return;
    }

    // Shift items to fill the gap
    for (int i = index; i < *itemCount - 1; i++) {
        strcpy(shoppingList[i], shoppingList[i + 1]);
    }

    (*itemCount)--;
    printf("Item '%s' removed successfully.\n", item);
}

// Function to display the shopping list
void displayShoppingList(char shoppingList[][ITEM_NAME_LENGTH], int itemCount) {
    if (itemCount == 0) {
        printf("Shopping list is empty.\n");
        return;
    }

    printf("Current Shopping List:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d. %s\n", i + 1, shoppingList[i]);
    }
}
