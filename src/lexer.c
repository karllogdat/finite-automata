#include "lexer.h"
#include <stdlib.h>

struct lexer *lexer_new(const char *src) 
{
        struct lexer *lexer = malloc(sizeof(struct lexer));
        if (!lexer)
                return NULL;

        FILE *fp = fopen(src, "rb");
        if (!fp) {
                fprintf(stderr, "cannot open file '%s'\n", src);
                goto free_lexer;
        }

        fseek(fp, 0, SEEK_END);
        size_t file_size = ftell(fp);
        rewind(fp);

        lexer->start_char = malloc(file_size + 1);
        if (lexer->start_char == NULL) {
                fprintf(stderr, "cannot allocate memory for file contents\n");
                goto close_fp;
        }

        size_t bytes_read = fread(lexer->start_char, 1, file_size, fp);
        if (bytes_read < file_size) {
                if (ferror(fp)) {
                        fprintf(stderr, "error while reading file\n");
                        goto free_buf;
                }
        }

        lexer->start_char[file_size] = '\0';
        lexer->cur_char = lexer->start_char;
        lexer->tokens = NULL;
        lexer->tok_count = 0;

        fclose(fp);

        return lexer;

free_buf:
        free(lexer->start_char);

close_fp:
        fclose(fp);

free_lexer:
        free(lexer);
        return NULL;
}