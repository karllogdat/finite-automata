#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>

enum tok_type {
        TOK_IDENT,
        TOK_MINUS,
        TOK_GT,
        TOK_COLON,
        TOK_WSPACE,
        TOK_NEWLINE,
};

struct token {
        enum tok_type type;
        char *value;
};

struct lexer {
        char *start_char;
        char *cur_char;
        struct token *tokens;
        size_t tok_count;
};

struct token token_new(enum tok_type type, const char *val);
void token_print(struct token *tok);
struct lexer *lexer_new(const char *src);
void lexer_insert_token(struct lexer *lx, enum tok_type type, const char *val);
void lexer_tokenize(struct lexer *lx);
void lexer_print_tokens(struct lexer *lx);
void lexer_free(struct lexer *lexer);

#endif