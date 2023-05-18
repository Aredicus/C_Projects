#include "lab23.h"

int main() {
    printf("ПОГНАЛИ!\n");
    printf("С чего начнем?\n");
    int stage;
    node *Node = NULL;
    while (1) {
        rules();
        if (scanf("%d", &stage) == 1) {
            int value1, value2;
            switch (stage) {
                case 1:
                    printf("Введите вершину дерева: ");
                    if (scanf("%d", &value1) == 1) {
                        if (Node != NULL) {
                            delTree(&Node);
                        }
                        Node = initTree(value1);
                    } else {
                        error();
                    }
                    break;
                case 2:
                    if (Node != NULL) {
                        printf("Введите куда добавлять и добавляемую вершину: ");
                        if (scanf("%d %d", &value1, &value2) == 2) {
                            addNode(Node, value1, value2);
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
                        if (scanf("%d", &value1) == 1) {
                            if (Node->value == value1) {
                                printf("Вы точно хотите удалить дерево? (y/n)");
                                fflush(stdin);
                                char c = getchar();
                                if (c == 'y') {
                                    delTree(&Node);
                                }
                            } else {
                                delNode(Node, value1);
                            }
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
                        printf("Нет дерева\n");
                        error();
                    }
                    break;
                case 7:
                    if (Node != NULL) {
                        delTree(&Node);
                    }
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