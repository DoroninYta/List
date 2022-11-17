#include "list_header.h"

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
    list->ar.next = ft_calloc(count_elements);
    list->ar.prev = ft_calloc(count_elements);

    assert(list->ar.data);
    assert(list->ar.next);
    assert(list->ar.prev);
    
    list->head = 1;
    list->tail = 1;
    list->free_head = 1;
    list->free_tail = count_elements - 1;
    list->ar.prev[0] = 0;
    list->ar.next[0] = 0;

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