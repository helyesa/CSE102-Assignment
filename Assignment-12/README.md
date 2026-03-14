# Assignment 12 – Custom Dictionary in C

A custom dictionary data structure implemented in C, supporting key-value pairs where values can be arrays of mixed types (int, float, double, char). Data is loaded from a CSV file.

## Features

- Add, delete, search, and update key-value pairs
- Dynamic resizing when capacity is exceeded
- Sort dictionary keys alphabetically
- Read initial data from a CSV file
- Print all key-value pairs

## File Structure

```
Assignment-12/
├── main.c      ← entry point, test cases
├── util.c      ← dictionary operations
├── util.h      ← structs, union, and function declarations
└── data.csv    ← sample input data
```

## Build & Run

```bash
gcc --ansi main.c util.c -o dict
./dict
```

## Concepts Used

- Union (`Value`) for multi-type storage
- Dynamic memory allocation (`malloc`, `realloc`, `free`)
- Struct-based data structures (`CustomDict`, `Item`)
- CSV file parsing with `strtok`
- Bubble sort on string keys
