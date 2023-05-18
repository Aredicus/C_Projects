#ifndef LAB23_LAB23_H
#define LAB23_LAB23_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

struct Set { // структура множества
    int size; // текущий размер
    int capacity; // максимальный текущий размер
    int *values;
} typedef Set;

struct node { // Структура узла
    int value;
    struct node *children;
    struct node *brothers;
    Set *set;
} typedef node;

struct pair { // Вспомогательная структура пары
    int i;
    int value;
} typedef pair;

node *initTree(int); // Создание нового узла с заданным значением и возвращение на него указателя

void addNode(node *, int, int); // Добавление нового узла (дерево, куда, что)

void delNode(node *, int); // Удаление узла с заданным значением

void showTree(node, int); // Вывод текущего дерева в консоль

void delTree(node **); // Удаление дерева (или под дерева)

pair search(node *, int); // Вспомогательная функция для поиска нетерминальной вершины с максимальной глубиной

void deep(node *); // Поиск нетерминальной вершины с максимальной глубиной (выводит на экран значение и глубины)

void rules(); // Вывод правил ввода

void error(); // Вывод ошибки

Set *initSet(); // инициализация стека

bool addSet(Set *, int); // добавления значения в стек

void sumSet(Set *, Set); // сложение стеков (куда, с чем складывать)

void delSet(Set *, int); // удаление значения в стеке

bool isSet(Set *set, int val); //нет ли значения в стеке (true - нет, false - есть)

void destroySet(Set **); // высвобождение памяти

#endif //LAB23_LAB23_H
