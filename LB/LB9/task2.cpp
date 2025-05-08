#include <iostream>
#include <locale>
#include <conio.h>  // Для _getch()
#include <memory>   // Для std::unique_ptr

using namespace std;

class Node {
public:
    int info;
    Node* next;
    Node* prev;

    Node(int value) : info(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* begin = nullptr;
    Node* end = nullptr;

public:
    ~DoublyLinkedList() {
        clear();
    }

    void create() {
        cout << "\nВведите элементы списка (ESC - завершить): \n";
        
        // Создание первого элемента
        if (begin == nullptr) {
            int value;
            cout << "Значение первого элемента: ";
            cin >> value;
            begin = new Node(value);
            end = begin;
            
            // Проверка на ESC
            if (_getch() == 27) return;
        }

        // Добавление последующих элементов
        while (true) {
            int value;
            cout << "Значение следующего элемента: ";
            cin >> value;
            
            Node* newNode = new Node(value);
            newNode->prev = end;
            end->next = newNode;
            end = newNode;
            
            if (_getch() == 27) break;  // ESC - завершить ввод
        }
    }

    void view() const {
        cout << "\nЭлементы списка: ";
        for (Node* t = begin; t != nullptr; t = t->next) {
            cout << t->info << " ";
        }
        cout << endl;
    }

    void removeMultiplesOfFive() {
        Node* current = begin;
        Node* temp;
        
        while (current != nullptr) {
            Node* nextNode = current->next;
            
            if (current->info % 5 == 0) {
                // Удаление узла
                if (current == begin) {
                    begin = current->next;
                    if (begin != nullptr) {
                        begin->prev = nullptr;
                    }
                }
                
                if (current == end) {
                    end = current->prev;
                    if (end != nullptr) {
                        end->next = nullptr;
                    }
                }
                
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                }
                
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
                
                delete current;
            }
            current = nextNode;
        }
    }

    void clear() {
        while (begin != nullptr) {
            Node* temp = begin;
            begin = begin->next;
            delete temp;
        }
        end = nullptr;
    }

    // Геттеры для тестирования
    Node* getBegin() const { return begin; }
    Node* getEnd() const { return end; }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    DoublyLinkedList list;
    char yn;
    
    cout << "Создание списка.\n";
    list.create();
    
    do {
        system("cls");
        int n;
        
        cout << "\nВыберите действие:\n"
             << "1) Вывести список\n"
             << "2) Добавить элементы\n"
             << "3) Удалить элементы, кратные 5\n"
             << "Выбор: ";
        cin >> n;
        
        switch (n) {
            case 1: list.view(); break;
            case 2: list.create(); break;
            case 3: 
                list.removeMultiplesOfFive(); 
                cout << "\nУдалены элементы, кратные 5\n"; 
                break;
            default: cout << "Неверный выбор\n";
        }
        
        cout << "\nПродолжить? (д/н): ";
        cin >> yn;
        yn = tolower(yn);
        
    } while (yn == 'д');
    
    return 0;
}
