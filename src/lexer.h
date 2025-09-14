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

struct token token_new(enum tok_type type, char *value);
struct lexer *lexer_new(const char *src);
void lexer_insert_token(struct lexer *lexer, enum tok_type type, char *value);
void lexer_tokenize(struct lexer *lexer);
void lexer_free(struct lexer *lexer);

#endif