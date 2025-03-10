#include <stdio.h>
#include <stdlib.h>

#define INITIAL_TABLE_SIZE 5


// Node structure for Chaining
struct Node {
    int key;
    struct Node* next;
};

// Hash Table structure
struct HashTable {
    int* table;
    struct Node** chain;
    int (*hashFunction)(int, int);
    int collisionMethod;
    int tableSize;
};

// Hash Functions
int midSquareHash(int key, int tableSize) {
    int squared = key * key;
    int mid = (squared / 10) % 100;
    return mid % tableSize;
}

int divisionHash(int key, int tableSize) {
    return key % tableSize;
}

int foldingHash(int key, int tableSize) {
    int sum = 0;
    while (key > 0) {
        sum += key % 100;
        key /= 100;
    }
    return sum % tableSize;
}

int digitExtractionHash(int key, int tableSize) {
    int extracted = (key / 10) % 10;
    return extracted % tableSize;
}

int rotationHash(int key, int tableSize) {
    int lastDigit = key % 10;
    key /= 10;
    int rotatedKey = lastDigit * 1000 + key;
    return rotatedKey % tableSize;
}


void insert(struct HashTable* ht, int key);
void rehash(struct HashTable* ht);

// Initialize Hash Table
void initTable(struct HashTable* ht, int size) {
    ht->tableSize = size;
    ht->table = (int*)malloc(size * sizeof(int));
    ht->chain = (struct Node**)malloc(size * sizeof(struct Node*));

    for (int i = 0; i < size; i++) {
        ht->table[i] = -1;
        ht->chain[i] = NULL;
    }
}

int isRehashing = 0;

// Insert function with collision handling
void insert(struct HashTable* ht, int key) {
    if (!isRehashing) { 
        int filledSlots = 0;
        for (int i = 0; i < ht->tableSize; i++) {
            if (ht->table[i] != -1) filledSlots++;
        }

        
        if (ht->collisionMethod == 3 && filledSlots >= ht->tableSize / 2) { 
            rehash(ht);
        }
    }

    int index = ht->hashFunction(key, ht->tableSize);

    if (ht->collisionMethod == 1) { 
        while (ht->table[index] != -1) {
            index = (index + 1) % ht->tableSize;
        }
        ht->table[index] = key;
    } 
    else if (ht->collisionMethod == 2) { 
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->key = key;
        newNode->next = ht->chain[index];
        ht->chain[index] = newNode;
    } 
    else if (ht->collisionMethod == 3) { 
        rehash(ht);
        insert(ht, key);
    }
}



// Rehashing (susaaah)
void rehash(struct HashTable* ht) {
    isRehashing = 1;  

    int oldSize = ht->tableSize;
    int newSize = oldSize * 2; 
    int* oldTable = ht->table;
    struct Node** oldChain = ht->chain;

   
    ht->table = (int*)malloc(newSize * sizeof(int));
    ht->chain = (struct Node**)malloc(newSize * sizeof(struct Node*));
    ht->tableSize = newSize;

    
    for (int i = 0; i < newSize; i++) {
        ht->table[i] = -1;
        ht->chain[i] = NULL;
    }

 
    if (ht->collisionMethod == 1) {  
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != -1) {
                int newIndex = ht->hashFunction(oldTable[i], newSize);
                
     
                while (ht->table[newIndex] != -1) {
                    newIndex = (newIndex + 1) % newSize;
                }
                
                ht->table[newIndex] = oldTable[i];  
            }
        }
    } else if (ht->collisionMethod == 2) { 
        for (int i = 0; i < oldSize; i++) {
            struct Node* temp = oldChain[i];
            while (temp) {
                int newIndex = ht->hashFunction(temp->key, newSize);
                
             
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->key = temp->key;
                newNode->next = ht->chain[newIndex];
                ht->chain[newIndex] = newNode;

        
                struct Node* toFree = temp;
                temp = temp->next;
                free(toFree);  
            }
        }
    }

  
    free(oldTable);
    free(oldChain);

    printf("Rehashing completed! New table size: %d\n", newSize);

    isRehashing = 0; 
}





// Display Hash Table
void display(struct HashTable* ht) {
    printf("\nHash Table:\n");
    for (int i = 0; i < ht->tableSize; i++) {
        printf("[%d]: ", i);
        if (ht->table[i] != -1) {
            printf("%d", ht->table[i]);
        }

        struct Node* temp = ht->chain[i];
        while (temp) {
            printf(" | %d", temp->key);  // Change "->" to " | "
            temp = temp->next;
        }
        printf("\n");
    }
}



int main() {
    struct HashTable ht;
    initTable(&ht, INITIAL_TABLE_SIZE);

    int hashChoice, collisionChoice, key;
    

    printf("Select Hash Function:\n");
    printf("1. Mid-Square\n2. Division\n3. Folding\n4. Digit Extraction\n5. Rotation\n");
    printf("Enter choice: ");
    scanf("%d", &hashChoice);

    if (hashChoice == 1) ht.hashFunction = midSquareHash;
    else if (hashChoice == 2) ht.hashFunction = divisionHash;
    else if (hashChoice == 3) ht.hashFunction = foldingHash;
    else if (hashChoice == 4) ht.hashFunction = digitExtractionHash;
    else if (hashChoice == 5) ht.hashFunction = rotationHash;
    else {
        printf("Invalid choice!\n");
        return 0;
    }


    printf("\nSelect Collision Handling Method:\n");
    printf("1. Linear Probing\n2. Chaining\n3. Rehashing\n");
    printf("Enter choice: ");
    scanf("%d", &collisionChoice);

    if (collisionChoice >= 1 && collisionChoice <= 3) {
        ht.collisionMethod = collisionChoice;
    } else {
        printf("Invalid choice!\n");
        return 0;
    }

  
    int option;
    do {
        printf("\nMenu:\n1. Insert Key\n2. Display Hash Table\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &option);

        if (option == 1) {
            printf("Enter key to insert: ");
            scanf("%d", &key);
            insert(&ht, key);
        } 
        else if (option == 2) {
            display(&ht);
        }
    } while (option != 3);

    printf("Exiting\n");
    return 0;
}

