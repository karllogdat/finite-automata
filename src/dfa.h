#ifndef DFA_H
#define DFA_H

#include <stdlib.h>
#include "ast_dfa.h"
#include "set.h"

/*
 * dfa owns its string copies of states, alphabet, start, and accept_states
 * please free properly (write a proper destructor for struct set)
 */
struct dfa {
        struct set *states;
        struct set *alphabet;
        // use state and alphabet set .size member
        // transition_table[state_index][alphabet_index] = state
        int **transition_table;
        char *start_state;
        struct set *accept_states;
};

struct dfa *dfa_from_ast(struct ast_dfa ast);

#endif