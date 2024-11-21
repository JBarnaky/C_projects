#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <cstdlib>

void menu();
std::ifstream openFile(const std::string& name);
void readAndWriteWord();

int main() {
    std::locale::global(std::locale("Russian_Russia.1251"));
    system("cls");

    menu(); // Call the menu function
    return 0;
}

// Program menu
void menu() {
    int n = 0; // Initialize variable
    std::cout << "Выберите следующее действие:\n 1 - Вывод текста из файла на экран. Вывод количества слов в файле. \n 2 - Выход\n";
    std::cin >> n; // Input command number

    switch (n) {
        case 1: readAndWriteWord(); break; // Output text and count words
        case 2: return; // Exit
        default: menu(); // Return to menu
    }
}

// Function reads and outputs the content of the file, as well as the number of sentences
void readAndWriteWord() {
    char word;
    int count = 0; // Initialize variable
    const std::string symbols = ".?!"; // Array with sentence delimiters
    std::ifstream f;

    f = openFile("d:\\asd.dat"); // Call the function to open the file

    std::cout << "\n Содержимое файла \n"; // Output to screen

    if (f) {
        while (f.get(word)) { // Read characters from the file
            std::cout << word; // Output character
            if (symbols.find(word) != std::string::npos) { // If the character is a sentence delimiter
                count++; // Increment count
            }
        }
        std::cout << "\nКоличество предложений: " << count << "\n"; // Output the number of sentences
    } else {
        std::cout << "Файл пуст!\n"; // Output if the file is empty
    }

    f.close(); // Close the file
    menu(); // Return to the menu
}

// Function to open the file
std::ifstream openFile(const std::string& name) {
    std::locale::global(std::locale("Russian_Russia.1251"));
    system("cls");

    std::ifstream f(name); // Open the file
    if (!f) {
        std::cout << "Ошибка открытия файла\n"; // Output if the file cannot be opened
        menu(); // Return to the menu
    }
    return f; // Return the file stream
}
