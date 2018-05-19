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
	// print the edit distance
	printf("%d\n", ldist(word1, word2));
}

// see Assignment Task 2: Enumerating all possible edits
void print_all_edits(char *word) {
	// Obtain the levenshtein distance 1 words
	warray_t *leven1 = gen_edit_one(word);
	for(int i=0; i < leven1->written; i++) {
		// Print the levenshtein distance words
		printf("%s\n", leven1->data[i]);
	}
	// Free the words
	free_warray(leven1);
}

// see Assignment Task 3: Spell checking
void print_checked(List *dictionary, List *document) {
	// Create a new has table
	htable_t *htable = new_hash_table(dictionary->size);
	Node *curr = dictionary->head;

	while(curr != NULL) {
		// Insert to the hash table a string and a value
		// value is not relavant.
		hash_table_put(htable, (char *)curr->data, 1);
		// Next item
		curr= curr->next;
	}

	// Look through the testing words
	curr = document->head;

	while(curr != NULL) {
		// check the words
		if(!hash_table_has(htable, (char *)curr->data)) {
			// This word was not found in the hash table
			printf("%s?\n", (char *)curr->data);
		}else {
			// Word was found in the hash table
			printf("%s\n", (char *)curr->data);
		}
		curr = curr->next; 
	}
	
	free_hash_table(htable);
}

bool warray_in_hash(htable_t *table, warray_t *w) {
	// Check if a set of words occurs in a hash table
	// however ensure the first occuring is printed.
	bool in = 0;
	char *best = NULL; // Nothing found yet
	int best_index = table->nslots; // This is the worst score we can have.
	// Iterate through the array of words
	for(int i=0; i < w->written; i++) {
		// Error code
		int error = 0;
		int value = hash_table_gets(table, w->data[i], &error);
		// The word exists
		if(error != -1) {
			// The word is better than out previous
			if(value < best_index) {
				// update the word and its score
				best_index = value;
				best = w->data[i];
				// we have found a match
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
	int slen = strlen(s);
	// Iterate through an order list of words in the hash table
	for(int i=0; i < table->nkeys; i++) {
		char *word = table->keys[i];
		int wlen = strlen(word);
		// There is no way that the levenshtein distance
		// will be less than 3 in this case
		if(abs(slen - wlen) <= 3) {
			if(ldist(word, s)==3) {
				// We found the word that occurs first 
				// in the dictionary and is at a levenshtein distance 
				// of 1
				printf("%s\n", word);
				return 1;
			}
		}

	}
	return in;
}

// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {
	// Creat a new hash table
	htable_t *htable = new_hash_table(dictionary->size);

	Node *curr = dictionary->head;
	int i = 1;
	while(curr != NULL) {
		// Insert the wordto the hash table
		hash_table_put(htable, (char *)curr->data, i);
		// Need to know the position
		i++;
		curr = curr->next;
	}
	
	curr = document->head;

	while(curr != NULL) {
		// Check if the word exits in the hash table
		if(hash_table_has(htable, (char *)curr->data)) {
			printf("%s\n", (char *)curr->data);
		}else {
			// Generate levenshtein distance 1
			warray_t *leven1 = gen_edit_one((char *)curr->data);
			int found = 0;
			// check if the word is with levenshtein distance 1
			found = warray_in_hash(htable, leven1);
			// word not in levenshtein distance 1
			if(!found) {
				// Create new array to hold levenshtein distance 2
				warray_t *leven2 = new_warray();

				for(int i=0; i< leven1->written; i++) {
					warray_t *tmp = gen_edit_one(leven1->data[i]);

					for(int j=0; j < tmp->written; j++) {
						// Add to the levenshtein distance 2 array
						warray_append(leven2, tmp->data[j]);
					}
					// We can't use free_warray since it would free the
					// actual words
					free(tmp->data);
					free(tmp);
				}

				// Check if the word is in lvenshtein distance 2
				found = warray_in_hash(htable, leven2);

				if(!found) {
					// Levenshtein distance 3 is too expensive
					// so just look through the dicitonary
					found = string_in_hash(htable, (char *)curr->data);
				}

				// Word does not exist anywhere.
				if(!found) {
					printf("%s?\n", (char *) curr->data);
				}
				free_warray(leven2);
			}

			free_warray(leven1);
		}
		curr = curr->next;
	}
	free_hash_table(htable);
}
