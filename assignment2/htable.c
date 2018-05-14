#include "htable.h"

htable_t *new_hash_table(int size) {
    htable_t *table = malloc(sizeof(htable_t));
    table->nslots = size;
    table->slots = malloc(size*sizeof(slot_t));
    table->seed = SEED;
    for(int i=0; i < table->nslots; i++) {
        table->slots[i].keys = NULL;
        table->slots[i].vals = NULL;
        table->slots[i].written = 0;
        table->slots[i].cap = 0;
    }
    return table;
}

void move_to_front(slot_t *slot, int i) {
    char *tmpkey = slot->keys[i];
    int tmpval = slot->vals[i];
    slot->keys[i] = slot->keys[0];
    slot->vals[i] = slot->vals[0];
    slot->keys[0] = tmpkey;
    slot->vals[0] = tmpval;
}

bool slot_has(slot_t *slot, char *s) {
    bool in = 0;
    for(int i=0; i < slot->written; i++) {
        if(strcmp(slot->keys[i], s)==0) {
            move_to_front(slot, i);
            return 1;
        }
    }
    return in;
}

int slot_gets(slot_t *slot, char *s, int *err) {

    *err = -1;
    for(int i = 0; i < slot->written; i++) {
        if(strcmp(slot->keys[i], s) == 0) {
            *err = 0;
            move_to_front(slot, i);
            return slot->vals[i];
        }
    }
    return -1;
}


bool hash_table_has(htable_t *table, char *s) {
    bool in = 0;
    int slot = xorhash(s, table->seed, table->nslots);
    in = slot_has(&table->slots[slot], s);
    return in;
}

int hash_table_gets(htable_t *table, char *s, int *error) {
    int tmp = 0;
    int *write = error;
    if(error == NULL) {
        write = &tmp;
    }

    int slot = xorhash(s, table->seed, table->nslots);
    return slot_gets(&table->slots[slot], s, write);


}


void insert_to_slot(slot_t *slot, char *s, int val) {
    if(slot->keys == NULL) {
        slot->cap = INITAL_SIZE;
        slot->keys = malloc(INITAL_SIZE*sizeof(char *));
        slot->vals = malloc(INITAL_SIZE*sizeof(int));
        slot->written = 0;
    }
    if(slot->cap <= slot->written) {
        slot->cap *= 2;
        slot->keys = realloc(slot->keys, slot->cap*sizeof(char *));
        slot->vals = realloc(slot->vals, slot->cap*sizeof(int));
    }

    char *cpy = malloc((strlen(s)+1) *(sizeof(char)));
    cpy = strcpy(cpy, s);
    slot->keys[slot->written] = cpy;
    slot->vals[slot->written] = val;
    slot->written++;
    move_to_front(slot, slot->written-1);
}

void hash_table_put(htable_t *table, char *key, int val) {
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
    free(table->slots);
    free(table);
}