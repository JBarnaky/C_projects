#include <iostream>
#include <vector>
#include <limits>

// Функция для ввода элементов массива
void read(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "Введите элемент [" << i << "]: ";
        std::cin >> arr[i];
    }
}

// Функция для вывода элементов массива
void write(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "&arr[" << i << "] = " << &arr[i] << " = " << arr[i] << std::endl;
    }
}

// Функция для поиска максимального положительного элемента и суммы до него
void findMaxAndSum(const std::vector<int>& arr) {
    int maxVal = std::numeric_limits<int>::min();
    size_t maxIndex = 0;
    int sum = 0;

    // Поиск максимального положительного элемента
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] > 0 && arr[i] > maxVal) {
            maxVal = arr[i];
            maxIndex = i;
        }
    }

    // Проверка на наличие положительных элементов
    if (maxVal <= 0) {
        std::cout << "В массиве нет положительных элементов." << std::endl;
        return;
    }

    // Суммирование положительных элементов до maxIndex
    for (size_t i = 0; i < maxIndex; ++i) {
        if (arr[i] > 0) {
            sum += arr[i];
        }
    }

    std::cout << "Сумма положительных элементов до максимального (" << maxVal << ") = " << sum << std::endl;
}

int main() {
    int M;
    std::vector<int> A;

    std::cout << "Введите размер массива M: ";
    std::cin >> M;

    if (M <= 0) {
        std::cerr << "Размер массива должен быть положительным." << std::endl;
        return 1;
    }

    A.resize(M);

    std::cout << "\nВвод массива A:" << std::endl;
    read(A);
    write(A);
    findMaxAndSum(A);

    return 0;
}
