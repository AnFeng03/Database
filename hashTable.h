
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct Entry {
    char *key;
    void *value;
    struct Entry *next;
} Entry;

typedef struct HashTable {
    int size;
    Entry **table;
} HashTable;

HashTable *createHashTable(int size);
unsigned int hash(HashTable *hashtable, char *key);
void insert(HashTable *hashtable, char *key, void *value);
void *lookup(HashTable *hashtable, char *key);
bool delete(HashTable *hashtable, char *key);
void freeHashTable(HashTable *hashtable);

#endif //HASHTABLE_H
