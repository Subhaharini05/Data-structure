/* Design a BST to store Students records, what methods will you implement to add new students, find a student by ID and retrieve all students IDs in ascending order*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a Student
typedef struct Student {
    int studentID;              // Unique Student ID
    char name[100];             // Name of the student
    struct Student* left;       // Pointer to the left subtree
    struct Student* right;      // Pointer to the right subtree
} Student;

// Function prototypes
Student* createStudent(int studentID, char* name);
Student* insertStudent(Student* root, int studentID, char* name);
Student* searchStudent(Student* root, int studentID);
void displayStudentIDsInOrder(Student* root);
void freeTree(Student* root);

int main() {
    Student* root = NULL;  // Root of the BST (initially empty)
    int choice, studentID;
    char name[100];
    Student* result;

    // Menu-driven program for student record management
    do {
        printf("\nStudent Record Management System:\n");
        printf("1. Add a Student\n");
        printf("2. Find a Student by ID\n");
        printf("3. Display All Student IDs in Ascending Order\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &studentID);
                printf("Enter Student Name: ");
                getchar();  // Consume newline character
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline character
                root = insertStudent(root, studentID, name);
                printf("Student added successfully.\n");
                break;
            case 2:
                printf("Enter Student ID to search: ");
                scanf("%d", &studentID);
                result = searchStudent(root, studentID);
                if (result != NULL) {
                    printf("Student Found: ID: %d, Name: %s\n",
                           result->studentID, result->name);
                } else {
                    printf("Student with ID %d not found.\n", studentID);
                }
                break;
            case 3:
                printf("All Student IDs in Ascending Order:\n");
                displayStudentIDsInOrder(root);
                break;
            case 4:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    // Free allocated memory
    freeTree(root);
    return 0;
}

// Function to create a new student node
Student* createStudent(int studentID, char* name) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->studentID = studentID;
    strcpy(newStudent->name, name);
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

// Function to insert a student into the BST
Student* insertStudent(Student* root, int studentID, char* name) {
    if (root == NULL) {
        return createStudent(studentID, name);
    }
    if (studentID < root->studentID) {
        root->left = insertStudent(root->left, studentID, name);
    } else if (studentID > root->studentID) {
        root->right = insertStudent(root->right, studentID, name);
    }
    return root;
}

// Function to search for a student in the BST by ID
Student* searchStudent(Student* root, int studentID) {
    if (root == NULL || root->studentID == studentID) {
        return root;
    }
    if (studentID < root->studentID) {
        return searchStudent(root->left, studentID);
    } else {
        return searchStudent(root->right, studentID);
    }
}

// Function to display all student IDs in ascending order (inorder traversal)
void displayStudentIDsInOrder(Student* root) {
    if (root != NULL) {
        displayStudentIDsInOrder(root->left);
        printf("%d ", root->studentID);
        displayStudentIDsInOrder(root->right);
    }
}

// Function to free all nodes in the BST
void freeTree(Student* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
