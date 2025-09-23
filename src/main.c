#include "ast_dfa.h"
#include "hash_table.h"
#include "lexer.h"
#include "parser.h"
#include "set.h"
#include <stdio.h>

int main(int argc, const char **argv)
{
        if (argc < 2) {
                fprintf(stderr, "Add DFA file to simulate as argument:\n");
                fprintf(stderr, "\t./main <file>\n");
                exit(EXIT_FAILURE);
        }

        struct lexer *lexer = lexer_new(argv[1]);
        // printf("File Contents:\n\n%s\n", lexer->start_char);
        lexer_tokenize(lexer);

        struct parser *p = parser_new(lexer);
        struct ast_dfa *ad = parse(p);
        for (int i = 0; i < p->tok_count; i++)
                token_print(&p->tokens[i]);

        ast_dfa_print(ad);
}
