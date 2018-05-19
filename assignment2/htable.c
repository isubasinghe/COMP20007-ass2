#include "htable.h"

htable_t *new_hash_table(int size) {
    htable_t *table = malloc(sizeof(htable_t));
    
    table->nslots = size;
    table->slots = malloc(size*sizeof(slot_t));
    // Hashing seed
    table->seed = SEED;
    // Instead of iterating 
    // through the table we can 
    // iterate through this.
    // Which is a faster as it allows
    // us to break if we find a match since 
    // this array will be in order.
    table->keys = malloc(size*sizeof(char *));
    table->nkeys = 0;

    for(int i=0; i < table->nslots; i++) {
        table->slots[i].keys = NULL;
        table->slots[i].vals = NULL;
        table->slots[i].written = 0;
        table->slots[i].cap = 0;
    }
    return table;
}


bool slot_has(slot_t *slot, char *s) {
    // If we dont find a key this will return 0
    bool in = 0;
    for(int i=0; i < slot->written; i++) {
        if(strcmp(slot->keys[i], s)==0) {
            // we have found the key so return True
            return 1;
        }
    }
    return in;
}

int slot_gets(slot_t *slot, char *s, int *err) {
    // Error handler indicates if a key was found
    *err = -1;
    for(int i = 0; i < slot->written; i++) {
        if(strcmp(slot->keys[i], s) == 0) {
            // No error
            *err = 0;
            // Found value
            return slot->vals[i];
        }
    }
    return -1;
}


bool hash_table_has(htable_t *table, char *s) {
    bool in = 0;
    // Obtain the slot number
    int slot = xorhash(s, table->seed, table->nslots);
    // Check if the key exists
    in = slot_has(&table->slots[slot], s);
    return in;
}

int hash_table_gets(htable_t *table, char *s, int *error) {
    // tmp variables to write to
    // in case the error pointer is NULL
    int tmp = 0;
    int *write = error;
    if(error == NULL) {
        // write to the tmp variable instead of NULL.
        write = &tmp;
    }
    // Obtain slot
    int slot = xorhash(s, table->seed, table->nslots);
    // Reurn value
    return slot_gets(&table->slots[slot], s, write);

}

void insert_to_slot(slot_t *slot, char *s, int val) {
    // slots are set to NULL initially to save space
    // when we need to write to that slot a malloc call 
    // is done

    if(slot->keys == NULL) {
        // We need to fill this slot with memory
        slot->cap = INITAL_SIZE;
        // Allocate memory
        slot->keys = malloc(INITAL_SIZE*sizeof(char *));
        slot->vals = malloc(INITAL_SIZE*sizeof(int));
        // nothing was written yet
        slot->written = 0;
    }
    if(slot->cap <= slot->written) {
        // We have run out of memory so allocate some more
        // using power of 2.
        slot->cap *= 2;
        slot->keys = realloc(slot->keys, slot->cap*sizeof(char *));
        slot->vals = realloc(slot->vals, slot->cap*sizeof(int));
    }

    // This hash table was initially meant to be truly modular 
    // (it isn't anymore, since table->keys does not allocate memory for char *)
    // and not just for this assignment and therefore we 
    // allocate memory for the keys since we don't know how long
    // the pointer passed in will last.
    char *cpy = malloc((strlen(s)+1) *(sizeof(char)));
    cpy = strcpy(cpy, s);
    
    // Fill the slots
    slot->keys[slot->written] = cpy;
    slot->vals[slot->written] = val;
    slot->written++;
    
}

void hash_table_put(htable_t *table, char *key, int val) {
    // Store in an ordered array to speed up levenshtein distance
    table->keys[table->nkeys] = key;
    table->nkeys++;
    // Get the slot
    int slotn = xorhash(key, table->seed, table->nslots);
    insert_to_slot(&table->slots[slotn], key, val);
}

void free_slot(slot_t *slot) {
    for(int i=0; i < slot->written; i++) {
        free(slot->keys[i]);
    }
}

void free_slots(htable_t *table) {
    for(int i=0; i < table->nslots; i++) {
        if(table->slots[i].keys) {
            free_slot(&table->slots[i]);
            free(table->slots[i].keys);
            free(table->slots[i].vals);
        }
    }
}


void free_hash_table(htable_t *table) {
    free_slots(table);
    free(table->keys);
    free(table->slots);
    free(table);
}