#include "lab23.h"


node *initTree(int value) {
    node *res = malloc(sizeof(node)); // Выделение памяти
    res->value = value; // Начальная инициализация
    res->left = NULL;
    res->right = NULL;
    return res; // Возвращение указателя на созданный узел
}

void showTree(node tmp, int i) {
    if (i == 0)
        printf("\n\n"); // Чтоб отделить от общего вывода
    if (tmp.left != NULL) {
        showTree(*tmp.left, i + 1); // Вызов левых вершин (Они верхние)
    }
    for (int j = 0; j < i; ++j) printf("\t"); // Для понимания уровня узла
    printf("%d\n", tmp.value);
    if (tmp.right != NULL) {
        showTree(*tmp.right, i + 1); // Вызов нижних вершин (Они нижние)
    }
}

void addNode(node *tmp, int value) { // Исключает возможность двух одинаковых вершин
    if (value > tmp->value) { // Ставим в левых потомков, если больше текущего узла
        if (tmp->left != NULL) { // Спускаемся левее
            addNode(tmp->left, value);
        } else { // Ставим на левого потомка
            tmp->left = initTree(value);
        }
    } else if (value < tmp->value) { // Ставим в правого потомка, если меньше текущего узла
        if (tmp->right != NULL) { // Спускаемся правее
            addNode(tmp->right, value);
        } else { // Ставим на правого потомка
            tmp->right = initTree(value);
        }
    }
}

void delNode(node *tmp, int value) {
    if (tmp != NULL) { // Если узел вообще есть
        if (tmp->right != NULL) { // Если есть правые потомки
            if (tmp->right->value == value) { // Если правый потомок - нужный узел
                node *temp = tmp->right; // Делаем указатель на нужный узел
                tmp->right = tmp->right->left; // Ставим новым правым узлом левого потомка предыдущего узла
                if (tmp->right != NULL) { // Если этот потомок вообще был
                    node *right = tmp->right->right; // Спускаемся в самый правый низ новой вершины
                    if (right != NULL) { // Логично, ведь левее предыдущей вершины все точно больше любой вершины справа
                        while (right->right != NULL) right = right->right;
                        right->right = temp->right; // Ставим самым правим потомком правое поддерево удаляемой вершины
                    } else {
                        right = temp->right;
                    }
                } else { // Если не был
                    tmp->right = temp->left;
                }
                free(temp); // Удаляем искомый узел
                return; // чтоб не идти дальше
            }
        }
        if (tmp->left != NULL) { // Если есть левый потомок
            if (tmp->left->value == value) { // алгоритм такой же как и выше
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
        if (tmp->value < value && tmp->left != NULL) { // Если есть левый потомок и искомое значение в той стороне
            delNode(tmp->left, value);
        } else if (tmp->value > value && tmp->right != NULL) { // Если есть правый потомок и искомое значение в той стороне
            delNode(tmp->right, value);
        } else if (tmp->value == value) { // Если искомое значение - вершина дерева
            if (tmp->left != NULL) // Если есть левый потомок
                tmp->value = tmp->left->value; // Ставим на верх вершины левое значение (чтоб сохранить структуру
            else if (tmp->right != NULL) // Ну или хотя бы правый
                tmp->value = tmp->right->value; // Ставим на верх вершины правое
            else { // Тогда срубаем всё дерево
                delTree(&tmp);
                return;
            }
            delNode(tmp, tmp->value); // Удаляем уже выставленную на верх вершину
            // Это работает так, что так как мы сначала проверяем потомков, то первыми мы видим левого или правого потомка
            // Удаляем его, а так как на верхушке стоит его значение, то по факту удалили верхушку
        }

    } else { // ОшибОчка
        printf("AHTUNG! Empty tree\n");
    }

}

void delTree(node **Node) {
    node *left = (*Node)->left; // Чтоб идти по левым потомкам
    node *right = (*Node)->right; // ЧТоб идти по правым потомкам
    free(*Node); // Чистим вершину
    *Node = NULL; // Чтоб точно знать, что дерева больше нет
    if (left != NULL) { // Если были левые потомки
        delTree(&left); // Чистим их
    }
    if (right != NULL) { // Если были правые потомки
        delTree(&right); // Чистим их
    }
}

pair search(node *Node, int i) {
    if (Node->right == NULL && Node->left == NULL) { // Если мы в самой глубокой вершины ветви
        pair res;
        res.i = i;
        res.value = Node->value;
        return res; // Возвращаем пару: текущая глубина и значение узла
    }
    pair right;
    right.i = 0;
    pair left;
    left.i = 0;
    if (Node->right != NULL) { // Если есть правые поддеревья
        right = search(Node->right, i + 1); // Идем искать ниже, увеличивая счетчик глубины
    }
    if (Node->left != NULL) { // Если есть левые поддеревья
        left = search(Node->left, i + 1); // Идем искать ниже, увеличивая счетчик глубины
    }
    return right.i > left.i ? right : left; // Возвращаем пару с самым глубоким значением глубины
}

void deep(node *Node) { // Поиск самого глубокого листа (на максимальной удаленности от вершины)
    pair res = search(Node, 1); // Запуск поиска
    printf("deep:%d value:%d\n", res.i, res.value); // Выводим глубину и само значение
}

void rules() { // Правила
    printf("\n1. Создать дерево\n");
    printf("2. Добавить вершину\n");
    printf("3. Удалить вершину\n");
    printf("4. Показать дерево\n");
    printf("5. Найти значение нетерминальной вершины дерева с максимальной глубиной\n");
    printf("6. Удалить дерево\n");
    printf("7. Закончить программу\n");
    printf("\nВведите номер нужного пункта\n");
}

void error() { // Вывод ошибки
    printf("Что-то не так. Попробуй ещё раз\n");
    fflush(stdin); // Очистка буфера (на всякий)
    sleep(1); // Задержка, чтоб понять, что вообще происходит (френдли интерфейс, все дела)
}
