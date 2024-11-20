typedef struct {
    char* key;
    char* value;
} hash_item;

typedef struct {
    int size;
    int count;
    hash_item **items;
} hash_table;
