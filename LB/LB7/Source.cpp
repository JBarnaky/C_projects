#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <locale>

class FileHandler {
public:
    static void writeToFile(const std::string& text) {
        std::ofstream file("text.txt", std::ios::trunc);
        if (!file.is_open()) throw std::runtime_error("Ошибка открытия файла для записи");
        file << text;
    }

    static std::string readFromFile() {
        std::ifstream file("text.txt");
        if (!file.is_open()) throw std::runtime_error("Ошибка открытия файла для чтения");
        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

    static void encrypt(const std::string& input, const std::string& key) {
        std::string encrypted = input;
        char placeholder = '1';
        for (size_t i = 0; i < encrypted.size(); i += 2) {
            if (i < key.size()) {
                encrypted[i] = placeholder;
                key[i] = input[i]; // Сохраняем ключ
            }
        }
        writeToFile(encrypted);
        std::cout << "Зашифровано:\n" << encrypted << std::endl;
    }

    static void decrypt(const std::string& encrypted, const std::string& key) {
        std::string decrypted = encrypted;
        char placeholder = '1';
        for (size_t i = 0; i < decrypted.size(); i += 2) {
            if (i < key.size() && decrypted[i] == placeholder) {
                decrypted[i] = key[i];
            }
        }
        writeToFile(decrypted);
        std::cout << "Дешифровано:\n" << decrypted << std::endl;
    }
};

int main() {
    try {
        std::setlocale(LC_CTYPE, "Russian");
        int choice;
        std::string str, key;

        while (true) {
            std::cout << "Меню:\n"
                      << "1 - Записать текст в файл\n"
                      << "2 - Прочитать текст из файла\n"
                      << "3 - Зашифровать текст\n"
                      << "4 - Дешифровать текст\n"
                      << "5 - Выход\n";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    std::cin.ignore();
                    std::getline(std::cin, str);
                    FileHandler::writeToFile(str);
                    break;
                case 2:
                    str = FileHandler::readFromFile();
                    std::cout << "Содержимое файла:\n" << str << std::endl;
                    break;
                case 3:
                    key.clear(); // Очистка ключа перед использованием
                    str = FileHandler::readFromFile();
                    FileHandler::encrypt(str, key);
                    break;
                case 4:
                    str = FileHandler::readFromFile();
                    FileHandler::decrypt(str, key);
                    break;
                case 5:
                    return 0;
                default:
                    continue;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
