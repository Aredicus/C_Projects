#include "lab23.h"

int main() {
    printf("ПОГНАЛИ!\n");
    printf("С чего начнем?\n");
    int stage;
    node *Node = NULL;
    while (1) {
        rules();
        if (scanf("%d", &stage) == 1) {
            int value;
            switch (stage) {
                case 1:
                    printf("Введите вершину дерева: ");
                    if (scanf("%d", &value) == 1) {
                        Node = initTree(value);
                    } else {
                        error();
                    }
                    break;
                case 2:
                    if (Node != NULL) {
                        printf("Введите добавляемую вершину: ");
                        if (scanf("%d", &value) == 1) {
                            addNode(Node, value);
                        } else {
                            error();
                        }
                    } else {
                        printf("Нет дерева\n");
                        error();
                    }
                    break;
                case 3:
                    if (Node != NULL) {
                        printf("Введите удаляемую вершину: ");
                        if (scanf("%d", &value) == 1) {
                            delNode(Node, value);
                        } else {
                            error();
                        }
                    } else {
                        printf("Нет дерева\n");
                        error();
                    }
                    break;
                case 4:
                    if (Node != NULL) {
                        showTree(*Node, 0);
                    } else {
                        printf("Нет дерева\n");
                        error();
                    }
                    break;
                case 5:
                    if (Node != NULL) {
                        deep(Node);
                    } else {
                        printf("Нет дерева\n");
                        error();
                    }
                    break;
                case 6:
                    if (Node != NULL) {
                        delTree(&Node);
                    } else {
                        printf("Его и так нет\n");
                    }
                    break;
                case 7:
                    if (Node != NULL) {
                        delTree(&Node);
                    }
                    printf("Пока!");
                    exit(0);
                default:
                    error();
                    break;
            }
        } else {
            error();
        }
    }
}