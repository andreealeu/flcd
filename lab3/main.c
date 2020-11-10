#include "automata.h"

void verify_tokens(automata *a, char filename[20]){
    FILE *fp;
    fp=fopen(filename, "r");

    char *token;
    size_t size=20;
    size_t size_read;
    token=(char*)malloc(size * sizeof(char));

    while(!feof(fp)){
        //reading token and deletig newline 
        size_read=getline(&token, &size, fp);
        token[size_read-1]='\0';

        if (parse_token(a, token))
            printf("%s is valid\n", token);
        else
            printf("%s is not valid\n", token);    
    }
}

int main(){
    
    automata *a = new_automata();
    
    read_automata(a, "in.txt");
    print_automata(a);

    verify_tokens(a, "tokens.txt");

    return 0;
}