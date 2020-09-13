#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <Windows.h>

typedef int tData; // хранимый тип данных

typedef struct tNode // элемент списка
{
    tData data;
    struct tNode *next;
} tNode;

typedef struct tList // список
{
    int size;
    tNode *head;
} tList;

tList * create_list(void) //создание списка
{
    tList *list = malloc(sizeof(tList));

    list->size = 0;
    list->head = NULL;

    return list;
}

void push_front_list(tList *list, tData data) //добавление элемента в начало списка
{
    tNode *Node = malloc(sizeof(tNode));
    Node->data = data;
    Node->next = list->head;

    list->head = Node;
    list->size += 1;
}

void pop_front_list(tList *list) //удаление элемента из начала
{
    if (list->size == 0)
    {
        return 0;
    }

    tNode *tmp = list->head;

    list->head = list->head->next;

    free(tmp);
    list->size -=1;
}

void insert_list(tList *list, int index, tData data) // вставка элемента по индексу
{
    if (index == 0)
    {
        push_front_list(list, data);
    }
    else
    {
        tNode *previos = list->head;
        for (int i = 0; i < index - 1; i++)
            previos = previos->next;

        tNode *Node = malloc(sizeof(tNode));
        Node->data = data;
        Node->next = previos->next;

        previos->next = Node;
        list->size += 1;
    }
}

void removeAt_list(tList *list, int index) // удаление элемента по индексу
{
    if (index == 0)
    {
        pop_front_list(list);
    }
    else
    {
        tNode *previos = list->head;
        for (int i = 0; i < index - 1; i++)
            previos = previos->next;

        tNode *toDelete = previos->next;

        previos->next = toDelete->next;

        free(toDelete);
        list->size -=1;
    }
}

void clear_list(tList *list) // удаление всего списка
{
    while(list->size)
    {
        pop_front_list(list);
    }
}

void print_list(tList *list) // вывод списка на экран
{
    system("cls");
    printf("Для возврата в главное меню нажмите Esc \n\n");

    int i = 1;//для распечатки
    tNode *print_node = list->head;
    while (print_node != NULL)
    {
        printf("%d. %d \n", i, print_node->data);
        i += 1;
        print_node = print_node->next;
    }

    int choice = _getch();
    if (choice == 27)//если Escape
        startMenu(1, list);
}

void add_node(tList *list) // интерфейс добавления
{
    system("cls");
    printf("Для возврата в главное меню нажмите Esc \n");

    int index;
    printf("Введите номер элемента в промежутке [1;%d] \n", list->size+1);
    scanf("%d", &index);

    int data;
    printf("Введите данные (число) \n");
    scanf("%d", &data);

    insert_list(list, index-1, data);
    printf("Элемент списка успешно добавлен!");

    int choice = _getch();
    if (choice == 27)//если Escape
        startMenu(1, list);
}

void delete_node(tList *list) // интерфейс удаления
{
    system("cls");
    printf("Для возврата в главное меню нажмите Esc \n");

    int index;
    printf("Введите номер элемента в промежутке [1;%d] \n", list->size);
    printf("Если вы хотите удалить весь список, введите 0 \n");
    scanf("%d", &index);

    if (index == 0)
    {
        clear_list(list);
        printf("Cписок успешно удалён!");
    }
    else
    {
        removeAt_list(list, index-1);
        printf("Элемент списка успешно удалён!");
    }

    int choice = _getch();
    if (choice == 27)//если Escape
        startMenu(1, list);
}

void startMenu(int switcher, tList *list) // главное меню
{
    system("cls");

    switch (switcher)//возможные типы текста на экране
    {
    case 1:
        printf("\n\n\n\n\n\n               < ДОБАВИТЬ элемент в список >\n\n               УДАЛИТЬ элемент из списка\n\n               ВЫВЕСТИ список на экран");
        break;
    case 2:
        printf("\n\n\n\n\n\n               ДОБАВИТЬ элемент в список\n\n               < УДАЛИТЬ элемент из списка >\n\n               ВЫВЕСТИ список на экран");
        break;
    case 3:
        printf("\n\n\n\n\n\n               ДОБАВИТЬ элемент в список\n\n               УДАЛИТЬ элемент из списка\n\n               < ВЫВЕСТИ список на экран >");
        break;
    }
    int choice = _getch(); //считанный символ
    if (choice == 224 || choice == 0)//любая стрелка
        choice = _getch();
    if (choice == 72)//вверх
        if (switcher != 1)
            startMenu(switcher - 1, list);
        else
            startMenu(3, list);
    if (choice == 80)//вниз
        if (switcher != 3)
            startMenu(switcher + 1, list);
        else
            startMenu(1, list);
    if (choice == 13 || choice == 32) //пробел
    {
        if (switcher == 1)
            add_node(list);
        if (switcher == 2)
            delete_node(list);
        if (switcher == 3)
            print_list(list);
    }
}

int main(void)
{
    setlocale(LC_ALL, "rus");
    system( "color 74" );
    system("title Связный список");
    system("mode con cols=60 lines=20");


    tList *list = create_list();
    startMenu(1, list);

    return 0;
}
