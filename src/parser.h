#ifndef PARSER_H
#define PARSER_H

#include "ast_dfa.h"
#include "lexer.h"

struct parser {
        struct token *tokens;
        size_t tok_count;
        size_t pos;

        struct ast_dfa *dfa;
};

struct parser *parser_new(struct lexer *lx);
struct ast_dfa *parse(struct parser *p);

struct ast_transition *parse_transition(struct parser *p);
void parse_transition_list(struct parser *p);
void parse_start_state(struct parser *p);
void parse_accept_states(struct parser *p);

#endif
