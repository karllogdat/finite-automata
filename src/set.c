#include "hash_table.h"
#include "set.h"
#include <stdio.h>

struct set *set_create()
{
        struct set *s = malloc(sizeof(struct set));
        if (!s) {
                fprintf(stderr, "cannot create set\n");
                return NULL;
        }
        s->elements = hash_table_create();
        s->size = 0;
        return s;
}

void set_insert(struct set *s, const char *e)
{
        if (hash_table_contains(s->elements, e) != -1) {
                printf("set contains '%s'\n", e);
                return;
        }

        hash_table_insert(s->elements, e, s->size++);
        // printf("element '%s' inserted\n", e);
}

// todo: remove does not guarantee index uniqueness due to s.elements.val
void set_remove(struct set *s, const char *e)
{
        hash_table_delete(s->elements, e);
}