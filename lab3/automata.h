#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    char ch, dest;
} transition;

transition *new_transition(char ch, char dest);

typedef struct {
    char name;
    transition *transitions[50];
    int next_pos;
} state;

state *new_state(char name);
void add_transition_state(state *s, char ch, char dest);
char find_transition(state *s, char ch);

typedef struct {
    char initial_state;
    
    char final_states[5];
    int next_final_pos;

    char alphabet[40];
    char next_alphabet_pos;
    
    state *states[5];
    int last_state_pos;

} automata;

automata *new_automata();
void initialize_automata(automata *a, char initial_state);
void add_final_stste(automata *a, char final_state);
void add_alphabet_character(automata *a, char ch);
void add_transition_automata(automata *a, char state, char ch, char dest);
char find_next_state(automata *a, int state_index, char ch);
int get_state_by_name(automata *a, char name);
bool check_if_final_state(automata *a, char state_name);
void read_automata(automata *a, char filename[20]);
void print_automata(automata *a);
bool check_token_in_alphabet(automata *a, char token[20]);
bool parse_token(automata *a, char token[20]);









