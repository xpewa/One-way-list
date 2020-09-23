#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <Windows.h>

typedef int tData;

typedef struct tNode
{
    tData data;
    struct tNode *next;
} tNode;

typedef struct tList
{
    int size;
    tNode *head;
} tList;

tList * create_list(void)
{
    tList *list = malloc(sizeof(tList));

    list->size = 0;
    list->head = NULL;

    return list;
}

void push_front_list(tList *list, tData data)
{
    tNode *Node = malloc(sizeof(tNode));
    Node->data = data;
    Node->next = list->head;

    list->head = Node;
    list->size += 1;
}

void pop_front_list(tList *list)
{
    if (list->size == 0)
        return 0;

    tNode *tmp = list->head;

    list->head = list->head->next;

    free(tmp);
    list->size -=1;
}

void insert_list(tList *list, int index, tData data)
{
    if (index == 0)
        push_front_list(list, data);

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

void removeAt_list(tList *list, int index)
{
    if (index == 0)
        pop_front_list(list);

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

void clear_list(tList *list)
{
    while(list->size)
        pop_front_list(list);
}

void print_list(tList *list)
{
    system("cls");
    printf("��� �������� � ������� ���� ������� Esc \n"
           "____________________________________________________________\n");

    int i = 1;
    tNode *print_node = list->head;
    while (print_node != NULL)
    {
        printf("%d. %d \n", i, print_node->data);
        i += 1;
        print_node = print_node->next;
    }

    int choice;
    while (choice != 27)
    {
        choice = _getch();
        if (choice == 27)
            startMenu(1, list);
    }
}

void add_node(tList *list)
{
    system("cls");
    printf("��� �������� � ������� ���� ������� Esc \n"
           "____________________________________________________________\n");

    int index = -1;
    printf("������� ����� �������� � ���������� [1;%d] \n", list->size+1);
    while (scanf("%d", &index) != 1 || index < 1 || index > list->size+1)
    {
        scanf("%*[^\n]");
        printf("�� �� ����������! ������� ����� �������� � ���������� [1;%d] \n", list->size+1);
    }

    int data;
    printf("������� ������ (�����) \n");
    while (scanf("%d", &data) != 1)
    {
        printf("������� ������ (�����) \n");
        scanf("%*[^\n]");
    }

    insert_list(list, index-1, data);
    printf("������� ������ ������� ��������!");

    int choice;
    while (choice != 27)
    {
        choice = _getch();
        if (choice == 27)
            startMenu(1, list);
    }
}

void delete_node(tList *list)
{
    system("cls");
    printf("��� �������� � ������� ���� ������� Esc \n"
           "____________________________________________________________\n");

    if (list->size == 0)
        printf("�� � ��� �� ��������� �������? ������ ���.\n");

    else
    {
        int index;
        printf("������� ����� �������� � ���������� [1;%d] \n", list->size);
        printf("���� �� ������ ������� ���� ������, ������� 0 \n");
        while (scanf("%d", &index) != 1 || index < 0 || index > list->size)
        {
            scanf("%*[^\n]");
            printf("�� �� ����������! ������� ����� �������� � ���������� [1;%d] \n", list->size);
        }

        if (index == 0)
        {
            clear_list(list);
            printf("C����� ������� �����!");
        }
        else
        {
            removeAt_list(list, index-1);
            printf("������� ������ ������� �����!");
        }
    }

    int choice;
    while (choice != 27)
    {
        choice = _getch();
        if (choice == 27)
            startMenu(1, list);
    }
}

void startMenu(int switcher, tList *list)
{
    system("cls");

    switch (switcher)
    {
    case 1:
        printf("\n\n\n\n\n\n             < �������� ������� � ������ >\n\n               ������� ������� �� ������\n\n               ������� ������ �� �����");
        break;
    case 2:
        printf("\n\n\n\n\n\n               �������� ������� � ������\n\n             < ������� ������� �� ������ >\n\n               ������� ������ �� �����");
        break;
    case 3:
        printf("\n\n\n\n\n\n               �������� ������� � ������\n\n               ������� ������� �� ������\n\n             < ������� ������ �� ����� >");
        break;
    }

    int choice = -1;
    while (choice != 224 || choice != 0 || choice != 72 || choice != 80 || choice != 13 || choice != 32)
    {
        choice = _getch();
        if (choice == 224 || choice == 0)
            choice = _getch();
        if (choice == 72)
            if (switcher != 1)
                startMenu(switcher - 1, list);
            else
                startMenu(3, list);
        if (choice == 80)
            if (switcher != 3)
                startMenu(switcher + 1, list);
            else
                startMenu(1, list);
        if (choice == 13 || choice == 32)
        {
            if (switcher == 1)
                add_node(list);
            if (switcher == 2)
                delete_node(list);
            if (switcher == 3)
                print_list(list);
        }
    }
}

int main(void)
{
    setlocale(LC_ALL, "rus");
    system("color 74");
    system("title ������� ������");
    system("mode con cols=60 lines=20");
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 100, 0 };
    SetConsoleCursorInfo(hCons, &cursor);/


    tList *list = create_list();
    startMenu(1, list);

    return 0;
}
