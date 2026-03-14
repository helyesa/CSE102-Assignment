#ifndef UTIL_H
#define UTIL_H

/* Define a union to hold different data types */
typedef union {
    int i;
    float f;
    double d;
    char c;
} Value;

/* Define a structure to hold a key and its associated values */
typedef struct {
    char *key;
    Value *values;
    char type;
    int value_count;
} Item;

/* Define a structure to hold an array of items */
typedef struct {
    Item *items;
    int capacity;
    int size;
} CustomDict;

/* Function declarations for dictionary operations */
CustomDict* create_dict();
void resize_dict(CustomDict *dict);
int read_csv(CustomDict *dict, const char *filename);
void add_item(CustomDict *dict, char *key, Value *values, char type);
void delete_item(CustomDict* dict, char* key);
void print_dict(CustomDict *dict);
Value* search_item(CustomDict *dict, char *key);
void set_value(CustomDict *dict, Value *values, char *key);
void sort_dict(CustomDict *dict);
void free_dict(CustomDict *dict);

#endif 
