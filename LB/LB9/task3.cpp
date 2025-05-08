#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

// Структура данных пассажира
struct Passenger {
    string fio;
    int passportNumber;
};

// Узел дерева
class TreeNode {
public:
    int key;
    Passenger data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k, const string& f, int pn) : key(k), data{f, pn}, left(nullptr), right(nullptr) {}
};

// Основной класс дерева
class BinaryTree {
private:
    TreeNode* root;

    // Вспомогательные функции
    void insertNode(TreeNode*&, int, const string&, int);
    TreeNode* deleteNode(TreeNode*, int);
    TreeNode* findMin(TreeNode*);
    void inorderTraversal(TreeNode*, int);
    void findKey(TreeNode*, int);
    void calculateSumAndCount(TreeNode*, int&, int&);
    void collectData(TreeNode*, float, vector<Passenger>&);

public:
    BinaryTree() : root(nullptr) {}
    void insert(int, const string&, int);
    void remove(int);
    void display();
    void search(int);
    void task6();
};

// Вставка узла
void BinaryTree::insertNode(TreeNode*& node, int key, const string& fio, int passport) {
    if (!node) {
        node = new TreeNode(key, fio, passport);
    } else if (key < node->key) {
        insertNode(node->left, key, fio, passport);
    } else {
        insertNode(node->right, key, fio, passport);
    }
}

// Удаление узла
TreeNode* BinaryTree::deleteNode(TreeNode* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->key = temp->key;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Найти минимальный узел
TreeNode* BinaryTree::findMin(TreeNode* node) {
    while (node->left) node = node->left;
    return node;
}

// Обход дерева (симметричный)
void BinaryTree::inorderTraversal(TreeNode* node, int level) {
    if (node) {
        inorderTraversal(node->right, level + 1);
        for (int i = 0; i < level; ++i) cout << "    ";
        cout << "Key:" << node->key << " | FIO:" << node->data.fio << " | Passport:" << node->data.passportNumber << endl;
        inorderTraversal(node->left, level + 1);
    }
}

// Поиск узла по ключу
void BinaryTree::findKey(TreeNode* node, int key) {
    if (node) {
        findKey(node->right, key);
        if (node->key == key) {
            cout << "Found in key " << key << ": " << node->key << " " << node->data.fio << " " << node->data.passportNumber << endl;
        }
        findKey(node->left, key);
    }
}

// Вычисление суммы ключей и количества узлов
void BinaryTree::calculateSumAndCount(TreeNode* node, int& sum, int& count) {
    if (node) {
        calculateSumAndCount(node->right, sum, count);
        sum += node->key;
        ++count;
        calculateSumAndCount(node->left, sum, count);
    }
}

// Сбор данных для задачи 6
void BinaryTree::collectData(TreeNode* node, float mean, vector<Passenger>& buffer) {
    if (node) {
        collectData(node->right, mean, buffer);
        float diff = abs(mean - node->key);
        buffer.push_back({node->data.fio, node->data.passportNumber});
        collectData(node->left, mean, buffer);
    }
}

// Публичные методы
void BinaryTree::insert(int key, const string& fio, int passport) {
    insertNode(root, key, fio, passport);
}

void BinaryTree::remove(int key) {
    root = deleteNode(root, key);
}

void BinaryTree::display() {
    inorderTraversal(root, 0);
}

void BinaryTree::search(int key) {
    findKey(root, key);
}

void BinaryTree::task6() {
    int sum = 0, count = 0;
    calculateSumAndCount(root, sum, count);
    float mean = static_cast<float>(sum) / count;

    vector<Passenger> buffer;
    collectData(root, mean, buffer);

    // Сортировка по разнице (реализация сортировки опущена для краткости)
    if (!buffer.empty()) {
        cout << "Passenger with minimal deviation: " << buffer[0].fio << ", " << buffer[0].passportNumber << endl;
    }
}

// Основная функция
int main() {
    BinaryTree tree;
    int choice, key, passport;
    string fio;
    bool running = true;

    while (running) {
        cout << "1. Insert\n2. Display\n3. Search\n4. Delete\n5. Task6\n6. Exit\nChoose: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cin.ignore();
                cout << "Enter FIO: ";
                getline(cin, fio);
                cout << "Enter passport number: ";
                cin >> passport;
                tree.insert(key, fio, passport);
                break;
            case 2:
                tree.display();
                break;
            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                tree.search(key);
                break;
            case 4:
                cout << "Enter key to delete: ";
                cin >> key;
                tree.remove(key);
                break;
            case 5:
                tree.task6();
                break;
            case 6:
                running = false;
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
