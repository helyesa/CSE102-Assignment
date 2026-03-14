#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* Create a new dictionary */
CustomDict* create_dict() {
    CustomDict *dict = (CustomDict *)malloc(sizeof(CustomDict));
    dict->capacity = 0;  
    dict->size = 0;
    dict->items = NULL;  
    return dict;
}

/* Resize the dictionary when needed */
void resize_dict(CustomDict *dict) {
    if (dict->capacity == 0) {
        dict->capacity = 1;  
    } else {
        dict->capacity = 2 * dict->size;
    }
    dict->items = (Item *)realloc(dict->items, dict->capacity * sizeof(Item));
}

/* Read data from a CSV file and populate the dictionary */
int read_csv(CustomDict *dict, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    
    char line[100];
    while (fgets(line, sizeof(line), file)) {  
        if (dict->size >= dict->capacity) {
            resize_dict(dict);
        }
        
        char *token = strtok(line, ",");
        char type = token[0];

        token = strtok(NULL, ",");
        dict->items[dict->size].key = (char *)malloc(strlen(token) + 1);
        strcpy(dict->items[dict->size].key, token);

        dict->items[dict->size].values = (Value *)malloc(10 * sizeof(Value));
        dict->items[dict->size].type = type;
        dict->items[dict->size].value_count = 0;
        
        while ((token = strtok(NULL, ",")) != NULL) {
            switch (type) {
                case 'i':
                    dict->items[dict->size].values[dict->items[dict->size].value_count].i = atoi(token);
                    break;
                case 'd':
                    dict->items[dict->size].values[dict->items[dict->size].value_count].d = atof(token);
                    break;
                case 'f':
                    dict->items[dict->size].values[dict->items[dict->size].value_count].f = atof(token);
                    break;
                case 'c':
                    dict->items[dict->size].values[dict->items[dict->size].value_count].c = token[1];
                    break;
            }
            dict->items[dict->size].value_count++;
        }
        dict->items[dict->size].values = (Value *)realloc(dict->items[dict->size].values, dict->items[dict->size].value_count * sizeof(Value));
        dict->size++;
    }
    fclose(file);
    return 1;
}

/* Add a new item to the dictionary */
void add_item(CustomDict *dict, char *key, Value *values, char type) {
    int new_key = 1;
    int i, j, value_count = 0;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            new_key = 0;
            switch (type) {
                case 'i':
                    while (values[value_count].i != -1) value_count++;  
                    break;
                case 'd':
                    while (values[value_count].d != -1) value_count++;
                    break;
                case 'f':
                    while (values[value_count].f != -1) value_count++;
                    break;
                case 'c':
                    while (values[value_count].c != '\0') value_count++;
                    break;
            }
            dict->items[i].value_count += value_count;
            dict->items[i].values = (Value *)realloc(dict->items[i].values, dict->items[i].value_count * sizeof(Value));
            int k = 0;
            for (j = dict->items[i].value_count - value_count; j < dict->items[i].value_count; j++) {
                dict->items[i].values[j] = values[k];
                k++;
            }
        }
    }
    if (new_key) {
        if (dict->size >= dict->capacity) {
            resize_dict(dict);
        }
        dict->items[dict->size].key = (char *)malloc(strlen(key) + 1);
        strcpy(dict->items[dict->size].key, key);
        dict->items[dict->size].type = type;

        value_count = 0;
        switch (type) {
            case 'i':
                while (values[value_count].i != -1) value_count++;
                break;
            case 'd':
                while (values[value_count].d != -1) value_count++;
                break;
            case 'f':
                while (values[value_count].f != -1) value_count++;
                break;
            case 'c':
                while (values[value_count].c != '\0') value_count++;
                break;
        }
        dict->items[dict->size].values = (Value *)malloc(value_count * sizeof(Value));
        for (j = 0; j < value_count; j++) {
            dict->items[dict->size].values[j] = values[j];
        }
        dict->items[dict->size].value_count = value_count;
        dict->size++;
    }
}

/* Delete an item from the dictionary */
void delete_item(CustomDict* dict, char* key) {
    int i, j;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            free(dict->items[i].key);
            free(dict->items[i].values);
            for (j = i; j < dict->size - 1; j++) {
                dict->items[j] = dict->items[j + 1];
            }
            dict->size--;
        }
    }
}

/* Print the dictionary contents */
void print_dict(CustomDict *dict) {
    int i, j;
    for (i = 0; i < dict->size; i++) {
        printf("%s ", dict->items[i].key);
        for (j = 0; j < dict->items[i].value_count; j++) {
            switch (dict->items[i].type) {
                case 'i':
                    printf("%d ", dict->items[i].values[j].i);
                    break;
                case 'd':
                    printf("%.2f ", dict->items[i].values[j].d);
                    break;
                case 'f':
                    printf("%.2f ", dict->items[i].values[j].f);
                    break;
                case 'c':
                    printf("%c ", dict->items[i].values[j].c);
                    break;
            }
        }
        printf("\n");
    }
}

/* Search for an item by key */
Value* search_item(CustomDict *dict, char *key) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return dict->items[i].values;
        }
    }
    return NULL;
}

/* Set values for an existing item */
void set_value(CustomDict *dict, Value *values, char *key) {
    int i, value_count = 0, j;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            switch (dict->items[i].type) {
                case 'i':
                    while (values[value_count].i != -1) value_count++;
                    break;
                case 'd':
                    while (values[value_count].d != -1) value_count++;
                    break;
                case 'f':
                    while (values[value_count].f != -1) value_count++;
                    break;
                case 'c':
                    while (values[value_count].c != '\0') value_count++;
                    break;
            }
            dict->items[i].value_count = value_count;
            dict->items[i].values = (Value *)realloc(dict->items[i].values, dict->items[i].value_count * sizeof(Value));
            for (j = 0; j < dict->items[i].value_count; j++) {
                dict->items[i].values[j] = values[j];
            }
        }
    }
}

/* Swap two items */
void swap_items(Item *item1, Item *item2) {
    Item temp = *item1;
    *item1 = *item2;
    *item2 = temp;
}

/* Swap two items */
void sort_dict(CustomDict *dict) {
    int i, j;
    for (i = 0; i < dict->size - 1; i++) {
        for (j = 0; j < dict->size - i - 1; j++) {
            if (strcmp(dict->items[j].key, dict->items[j + 1].key) > 0) {
                swap_items(&dict->items[j], &dict->items[j + 1]);
            }
        }
    }
}
/* Free the memory used by the dictionary */
void free_dict(CustomDict *dict) {
    int i;
    for (i = 0; i < dict->size; ++i) {
        free(dict->items[i].key);
        free(dict->items[i].values);
    }
    free(dict->items);
    free(dict);
}
