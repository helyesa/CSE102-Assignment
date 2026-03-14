#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define the structure for a node in the linked list */
typedef struct node {
    char class[30];
    char order[30];
    char family[30];
    char genus[30];
    char species[30];
    struct node *next;
} node;

/* Enum to represent sorting criteria */
typedef enum {
    class = 1,
    order, 
    family,
    genus,
    species
} Criteria;

/* Function to create a new node */
node* create_node() {
    node *new_node = (node*)malloc(sizeof(node)); /* Allocate memory for a new node */
    new_node->next = NULL; /* Initialize the next pointer to NULL */
    return new_node;
}

/* Function to get sorting criteria from the user */
int return_criteria() {
    char input[15];
    Criteria criteria;
    printf("Enter list criteria (class, order, family, genus, species): ");
    scanf("%s",input);

    /* Determine the criteria based on user input */
    if (strcmp(input, "class") == 0) {
        criteria = class;
    } else if (strcmp(input, "order") == 0) {
        criteria = order;
    } else if (strcmp(input, "family") == 0) {
        criteria = family;
    } else if (strcmp(input, "genus") == 0) {
        criteria = genus;
    } else if (strcmp(input, "species") == 0) {
        criteria = species;
    }
    return criteria;
}

/* Function to display the menu */
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add species information\n");
    printf("2. Modify species information\n");
    printf("3. Delete species information\n");
    printf("4. Sort species information\n");
    printf("5. Print species information\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

/* Function to print the linked list information */
void print_lli(node* lli) {
    node *temp = lli;
    if (temp == NULL) {
        printf("No species information available.\n");
    } else {
        while (temp != NULL) {
            printf("Class: %s\n", temp->class);
            printf("Order: %s\n", temp->order);
            printf("Family: %s\n", temp->family);
            printf("Genus: %s\n", temp->genus);
            printf("Species: %s\n\n", temp->species);
            temp = temp->next;
        }
    }
}

/* Function to add a new node to the linked list */
void add_node_lli(node** lli) {
    node* new_node = create_node(); /* Create a new node */
    
    /* Get species information from the user */
    printf("Class: ");
    scanf("%s", new_node->class);
    printf("Order: ");
    scanf("%s", new_node->order);
    printf("Family: ");
    scanf("%s", new_node->family);
    printf("Genus: ");
    scanf("%s", new_node->genus);
    getchar();
    printf("Species: ");
    scanf("%[^\n]", new_node->species);

    /* Insert the new node at the end of the list */
    if (*lli == NULL) {
        *lli = new_node;
    } else {
        node* temp = *lli;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}


/* Function to delete a node from the linked list */
void delete_node_lli(node** lli) {
    char speciesName[30];
    printf("Enter the species name to delete: ");
    getchar();
    scanf("%[^\n]", speciesName);
    node* current = *lli;
    node* prev = NULL;

    /* Search for the node to delete */
    while (current != NULL && strcmp(current->species, speciesName) != 0) {
        prev = current;
        current = current->next;
    }

    /* If the node is found, delete it */
    if (current != NULL) {
        if (prev == NULL) {
            *lli = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
    } else {
        printf("Species not found.\n");
    }
}

/* Function to modify a node in the linked list */
void modify_node_lli(node* lli) {
    char speciesName[50];
    printf("Enter the species name to modify: ");
    getchar();
    scanf("%[^\n]", speciesName);
    node* current = lli;

    /* Search for the node to modify */
    while (current != NULL && strcmp(current->species, speciesName) != 0) {
        current = current->next;
    }

    /* If the node is found, modify its information */
    if (current != NULL) {
        printf("Enter Species information to modify: \n");
        printf("Old Species: %s\n",current->species);
        printf("New class: ");
        scanf("%s", current->class);
        printf("New order: ");
        scanf("%s", current->order);
        printf("New family: ");
        scanf("%s", current->family);
        printf("New genus: ");
        scanf("%s", current->genus);
        printf("New species: ");
        getchar();
        scanf("%[^\n]", current->species);
    } else {
        printf("Species not found.\n");
    }
}

/* Function to swap the information of two nodes */
void swap(node* a, node* b) {
    char temp[50];
    
    /* Swap the class information */
    strcpy(temp, a->class);
    strcpy(a->class, b->class);
    strcpy(b->class, temp);
    
    /* Swap the order information */
    strcpy(temp, a->order);
    strcpy(a->order, b->order);
    strcpy(b->order, temp);
    
    /* Swap the family information */
    strcpy(temp, a->family);
    strcpy(a->family, b->family);
    strcpy(b->family, temp);
    
    /* Swap the genus information */
    strcpy(temp, a->genus);
    strcpy(a->genus, b->genus);
    strcpy(b->genus, temp);
    
    /* Swap the species information */
    strcpy(temp, a->species);
    strcpy(a->species, b->species);
    strcpy(b->species, temp);
}

/* Function to sort the linked list based on the given criteria */
void sort_species(node** lli, Criteria criteria) {
    if (*lli == NULL) {
        printf("List is empty.\n");
    } else {

        int swapped;
        node *ptr1;
        node *lptr = NULL;

        /* Bubble sort algorithm */
        do {
            swapped = 0;
            ptr1 = *lli;

            while (ptr1->next != lptr) {
                int cmp;

                /* Compare nodes based on the given criteria */
                switch (criteria) {
                    case 1:
                        cmp = strcmp(ptr1->class, ptr1->next->class);
                        break;
                    case 2:
                        cmp = strcmp(ptr1->order, ptr1->next->order);
                        break;
                    case 3:
                        cmp = strcmp(ptr1->family, ptr1->next->family);
                        break;
                    case 4:
                        cmp = strcmp(ptr1->genus, ptr1->next->genus);
                        break;
                    case 5:
                        cmp = strcmp(ptr1->species, ptr1->next->species);
                        break;
                    default:
                        printf("Invalid criteria.\n");
                        return;
                }

                /* Swap the nodes if they are in the wrong order */
                if (cmp > 0) {
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }
}

/* Function to free the memory allocated for the linked list */
void freeList(node* lli) {
    node* current = lli;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    node* lli = NULL; /* Initialize the linked list */
    int choice;
    Criteria criteria;
    do {
        displayMenu(); /* Display the menu */
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_node_lli(&lli); /* Add a new node */
                break;
            case 2:
                modify_node_lli(lli); /* Modify an existing node */
                break;
            case 3:
                delete_node_lli(&lli); /* Delete a node */
                break;
            case 4:
                criteria = return_criteria(); /* Get sorting criteria */
                sort_species(&lli,criteria); /* Sort the list */
                break;
            case 5:
                print_lli(lli); /* Print the list */
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    freeList(lli); /* Free the allocated memory */
    return 0;
}
