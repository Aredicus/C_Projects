#include "lab23.h"


node *initTree(int value) {
    node *res = malloc(sizeof(node));
    res->value = value;
    res->left = NULL;
    res->right = NULL;
    return res;
}

void showTree(node tmp, int i) {
    if (i == 0)
        printf("\n\n");
    if (tmp.left != NULL) {
        showTree(*tmp.left, i + 1);
    }
    for (int j = 0; j < i; ++j) printf("\t");
    printf("%d\n", tmp.value);
    if (tmp.right != NULL) {
        showTree(*tmp.right, i + 1);
    }
}

void addNode(node *tmp, int value) {
    if (value > tmp->value) {
        if (tmp->left != NULL) {
            addNode(tmp->left, value);
        } else {
            tmp->left = initTree(value);
        }
    } else if (value < tmp->value) {
        if (tmp->right != NULL) {
            addNode(tmp->right, value);
        } else {
            tmp->right = initTree(value);
        }
    }
}

void delNode(node *tmp, int value) {
    if (tmp != NULL) {
        if (tmp->right != NULL) {
            if (tmp->right->value == value) {
                node *temp = tmp->right;
                tmp->right = tmp->right->left;
                if (tmp->right != NULL) {
                    node *right = tmp->right->right;
                    if (right != NULL) {
                        while (right->right != NULL) right = right->right;
                        right->right = temp->right;
                    } else {
                        right = temp->right;
                    }
                } else {
                    tmp->right = temp->left;
                }
                free(temp);
                return;
            }
        }
        if (tmp->left != NULL) {
            if (tmp->left->value == value) {
                node *temp = tmp->left;
                tmp->left = tmp->left->left;
                if (tmp->left != NULL) {
                    node *right = tmp->left->right;
                    if (right != NULL) {
                        while (right->right != NULL) right = right->right;
                        right->right = temp->right;
                    } else {
                        right = temp->right;
                    }
                } else {
                    tmp->left = temp->right;
                }
                free(temp);
                return;
            }
        }
        if (tmp->value < value && tmp->left != NULL) {
            delNode(tmp->left, value);
        } else if (tmp->value > value && tmp->right != NULL) {
            delNode(tmp->right, value);
        } else if (tmp->value == value) {
            if (tmp->left != NULL)
                tmp->value = tmp->left->value;
            else if (tmp->right != NULL)
                tmp->value = tmp->right->value;
            else {
                delTree(&tmp);
                return;
            }
            delNode(tmp, value);
        }

    } else {
        printf("AHTUNG! Empty tree\n");
    }

}

void delTree(node **Node) {
    node *left = (*Node)->left;
    node *right = (*Node)->right;
    free(*Node);
    *Node = NULL;
    if (left != NULL) {
        delTree(&left);
    }
    if (right != NULL) {
        delTree(&right);
    }
}

pair search(node *Node, int i) {
    pair res;
    pair right;
    pair left;
    if (Node->right == NULL && Node->left == NULL) {
        res.i = i;
        res.value = Node->value;
        return res;
    }
    if (Node->right != NULL) {
        right = search(Node->right, i + 1);
    }
    if (Node->left != NULL) {
        left = search(Node->left, i + 1);
    }
    return right.i > left.i ? right : left;
}

void deep(node *Node) {
    pair res = search(Node, 0);
    printf("deep:%d value:%d\n", res.i + 1, res.value);
}

void rules() {
    printf("\n1. Создать дерево\n");
    printf("2. Добавить вершину\n");
    printf("3. Удалить вершину\n");
    printf("4. Показать дерево\n");
    printf("5. Найти значение нетерминальной вершины дерева с максимальной глубиной\n");
    printf("6. Удалить дерево\n");
    printf("7. Закончить программу\n");
    printf("\nВведите номер нужного пункта\n");
}

void error() {
    printf("Что-то не так. Попробуй ещё раз\n");
    fflush(stdin);
    sleep(1);
}