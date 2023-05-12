#ifndef LAB23_LAB23_H
#define LAB23_LAB23_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

struct Set {
    int size;
    int capacity;
    int *values;
} typedef Set;

struct node { // Структура узла
    int value;
    struct node *f_child;
    struct node *children;
    struct node *brothers;
    Set *set;
} typedef node;

struct pair { // Вспомогательная структура пары
    int i;
    int value;
} typedef pair;

node *initTree(int); // Создание нового узла с заданным значением и возвращение на него указателя

void addNode(node *, int, int); // Добавление нового узла (по правилам бинарного дерева)

void delNode(node *, int); // Удаление узла с заданным значением (дерево все равно остается бинарным)

void showTree(node, int); // Вывод текущего дерева в консоль

void delTree(node **); // Удаление дерева (или под дерева)

pair search(node *, int); // Вспомогательная функция для поиска нетерминальной вершины с максимальной глубиной

void deep(node *); // Поиск нетерминальной вершины с максимальной глубиной (по факту обход в глубину)

void rules(); // Вывод правил ввода

void error(); // Вывод ошибки

Set *initSet();

bool addSet(Set *, int);

void delSet(Set *, int);

bool isSet(Set *set, int val);

void destroySet(Set **);

#endif //LAB23_LAB23_H
