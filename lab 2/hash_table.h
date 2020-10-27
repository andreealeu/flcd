#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define TABLE_SIZE 30
#define IDENTIFIER_MAX_SIZE 20  

typedef struct Hash_table{
    int inserted;
    int size;
    char **symbol_table;
}hash_table ;

hash_table *new_hash_table();
void print_table(hash_table *table);
unsigned int hash( char *identifier);
int search( hash_table *table, char *symbol );
int insert(char *symbol, hash_table *table);