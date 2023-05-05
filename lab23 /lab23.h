#ifndef LAB23_LAB23_H
#define LAB23_LAB23_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct node {
    int value;
    struct node *left;
    struct node *right;
} typedef node;

struct pair {
    int i;
    int value;
} typedef pair;

node *initTree(int);

void addNode(node *, int);

void delNode(node *, int);

void showTree(node, int);

void delTree(node **);

pair search(node *, int);

void deep(node *);

void rules();

void error();


#endif //LAB23_LAB23_H
