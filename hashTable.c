#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include <limits.h>

// Create a new hash table
HashTable *createHashTable(int size) {
    HashTable *newTable;

    if (size < 1) return NULL;

    // Allocate memory for the table structure
    if ((newTable = malloc(sizeof(HashTable))) == NULL) {
        return NULL;
    }

    // Allocate memory for the table itself
    if ((newTable->table = malloc(sizeof(Entry *) * size)) == NULL) {
        return NULL;
    }

    // Initialize the elements of the table
    for (int i = 0; i < size; i++) newTable->table[i] = NULL;

    newTable->size = size;

    return newTable;
}

// Hash function
unsigned int hash(HashTable *hashtable, char *key) {
    unsigned long int hashval = 0;
    int i = 0;

    // Convert string to an integer
    while (hashval < ULONG_MAX && i < strlen(key)) {
        hashval = hashval << 8;
        hashval += key[i];
        i++;
    }

    return hashval % hashtable->size;
}

// Insert a key-value pair into a hash table
void insert(HashTable *hashtable, char *key, void *value) {
    Entry *newEntry;
    unsigned int bin = 0;

    bin = hash(hashtable, key);

    // Create a new entry
    newEntry = malloc(sizeof(Entry));
    newEntry->key = strdup(key);
    newEntry->value = value;
    newEntry->next = hashtable->table[bin];
    hashtable->table[bin] = newEntry;
}

// Lookup a key in the hash table
void *lookup(HashTable *hashtable, char *key) {
    unsigned int bin = 0;
    Entry *entry;

    bin = hash(hashtable, key);

    // Step through the bin, looking for our value
    entry = hashtable->table[bin];
    while (entry != NULL && strcmp(key, entry->key) != 0) {
        entry = entry->next;
    }

    if (entry == NULL) return NULL;

    return entry->value;
}

// Delete a key-value pair from a hash table
bool delete(HashTable *hashtable, char *key) {
    unsigned int bin = 0;
    Entry *entry;
    Entry *previous = NULL;

    bin = hash(hashtable, key);

    entry = hashtable->table[bin];
    while (entry != NULL && strcmp(key, entry->key) != 0) {
        previous = entry;
        entry = entry->next;
    }

    if (entry == NULL) return false;

    if (previous == NULL) {
        hashtable->table[bin] = entry->next;
    } else {
        previous->next = entry->next;
    }

    free(entry->key);
    free(entry);

    return true;
}

// Free the hash table
void freeHashTable(HashTable *hashtable) {
    Entry *entry;
    Entry *next;

    for (int i = 0; i < hashtable->size; i++) {
        entry = hashtable->table[i];
        while (entry != NULL) {
            next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }

    free(hashtable->table);
    free(hashtable);
}
