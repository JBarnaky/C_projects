#include <iostream>
#include <vector>
#include <locale>
#include <cstdlib>

void read(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "Введите элемент массива [" << i << "]: ";
        std::cin >> arr[i];
    }
}

void write(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << &arr[i] << " = " << arr[i] << " [" << i << "]\n";
    }
}

void Fmax(const std::vector<int>& arr) {
    int max = 0;
    size_t pm = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] > max) {
            max = arr[i];
            pm = i;
        }
    }
    int sum = 0;
    for (size_t i = 0; i < pm; ++i) {
        if (arr[i] > 0 && arr[i] < max) {
            sum += arr[i];
        }
    }
    std::cout << "\nСумма положительных элементов до максимального " << max << " = " << sum << "\n";
}

int main() {
    try {
        std::locale::global(std::locale("")); // Установка локали
        int M;
        std::cout << "Введите размер массива M: ";
        std::cin >> M;

        if (M <= 0) {
            std::cerr << "Размер массива должен быть положительным.\n";
            return EXIT_FAILURE;
        }

        std::vector<int> A(M);
        std::cout << "\nМассив A:\n";
        read(A);
        write(A);
        Fmax(A);

        std::cout << "\nНажмите Enter для завершения...";
        std::cin.ignore(); // Очистка буфера
        std::cin.get();    // Ожидание ввода
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Неизвестная ошибка.\n";
        return EXIT_FAILURE;
    }

    return 0;
}
