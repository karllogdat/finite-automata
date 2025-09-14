#include "hash_table.h"
#include "lexer.h"
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

	printf("does this work\n");

	struct set *s = set_create();
	if (s)
		printf("set created\n");

	set_insert(s, "q0");
	set_insert(s, "q1");
	set_insert(s, "q2");
	set_insert(s, "q4");
	set_insert(s, "q4");

	hash_table_print(s->elements);

	set_remove(s, "q1");

	hash_table_print(s->elements);
}