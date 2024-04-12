#include <stdio.h>
#include <stdlib.h>

struct RecordType {
    int id;
    char name;
    int order; 
};

struct HashEntry {
    struct RecordType data;
    struct HashEntry* next;
};

struct HashTable {
    struct HashEntry** table;
    int size;
};

int hash(int x, int tableSize) {
    int hashValue = x;
    hashValue = hashValue ^ (hashValue >> 4);
    hashValue = hashValue ^ (hashValue >> 8);
    hashValue = hashValue % tableSize;
    return hashValue;
}

struct HashTable* createHashTable(int size) {
    struct HashTable* hashTable = (struct HashTable*) malloc(sizeof(struct HashTable));
    hashTable->size = size;
    hashTable->table = (struct HashEntry**) malloc(sizeof(struct HashEntry*) * size);
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insert(struct HashTable* hashTable, struct RecordType record) {
    int index = hash(record.id, hashTable->size);
    struct HashEntry* newEntry = (struct HashEntry*) malloc(sizeof(struct HashEntry));
    newEntry->data = record;
    newEntry->next = hashTable->table[index];
    hashTable->table[index] = newEntry;
}

void displayHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        struct HashEntry* entry = hashTable->table[i];
        if (entry != NULL) {
            printf("Index %d ->", i);
            while (entry != NULL) {
                printf(" %d %c %d ->", entry->data.id, entry->data.name, entry->data.order);
                entry = entry->next;
            }
            printf(" NULL\n");
        }
    }
}

int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i) {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }
        fclose(inFile);
    }
    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz) {
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

int main(void) {
    struct RecordType *pRecords;
    int recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);
    
    struct HashTable *hashTable = createHashTable(31);
    for (int i = 0; i < recordSz; i++) {
        insert(hashTable, pRecords[i]);
    }
    
    displayHashTable(hashTable);
    return 0;
}