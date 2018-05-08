/* * * * * * *
 * Program for taking strings and storing their frequencies in a hash table
 *
 * created for COMP20007 Design of Algorithms
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtbl.h"

// needed as an int AND as a string to use in scanf's format string
#define MAX_LINE_LEN 128
#define MAX_WORD_LEN 64
#define DELIMITERS " \t\n\r()/.,!?;:-_*\""

int main(int argc, char **argv) {

	// get table size
	if (argc < 2) {
		fprintf(stderr, "usage: %s <size>\n", argv[0]);
		fprintf(stderr, " size: positive integer size of hash table\n");
		return 1;
	}
	int size = atoi(argv[1]);
	if (size < 1) {
		fprintf(stderr, "table size must be a positive integer\n");
		return 1;
	}

	// initialise hash table
	printf("initialising table of size %d...\n", size);
	HashTable *table = new_hash_table(size);

	// read and count words from stdin
	printf("reading and counting words from stdin... (press ^D to stop)\n");

	char line[MAX_LINE_LEN+1];
	while (fgets(line, MAX_LINE_LEN+1, stdin)) {
		line[strlen(line)-1] = '\0'; // strip newline
		char *word;
		for (word=strtok(line, DELIMITERS);word;word=strtok(NULL, DELIMITERS)) {

			// update frequency of this word in hash table
			if ( ! hash_table_has(table, word)) {
				hash_table_put(table, word, 1);
			} else {
				int count = hash_table_get(table, word);
				hash_table_put(table, word, count+1);
			}
		}
	}
	printf("\n");
	printf("finished hashing words\n");
	
	// print the resulting hashtable
	printf("resulting hash table:\n");
	print_hash_table(table);

	// clean up and go home
	free_hash_table(table);
	return 0;
}