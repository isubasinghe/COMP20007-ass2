/* ... */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	free_hash_table(htable);
}

// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {

	HashTable *htable = new_hash_table(dictionary->size);

	Node *curr = dictionary->head;

	while(curr != NULL) {
		hash_table_put(htable, (char *)curr->data, 1);
		curr = curr->next;
	}

	curr = document->head;

	while(curr != NULL) {
		if(hash_table_has(htable, curr->data)) {
			printf("%s\n", (char *)curr->data);
		}else {
			warray_t leven1 = gen_edit_one(curr->data);
			int found = 0;
			for(int i=0; i < leven1.written; i++) {
				if(hash_table_has(htable, leven1.data[i])) {
					found = 1;
					printf("%s\n", leven1.data[i]);
					//free_warray(&leven1);
					break;
				}
			}
			
			if(!found) {
				// We have roughly (26*s)^3 operations to check the levenshtein
				// distance, so we see if iterating through the dicitonary is faster.
				if(pow(26*strlen(curr->data), 3) >= dictionary->size) {
					// Iterating through the dictionary is faster.
				}

				if(!found) {
					// We have roughly (26*s)^4 operations to generate the levenshtein
					// distance, so we see if iterating through the dicionary is faster.
					if(pow(26*strlen(curr->data), 4) >= dictionary->size) {
						// Iterating though the dicitonary is faster.
					}
				}		
			}

			free_warray(&leven1);


		}
		curr = curr->next;
	}
	free_hash_table(htable);
}
