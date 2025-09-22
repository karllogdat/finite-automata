#include "ast_dfa.h"
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

struct parser *parser_new(struct lexer *lx)
{
        struct parser *p = malloc(sizeof(p));
        p->tokens = lx->tokens;
        p->tok_count = lx->tok_count;
        p->pos = 0;
        p->dfa = malloc(sizeof(p->dfa));
        return p;
}