/*A database of student records contains student IDs and their corresponding details. The system needs to find the record of a student based on their unique student ID. The list of records is stored in a dynamic array.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student records
typedef struct {
    int id;
    char name[50];
    int age;
} Student;

// Function to find a student record by ID
void findStudent(Student* records, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (records[i].id == id) {
            printf("Student Found:\n");
            printf("ID: %d\n", records[i].id);
            printf("Name: %s\n", records[i].name);
            printf("Age: %d\n", records[i].age);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// Main function
int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    Student* records = (Student*)malloc(n * sizeof(Student));
    if (records == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter student details (ID Name Age):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %s %d", &records[i].id, records[i].name, &records[i].age);
    }

    int searchId;
    printf("Enter the student ID to search: ");
    scanf("%d", &searchId);

    findStudent(records, n, searchId);

    free(records);
    return 0;
}
