#ifndef DFA_H
#define DFA_H

#include "set.h"

struct dfa {
        struct set *states;
        struct set *alphabet;
        struct transition *trans_func;
        int trans_count;
        const char *start_state;
        struct set *accept_states;
};

struct transition {
        const char *state;
        const char *symb;
        const char *out;
};

struct dfa *dfa_create(const char *src);

void dfa_simulate(struct dfa *dfa);
const char *dfa_next_trans(const char *state, const char *symb);

#endif