
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define DUMP DUMP_MIN(__PRETTY_FUNCTION__, __LINE__);
// может быть лучше сделать LIST_STATUS(list) НЕТ НЕ ЛУЧШЕ

#define list_status_(list) list_status(list, __LINE__, __PRETTY_FUNCTION__) 

typedef int Elem_t;

const int POISON = -429;

struct array {
    Elem_t data;
    int next;
    int prev;
};

struct LIST {
    int head;
    int tail;
    struct array * data;
    struct array * free;
    int capacity;
    int free_head;
    int free_tail;
    int sorted;
};

// struct array * ar = (struct array *)calloc(...)
// ar[10].data = ...
// ar->data = ar;
// ar->next = data + capacity;
// ar->prev = next + capacity; 

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

enum sort_command{
    not_sorted = 0,
    sorted = 1
};

void DUMP_MIN(const char * function, int line);
void list_ctor(LIST * list, int count_elements, const Elem_t * text, const int len);
void list_real(LIST * list); // make static
void checking_rise(int * number, int capacity); // make static
void checking_down(int * number, int capacity); // make static
int list_push(LIST * list, Elem_t value, int command);
Elem_t list_pop(LIST * list, const int command_place);
void list_status(const LIST * list, int line, const char * fun);
Elem_t * ft_calloc(const int size); // make static
void text_push(LIST * list, const Elem_t * text, const int array_size);
void poison_input(Elem_t * array, const int head, const int tail); // make static
void graphic_dump(LIST * list, FILE * stream);

void list_push_tail(LIST * list);
void list_push_middle(LIST * list, const int command_place);
void list_push_head(LIST * list);

int searching_place(int * array, int elem_logical, int head); // make static
void list_sorting(LIST * list);
int find_place(LIST * list, int command_place);

// может быть написать реализацию сразу в list_main.cpp ЗАЧЕМ?
FILE * file_open_writing(const char * file_name);