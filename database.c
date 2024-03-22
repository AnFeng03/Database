#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "database.h"

HashTable *snapTable;
HashTable *csgTable;
HashTable *cpTable;
HashTable *cdhTable;
HashTable *crTable;

char *createKeyForSNAP(int studentId) {
    char *key = malloc(20 * sizeof(char));
    sprintf(key, "%d", studentId);
    return key;
}

char *createKeyForCSG(char *course, int studentId) {
    char *key = malloc(50 * sizeof(char));
    sprintf(key, "%s_%d", course, studentId);
    return key;
}

char *createKeyForCP(char *course) {
    char *key = strdup(course);
    return key;
}

char *createKeyForCDH(char *course, char *day, int hour) {
    char *key = malloc(50 * sizeof(char));
    sprintf(key, "%s_%s_%d", course, day, hour);
    return key;
}

char *createKeyForCR(char *course) {
    char *key = strdup(course);
    return key;
}

void initializeDatabase(void) {
    snapTable = createHashTable(100);
    csgTable = createHashTable(100);
    cpTable = createHashTable(100);
    cdhTable = createHashTable(100);
    crTable = createHashTable(100);
}

void insertSNAP(int studentId, char *name, char *address, int phone) {
    SNAP *newSNAP = malloc(sizeof(SNAP));
    newSNAP->studentId = studentId;
    newSNAP->name = strdup(name);
    newSNAP->address = strdup(address);
    newSNAP->phone = phone;

    char *key = createKeyForSNAP(studentId);
    insert(snapTable, key, newSNAP);
    free(key);
}

void insertCSG(char *course, int studentId, char *grade) {
    CSG *newCSG = malloc(sizeof(CSG));
    newCSG->course = strdup(course);
    newCSG->studentId = studentId;
    newCSG->grade = strdup(grade);

    char *key = createKeyForCSG(course, studentId);
    insert(csgTable, key, newCSG);
    free(key);
}

void insertCP(char *course, char *prerequisite) {
    CP *newCP = malloc(sizeof(CP));
    newCP->course = strdup(course);
    newCP->prerequisite = strdup(prerequisite);

    char *key = createKeyForCP(course);
    insert(cpTable, key, newCP);
    free(key);
}

void insertCDH(char *course, char *day, int hour) {
    CDH *newCDH = malloc(sizeof(CDH));
    newCDH->course = strdup(course);
    newCDH->day = strdup(day);
    newCDH->hour = hour;

    char *key = createKeyForCDH(course, day, hour);
    insert(cdhTable, key, newCDH);
    free(key);
}

void insertCR(char *course, char *room) {
    CR *newCR = malloc(sizeof(CR));
    newCR->course = strdup(course);
    newCR->room = strdup(room);

    char *key = createKeyForCR(course);
    insert(crTable, key, newCR);
    free(key);
}

bool isWildcardOrMatch(const char *param, const char *value) {
    return (strcmp(param, "*") == 0 || strcmp(param, value) == 0);
}

bool isIntWildcardOrMatch(const char *param, int value) {
    if (strcmp(param, "*") == 0) return true;
    int paramValue = atoi(param);
    return (paramValue == value);
}

void deleteSNAP(char *studentId, char *name, char *address, char *phone) {
    for (int i = 0; i < snapTable->size; i++) {
        Entry *entry = snapTable->table[i];
        Entry *prev = NULL;
        while (entry != NULL) {
            SNAP *snap = (SNAP *)entry->value;
            if (isIntWildcardOrMatch(studentId, snap->studentId) &&
                isWildcardOrMatch(name, snap->name) &&
                isWildcardOrMatch(address, snap->address) &&
                isIntWildcardOrMatch(phone, snap->phone)) {
                if (prev == NULL) {
                    snapTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(snap->name);
                free(snap->address);
                free(snap);
                free(entry);
                entry = (prev == NULL) ? snapTable->table[i] : prev->next;
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}

void deleteCSG(char *course, char *studentId, char *grade) {
    for (int i = 0; i < csgTable->size; i++) {
        Entry *entry = csgTable->table[i];
        Entry *prev = NULL;
        while (entry != NULL) {
            CSG *csg = (CSG *)entry->value;
            if (isWildcardOrMatch(course, csg->course) &&
                isIntWildcardOrMatch(studentId, csg->studentId) &&
                isWildcardOrMatch(grade, csg->grade)) {
                if (prev == NULL) {
                    csgTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(csg->course);
                free(csg->grade);
                free(csg);
                free(entry);
                entry = (prev == NULL) ? csgTable->table[i] : prev->next;
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}

void deleteCP(char *course, char *prerequisite) {
    for (int i = 0; i < cpTable->size; i++) {
        Entry *entry = cpTable->table[i];
        Entry *prev = NULL;
        while (entry != NULL) {
            CP *cp = (CP *)entry->value;
            if (isWildcardOrMatch(course, cp->course) &&
                isWildcardOrMatch(prerequisite, cp->prerequisite)) {
                if (prev == NULL) {
                    cpTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(cp->course);
                free(cp->prerequisite);
                free(cp);
                free(entry);
                entry = (prev == NULL) ? cpTable->table[i] : prev->next;
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}

void deleteCDH(char *course, char *day, char *hour) {
    for (int i = 0; i < cdhTable->size; i++) {
        Entry *entry = cdhTable->table[i];
        Entry *prev = NULL;
        while (entry != NULL) {
            CDH *cdh = (CDH *)entry->value;
            if (isWildcardOrMatch(course, cdh->course) &&
                isWildcardOrMatch(day, cdh->day) &&
                isIntWildcardOrMatch(hour, cdh->hour)) {
                if (prev == NULL) {
                    cdhTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(cdh->course);
                free(cdh->day);
                free(cdh);
                free(entry);
                entry = (prev == NULL) ? cdhTable->table[i] : prev->next;
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}

void deleteCR(char *course, char *room) {
    for (int i = 0; i < crTable->size; i++) {
        Entry *entry = crTable->table[i];
        Entry *prev = NULL;
        while (entry != NULL) {
            CR *cr = (CR *)entry->value;
            if (isWildcardOrMatch(course, cr->course) &&
                isWildcardOrMatch(room, cr->room)) {
                if (prev == NULL) {
                    crTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(cr->course);
                free(cr->room);
                free(cr);
                free(entry);
                entry = (prev == NULL) ? crTable->table[i] : prev->next;
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}

void lookupSNAP(char *studentId, char *name, char *address, char *phone) {
    int found = 0;
    for (int i = 0; i < snapTable->size; i++) {
        Entry *entry = snapTable->table[i];
        while (entry != NULL) {
            SNAP *snap = (SNAP *)entry->value;
            if (isIntWildcardOrMatch(studentId, snap->studentId) &&
                isWildcardOrMatch(name, snap->name) &&
                isWildcardOrMatch(address, snap->address) &&
                isIntWildcardOrMatch(phone, snap->phone)) {
                printf("SNAP: Student ID: %d, Name: %s, Address: %s, Phone: %d\n", snap->studentId, snap->name, snap->address, snap->phone);
                found = 1;
            }
            entry = entry->next;
        }
    }
    if (!found) {
        printf("No result found in SNAP.\n");
    }
}


void lookupCSG(char *course, char *studentId, char *grade) {
    int found = 0;
    for (int i = 0; i < csgTable->size; i++) {
        Entry *entry = csgTable->table[i];
        while (entry != NULL) {
            CSG *csg = (CSG *)entry->value;
            if (isWildcardOrMatch(course, csg->course) &&
                isIntWildcardOrMatch(studentId, csg->studentId) &&
                isWildcardOrMatch(grade, csg->grade)) {
                printf("CSG: Course: %s, Student ID: %d, Grade: %s\n", csg->course, csg->studentId, csg->grade);
                found = 1;
            }
            entry = entry->next;
        }
    }
    if (!found) {
        printf("No result found in CSG.\n");
    }
}


void lookupCP(char *course, char *prerequisite) {
    int found = 0;
    for (int i = 0; i < cpTable->size; i++) {
        Entry *entry = cpTable->table[i];
        while (entry != NULL) {
            CP *cp = (CP *)entry->value;
            if (isWildcardOrMatch(course, cp->course) &&
                isWildcardOrMatch(prerequisite, cp->prerequisite)) {
                printf("CP: Course: %s, Prerequisite: %s\n", cp->course, cp->prerequisite);
                found = 1;
            }
            entry = entry->next;
        }
    }
    if (!found) {
        printf("No result found in CP.\n");
    }
}


void lookupCDH(char *course, char *day, char *hour) {
    int found = 0;
    for (int i = 0; i < cdhTable->size; i++) {
        Entry *entry = cdhTable->table[i];
        while (entry != NULL) {
            CDH *cdh = (CDH *)entry->value;
            if (isWildcardOrMatch(course, cdh->course) &&
                isWildcardOrMatch(day, cdh->day) &&
                isIntWildcardOrMatch(hour, cdh->hour)) {
                printf("CDH: Course: %s, Day: %s, Hour: %d\n", cdh->course, cdh->day, cdh->hour);
                found = 1;
            }
            entry = entry->next;
        }
    }
    if (!found) {
        printf("No result found in CDH.\n");
    }
}


void lookupCR(char *course, char *room) {
    for (int i = 0; i < crTable->size; i++) {
        Entry *entry = crTable->table[i];
        while (entry != NULL) {
            CR *cr = (CR *)entry->value;
            if (isWildcardOrMatch(course, cr->course) &&
                isWildcardOrMatch(room, cr->room)) {
                printf("CR: Course: %s, Room: %s\n", cr->course, cr->room);
            }
            entry = entry->next;
        }
    }
}


void printSNAPTable(void) {
    printf("SNAP Table:\n");
    for (int i = 0; i < snapTable->size; i++) {
        Entry *entry = snapTable->table[i];
        while (entry != NULL) {
            SNAP *snap = (SNAP *)entry->value;
            printf("Student ID: %d, Name: %s, Address: %s, Phone: %d\n", snap->studentId, snap->name, snap->address, snap->phone);
            entry = entry->next;
        }
    }
}

void printCSGTable(void) {
    printf("CSG Table:\n");
    for (int i = 0; i < csgTable->size; i++) {
        Entry *entry = csgTable->table[i];
        while (entry != NULL) {
            CSG *csg = (CSG *)entry->value;
            printf("Course: %s, Student ID: %d, Grade: %s\n", csg->course, csg->studentId, csg->grade);
            entry = entry->next;
        }
    }
}

void printCPTable(void) {
    printf("CP Table:\n");
    for (int i = 0; i < cpTable->size; i++) {
        Entry *entry = cpTable->table[i];
        while (entry != NULL) {
            CP *cp = (CP *)entry->value;
            printf("Course: %s, Prerequisite: %s\n", cp->course, cp->prerequisite);
            entry = entry->next;
        }
    }
}

void printCDHTable(void) {
    printf("CDH Table:\n");
    for (int i = 0; i < cdhTable->size; i++) {
        Entry *entry = cdhTable->table[i];
        while (entry != NULL) {
            CDH *cdh = (CDH *)entry->value;
            printf("Course: %s, Day: %s, Hour: %d\n", cdh->course, cdh->day, cdh->hour);
            entry = entry->next;
        }
    }
}

void printCRTable(void) {
    printf("CR Table:\n");
    for (int i = 0; i < crTable->size; i++) {
        Entry *entry = crTable->table[i];
        while (entry != NULL) {
            CR *cr = (CR *)entry->value;
            printf("Course: %s, Room: %s\n", cr->course, cr->room);
            entry = entry->next;
        }
    }
}

void findGradeForStudentInCourse(char *studentName, char *courseName) {
    int found = 0;
    for (int i = 0; i < snapTable->size; i++) {
        Entry *entry = snapTable->table[i];
        while (entry != NULL) {
            SNAP *snapData = (SNAP *)entry->value;
            if (strcmp(snapData->name, studentName) == 0) {
                // Found the student, now look up their grade in CSG
                char key[100];
                sprintf(key, "%s_%d", courseName, snapData->studentId);
                CSG *csgData = (CSG *)lookup(csgTable, key);
                if (csgData != NULL) {
                    printf("Grade of %s in %s is %s\n", studentName, courseName, csgData->grade);
                    found = 1;
                }
            }
            entry = entry->next;
        }
    }
    if (!found) {
        printf("No grade found for %s in %s\n", studentName, courseName);
    }
}

void findStudentLocation(char *studentName, int hour, char *day) {
    int found = 0;
    for (int i = 0; i < snapTable->size; i++) {
        Entry *entry = snapTable->table[i];
        while (entry != NULL) {
            SNAP *snapData = (SNAP *)entry->value;
            if (strcmp(snapData->name, studentName) == 0) {
                // Found the student, now look up their courses in CSG
                for (int j = 0; j < csgTable->size; j++) {
                    Entry *csgEntry = csgTable->table[j];
                    while (csgEntry != NULL) {
                        CSG *csgData = (CSG *)csgEntry->value;
                        if (csgData->studentId == snapData->studentId) {
                            // Found a course, now look up the day and hour in CDH
                            char cdhKey[100];
                            sprintf(cdhKey, "%s_%s_%d", csgData->course, day, hour);
                            CDH *cdhData = (CDH *)lookup(cdhTable, cdhKey);
                            if (cdhData != NULL) {
                                // Found the day and hour, now find the room in CR
                                CR *crData = (CR *)lookup(crTable, csgData->course);
                                if (crData != NULL) {
                                    printf("%s is in room %s at %d on %s\n", studentName, crData->room, hour, day);
                                    found = 1;
                                }
                            }
                        }
                        csgEntry = csgEntry->next;
                    }
                }
            }
            entry = entry->next;
        }
    }
    if (!found) {
        printf("No location found for %s at %d on %s\n", studentName, hour, day);
    }
}


void selectionSNAPByName(char *name, SelectedSNAP result[], int *resultSize) {
    int maxResultSize = 100;  // Assuming a maximum of 100 results for simplicity
    *resultSize = 0;

    //printf("Selection: σName=“%s”(SNAP)\n", name);
    for (int i = 0; i < snapTable->size; i++) {
        Entry *entry = snapTable->table[i];
        while (entry != NULL && *resultSize < maxResultSize) {
            SNAP *snap = (SNAP *)entry->value;
            if (strcmp(snap->name, name) == 0) {
                SelectedSNAP selectedEntry;
                selectedEntry.studentId = snap->studentId;
                strcpy(selectedEntry.name, snap->name);
                strcpy(selectedEntry.address, snap->address);
                selectedEntry.phone = snap->phone;

                result[*resultSize] = selectedEntry;
                (*resultSize)++;
            }
            entry = entry->next;
        }
    }
}

void projectionCSGToCourse(ProjectedCourse result[], int *resultSize) {
    int maxResultSize = 100;  // Assuming a maximum of 100 results for simplicity
    *resultSize = 0;

    //printf("Projection: πCourse(CSG)\n");
    for (int i = 0; i < csgTable->size; i++) {
        Entry *entry = csgTable->table[i];
        while (entry != NULL && *resultSize < maxResultSize) {
            CSG *csg = (CSG *)entry->value;
            ProjectedCourse projectedEntry;
            projectedEntry.course = strdup(csg->course);

            result[*resultSize] = projectedEntry;
            (*resultSize)++;
            entry = entry->next;
        }
    }
}


void joinSNAPAndCSG(SNAP_CSG_Join result[], int *resultSize) {
    int maxResultSize = 100;  // Assuming a maximum of 100 results for simplicity
    *resultSize = 0;

    //printf("Join: SNAP ⨝ CSG\n");
    for (int i = 0; i < snapTable->size; i++) {
        Entry *snapEntry = snapTable->table[i];
        while (snapEntry != NULL) {
            SNAP *snap = (SNAP *)snapEntry->value;
            for (int j = 0; j < csgTable->size; j++) {
                Entry *csgEntry = csgTable->table[j];
                while (csgEntry != NULL && *resultSize < maxResultSize) {
                    CSG *csg = (CSG *)csgEntry->value;
                    if (snap->studentId == csg->studentId) {
                        SNAP_CSG_Join joinEntry;
                        joinEntry.studentId = snap->studentId;
                        joinEntry.name = strdup(snap->name);
                        joinEntry.address = strdup(snap->address);
                        joinEntry.phone = snap->phone;
                        joinEntry.course = strdup(csg->course);
                        joinEntry.grade = strdup(csg->grade);

                        result[*resultSize] = joinEntry;
                        (*resultSize)++;
                    }
                    csgEntry = csgEntry->next;
                }
            }
            snapEntry = snapEntry->next;
        }
    }
}

void projectionCSGonFinal(SNAP_CSG_Join joinedEntries[], int joinedSize, FinalResult finalResults[], int *finalResultSize) {
    *finalResultSize = 0;
    //printf("Projection: πStudentID,Course,Grade((σName=“O. Gonzalez”(SNAP ▷◁ CSG))\n");

    for (int i = 0; i < joinedSize; i++) {
        finalResults[*finalResultSize].studentId = joinedEntries[i].studentId;
        finalResults[*finalResultSize].course = strdup(joinedEntries[i].course);
        finalResults[*finalResultSize].grade = strdup(joinedEntries[i].grade);
        (*finalResultSize)++;
    }
}


void findGradesForStudent(void) {
    // Step 1: Join SNAP and CSG
    printf("Join: SNAP ⨝ CSG\n");
    SNAP_CSG_Join joinedEntries[100];
    int joinedSize = 0;
    joinSNAPAndCSG(joinedEntries, &joinedSize);

    // Step 2: Select relevant SNAP entries for "O. Gonzalez"
    printf("Selection: σName=“O. Gonzales”(SNAP ⨝ CSG)\n");
    SelectedSNAP selectedSNAPEntries[100];
    int selectedSNAPSize = 0;
    selectionSNAPByName("O. Gonzalez", selectedSNAPEntries, &selectedSNAPSize);

    // Step 3: Project StudentId, Course, and Grade from joined entries
    printf("Projection: πStudentID,Course,Grade((σName=“O. Gonzalez”(SNAP ▷◁ CSG))\n");
    FinalResult finalResults[100];
    int finalResultSize = 0;
    projectionCSGonFinal(joinedEntries, joinedSize, finalResults, &finalResultSize);

    // Display the results
    printf("\nResults after all 3 operations:\n");
    for (int i = 0; i < finalResultSize; i++) {
        for (int j = 0; j < selectedSNAPSize; j++) {
            if (finalResults[i].studentId == selectedSNAPEntries[j].studentId) {
                printf("Student ID: %d, Course: %s, Grade: %s\n",
                       finalResults[i].studentId, finalResults[i].course, finalResults[i].grade);
            }
        }
    }

    // Free dynamically allocated memory
    for (int i = 0; i < finalResultSize; i++) {
        free(finalResults[i].course);
        free(finalResults[i].grade);
    }
    for (int i = 0; i < joinedSize; i++) {
        free(joinedEntries[i].name);
        free(joinedEntries[i].address);
        free(joinedEntries[i].course);
        free(joinedEntries[i].grade);
    }
}

void createAppendixA(void){
    // Initialize the database
    initializeDatabase();

    // Insert data into SNAP table
    insertSNAP(66252, "L. Adams", "55 Pear Ave.", 4559284);
    insertSNAP(1376, "R. Johnson", "88 Apple Dr.", 7175542);
    insertSNAP(39391, "O. Gonzalez", "62 Durian Blvd.", 6876203);
    insertSNAP(74533, "C. Johnson", "5 Raisin Ln.", 9924616);
    insertSNAP(58429, "O. Gonzalez", "78 Rhubarb Ave.", 1718839);
    insertSNAP(99730, "R. Johnson", "56 Kiwi Blvd.", 9039855);

    // Insert data into CSG table
    insertCSG("CSC171", 66252, "A");
    insertCSG("CSC171", 58429, "B");
    insertCSG("MATH150", 39391, "A");
    insertCSG("DSCC201", 66252, "C");
    insertCSG("DSCC201", 1376, "B+");
    insertCSG("CSC172", 99730, "A");
    insertCSG("MATH150", 58429, "C+");
    insertCSG("CSC173", 74533, "B+");
    insertCSG("CSC173", 99730, "A");
    insertCSG("DSCC201", 99730, "C");

    // Insert data into CP table
    insertCP("CSC172", "CSC171");
    insertCP("CSC172", "MATH150");
    insertCP("CSC173", "CSC172");
    insertCP("CSC252", "CSC172");
    insertCP("CSC254", "CSC252");
    insertCP("DSCC201", "CSC171");
    insertCP("DSCC202", "DSCC201");
    insertCP("DSCC265", "CSC262");
    insertCP("DSCC265", "CSC171");

    // Insert data into CDH table
    insertCDH("CSC171", "M", 1400);
    insertCDH("CSC171", "W", 1400);
    insertCDH("CSC172", "M", 1525);
    insertCDH("CSC172", "W", 1640);
    insertCDH("CSC173", "M", 1400);
    insertCDH("CSC173", "W", 1400);
    insertCDH("CSC252", "M", 1230);
    insertCDH("CSC252", "W", 1230);
    insertCDH("DSCC201", "T", 900);
    insertCDH("DSCC201", "R", 900);
    insertCDH("DSCC202", "T", 1650);
    insertCDH("DSCC202", "R", 1650);
    insertCDH("DSCC265", "T", 1400);
    insertCDH("DSCC265", "R", 1400);

    // Insert data into CR table
    insertCR("CSC171", "Hutchison Hall 141");
    insertCR("CSC172", "Hutchison Hall 141");
    insertCR("CSC173", "Wegmans 1400");
    insertCR("CSC252", "Wegmans 1400");
    insertCR("CSC254", "Wegmans 1400");
    insertCR("DSCC201", "Bausch & Lomb 109");
    insertCR("DSCC202", "Dewey 2162");
    insertCR("DSCC265", "Wegmans 1400");
    insertCR("MATH150", "Harkness 115");
}

void freeDatabase(void) {
    freeHashTable(snapTable);
    freeHashTable(csgTable);
    freeHashTable(cpTable);
    freeHashTable(cdhTable);
    freeHashTable(crTable);
}
