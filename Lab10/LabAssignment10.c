#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26 

struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};


struct Trie {
    struct TrieNode *root;
};

struct TrieNode *createNode(void) {
    struct TrieNode *pNode = malloc(sizeof(struct TrieNode));
    if (pNode) {
        pNode->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}

struct Trie *createTrie() {
    struct Trie *pTrie = malloc(sizeof(struct Trie));
    if (pTrie) {
        pTrie->root = createNode();
    }
    return pTrie;
}

void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *pCrawl = pTrie->root;
    while (*word != '\0') {
        int index = *word - 'a';
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = createNode();
        }
        pCrawl = pCrawl->children[index];
        word++;
    }
    pCrawl->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct TrieNode *pCrawl = pTrie->root;
    while (*word != '\0') {
        int index = *word - 'a';
        if (!pCrawl->children[index]) {
            return 0;
        }
        pCrawl = pCrawl->children[index];
        word++;
    }
    return pCrawl->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (!pTrie) return NULL;

    void deallocateTrieNodes(struct TrieNode *node) {
        if (node) {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (node->children[i]) {
                    deallocateTrieNodes(node->children[i]);
                }
            }
            free(node);
        }
    }

    deallocateTrieNodes(pTrie->root);
    free(pTrie);
    return NULL;
}

int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    char buffer[128];
    int index = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        pInWords[index++] = strdup(buffer);
    }
    fclose(file);
    return index;
}

int main(void) {
    char *inWords[256];
    
    int numWords = readDictionary("dictionary.txt", inWords);
    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }

    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL) {
        printf("There is an error in this program\n");
    }

    for (int i = 0; i < numWords; i++) {
        free(inWords[i]);
    }

    return 0;
}