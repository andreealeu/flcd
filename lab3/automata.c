#include "automata.h"

transition *new_transition(char ch, char dest){
    transition *new = (transition*)malloc(sizeof (transition));
 
    new->ch=ch;
    new->dest=dest;

    return new;
}

state *new_state(char name){
    state *new = (state*)malloc(sizeof (state));

    new->name= name;
    new->next_pos = 0;

    return new;
    
}


void add_transition_state(state *s, char ch, char dest){
    s->transitions[s->next_pos]= new_transition(ch, dest);
    s->next_pos++;
}

char find_transition(state *s, char ch){
    for (int i=0; i<s->next_pos; i++){
        if (s->transitions[i]->ch == ch){
            return s->transitions[i]->dest;
        }
    }
    return '\0';
}




automata *new_automata(){
    automata *new = (automata*)malloc(sizeof(automata));

    new->initial_state= 'p';
   
    
    new->last_state_pos=0;
    new->next_final_pos=0;
    new->next_alphabet_pos=0;

    return new;
}

void initialize_automata(automata *a, char initial_state){
    a->initial_state = initial_state;

    a->states[0] = new_state(initial_state);
}

void add_final_stste(automata *a, char final_state){
    a->final_states[a->next_final_pos] = final_state;
    a->next_final_pos++;
}

void add_alphabet_character(automata *a, char ch){
    a->alphabet[a->next_alphabet_pos++]=ch;
    
}

void add_transition_automata(automata *a, char state, char ch, char dest){
    
    //checking if input reached a new state
    if (a->states[a->last_state_pos]->name != state){
        a->last_state_pos++;
        a->states[a->last_state_pos] = new_state(state);
    }

    //adding the transition
    add_transition_state(a->states[a->last_state_pos], ch , dest);
 
}

char find_next_state(automata *a, int state_index, char ch){
    return find_transition(a->states[state_index], ch);
}

int get_state_by_name(automata *a, char name){
    for (int i=0; i<= a->last_state_pos; i++)
        if (a->states[i]->name == name)
            return i;
    return -1;
}


bool check_if_final_state(automata *a, char state_name){
    
    for (int i=0; i < a->next_final_pos; i++){

        if (a->final_states[i] == state_name)
            return true;
    }
    return false;
}

void read_automata(automata *a, char filename[20]){
    printf("%s\n", filename);

    FILE *fp;
    fp=fopen(filename, "r");

    char c;

    
    //reading initial state from first line
    c= fgetc(fp);
    fgetc(fp);
    
    // initiazlzing automata with state
    initialize_automata(a, c);

    //read final state
    char *line;
    size_t size=20;
    line=(char*)malloc(size * sizeof(char));
    getline(&line, &size, fp);
    // printf("%s\n", line);
    for(int i=0; line[i] != '\0'; i+=2){ 
            add_final_stste(a, line[i]);
    }

    //read alphabet
    getline(&line, &size, fp);
    for(int i=0; line[i] != '\0'; i+=2){ 
            add_alphabet_character(a, line[i]);
    }

    
    //reading transitions tuples, eating up spaces and newlines.
    char state,  ch,dest;
    while ( !feof(fp)){
        fscanf(fp, "%c", &state);

        fgetc(fp);

        fscanf(fp, "%c", &ch);

        fgetc(fp);

        fscanf(fp, "%c", &dest);

        fgetc(fp);

        // printf("state %c ch %c dest %c\n",state, ch, dest);
        add_transition_automata(a, state, ch, dest);


    }
    fclose(fp);


}
void print_automata(automata *a){
    printf("INITIAL STATE: %c\n", a->initial_state);
    printf("FINAL STATES: ");
    for (int i=0; i<a->next_final_pos; i++)
        printf("%c  ", a->final_states[i]);
    printf("\n");
    
    printf("ALPHABET:");
     for (int i=0; i<a->next_alphabet_pos; i++)
        printf("%c  ", a->alphabet[i]);
    printf("\n");  
    
    printf("TRANSITIONS: ");
    for (int i=0; i<=a->last_state_pos; i++){
        for (int j=0; j<a->states[i]->next_pos; j++){
            printf("(%c , %c) = %c\n ",a->states[i]->name, a->states[i]->transitions[j]->ch, a->states[i]->transitions[j]->dest);
        }
    }
}

bool check_token_in_alphabet(automata *a, char token[20]){
    int j;
    for (int i=0; token[i]!='\0';i++){
        for (j=0; j<a->next_alphabet_pos; j++)
            if (token[i] == a->alphabet[j])
                break;
        if (j==a->next_alphabet_pos)
            return false;
    }
    return true;
}


bool parse_token(automata *a, char token[20]){
    //first checking if token is in alphabet
    if (!check_token_in_alphabet(a,token) )
        return false;
    
    //initiazling to start from initial state
    int pos=0, state_current_index=0;
    char state_next_name;
    while(true){
        state_next_name= find_next_state(a, state_current_index, token[pos]);
        
        //case where transtition not find
        if (state_next_name == '\0'){
            return false;
        }
    
        //case end of string
        pos++;
        if (token[pos] == '\0'){
            if (check_if_final_state(a, state_next_name))
                return true;
            else
                return false;
        }
        
        //continuing parsing
        state_current_index= get_state_by_name(a, state_next_name);

    }
}

// int main(){
//     transition *t = new_transition('a', 'b');
//     state *s = new_state('a');
//     automata *a = new_automata();

//     read_automata(a, "in.txt");
//     print_automata(a);
   
//     return 0;
// }