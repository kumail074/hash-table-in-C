#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hash.h"

static hash_item *new_item(const char* val, const char* k) {
    hash_item *i = malloc(sizeof(hash_item));
    i->value = strdup(val);
    i->key = strdup(k);
    return i;
}

hash_table *new() {
    hash_table *ht = malloc(sizeof(hash_table));
    ht->size = 64;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(hash_item*));
    return ht;
}

static void del_item(hash_item* i) {
    free(i->value);
    free(i->key);
    free(i);
}

void del_hashtable(hash_table *ht) {
    for(int i = 0; i < ht->size; i++) {
        hash_item* item = ht->items[i];
        if(item != NULL){
            del_item(item);
        }
    }
        free(ht->items);
        free(ht);
}

int main() {
    hash_table *ht = new();
    del_hashtable(ht);
}

