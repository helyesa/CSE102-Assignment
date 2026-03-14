# Assignment 13 – Species Information Manager

A menu-driven C program that manages biological species data using a **singly linked list**.

## Features

- Add species records (class, order, family, genus, species)
- Modify existing records by species name
- Delete records by species name
- Sort the list alphabetically by any taxonomic level (class, order, family, genus, species)
- Print all records

## Build & Run

```bash
gcc --ansi main.c -o species
./species
```

## Concepts Used

- Singly linked list (dynamic memory allocation)
- Bubble sort on linked list nodes
- Enum for sort criteria
- String operations (`strcmp`, `strcpy`)
