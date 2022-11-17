
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define DUMP DUMP_MIN(__PRETTY_FUNCTION__, __LINE__);
#define list_status_(list) list_status(list, __LINE__, __PRETTY_FUNCTION__) 

typedef int Elem_t;

const int POISON = -429;
const int NO_ELEM = -2;

struct array{
    Elem_t * data;
    int * next;
    int * prev;
};

struct LIST {
    int head;
    int tail;
    struct array ar;
    int capacity;
    int free_head;
    int free_tail;
};



enum command{
    Exit = -2,
    ERROR = -1,
    From_head = 0,
    From_tail = 1
};

enum list_teams{
    cmd_push = 0,
    cmd_pop = 1
};


void DUMP_MIN(const char * function, int line);
void list_ctor( LIST * list, int count_elements, const Elem_t * text, const int len);
void list_real(LIST * list);
void checking_rise(int * number, int capacity);
void checking_down(int * number, int capacity);
int list_push(LIST * list, Elem_t value, int command);
void list_status(const LIST * list, int line, const char * fun);
Elem_t list_pop(LIST * list, const int command_place);
int my_strcmp(const char * string1, const char * string2);
int checking_cmd(const char * cmd);
int get_args(const char * string, Elem_t * value, const int command);
int list_work(LIST * list, const char * string);
void list_read_stdin(LIST * list);
void get_null(char * string);
Elem_t * ft_calloc(const int size);
void text_push(LIST * list, const Elem_t * text, const int array_size);
void poison_input(Elem_t * array, const int head, const int tail);
FILE * file_open_writing(const char * file_name);
void graphic_dump(LIST * list, FILE * stream);
void checking_rise_ar(int * number, int capacity);
void list_push_tail(LIST * list);
void list_push_middle(LIST * list, const int command_place);
void list_push_head(LIST * list);
int searching_place(int * array, int elem_logical, int head);
