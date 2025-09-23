#include "ast_dfa.h"
#include <stdlib.h>
#include <stdio.h>

void ast_dfa_print(struct ast_dfa *dfa)
{
        printf("Transitions\n:");
        for (size_t i = 0; i < dfa->transition_count; i++) {
                struct ast_transition *t = dfa->transitions[i];
                printf("\t%s -(%s)-> %s\n", t->from, t->symb, t->to);
        }

        printf("Start:\n\t%s\n", dfa->start);

        printf("Accept:\n\t");
        for (size_t i = 0; i < dfa->accept_state_count; i++) {
                printf("%s ", dfa->accept_states[i]);
        }
        printf("\n");
}