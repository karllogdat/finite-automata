#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct token token_new(enum tok_type type, const char *val)
{
        struct token tok;
        tok.type = type;

        if (val) {
                tok.value = strdup(val);
                if (!tok.value) {
                        fprintf(stderr,
                                "cannot allocate memory for token value\n");
                        exit(EXIT_FAILURE);
                }
        } else {
                tok.value = NULL;
        }

        return tok;
}

void token_print(struct token *tok)
{
        switch (tok->type) {
                case TOK_IDENT:
                        printf("TOK_IDENT(%s)", tok->value);
                        break;

                case TOK_MINUS:
                        printf("TOK_MINUS");
                        break;

                case TOK_GT:
                        printf("TOK_GT");
                        break;

                case TOK_COLON:
                        printf("TOK_COLON");
                        break;

                case TOK_WSPACE:
                        // reminder: can comment out if too much
                        // printf("TOK_WSPACE");
                        break;

                case TOK_NEWLINE:
                        printf("TOK_NEWLINE\n");
                        break;

                default:
                        printf("unkown token\n");
                        break;
        }
}

struct lexer *lexer_new(const char *src)
{
        struct lexer *lx = malloc(sizeof(struct lexer));
        if (!lx)
                return NULL;

        FILE *fp = fopen(src, "rb");
        if (!fp) {
                fprintf(stderr, "cannot open file '%s'\n", src);
                goto free_lexer;
        }

        fseek(fp, 0, SEEK_END);
        size_t file_size = ftell(fp);
        rewind(fp);

        lx->start_char = malloc(file_size + 1);
        if (lx->start_char == NULL) {
                fprintf(stderr, "cannot allocate memory for file contents\n");
                goto close_fp;
        }

        size_t bytes_read = fread(lx->start_char, 1, file_size, fp);
        if (bytes_read < file_size) {
                if (ferror(fp)) {
                        fprintf(stderr, "error while reading file\n");
                        goto free_buf;
                }
        }

        lx->start_char[file_size] = '\0';
        lx->cur_char = lx->start_char;
        lx->tokens = NULL;
        lx->tok_count = 0;

        fclose(fp);

        return lx;

free_buf:
        free(lx->start_char);

close_fp:
        fclose(fp);

free_lexer:
        free(lx);
        return NULL;
}

void lexer_insert_token(struct lexer *lx, enum tok_type type, const char *val)
{
        // reminder: free every token.val since token now owns a val copy
        struct token new = token_new(type, val);

        lx->tok_count++;
        lx->tokens = realloc(lx->tokens, sizeof(struct token) * lx->tok_count);
        if (!lx->tokens) {
                fprintf(stderr, "couldn't reallocate token list\n");
                exit(EXIT_FAILURE);
        }

        lx->tokens[lx->tok_count - 1] = new;
}

void lexer_tokenize(struct lexer *lx)
{
        while (*lx->cur_char != '\0') {
                char cur = *lx->cur_char;
                enum tok_type type;
                char *val = NULL;

                switch (cur) {
                        case ' ':
                        case '\t':
                                type = TOK_WSPACE;
                                val = " ";
                                break;

                        // intentional unbreaked case to handle windows
                        // `\r\n` quirk
                        case '\r':
                                if (lx->cur_char[1] == '\n') {
                                        lx->cur_char++;
                                }

                        case '\n':
                                type = TOK_NEWLINE;
                                val = "\\n";
                                break;

                        case ':':
                                type = TOK_COLON;
                                val = ":";
                                break;

                        case '-':
                                type = TOK_MINUS;
                                val = "-";
                                break;

                        case '>':
                                type = TOK_GT;
                                val = ">";
                                break;

                        default:
                                if (isalnum(cur)) {
                                        const char *start = lx->cur_char;
                                        while (isalnum(lx->cur_char[1])) {
                                                lx->cur_char++;
                                        }

                                        size_t len = lx->cur_char - start + 1;
                                        char *tmp = malloc(len + 1);
                                        if (!tmp) {
                                                fprintf(stderr,
                                                        "malloc failed\n");
                                                exit(EXIT_FAILURE);
                                        }

                                        strncpy(tmp, start, len);
                                        tmp[len] = '\0';

                                        type = TOK_IDENT;
                                        val = tmp;

                                        lexer_insert_token(lx, type, val);
                                        free(tmp);

                                        lx->cur_char++;
                                        continue;
                                } else {
                                        lx->cur_char++;
                                        continue;
                                }
                }

                lexer_insert_token(lx, type, val);
                lx->cur_char++;
        }
}

void lexer_print_tokens(struct lexer *lx)
{
        for (int i = 0; i < lx->tok_count; i++) {
                token_print(&lx->tokens[i]);
                printf(" ");
        }
}