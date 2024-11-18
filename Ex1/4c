#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a task
typedef struct Task {
    char description[100];
    struct Task* next;
} Task;

// Function prototypes
void addTaskAtBeginning(Task** head, const char* description);
void removeTaskFromEnd(Task** head);
void displayTasks(Task* head);

int main() {
    Task* taskList = NULL; // Head pointer for the linked list
    int choice;
    char description[100];

    while (1) {
        printf("\nTask Management Menu:\n");
        printf("1. Add Task at the Beginning\n");
        printf("2. Remove Task from the End\n");
        printf("3. Display All Tasks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = 0; // Remove newline character
                addTaskAtBeginning(&taskList, description);
                break;
            case 2:
                removeTaskFromEnd(&taskList);
                break;
            case 3:
                displayTasks(taskList);
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

// Function to add a task at the beginning of the list
void addTaskAtBeginning(Task** head, const char* description) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (!newTask) {
        printf("Memory allocation failed. Task not added.\n");
        return;
    }

    strcpy(newTask->description, description);
    newTask->next = *head;
    *head = newTask;
    printf("Task '%s' added successfully.\n", description);
}

// Function to remove a task from the end of the list
void removeTaskFromEnd(Task** head) {
    if (*head == NULL) {
        printf("Task list is empty. Nothing to remove.\n");
        return;
    }

    Task* temp = *head;
    Task* prev = NULL;

    // Traverse to the last node
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL) { // Only one task in the list
        *head = NULL;
    } else {
        prev->next = NULL;
    }

    printf("Task '%s' removed successfully.\n", temp->description);
    free(temp);
}

// Function to display all tasks
void displayTasks(Task* head) {
    if (head == NULL) {
        printf("Task list is empty.\n");
        return;
    }

    printf("Current Tasks:\n");
    int index = 1;
    while (head != NULL) {
        printf("%d. %s\n", index++, head->description);
        head = head->next;
    }
}
