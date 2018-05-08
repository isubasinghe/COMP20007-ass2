/* ... */

#include <stdio.h>

#include "spell.h"
#include "lshtein.h"
#include "gedit.h"

// see Assignment Task 1: Computing edit distance
void print_edit_distance(char *word1, char *word2) {
	printf("%d\n", ldist(word1, word2));
}

// see Assignment Task 2: Enumerating all possible edits
void print_all_edits(char *word) {
	warray_t w = gen_edit_one(word);

	for(int i=0; i < w.written; i++) {
		printf("%s\n", w.data[i]);
	}

	free_warray(&w);
}

// see Assignment Task 3: Spell checking
void print_checked(List *dictionary, List *document) {
	printf("not yet implemented: put code for task 3 here\n");
}

// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {
	printf("not yet implemented: put code for task 4 here\n");
}
