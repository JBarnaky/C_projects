#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

// Функция для ввода элементов матрицы
void inputMatrix(int n, int m, std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << "matrix[" << i << "][" << j << "] = ";
            std::cin >> matrix[i][j];
        }
    }
}

// Функция для вывода матрицы
void outputMatrix(int n, int m, const std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// Функция для вычисления произведения элементов главной диагонали
void productDiagonal(int n, int m, const std::vector<std::vector<int>>& matrix) {
    if (n != m) {
        std::cerr << "Матрица не квадратная, произведение диагонали невозможно." << std::endl;
        return;
    }

    int product = 1;
    for (int i = 0; i < n; ++i) {
        product *= matrix[i][i];
    }
    std::cout << "Произведение диагонали = " << product << std::endl;
}

int main() {
    int n, m;

    std::cout << "Введите количество строк матрицы: ";
    std::cin >> n;

    std::cout << "Введите количество столбцов матрицы: ";
    std::cin >> m;

    // Использование std::vector для автоматического управления памятью
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));

    inputMatrix(n, m, matrix);
    outputMatrix(n, m, matrix);
    productDiagonal(n, m, matrix);

    std::cin.get(); // Замена getch() для портируемости
    return 0;
}
