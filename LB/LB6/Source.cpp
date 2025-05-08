#include <iostream>
#include <string>
#include <locale>

void mod(std::string& str) {
    const char replacement = '&';
    for (size_t i = 0; i < str.length(); i += 2) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main() {
    // Установка русской локали
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::setlocale(LC_CTYPE, "ru_RU.UTF-8");

    std::string input;
    std::cout << "Введите строку: ";
    std::getline(std::cin, input);

    std::cout << "Вы ввели: " << input << std::endl;

    mod(input);
    std::cout << "С заменой пробелов: " << input << std::endl;

    return 0;
}
