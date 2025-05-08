#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

// Константы для позиций в строке
const int XX = 58;
const int YY = 64;
const int FF = 44;
const int DD = 51;
const int PR = 20;
const int WW = 25;
const int MAX_MODEL_LEN = 21;

// Структура для хранения данных ноутбука
struct NoteBook {
    struct DisplayRes {
        int x;
        int y;
    } display;
    int frequency;  // f, Hz
    float diagonal; // d, inches
    int price;      // price, $
    std::string model;

    // Метод для вывода данных
    friend std::ostream& operator<<(std::ostream& os, const NoteBook& nb) {
        return os << nb.model << " " << nb.diagonal << " " << nb.display.x << " "
                  << nb.display.y << " " << nb.frequency << " " << nb.price;
    }
};

// Функция для извлечения подстроки из массива
std::string extractField(const std::string& input, int startPos) {
    std::string result;
    for (int i = startPos; i < input.length(); ++i) {
        if (input[i] == ' ' || input[i] == 'x' || input[i] == '\0') break;
        result += input[i];
    }
    return result;
}

// Чтение данных из текстового файла и запись в бинарный
void processFile(const std::string& inputPath, const std::string& outputPath, int threshold) {
    std::ifstream input(inputPath);
    std::ofstream output(outputPath, std::ios::binary);
    
    if (!input.is_open() || !output.is_open()) {
        throw std::runtime_error("Ошибка открытия файла");
    }

    std::vector<NoteBook> notebooks;
    std::string line;

    while (std::getline(input, line)) {
        NoteBook nb;
        nb.model = line.substr(0, MAX_MODEL_LEN);
        line = line.substr(MAX_MODEL_LEN);

        nb.display.x = std::stoi(extractField(line, XX));
        nb.display.y = std::stoi(extractField(line, YY));
        nb.frequency = std::stoi(extractField(line, FF));
        nb.diagonal = std::stof(extractField(line, DD));
        nb.price = std::stoi(extractField(line, PR));

        // Фильтрация по диагонали
        if (nb.diagonal > threshold) {
            notebooks.push_back(nb);
        }
    }

    // Запись количества записей
    size_t count = notebooks.size();
    output.write(reinterpret_cast<char*>(&count), sizeof(count));

    // Запись данных
    for (const auto& nb : notebooks) {
        output.write(reinterpret_cast<const char*>(&nb), sizeof(nb));
    }
}

// Сортировка и вывод данных
void sortAndDisplay(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка открытия файла для сортировки");
    }

    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    std::vector<NoteBook> notebooks(count);
    file.read(reinterpret_cast<char*>(notebooks.data()), count * sizeof(NoteBook));

    // Сортировка по цене
    std::sort(notebooks.begin(), notebooks.end(), [](const NoteBook& a, const NoteBook& b) {
        return a.price < b.price;
    });

    // Вывод результатов
    std::cout << "       model         d,in  x    y  f,Hz price,$\n";
    std::cout << "----------------------------------------------\n";
    for (const auto& nb : notebooks) {
        std::cout << nb << "\n";
    }
}

int main() {
    try {
        // Первый проход: запись всех подходящих записей
        processFile("d:\\note.txt", "d:\\ksr.bin", 120);
        
        // Вывод отфильтрованных записей
        sortAndDisplay("d:\\ksr.bin");

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
