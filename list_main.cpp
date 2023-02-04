// This is a hash friendly list with normal graphic dump

// DOT COMPILE
// dot dump.dot -Tpng -o IMG.png


/*
    static
    structs array and calloc them        исправить на структуры  и коллок структуры , таким образом будет один кусок памяти, с ним уже и работать
    change func push pop on lots small func делать вызов функций push_back push_front & pop...
    change fun sort as on a letter      сртировка, алгоритм сортировки
    
    void ctor(List *list, size_t n = 0);
    void dtor(List *list);
    
    void push_front(List *list, Elem_t value);
    void push_back(List *list, Elem_t value);

    void pop_front(List *list);
    void pop_back(List *list);

    Elem_t* back(List *list);
    Elem_t* front(List *list);

    size_t size(List *list);

    void insert(List *list, struct ar *before_item, Elem_t value);
*/

#include "list_function.cpp"




int main()
{
    struct LIST list1;
    list_ctor(&list1, 10);
    list_status_(&list1);
    list_push_back(&list1, 11);
    list_push_back(&list1, 12);
    list_status_(&list1);
    printf("its working!!!");
    return 0;
}
// int main()
// {   
//     struct LIST list1 = {0};        // проверить head tail
//     printf("------------------------\n------------------------\n------------------------\n"
//             "------------------------\n------------------------\n------------------------\n");
//     printf("1\n");
//     Elem_t array[1] = {10, 11, 12};
//     list_ctor(&list1, 15, array, sizeof(array)/sizeof(Elem_t));
//     FILE * stream = file_open_writing("dump_new.dot");
//     list_status_(&list1);
//     list_push(&list1, 1, 1);
//     list_push(&list1, 2, 1);
//     list_push(&list1, 3, 1);
//     list_status_(&list1);
//     list_push(&list1, 5, 2);
//     list_status_(&list1);
//      list_push(&list1, 6, 3);
//     list_push(&list1, 7, 1);
//     list_status_(&list1);
//     list_push(&list1, 8, 5);
//     list_push(&list1, 9, 1);
//     list_status_(&list1);
//     list_sorting(&list1);       //sorting list



//     // printf("%d",list_pop(&list1, 1));
//     // printf("%d",list_pop(&list1, 0));
//     // printf("2\n");

//     list_status_(&list1);

//     graphic_dump(&list1, stream);
//     fclose(stream);
//     printf("3\n");
//     return 0;
// }


#if 0
#include <list>
void foo() {
    std::list<int> r;
    r.push_back();
    r.push_front();
    r.pop_back();
    r.pop_front();
    r.insert(/*where*/, /*what*/);
}
#endif










    
