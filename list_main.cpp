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
    list_status_(&list1);
    list_sorting(&list1);

    // printf("%d",list_pop(&list1, 1));
    // printf("%d",list_pop(&list1, 0));
    // printf("2\n");

    list_status_(&list1);

    graphic_dump(&list1, stream);
    fclose(stream);
    printf("3\n");
    return 0;
}













    
