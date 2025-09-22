#ifndef AST_DFA_H
#define AST_DFA_H

#include <stdlib.h>

struct ast_transition {
        char *from;
        char *to;
        char *symb;
};

struct adt_dfa {
        struct ast_transition **transitions;
        size_t transition_count;

        char *start;
        char **accept_states;
        size_t accept_state_count;
};

#endif