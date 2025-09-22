#include "ast_dfa.h"
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

// helper functions

static struct token *advance(struct parser *p)
{
        if (p->pos >= p->tok_count) {
                fprintf(stderr, "expected token, found end of file\n");
                exit(EXIT_FAILURE);
        }

        return &p->tokens[p->pos++];
}

static struct token *current(struct parser *p)
{
        if (p->pos >= p->tok_count) {
                fprintf(stderr, "expected token, found end of file\n");
                exit(EXIT_FAILURE);
        }

        return &p->tokens[p->pos];
}

static struct token *peek(struct parser *p)
{
        if (p->pos + 1 >= p->tok_count) {
                return NULL;
        }
        return &p->tokens[p->pos + 1];
}

struct parser *parser_new(struct lexer *lx)
{
        struct parser *p = malloc(sizeof(*p));
        if (!p) {
                fprintf(stderr, "could not allocate mem for parser\n");
                exit(EXIT_FAILURE);
        }
        p->tokens = lx->tokens;
        p->tok_count = lx->tok_count;
        p->pos = 0;
        p->dfa = malloc(sizeof(*p->dfa));
        return p;
}

struct ast_dfa *parse(struct parser *p)
{
        parse_transition_list(p);
        parse_start_state(p);
        parse_accept_states(p);

        return p->dfa;
}

struct ast_transition *parse_transition(struct parser *p)
{
        struct ast_transition *t = malloc(sizeof(*t));

        struct token *curr = advance(p);

        if (curr->type != TOK_IDENT) {
                fprintf(stderr, "expected identifier as from state\n");
                exit(EXIT_FAILURE);
        }
        t->from = curr->value;

        curr = advance(p);
        if (curr->type != TOK_MINUS && peek(p)->type != TOK_GT) {
                fprintf(stderr, "expected '->'\n");
                exit(EXIT_FAILURE);
        }

        // consume TOK_GT
        advance(p);

        curr = advance(p);
        if (curr->type != TOK_IDENT) {
                fprintf(stderr, "expected identifier as to state\n");
                exit(EXIT_FAILURE);
        }
        t->to = curr->value;

        if (advance(p)->type != TOK_COLON) {
                fprintf(stderr, "expected ':'\n");
                exit(EXIT_FAILURE);
        }

        curr = advance(p);
        if (curr->type != TOK_IDENT) {
                fprintf(stderr, "expected identifier as symbol\n");
                exit(EXIT_FAILURE);
        }
        t->symb = curr->value;

        return t;
}

void parse_transition_list(struct parser *p)
{
        while (current(p)->type == TOK_IDENT && peek(p)->type == TOK_MINUS) {
                p->dfa->transitions =
                    realloc(p->dfa->transitions, p->dfa->transition_count + 1);
                p->dfa->transitions[p->dfa->transition_count++] =
                    parse_transition(p);
        }
}

void parse_start_state(struct parser *p)
{
        struct token *curr = advance(p);
        if (curr->type != TOK_IDENT) {
                fprintf(stderr, "expected identifier as start state\n");
                exit(EXIT_FAILURE);
        }
        curr = advance(p);
        if (curr->type != TOK_NEWLINE) {
                fprintf(stderr,
                        "expected newline after start state identifier '%s'\n",
                        curr->value);
                exit(EXIT_FAILURE);
        }

        p->dfa->start = curr->value;
}

void parse_accept_states(struct parser *p)
{
        while (peek(p)->type != TOK_NEWLINE) {
                struct token *curr = advance(p);
                if (curr->type != TOK_IDENT) {
                        fprintf(stderr,
                                "expected identifier as an accept state\n");
                        exit(EXIT_FAILURE);
                }
                p->dfa->accept_states = realloc(p->dfa->accept_states,
                                                p->dfa->accept_state_count + 1);
                p->dfa->accept_states[p->dfa->accept_state_count++] =
                    curr->value;
        }
}
