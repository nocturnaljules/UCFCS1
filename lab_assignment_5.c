#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head) {
    int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Parses the string in the linkedList into a C string.
char* toCString(node* head) {
    int len = length(head);
    char* str = (char*)malloc(len + 1); // +1 for the null terminator
    node* current = head;
    int i = 0;
    while (current != NULL) {
        str[i++] = current->letter;
        current = current->next;
    }
    str[i] = '\0'; // Null-terminate the string
    return str;
}

// Inserts character to the linkedlist.
void insertChar(node** pHead, char c) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->letter = c;
    newNode->next = NULL;

    if (*pHead == NULL) {
        *pHead = newNode;
    } else {
        node* current = *pHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Deletes all nodes in the linkedList.
void deleteList(node** pHead) {
    node* current = *pHead;
    node* nextNode = NULL;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *pHead = NULL;
}

int main(void) {
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt","r");
    fscanf(inFile, " %d\n", &numInputs);
    while (numInputs-- > 0) {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++) {
            fscanf(inFile," %c", &c);
            insertChar(&head, c);
        }
        str = toCString(head);
        printf("String is : %s\n", str);
        free(str);
        deleteList(&head);
        if (head != NULL) {
            printf("deleteList is not correct!\n");
            break;
        }
    }
    fclose(inFile);
    return 0;
}