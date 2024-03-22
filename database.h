#ifndef DATABASE_H
#define DATABASE_H

#include "hashTable.h"

typedef struct {
    int studentId;
    char *name;
    char *address;
    int phone;
} SNAP;

typedef struct {
    char *course;
    int studentId;
    char *grade;
} CSG;

typedef struct {
    char *course;
    char *prerequisite;
} CP;

typedef struct {
    char *course;
    char *day;
    int hour;
} CDH;

typedef struct {
    char *course;
    char *room;
} CR;

void initializeDatabase(void);

void insertSNAP(int studentId, char *name, char *address, int phone);
void insertCSG(char *course, int studentId, char *grade);
void insertCP(char *course, char *prerequisite);
void insertCDH(char *course, char *day, int hour);
void insertCR(char *course, char *room);

void deleteSNAP(char *studentId, char *name, char *address, char *phone);
void deleteCSG(char *course, char *studentId, char *grade);
void deleteCP(char *course, char *prerequisite);
void deleteCDH(char *course, char *day, char *hour);
void deleteCR(char *course, char *room);

void lookupSNAP(char *studentId, char *name, char *address, char *phone);
void lookupCSG(char *course, char *studentId, char *grade);
void lookupCP(char *course, char *prerequisite);
void lookupCDH(char *course, char *day, char *hour);
void lookupCR(char *course, char *room);

void printSNAPTable(void);
void printCSGTable(void);
void printCPTable(void);
void printCDHTable(void);
void printCRTable(void);

void findGradeForStudentInCourse(char *studentName, char *courseName);
void findStudentLocation(char *studentName, int hour, char *day);

void freeDatabase(void);

typedef struct {
    int studentId;
    char name[100];  // Assuming a fixed size for simplicity
    char address[100];
    int phone;
} SelectedSNAP;

typedef struct {
    char *course;
} ProjectedCourse;

typedef struct {
    int studentId;
    char *name;
    char *address;
    int phone;
    char *course;
    char *grade;
} SNAP_CSG_Join;

typedef struct {
    int studentId;
    char *course;
    char *grade;
} FinalResult;


void selectionSNAPByName(char *name, SelectedSNAP result[], int *resultSize);
void projectionCSGToCourse(ProjectedCourse result[], int *resultSize);
void joinSNAPAndCSG(SNAP_CSG_Join result[], int *resultSize);
void projectionCSGonFinal(SNAP_CSG_Join joinedEntries[], int joinedSize, FinalResult finalResults[], int *finalResultSize);
void findGradesForStudent(void);

void createAppendixA(void);

#endif // DATABASE_H
