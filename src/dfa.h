#ifndef DFA_H
#define DFA_H

#include <stdlib.h>
#include "set.h"

struct transition {
        char *from;
        char *to;
        char *symb;
};

struct dfa {
        struct transition *transitions;
        size_t transition_count;

        char *start_state;
        struct set accept_states;
};

#endif