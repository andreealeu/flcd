
#include "hash_table.h"


//DO RESIZE & DELETE !!


char *symbol_table[TABLE_SIZE];

hash_table *new_hash_table(){
    hash_table *new = (hash_table*)malloc(sizeof (hash_table));
    new->inserted= 0;
    new->size= TABLE_SIZE;
    new->symbol_table = (char**)malloc(TABLE_SIZE * sizeof(char*));
    for (int i = 0; i < TABLE_SIZE; i++)
        new->symbol_table[i]= NULL;

    return new;
}


void print_table(hash_table *table) {
    FILE *fp;

    fp= fopen("symbol_table.txt","w");
    fprintf(fp,"SYMBOL TABLE\n");
    for (int i=0; i < TABLE_SIZE ; i++)
        if (table->symbol_table[i] != NULL)
            fprintf(fp,"%s\n", table->symbol_table[i]);       
}

unsigned int hash( char *identifier){
    int hash = 0;
    for (int i = 0; i < strlen(identifier); i++) {
        hash += identifier[i];
    }
    return hash % TABLE_SIZE;
}

// this checks for collision, also returns index
// if symbol already exists.
int search( hash_table *table, char *symbol ){

    int index=hash(symbol);
        
    for (int i=0; i<TABLE_SIZE; i++){
        int try= (i + index) % TABLE_SIZE;
        if (table->symbol_table[try] != NULL)
        {
            if (strcmp(table->symbol_table[try], symbol)==0) 
            {
                return try;
            }
        }
        else
        {
            return -1;
        }    
    }
}

int insert(char *symbol, hash_table *table){
   
    if (table->inserted == table->size)
        return -1;
    
    int index= search(table,symbol);
  
    if ( index != -1)
        return index;
    else
        index= hash(symbol);
    
    while (table->symbol_table[index] != NULL){
        index++;
        if (index == TABLE_SIZE)
            index=0;
    }

    table->symbol_table[index] = symbol;
    table->inserted++;

    return index;

}


