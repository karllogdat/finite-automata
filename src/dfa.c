#include "ast_dfa.h"
#include "dfa.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dfa *dfa_from_ast(struct ast_dfa *ast)
{
        struct dfa *dfa = malloc(sizeof(struct dfa));
        if (!dfa) {
                fprintf(stderr, "could not allocate memory for dfa\n");
                exit(EXIT_FAILURE);
        }
        dfa->states = set_create();
        dfa->alphabet = set_create();

        for (int i = 0; i < ast->transition_count; i++) {
                struct ast_transition *t = ast->transitions[i];
                char *from = strdup(t->from);
                char *to = strdup(t->to);
                char *symb = strdup(t->symb);

                set_insert(dfa->states, from);
                set_insert(dfa->states, to);
                set_insert(dfa->alphabet, symb);
        }

        size_t cols = dfa->alphabet->size;
        size_t rows = dfa->states->size;
        dfa->transition_table = malloc(rows * sizeof(int *));
        if (!dfa->transition_table) {
                fprintf(
                    stderr,
                    "could not allocate memory for transition table rows\n");
                exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < rows; i++) {
                dfa->transition_table[i] = malloc(cols * sizeof(int));
                if (!dfa->transition_table[i]) {
                        fprintf(stderr,
                                "could not allocate memory for transition "
                                "table columns\n");
                        exit(EXIT_FAILURE);
                }
        }

        // iterating over the transitions again to build the transition table
        // (state and alphabet size is unknown on first iteration)
        // inefficient, too lazy to rewrite
        for (int i = 0; i < ast->transition_count; i++) {
                struct ast_transition *t = ast->transitions[i];
                int from = hash_table_contains(dfa->states, t->from);
                if (from == -1) {
                        fprintf(stderr,
                                "transition.from '%s' is not a state\n",
                                t->from);
                        exit(EXIT_FAILURE);
                }

                int to = hash_table_contains(dfa->states, t->to);
                if (to == -1) {
                        fprintf(stderr,
                                "transition.to '%s' is not a state\n",
                                t->to);
                        exit(EXIT_FAILURE);
                }

                int symb = hash_table_contains(dfa->alphabet, t->symb);
                if (symb == -1) {
                        fprintf(stderr,
                                "transition.symb '%s' is not a symbol\n",
                                t->symb);
                        exit(EXIT_FAILURE);
                }

                dfa->transition_table[from][symb] = to;
        }

        dfa->start_state = strdup(ast->start);

        dfa->accept_states = set_create();
        for (int i = 0; i < ast->accept_state_count; i++) {
                char *a = strdup(ast->accept_states[i]);
                set_insert(dfa->accept_states, a);
        }

        return dfa;
}