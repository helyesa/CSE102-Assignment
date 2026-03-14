#include <stdio.h>
#include "util.h"

int main() {
    CustomDict *dict = create_dict();
    Value value1[4] = {{.d = 4.2}, {.d = 3.7}, {.d = 8.1}, {.d = -1}}; 
    int test;
    read_csv(dict,"data.csv");
    printf("1. adding item (named mavi)\n");
    printf("2. deleting item (deleted balance)\n");
    printf("3. sorting items\n");
    printf("4. setting value (setting distance)\n");
    printf("5. searching value (searched balance)\n");
    printf("test (1 to 5): ");
    scanf("%d",&test);
    
    switch (test) {
        case 1:
            print_dict(dict);
            printf("\n\n");
            add_item(dict," mavi",value1,'d');
            print_dict(dict);
            break;
        case 2:
            print_dict(dict);
            printf("\n\n");
            delete_item(dict," balance");
            print_dict(dict);
            break;
        case 3:
            print_dict(dict);
            printf("\n\n");
            sort_dict(dict);
            print_dict(dict);
            break;
        case 4:
            print_dict(dict);
            printf("\n\n");
            set_value(dict,value1," distance");
            print_dict(dict);
            break;
        case 5:
            print_dict(dict);
            printf("\n\n");
            Value *search_value = search_item(dict," balance");
            int i, temp_count, j, temp_i;;
            char temp_type;
            for (i = 0; i < dict->size; i++) {
                if (strcmp(dict->items[i].key," balance") == 0) {
                    temp_type = dict->items[i].type;
                    temp_count = dict->items[i].value_count;
                    temp_i = i;
                }
            }
            printf("searching item values: ");
            for (j = 0; j < dict->items[temp_i].value_count; j++) {
            switch (dict->items[temp_i].type) {
                case 'i':
                    printf("%d ", dict->items[temp_i].values[j].i);
                    break;
                case 'd':
                    printf("%.2f ", dict->items[temp_i].values[j].d);
                    break;
                case 'f':
                    printf("%.2f ", dict->items[temp_i].values[j].f);
                    break;
                case 'c':
                    printf("%c ", dict->items[temp_i].values[j].c);
                    break;
            }
        }
       
    }
    free_dict(dict);
    return 0;
}
