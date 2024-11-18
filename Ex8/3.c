/*: An e-commerce platform uses hashing to store and retrieve product IDs for fast lookups. The system uses dynamic memory allocation to handle varying numbers of products, allowing quick access by product ID.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1024

typedef struct Product {
    char product_id[20];
    char product_info[100]; // Information about the product
    struct Product* next; // For collision handling
} Product;

typedef struct HashTable {
    Product** table;
} HashTable;

// Hash function to compute index
unsigned int hash(char* product_id) {
    unsigned long int hash_value = 0;
    while (*product_id) {
        hash_value = (hash_value << 5) + *product_id++;
    }
    return hash_value % TABLE_SIZE;
}

// Function to create a hash table
HashTable* create_table() {
    HashTable* ht = malloc(sizeof(HashTable));
    ht->table = malloc(sizeof(Product*) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Function to insert product into the hash table
void insert(HashTable* ht, char* product_id, char* product_info) {
    unsigned int index = hash(product_id);
    Product* new_product = malloc(sizeof(Product));
    strcpy(new_product->product_id, product_id);
    strcpy(new_product->product_info, product_info);
    new_product->next = ht->table[index];
    ht->table[index] = new_product;
}

// Function to retrieve product information by ID
char* retrieve(HashTable* ht, char* product_id) {
    unsigned int index = hash(product_id);
    Product* current = ht->table[index];
    while (current != NULL) {
        if (strcmp(current->product_id, product_id) == 0) {
            return current->product_info;
        }
        current = current->next;
    }
    return NULL; // Product not found
}

// Function to free the hash table
void free_table(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Product* current = ht->table[i];
        while (current != NULL) {
            Product* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// Main function to demonstrate usage
int main() {
    HashTable* ecommerce_system = create_table();

    insert(ecommerce_system, "prod123", "Laptop, Price: $999.99");
    insert(ecommerce_system, "prod456", "Smartphone, Price: $499.99");

    printf("Retrieving prod123: %s\n", retrieve(ecommerce_system, "prod123"));
    printf("Retrieving prod456: %s\n", retrieve(ecommerce_system, "prod456"));

    free_table(ecommerce_system);
    return 0;
}
