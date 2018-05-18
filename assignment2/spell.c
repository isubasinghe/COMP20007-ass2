/* ... */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "spell.h"
#include "lshtein.h"
#include "gedit.h"

#include "htable.h"
#include "list.h"
#include "warray.h"


// see Assignment Task 1: Computing edit distance
void print_edit_distance(char *word1, char *word2) {
	printf("%d\n", ldist(word1, word2));
}

// see Assignment Task 2: Enumerating all possible edits
void print_all_edits(char *word) {
	warray_t *leven1 = gen_edit_one(word);
	for(int i=0; i < leven1->written; i++) {
		printf("%s\n", leven1->data[i]);
	}
	free_warray(leven1);
}

// see Assignment Task 3: Spell checking
void print_checked(List *dictionary, List *document) {
	
	htable_t *htable = new_hash_table(dictionary->size);
	Node *curr = dictionary->head;

	while(curr != NULL) {
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
	
	free_hash_table(htable);
}

bool warray_in_hash(htable_t *table, warray_t *w) {
	bool in = 0;
	char *best = NULL;
	int best_index = table->nslots;
	for(int i=0; i < w->written; i++) {
		int error = 0;
		int value = hash_table_gets(table, w->data[i], &error);
		if(error != -1) {
			if(value < best_index) {
				best_index = value;
				best = w->data[i];
				in = 1;
			}
		}
	}
	if(best) {
		printf("%s\n", best);
	}
	return in;
}

bool string_in_hash(htable_t *table, char *s) {
	bool in = 0;
	return in;
}

// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {
	
	htable_t *htable = new_hash_table(dictionary->size);

	Node *curr = dictionary->head;
	int i = 1;
	while(curr != NULL) {
		hash_table_put(htable, (char *)curr->data, i);
		i++;
		curr = curr->next;
	}
	/*
	curr = document->head;

	while(curr != NULL) {
		warray_t *leven1 = gen_edit_one((char *)curr->data);
		warray_t *l = new_warray();
		for(int i=0; i < leven1->written; i++) {
			warray_t *leven2 = gen_edit_one(leven1->data[i]);
			for(int j=0; j < leven2->written; j++) {
				
			}
			free_warray(leven2);
		}
		free_warray(l);
		free_warray(leven1);
		curr = curr->next;
	}
	*/

	free_hash_table(htable);
}
