#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

#define HASH_TABLE_SIZE 1000

struct hash_entry {
        char *key;
        int value;
        struct hash_entry *next;
};

struct hash_table {
        struct hash_entry *table[HASH_TABLE_SIZE];
};

/**
 * @brief Computes the hash of a string using djb2 hash function
 *
 * @param key String to compute
 * @return Unsigned integer hash of key
 */
size_t hash(const char *key);

/**
 * @brief Creates an empty hash table
 *
 * @return Pointer to the newly created hash table
 */
struct hash_table *hash_table_create();
/**
 * @brief Creates a hash table entry
 *
 * @param key A string
 * @param value Integer value associated with the key
 * @return A pointer to the hash entry
 */
struct hash_entry *hash_entry_create(const char *key, int value);

/**
 * @brief Inserts a key-value pair to a hash table
 *
 * @param ht Pointer to the hash table
 * @param key A string to insert
 * @param value An integer value to insert associated with the key
 */
void hash_table_insert(struct hash_table *ht, const char *key, int value);
/**
 * @brief Checks whether a key is in a hash table
 *
 * @param ht Pointer to a hash table
 * @param key A string
 * @return The index of `key` if in `ht`, -1 if it doesn't
 */
int hash_table_contains(struct hash_table *ht, const char *key);
void hash_table_delete(struct hash_table *ht, const char *key);
void hash_table_print(struct hash_table *ht);

#endif