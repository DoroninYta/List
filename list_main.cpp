// This is a hash friendly list with normal graphic dump

// DOT COMPILE
// dot dump.dot -Tpng -o IMG.png


/*what i am need to do

    make push head
    make normal function pop
    make array sorting mode and into the struct list new int variable, which will be keep info about sorting
    POP
    */

#include "list_function.cpp"

int main()
{   
    struct LIST list1 = {0};        // проверить head tail
    printf("------------------------\n------------------------\n------------------------\n"
            "------------------------\n------------------------\n------------------------\n");
    printf("1\n");
    Elem_t array[1] = {10};
    list_ctor(&list1, 15, array, sizeof(array)/sizeof(Elem_t));
  //  text_push(&list1, array, sizeof(array)/sizeof(Elem_t));
    FILE * stream = file_open_writing("dump_new.dot");
    list_status_(&list1);
    list_push(&list1, 1, 1);
    list_push(&list1, 2, 1);
    list_push(&list1, 3, 1);
    list_status_(&list1);
    list_push(&list1, 5, 2);
    list_status_(&list1);
     list_push(&list1, 6, 3);
    list_push(&list1, 7, 1);
    list_status_(&list1);
    list_push(&list1, 8, 5);
    list_push(&list1, 9, 1);
    list_push(&list1, -1, 0);

    // printf("%d",list_pop(&list1, 1));
    // printf("%d",list_pop(&list1, 0));
    // printf("2\n");

    list_status_(&list1);

    graphic_dump(&list1, stream);
    fclose(stream);
    printf("3\n");
    return 0;
}

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
     int i = searching_place(list->ar.next, command_place, list->head);
    
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



Elem_t list_pop(LIST * list, const int command_place)
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
        int i = searching_place(list->ar.next, command_place, list->head);
        printf("\n\n\n\ncommand_place = %d, i = %d\n\n\n\n", command_place, i);
        ret_val = list->ar.data[i];

        list->ar.next[list->ar.prev[i]] = list->ar.next[i];
        list->ar.prev[list->ar.next[i]] = list->ar.prev[i];  

        list->ar.data[i] = POISON;

        return ret_val;
    }

    return POISON;
}

//! search physical element, which correlation with logical, second - elems, which can be filled, third list->head
int searching_place(int * array, int elem_logical, int head)
{
   int i = head;
     
    for(int elem = 1; elem < elem_logical; elem++)
        i = array[i];
    return i;
}








//     Elem_t ret_val = POISON;
//     printf("command int list_pop = %d\n", command);
//     if (command == From_head)  //0
//     {  
//         // printf("\n-----------------\n\nlist_pop working uncorrect\n\n");
//         checking_rise(&list->head, list->capacity);
//         ret_val = list->ar.data[list->head];
//         list->ar.data[list->head] = POISON;
//         return ret_val;
//     }
//     else if (command == From_tail) //1
//     {
//         // printf("\n-----------------\n\nlist_pop working normaly\n\n");
//         // printf("list-> tail = %d\n", list->tail);
//         checking_down(&list->tail, list->capacity);
//         ret_val = list->ar.data[list->tail];
//         list->ar.data[list->tail] = POISON;
//         return ret_val;
//     }
//     else 
//     {
//         DUMP
//         printf("incorrect command = %d ", command);
//         printf("\n\n");
//     }
//     return POISON;
// }








    
