#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

int main(void) {
    createAppendixA();

    // Print the contents of each table
    printf("Showing original content of tables in Appendix A:\n");

    printSNAPTable();
    printf("\n");

    printCSGTable();
    printf("\n");

    printCPTable();
    printf("\n");

    printCDHTable();
    printf("\n");

    printCRTable();
    printf("\n");


    //Part 1
    // Perform operations as per the assignment
    printf("\nPerforming Operations:\n");

    // (a) lookup(⟨“DSCC201”, 01376, “B+”⟩, Course-StudentId-Grade)
    printf("Operation: Lookup in CSG - DSCC201, 01376, B+\n");
    lookupCSG("DSCC201", "01376", "B+");
    printf("\n");

    // (b) lookup(⟨∗, “R. Johnson”, ∗, ∗⟩, StudentId-Name-Address-Phone)
    printf("Operation: Lookup in SNAP - *, R. Johnson, *, *\n");
    lookupSNAP("*", "R. Johnson", "*", "*");
    printf("\n");

    // (c) lookup(⟨“CSC252”, “CSC173”⟩, Course-Prerequisite)
    printf("Operation: Lookup in CP - CSC252, CSC173\n");
    lookupCP("CSC252", "CSC173");
    printf("\n");

    // (d) delete(⟨“DSCC201”, “T”, “900”⟩, Course-Day-Hour)
    printf("Operation: Delete from CDH - DSCC201, T, 900\n");
    deleteCDH("DSCC201", "T", "900");
    printCDHTable();
    printf("\n");

    // (e) delete(⟨“CSC171”, “T”, ∗⟩, Course-Day-Hour)
    printf("Operation: Delete from CDH - CSC171, T, *\n");
    deleteCDH("CSC171", "T", "*");
    printCDHTable();
    printf("\n");

    // (f) delete(⟨“CSC173”, ∗, ∗⟩, Course-Day-Hour)
    printf("Operation: Delete from CDH - CSC173, *, *\n");
    deleteCDH("CSC173", "*", "*");
    printCDHTable();
    printf("\n");

    // (g) insert(⟨“CSC252”, 74533, “A-”⟩, Course-StudentId-Grade)
    printf("Operation: Insert into CSG - CSC252, 74533, A-\n");
    insertCSG("CSC252", 74533, "A-");
    printCSGTable();
    printf("\n");

    // (h) insert(⟨“DSCC201”, 66252, “C”⟩, Course-StudentId-Grade)
    printf("Operation: Insert into CSG - DSCC201, 66252, C\n");
    insertCSG("DSCC201", 66252, "C");
    printCSGTable();
    printf("\n");

    //Reset database for part 2
    freeDatabase();

    // Part 2
    createAppendixA();
    printf("\nPart 2 - Using Queries:\n");

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Find grade for student in course\n");
        printf("2. Find student location\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number (1, 2, or 3).\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        if (choice == 1) {
            char studentName[50];
            char courseName[50];

            printf("Enter student name: ");
            fgets(studentName, 50, stdin);
            studentName[strcspn(studentName, "\n")] = 0;

            printf("Enter course name: ");
            fgets(courseName, 50, stdin);
            courseName[strcspn(courseName, "\n")] = 0;

            findGradeForStudentInCourse(studentName, courseName);
        } else if (choice == 2) {
            char studentName[50];
            int hour;
            char day[10];

            printf("Enter student name: ");
            fgets(studentName, 50, stdin);
            studentName[strcspn(studentName, "\n")] = 0;

            printf("Enter hour (as integer, e.g., 1400 or 900): ");
            scanf("%d", &hour);
            getchar();

            printf("Enter day (e.g., M, T, W, R, F): ");
            fgets(day, 10, stdin);
            day[strcspn(day, "\n")] = 0;

            findStudentLocation(studentName, hour, day);
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }

    //Reset database for part 3
    freeDatabase();

    // Part 3 - Demonstrating Relational Algebra Operations
    createAppendixA();
    printf("\nPart 3 - Demonstrating Relational Algebra Operations:\n");

    // 1. Selection: σName=“O. Gonzalez”(SNAP)
    SelectedSNAP selectedResults[100];
    int selectedResultsSize = 0;
    selectionSNAPByName("O. Gonzalez", selectedResults, &selectedResultsSize);

    printf("1. Selection: σName=“O. Gonzales”(SNAP)\n");
    printf("Results of: σName=“O. Gonzalez”(SNAP)\n");
    for (int i = 0; i < selectedResultsSize; i++) {
        printf("Student ID: %d, Name: %s, Address: %s, Phone: %d\n",
               selectedResults[i].studentId, selectedResults[i].name,
               selectedResults[i].address, selectedResults[i].phone);
    }
    printf("\n");

    // 2. Projection: πCourse(CSG)
    ProjectedCourse projectedResults[100];
    int projectedResultsSize = 0;
    projectionCSGToCourse(projectedResults, &projectedResultsSize);

    printf("2. Projection: πCourse(CSG)\n");
    printf("Results of: πCourse(CSG)\n");
    for (int i = 0; i < projectedResultsSize; i++) {
        printf("Course: %s\n", projectedResults[i].course);
        free(projectedResults[i].course);  // Remember to free the duplicated string
    }
    printf("\n");

    // 3. Join: SNAP ⨝ CSG
    SNAP_CSG_Join joinResults[100];
    int joinResultsSize = 0;
    joinSNAPAndCSG(joinResults, &joinResultsSize);

    printf("3. Join: SNAP ⨝ CSG\n");
    printf("Results of: SNAP ⨝ CSG\n");
    for (int i = 0; i < joinResultsSize; i++) {
        printf("Student ID: %d, Name: %s, Address: %s, Phone: %d, Course: %s, Grade: %s\n",
               joinResults[i].studentId, joinResults[i].name, joinResults[i].address,
               joinResults[i].phone, joinResults[i].course, joinResults[i].grade);

        // Free the duplicated strings
        free(joinResults[i].name);
        free(joinResults[i].address);
        free(joinResults[i].course);
        free(joinResults[i].grade);
    }
    printf("\n");

    // 4. All together
    printf("4. Combining all 3:\n");
    findGradesForStudent();

    // Free the database
    freeDatabase();

    return 0;
}
