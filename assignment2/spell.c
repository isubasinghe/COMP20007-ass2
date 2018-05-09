/* ... */

#include <stdio.h>

#include "spell.h"
#include "lshtein.h"
#include "gedit.h"

#include "list.h"
#include "hashtbl.h"

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
	
	HashTable *htable = new_hash_table(dictionary->size);
	Node *curr = dictionary->head;

	while(curr != NULL) {
		//printf("%s\n", (char *)curr->data);
		hash_table_put(htable, (char *)curr->data, 1);
		curr= curr->next;
	}

	curr = document->head;

	while(curr != NULL) {
		if(!hash_table_has(htable, (char *)curr->data)) {
			printf("%s?\n", (char *)curr->data);
		}
		curr = curr->next; 
	}
}

// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {
	
}
