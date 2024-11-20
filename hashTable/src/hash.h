typedef struct {
    char* key;
    char* value;
} hash_item;

typedef struct {
    int size;
    int count;
    int base_size;
    hash_item **items;
} hash_table;

void hash_insert(hash_table* ht, const char* key, const char* value);
char* hash_search(hash_table* ht, const char *key);
void hash_delete(hash_table* h, const char* key);
