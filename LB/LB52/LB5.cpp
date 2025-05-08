#include <iostream>
#include <vector>
#include <cstdlib>  // Для std::abs
#include <locale>
#include <codecvt>

void in(int n, int m, std::vector<std::vector<int>>& a);
void out(int n, int m, const std::vector<std::vector<int>>& a);
void sumdiag(int n, int m, const std::vector<std::vector<int>>& a);

int main() {
    // Установка русской локали для корректного вывода
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale());

    int n, m;
    std::vector<std::vector<int>> A;

    std::wcout << L"Введите количество строк: ";
    if (!(std::wcin >> n) || n <= 0) {
        std::wcerr << L"Ошибка ввода количества строк.\n";
        return 1;
    }

    std::wcout << L"Введите количество столбцов: ";
    if (!(std::wcin >> m) || m <= 0) {
        std::wcerr << L"Ошибка ввода количества столбцов.\n";
        return 1;
    }

    if (n == m) {
        std::wcout << L"Матрица квадратная. Программа завершена.\n";
        std::wcin.get();
        return 0;
    }

    // Инициализация матрицы
    A.resize(n, std::vector<int>(m));

    in(n, m, A);
    out(n, m, A);
    sumdiag(n, m, A);

    std::wcin.get();
    return 0;
}

void in(int n, int m, std::vector<std::vector<int>>& a) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::wcout << L"a[" << i << L"][" << j << L"] = ";
            if (!(std::wcin >> a[i][j])) {
                std::wcerr << L"Ошибка ввода значения.\n";
                exit(EXIT_FAILURE);
            }
        }
    }
}

void out(int n, int m, const std::vector<std::vector<int>>& a) {
    for (int i = 0; i < n; ++i) {
        std::wcout << L"\n";
        for (int j = 0; j < m; ++j) {
            std::wcout << a[i][j] << L"\t";
        }
    }
}

void sumdiag(int n, int m, const std::vector<std::vector<int>>& a) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < m; ++j) {
            sum += std::abs(a[i][j]);
        }
    }
    std::wcout << L"\nСумма модулей элементов выше главной диагонали: " << sum << L"\n";
}
