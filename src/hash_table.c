#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t hash(const char *key)
{
        size_t hash_val = 5381;
        int c;
        while ((c = *key++))
                hash_val = ((hash_val << 5) + hash_val) + c;
        return hash_val % HASH_TABLE_SIZE;
}

struct hash_table *hash_table_create()
{
        struct hash_table *ht = malloc(sizeof(struct hash_table));
        for (int i = 0; i < HASH_TABLE_SIZE; i++)
                ht->table[i] = NULL;
        return ht;
}

struct hash_entry *hash_entry_create(const char *key, int value)
{
        struct hash_entry *new = malloc(sizeof(struct hash_entry));
        new->key = strdup(key);
        new->value = value;
        new->next = NULL;
        return new;
}

void hash_table_insert(struct hash_table *ht, const char *key, int value)
{
        size_t index = hash(key);
        struct hash_entry *new = hash_entry_create(key, value);

        if (ht->table[index] == NULL) {
                ht->table[index] = new;
                return;
        }
        struct hash_entry *current = ht->table[index];
        while (current->next != NULL) {
                if (strcmp(current->key, key) == 0) {
                        current->value = value;
                        free(new->key);
                        free(new);
                }
                current = current->next;
        }
        current->next = new;
}

int hash_table_contains(struct hash_table *ht, const char *key)
{
        size_t index = hash(key);
        struct hash_entry *current = ht->table[index];

        if (!current)
                return -1;

        while (current) {
                if (strcmp(current->key, key) == 0)
                        return index;
                current = current->next;
        }

        return -1;
}

void hash_table_delete(struct hash_table *ht, const char *key)
{
        size_t index = hash(key);
        struct hash_entry *current = ht->table[index];
        struct hash_entry *prev = NULL;

        while (current) {
                if (strcmp(current->key, key) == 0) {
                        if (!prev)
                                ht->table[index] = current->next;
                        else
                                prev->next = current->next;

                        free(current->key);
                        free(current);
                        return;
                }
                prev = current;
                current = current->next;
        }
}

void hash_table_print(struct hash_table *ht)
{
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
                if (!(ht->table[i]))
                        continue;

                printf("[%4.d]: ", i);
                struct hash_entry *current = ht->table[i];
                while (current) {
                        printf("(%s, %d) -> ", current->key, current->value);
                        current = current->next;
                }
                printf("NULL\n");
        }
}