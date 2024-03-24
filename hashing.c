#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
struct Node {
    int data;
    struct Node *next;
};

// Function to search for a key in the hash table
int searchKey(struct Node *hashTable[], int size, int key) {
    int index = key % size;

    struct Node *temp = hashTable[index];
    while (temp != NULL) {
        if (temp->data == key) {
            return index; // Key found at index
        }
        temp = temp->next;
    }
    return -1; // Key not found
}

int main() {
    int size, i;

    printf("Enter the size of the Hash Table: ");
    scanf("%d", &size);

    // Creating an array of linked lists
    struct Node *hashTable[size];
    for (i = 0; i < size; i++) {
        hashTable[i] = NULL; // Initializing all elements of the array to NULL
    }

    int numKeys;
    printf("Enter the number of keys to insert: ");
    scanf("%d", &numKeys);

    int keys[numKeys];
    printf("Enter the keys:\n");
    for (i = 0; i < numKeys; i++) {
        scanf("%d", &keys[i]);
    }

    for (i = 0; i < numKeys; i++) {
        int index = keys[i] % size;

        // Creating a new node for the current key
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed!");
            return -1;
        }
        newNode->data = keys[i];
        newNode->next = NULL;

        // Inserting the node in the linked list at the calculated index
        if (hashTable[index] == NULL) {
            // If no element exists at this index, directly add the node
            hashTable[index] = newNode;
        } else {
            // If elements exist, traverse the list and append the new node
            struct Node *temp = hashTable[index];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
printf("\nThe indexes of the values in the Hash Table with chaining:\n");
for (i = 0; i < size; i++) {
    printf("Index %d: ", i);
    struct Node *temp = hashTable[i];
    if (temp == NULL) {
        printf("\n");
        continue;
    }
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
    int Key;
    printf("\nEnter the key to search: ");
    scanf("%d", &Key);
    int result = searchKey(hashTable, size, Key);
    if (result != -1) {
        printf("Key %d found at index %d\n", Key, result);
    } else {
        printf("Key %d not found in the hash table\n", Key);
    }
    // Free allocated memory for nodes
    for (i = 0; i < size; i++) {
        struct Node *temp = hashTable[i];
        while (temp != NULL) {
            struct Node *prev = temp;
            temp = temp->next;
            free(prev);
        }
    }

    return 0;
}