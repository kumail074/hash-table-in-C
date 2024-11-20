#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "hash.h"

#define HT_PRIME_1 31
#define HT_PRIME_2 7
static hash_item HT_DELETED_ITEM = {NULL, NULL};

static hash_item *new_item(const char* k, const char* val) {
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

static int hash(const char *s, const int a, const int m) {
    long h = 0;
    const int len = strlen(s);
    for(int i = 0; i < len; i++) {
        h += (long)pow(a, len - (i+1)) * s[i];
        h = h % m;
    }
    return (int) h;
}

static int get_hash(const char *s, const int brackets, const int attempt) {
    const int hash_a = hash(s, HT_PRIME_1, brackets);
    const int hash_b = hash(s, HT_PRIME_2, brackets);
    return (hash_a + (attempt * (hash_b + 1))) % brackets;
}

void hash_insert(hash_table* ht, const char* key, const char* value) {
    hash_item* item = new_item(key, value);
    int index = get_hash(item->key, ht->size, 0);
    hash_item* current_item = ht->items[index];
    int i = 1;
    while(current_item != NULL) {
        if(current_item != &HT_DELETED_ITEM) {
            if(strcmp(current_item->key, key) == 0) {
                del_item(current_item);
                ht->items[index] = item;
                return;
            }
        }
        index = get_hash(item->key, ht->size, i);
        current_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

char* hash_search(hash_table* ht, const char* key) {
    int index = get_hash(key, ht->size, 0);
    hash_item* item = ht->items[index];
    int i = 0;
    while(item != NULL) {
        if(item != &HT_DELETED_ITEM) {
            if(strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

void hash_delete(hash_table* ht, const char* key) {
    int index = get_hash(key, ht->size, 0);
    hash_item* item = ht->items[index];
    int i = 1;
    while(item != NULL) {
        if(item != &HT_DELETED_ITEM) {
            if(strcmp(item->key, key) == 0) {
                del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}

int main() {
    hash_table *ht = new();
    del_hashtable(ht);
}

