#ifndef SET_H
#define SET_H

#include "hash_table.h"

struct set {
        struct hash_table *elements;
};

/**
 * @brief Creates an empty set.
 *
 * @return Pointer to the newly created set.
 */
struct set *set_create();

/**
 * @brief Inserts an element to a set
 *
 * @param s Pointer to a set
 * @param e String to insert
 */
void set_insert(struct set *s, const char *e);

/**
 * @brief Removes an element from a set
 *
 * @param s Pointer to a set
 * @param e String to remove
 */
void set_remove(struct set *s, const char *e);

#endif