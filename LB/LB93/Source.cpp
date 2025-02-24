//15. Íàéòè çàïèñü ñ êëþ÷îì, áëèæàéøèì ê ñðåäíåìó çíà÷åíèþ ìåæäó
//ìàêñèìàëüíûì è ìèíèìàëüíûì çíà÷åíèÿìè êëþ÷åé.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Passenger {
    char fio[20];
    int pas_num;
} Passenger;

typedef struct TreeNode {
    int key;
    Passenger data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Buffer {
    int key;
    float z; // |x - key|
    char fio[20];
    int pas_num;
} Buffer;

// Прототипы функций
TreeNode* create_node(int key);
TreeNode* insert_node(TreeNode* root, int key);
TreeNode* delete_node(TreeNode* root, int key);
void find_node(TreeNode* root, int key);
void view_tree(TreeNode* root, int level);
void traverse_and_sum(TreeNode* root, int* key_sum, int* count);
void task(TreeNode* root, float x, Buffer buffer[], int* count);
int find_max(TreeNode* root, int curr_max);
int find_min(TreeNode* root, int curr_min);
void sort_buffer(Buffer buffer[], int count);
void free_tree(TreeNode* root);

int main(void) {
    setbuf(stdout, NULL);
    TreeNode* root = NULL;
    int choice, key, dummy;
    int key_sum = 0, count = 0;
    Buffer buffer[30];
    char yn[3] = "Y"; // Для продолжения работы

    while (yn[0] != 'n' && yn[0] != 'N') {
        printf("\nМеню:\n");
        printf("1. Добавить узел в дерево\n");
        printf("2. Вставить несколько узлов (не используется отдельно)\n");
        printf("3. Поиск узла по ключу\n");
        printf("4. Удалить узел\n");
        printf("5. Вывод дерева\n");
        printf("6. Задание: обработка дерева\n");
        printf("Выберите действие: ");
        if(scanf("%d", &choice) != 1){
            printf("Ошибка ввода!\n");
            exit(EXIT_FAILURE);
        }

        switch (choice) {
            case 1: {
                printf("Введите ключ (целое число): ");
                if (scanf("%d", &key) != 1) {
                    printf("Некорректный ввод\n");
                    break;
                }
                root = insert_node(root, key);
                break;
            }
            case 3: {
                printf("Введите ключ для поиска: ");
                if (scanf("%d", &key) != 1) {
                    printf("Некорректный ввод\n");
                    break;
                }
                find_node(root, key);
                break;
            }
            case 4: {
                printf("Введите ключ для удаления: ");
                if (scanf("%d", &key) != 1) {
                    printf("Некорректный ввод\n");
                    break;
                }
                root = delete_node(root, key);
                break;
            }
            case 5: {
                printf("Дерево:\n");
                view_tree(root, 0);
                break;
            }
            case 6: {
                key_sum = 0;
                count = 0;
                traverse_and_sum(root, &key_sum, &count);
                if (count == 0) {
                    printf("Дерево пустое\n");
                    break;
                }
                float avg = (float)key_sum / count;
                printf("Среднее значение ключей: %.2f\n", avg);
                
                // Сбор данных в буфер
                count = 0;
                task(root, avg, buffer, &count);
                // Сортировка буфера по увеличению z=|x-key|
                sort_buffer(buffer, count);
                if(count > 0) {
                    printf("\nУзел с ключом ближайшим к среднему:\n");
                    printf("Ключ: %d, ФИО: %s, Паспорт: %d\n",
                           buffer[0].key, buffer[0].fio, buffer[0].pas_num);
                }
                break;
            }
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
        printf("\nПродолжить? (Y/N): ");
        scanf("%s", yn);
    }

    free_tree(root);
    return 0;
}

/* Функция создаёт узел дерева и инициализирует данные */
TreeNode* create_node(int key) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    printf("Введите ФИО (до 19 символов): ");
    scanf("%19s", node->data.fio);
    printf("Введите номер паспорта: ");
    scanf("%d", &node->data.pas_num);
    node->left = node->right = NULL;
    return node;
}

/* Функция вставки узла в бинарное дерево поиска.
   При совпадении ключей узел не вставляется. */
TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (key < root->key)
        root->left = insert_node(root->left, key);
    else if (key > root->key)
        root->right = insert_node(root->right, key);
    else
        printf("Узел с ключом %d уже существует.\n", key);
    return root;
}

/* Рекурсивный поиск и вывод узлов с указанным ключом */
void find_node(TreeNode* root, int key) {
    if (root == NULL)
        return;
    if (root->key == key)
        printf("Найден узел: ключ = %d, ФИО = %s, паспорт = %d\n",
               root->key, root->data.fio, root->data.pas_num);
    if (key <= root->key)
        find_node(root->left, key);
    if (key >= root->key)
        find_node(root->right, key);
}

/* Функция поиска минимального узла в правом или левом поддереве */
TreeNode* find_min_node(TreeNode* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

/* Удаление узла по ключу */
TreeNode* delete_node(TreeNode* root, int key) {
    if (root == NULL) {
        printf("Узел с ключом %d не найден.\n", key);
        return NULL;
    }
    if (key < root->key)
        root->left = delete_node(root->left, key);
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    else {
        // Нашли узел для удаления
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            printf("Удалён узел с ключом %d\n", root->key);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            printf("Удалён узел с ключом %d\n", root->key);
            free(root);
            return temp;
        } else {
            // Узел имеет двух детей, находим наименьший узел в правом поддереве
            TreeNode* temp = find_min_node(root->right);
            root->key = temp->key;
            strcpy(root->data.fio, temp->data.fio);
            root->data.pas_num = temp->data.pas_num;
            root->right = delete_node(root->right, temp->key);
        }
    }
    return root;
}

/* Рекурсивная функция для вывода дерева в консоль с отступами */
void view_tree(TreeNode* root, int level) {
    if (root) {
        view_tree(root->right, level + 1);
        for (int i = 0; i < level; i++)
            printf("    ");
        printf("Ключ: %d | ФИО: %s | Паспорт: %d\n", root->key, root->data.fio, root->data.pas_num);
        view_tree(root->left, level + 1);
    }
}

/* Обход дерева для суммирования ключей и подсчета узлов */
void traverse_and_sum(TreeNode* root, int* key_sum, int* count) {
    if (root) {
        traverse_and_sum(root->left, key_sum, count);
        *key_sum += root->key;
        (*count)++;
        traverse_and_sum(root->right, key_sum, count);
    }
}

/* Обход дерева для заполнения буфера данными, вычисляя z = fabs(x - key) */
void task(TreeNode* root, float x, Buffer buffer[], int* count) {
    if (root) {
        task(root->left, x, buffer, count);
        buffer[*count].key = root->key;
        buffer[*count].z = fabs(x - (float)root->key);
        strcpy(buffer[*count].fio, root->data.fio);
        buffer[*count].pas_num = root->data.pas_num;
        (*count)++;
        task(root->right, x, buffer, count);
    }
}

/* Сортировка пузырьком буфера по полю z */
void sort_buffer(Buffer buffer[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (buffer[j].z > buffer[j + 1].z) {
                Buffer tmp = buffer[j];
                buffer[j] = buffer[j + 1];
                buffer[j + 1] = tmp;
            }
        }
    }
}

/* Рекурсивное нахождение максимального значения ключа */
int find_max(TreeNode* root, int curr_max) {
    if (root == NULL)
        return curr_max;
    if (root->key > curr_max)
        curr_max = root->key;
    curr_max = find_max(root->left, curr_max);
    curr_max = find_max(root->right, curr_max);
    return curr_max;
}

/* Рекурсивное нахождение минимального значения ключа */
int find_min(TreeNode* root, int curr_min) {
    if (root == NULL)
        return curr_min;
    if (root->key < curr_min)
        curr_min = root->key;
    curr_min = find_min(root->left, curr_min);
    curr_min = find_min(root->right, curr_min);
    return curr_min;
}

/* Освобождение занятой памяти дерева */
void free_tree(TreeNode* root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}
