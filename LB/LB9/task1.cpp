#include <iostream>
#include <vector>
#include <memory>
#include <conio.h>

class Node {
public:
    int info;
    std::unique_ptr<Node> next;

    Node(int val) : info(val), next(nullptr) {}
};

class LinkedList {
private:
    std::unique_ptr<Node> head;
    std::unique_ptr<Node> tail;
    size_t count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~LinkedList() = default; // Удаление через unique_ptr автоматическое

    void create() {
        std::cout << "Enter elements (ESC to exit):" << std::endl;
        while (true) {
            int value;
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 27) break; // ESC
            }

            std::cin >> value;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            auto node = std::make_unique<Node>(value);
            if (!head) {
                head = std::move(node);
                tail = head.get();
            } else {
                tail->next = std::move(node);
                tail = tail->next.get();
            }
            count++;
        }
    }

    void view() const {
        if (!head) {
            std::cout << "List is empty!" << std::endl;
            return;
        }

        for (Node* current = head.get(); current; current = current->next.get()) {
            std::cout << current->info << " ";
        }
        std::cout << std::endl;
    }

    void task() {
        if (!head) {
            std::cout << "List is empty!" << std::endl;
            return;
        }

        std::vector<int> result;
        result.reserve(count);

        // Collect even numbers first
        for (Node* current = head.get(); current; current = current->next.get()) {
            if (current->info % 2 == 0) {
                result.push_back(current->info);
            }
        }

        // Collect odd numbers
        for (Node* current = head.get(); current; current = current->next.get()) {
            if (current->info % 2 != 0) {
                result.push_back(current->info);
            }
        }

        // Update list values
        size_t i = 0;
        for (Node* current = head.get(); current; current = current->next.get()) {
            if (i < result.size()) {
                current->info = result[i++];
            }
        }
    }

    size_t getCount() const { return count; }
};

int main() {
    std::locale::global(std::locale("Russian"));
    std::setlocale(LC_ALL, "");

    LinkedList list;
    char choice;
    bool running = true;

    std::cout << "Create initial list." << std::endl;
    list.create();

    do {
        std::cout << "\nSelect action:\n"
                  << "1) View list\n"
                  << "2) Add elements\n"
                  << "3) Execute task\n"
                  << "Enter your choice (1-3) or 'q' to quit: ";

        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case '1':
                list.view();
                break;
            case '2':
                list.create();
                break;
            case '3':
                list.task();
                std::cout << "List reordered: even numbers first, odd numbers last.\n";
                break;
            case 'q':
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (running);

    return 0;
}
