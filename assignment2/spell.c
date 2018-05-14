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
	for(int i=0; i < w->written; i++) {
		if(hash_table_has(table, w->data[i])) {
			printf("%s\n", w->data[i]);
			return 1;
		}
	}
	return in;
}

bool string_in_hash(htable_t *table, char *s) {
	bool in = 0;
	char *dist2 = NULL;
	char *dist3 = NULL;
	for(int i =0; i < table->nslots; i++) {
		if(table->slots[i].keys) {
			for(int j=0; j < table->slots[i].written; j++) {
				int dist = ldist(s, table->slots[i].keys[j]);
				if(dist == 1) {
					printf("%s\n", table->slots[i].keys[j]);
					return 1;
				}else if (dist == 2) {
					dist2 = table->slots[i].keys[j];
				}else if(dist == 3) {
					dist3 = table->slots[i].keys[j];
				}
			}
		}
	}
	if(dist2) {
		printf("%s\n", dist2);
		return 1;
	}
	if(dist3) {
		printf("%s\n", dist3);
		return 1;
	}
	printf("%s?\n", s);
	return in;
}

// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {
	
	htable_t *htable = new_hash_table(dictionary->size);

	Node *curr = dictionary->head;

	while(curr != NULL) {
		hash_table_put(htable, (char *)curr->data, 1);
		curr = curr->next;
	}

	curr = document->head;

	while(curr != NULL) {
		int slen = strlen(curr->data);
		float cost_d2 = pow(26*(slen+1), 3);
		float cost_d3 = pow(26*(slen+1), 4);

		if(hash_table_has(htable, curr->data)) {
			printf("%s\n", (char *)curr->data);
		}else {
			warray_t leven1 = gen_edit_one(curr->data);
			int found = 0;
			found = warray_in_hash(htable, &leven1);
			
			if(cost_d2 > dictionary->size) {
				string_in_hash(htable, curr->data);
				found = 1;
			}

			if(!found) {
				for(int i=0; i < leven1.written; i++) {
					warray_t leven2 = gen_edit_one(leven1.data[i]);
					found = warray_in_hash(htable, &leven2);
					free_warray(&leven2);
					if(found) break;
				}

				if(cost_d3 > dictionary->size) {
					string_in_hash(htable, curr->data);
					found = 1;
				}

				if(!found) {
					for(int i=0; i < leven1.written; i++) {
						warray_t leven2 = gen_edit_one(leven1.data[i]);
							for(int j=0; j < leven2.written; j++) {
								warray_t leven3 = gen_edit_one(leven2.data[j]);
								found = warray_in_hash(htable, &leven3);
								free_warray(&leven3);
								if(found) break;
							}
						free_warray(&leven2);
						if(found) break;
					}
					if(!found) {
						printf("%s?\n", (char *)curr->data);
					}
				}
			}
			free_warray(&leven1);
		}
		curr = curr->next;
	}
	free_hash_table(htable);
}
