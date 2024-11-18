#include <stdio.h>
#define MAX_GRADES 100

// Function prototypes
void addGrade(float grades[], int* gradeCount, float grade);
float calculateAverage(float grades[], int gradeCount);
void displayGrades(float grades[], int gradeCount);

int main() {
    float grades[MAX_GRADES]; // Array to store grades
    int gradeCount = 0;       // Current number of grades
    int choice;
    float grade;

    while (1) {
        printf("\nGrade Management Menu:\n");
        printf("1. Add Grade\n");
        printf("2. Calculate Average Grade\n");
        printf("3. Display All Grades\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter grade to add: ");
                scanf("%f", &grade);
                addGrade(grades, &gradeCount, grade);
                break;
            case 2:
                if (gradeCount == 0) {
                    printf("No grades available to calculate average.\n");
                } else {
                    float average = calculateAverage(grades, gradeCount);
                    printf("Average Grade: %.2f\n", average);
                }
                break;
            case 3:
                displayGrades(grades, gradeCount);
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

// Function to add a grade to the list
void addGrade(float grades[], int* gradeCount, float grade) {
    if (*gradeCount >= MAX_GRADES) {
        printf("Grade list is full. Cannot add more grades.\n");
        return;
    }

    // Add the grade to the array
    grades[*gradeCount] = grade;
    (*gradeCount)++;
    printf("Grade %.2f added successfully.\n", grade);
}

// Function to calculate the average grade
float calculateAverage(float grades[], int gradeCount) {
    float sum = 0;
    for (int i = 0; i < gradeCount; i++) {
        sum += grades[i];
    }
    return sum / gradeCount;
}

// Function to display all grades
void displayGrades(float grades[], int gradeCount) {
    if (gradeCount == 0) {
        printf("No grades available to display.\n");
        return;
    }

    printf("Current Grades:\n");
    for (int i = 0; i < gradeCount; i++) {
        printf("%d. %.2f\n", i + 1, grades[i]);
    }
}
