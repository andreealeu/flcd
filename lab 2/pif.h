#include <stdlib.h>
#include <stdio.h>


typedef struct{
    int size,next_pos, *internal_code, *st_position;
} pif_table;

pif_table *new_pif_table();
   
void insert_pif(pif_table *pif, int code, int pos);
 
void print_pif_table(pif_table *pif);
    
