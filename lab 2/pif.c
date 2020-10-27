#include "pif.h"

pif_table *new_pif_table(){
    pif_table *new = (pif_table*)malloc(sizeof (pif_table));
    new->size=30;
    new->next_pos=0;
    new->internal_code= (int *)malloc(30*sizeof(int));
    new->st_position= (int*)malloc(30*sizeof(int));

    return new;
}

void insert_pif(pif_table *pif, int code, int pos){
    int next_pos = pif->next_pos;
    int size = pif->size;

    if (next_pos == size){
        //resize
    }

    pif->internal_code[next_pos]=code;
    pif->st_position[next_pos]=pos;
    pif->next_pos++;
}

void print_pif_table(pif_table *pif){
    FILE *fp;
    int i;
    fp = fopen("pif.txt","w");
    fprintf(fp,"\tCODE\tPOS IN ST\n");
    for (int i=0; i<pif->next_pos; i++)
        fprintf(fp,"\t%d\t\t%d\n", pif->internal_code[i], pif->st_position[i]);
    fclose(fp);
}