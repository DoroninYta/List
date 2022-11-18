#include "list_header.h"

int list_push(LIST * list, Elem_t value, int command_place)
{   
    assert(list);

    if (list->free_tail - list->free_head < 0)
    {
        printf("\n----------------------\nLIST OVERFLOW\n----------------------\n");
        abort();
    }

    list->ar.data[list->free_head] = value;
    
    if (list->free_head == 1)
    {
        list->ar.next[list->free_head] = 0;
        list->ar.prev[list->free_head] = 0;
    }

    if (command_place == From_tail)
        list_push_tail(list);

    else if(command_place == From_head)
        list_push_head(list);

    else
        list_push_middle(list, command_place);

    list->free_head++;

    // printf("\n\n\nfree = %d, tail = %d, data = %d, next = %d, prev = %d\n\n\n", list->free_head, list->tail,
    //        list->ar.data[list->free_tail], list->ar.next[list->free_tail], list->ar.prev[list->free_tail]);

    return 0;
}

void list_push_middle(LIST * list, const int command_place)
{
    int i = find_place(list, command_place);
    
    list->ar.prev[list->free_head] = list->ar.prev[i];
    list->ar.next[list->free_head] = list->ar.next[list->ar.prev[i]];

    list->ar.next[list->ar.prev[i]] = list->free_head;
    list->ar.prev[i] = list->free_head;
}


void list_push_tail(LIST * list)
{
    //list->ar.data[list->tail] = value;
    
    if (list->free_head == 1)
    {
        list->ar.prev[0] = 0;
        list->ar.next[0] = 0;
    }
    else
    {
        list->ar.next[list->tail] = list->free_head;
        list->ar.prev[list->free_head] = list->tail;
        list->ar.next[list->free_head] = 0;
        list->tail = list->free_head;
    }
}   

void list_push_head(LIST * list)
{
    list->ar.prev[list->head] = list->free_head;
    list->ar.next[list->free_head] = list->head;
    list->head = list->free_head;
}



Elem_t list_pop(LIST * list, const int command_place)   //am i need to do lots of function, like in push (push head, tail, middle)?
{   
    Elem_t ret_val = POISON;
    if (list->head == list->tail)
    {     
        printf("\n\nlist is empty\n\n");
        return POISON;
    }

    if (command_place == From_tail)
    {
        ret_val = list->ar.data[list->tail];
        list->ar.next[list->ar.prev[list->tail]] = list->ar.next[list->tail];
        
        list->ar.data[list->tail] = POISON;


        list->tail--;

        return ret_val;
    }

    else if (command_place == From_head)
    {
        ret_val = list->ar.data[list->head];

        list->ar.prev[list->ar.next[list->head]] = list->ar.prev[list->head];
        list->ar.data[list->head] = POISON;
        list->head = list->ar.next[list->head];

        return ret_val;
    }

    else if (command_place <= list->free_head && command_place >= list->head)
    {
        int i = find_place(list, command_place);
        
        ret_val = list->ar.data[i];

        list->ar.next[list->ar.prev[i]] = list->ar.next[i];
        list->ar.prev[list->ar.next[i]] = list->ar.prev[i];  

        list->ar.data[i] = POISON;

        return ret_val;
    }

    return POISON;
}

int find_place(LIST * list, int command_place)
{
    int i = 0;

    if (list->sorted == sorted)
    {
        i = command_place;
        list->sorted = not_sorted;
    }
    else
        i = searching_place(list->ar.next, command_place, list->head);
    
    return i;
}


//! search physical element, which correlation with logical, second - elems, which can be filled, third list->head
int searching_place(int * array, int elem_logical, int head)
{
   int i = head;
     
    for(int elem = 1; elem < elem_logical; elem++)
        i = array[i];
    return i;
}


FILE * file_open_writing(const char * file_name)
{
    FILE * stream = fopen(file_name, "w+");
    if (stream == 0)
    {
        DUMP
        printf("cant open file with name %s", file_name);
        abort();
    }
    return stream;
}


void graphic_dump(LIST * list, FILE * stream)
{
    assert(stream);

    fprintf(stream, "digraph structs {\n    rankdir=LR;\n   edge[style = bold, color = blue];\n   "
            "subgraph info1{\n      "
            "info[shape = record, style = filled, fillcolor = \"grey\", label = \"capacity = %d| head = %d|"
            "tail = %d| free_head = %d | free_tail = %d\"];\n}", list->capacity, list->head,
            list->tail, list->free_head, list->free_tail);

    int i = 0;
    int count_operations = 0;
    while (count_operations < list->free_head)
    {
        fprintf(stream, "   subgraph cluster%d{\n        "
                "first%d[shape = record, style = filled, fillcolor = \"darkolivegreen1\", label = \"data[%d] = %d| { <p%d> prev = %d| <n%d> next = %d}\"];\n}\n  ",
                i, i, i, list->ar.data[i], list->ar.prev[i], list->ar.prev[i], list->ar.next[i], list->ar.next[i]);
        checking_rise(&i, list->capacity);
        count_operations++;
    }
    i = list->head;
    count_operations = 2;

    while (count_operations < list->free_head)
    {   
        if (i == 0)
            break;
        if (list->ar.data[i] != POISON)
        {
            fprintf(stream, "first%d:<n%d>->", i, list->ar.next[i]);
            if (count_operations == list->capacity -1)
            i = 0;
        
             fprintf(stream, "first%d:<p%d>;\n    ", list->ar.next[i], list->ar.prev[list->ar.next[i]]);
        }
        count_operations++;
        i = list->ar.next[i];
    }

    fprintf(stream, "}");
} 


void DUMP_MIN(const char * function, int line)
{
    printf("line %d     function name %s\n", line, function);
}

void list_status(const LIST * list, int line, const char * fun)
{   
    printf("\n\n-----------------------------\nLIST STATUS WORK:\nLine = %d    in function: %s\n", line, fun);
    printf("list.head = %d  |  list.tail = %d   |   list.capacity = %d\n", list->head, list->tail, list->capacity);
    printf("list.free_head = %d list.free_tail = %d\n", list->free_head, list->free_tail);
    int i = 0;
    
    while (i < list->capacity)                                            
    {   
        printf("|||DATA[%d] = %d    |   NEXT{%d] = %d   |   PREV[%d] = %d|||",
               i, list->ar.data[i], i, list->ar.next[i], i, list->ar.prev[i]);
        if (list->ar.data[i] == -429)
            printf(" POISON");
        printf("\n");
        i++;
    }  

}       

void list_ctor( LIST * list, int count_elements, const Elem_t * text, const int len)
{
    assert(list);

    list->capacity = count_elements;
    list->ar.data = ft_calloc(count_elements);
    list->ar.next = (int *)calloc(list->capacity, sizeof(list->ar.next[0]));
    list->ar.prev = (int *)calloc(list->capacity, sizeof(list->ar.prev[0]));
    
    assert(list->ar.data);
    assert(list->ar.next);
    assert(list->ar.prev);
    
    list->head = 1;
    list->tail = 1;
    list->free_head = 1;
    list->free_tail = count_elements - 1;
    list->ar.prev[0] = 0;
    list->ar.next[0] = 0;
    list->sorted = not_sorted;

    //poison_input(list->ar.data, list->free_head, list->free_capacity);
    text_push(list, text, len);
}

void poison_input(Elem_t * array, const int head, const int tail)
{
    int i = head - 1;
    
    while(i < tail)
    {
        array[i++] = POISON;
    }
        
}

Elem_t * ft_calloc(const int size)
{
    Elem_t * string = (Elem_t *)calloc(size, sizeof(string[0]));
    if (string == NULL)
    {
        printf("memory wasn't given by calloc\n");
        abort();
    }
    return string;
}

void text_push(LIST * list, const Elem_t * text, const int array_size)
{
    printf("array_ssize = %d\n", array_size);
    for(int i = 0; i < array_size; checking_rise(&i, list->capacity))
        list_push(list, text[i], From_tail);
}    



void list_real(LIST * list)
{   
    assert(list);

    list->capacity+=5;

    Elem_t * realloc_checker = (Elem_t *)realloc(list->ar.data, (list->capacity) * sizeof(realloc_checker));
    if (realloc_checker == NULL)
    {
        DUMP
        abort();
    }

    list->ar.data = realloc_checker;
}

void checking_down(int * number, int capacity)
{
    if (*number <= 1)
        *number = capacity - 1;
    else
        (*number)--;
}

void checking_rise(int * number, int capacity)
{
    if (*number >= capacity - 1)
        *number = 1;
    else
        (*number)++;
}

void checking_rise_ar(int * number, int capacity)
{
    if (*number >= capacity - 1)
        *number = 0;
    else
        (*number)++;
}

void list_sorting(LIST * list)
{
    Elem_t * sort_data = ft_calloc(list->capacity);
    int * sort_next = (int * )calloc(list->capacity, sizeof(sort_next[0]));
    int * sort_prev = (int * )calloc(list->capacity, sizeof(sort_prev[0]));

    assert(sort_data); 
    assert(sort_next);
    assert(sort_prev);

    int i = 1;
    while (i < list->capacity)
    {
        sort_data[i] = list->ar.data[list->head];
        if (i != list->capacity - 1)
            sort_next[i] = i + 1;
        else 
            sort_next[i] = 0;    
        sort_prev[i] = i - 1;
        i++;
        list->head = list->ar.next[list->head];
    }
    
    list->sorted = sorted;
    list->head = 1;
    list->tail = list->free_head - 1;
    list->ar.data = sort_data;
    list->ar.prev = sort_prev;
    list->ar.next = sort_next;
};
