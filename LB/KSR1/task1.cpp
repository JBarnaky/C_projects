#include <stdio.h> 
#include <conio.h>
#include <locale.h> 
#include <process.h>
#include <string.h>
#include <Windows.h>

void menu(); //
FILE* openFile(char*);
void readAndWriteword();

void main()
{
	setlocale(LC_CTYPE, "Russian");
	system("cls");
	fflush(stdin);

	menu(); //вызов функции 
}
//Меню программы
void menu()
{
	int n = 0; //инициализация переменной
	puts("Выберите следующее действие:\n 1 - Вывод текста из файла на экран. Вывод количества слов в файле. \n 2 - Выход");//вывод сообщения на экран
	scanf_s("%d", &n);//ввод номера команды

	switch (n)//выбор введенной программы
	{
	case 1: {readAndWriteword(); break; } //вывод текста и подсчет слов
	case 2: {return; }//выход
	default: menu(); //возвращение в меню
	}
}

// Функция считывает и выводит содержание файла, а так же выводит количество предложений
void readAndWriteword()
{
	fflush(stdin);
	char word; //объявление переменной
	int count = 0; //инициализация переменной
	char symble[70] = ".?!"; //массив с пробелом
	FILE *f; // объявление переменной
	char *str = new char[70]; //массив символов
	
	f = openFile("d:\\asd.dat"); //вызов функции для открытия файла



	puts("\n Содержимое файла \n"); //вывод на экран
	
	if (!feof(f)) //если конец файла
	{
		word = fgetc(f); //считывание символа из файла

		if (strchr(symble, word) != NULL) //поиск символов конца предложения
		{
			count++; //+1
		}
		while (!feof(f)) //пока не конец файла
		{
			printf("%c", word); //вывод символа
			{
				if (!feof(f)) //если не конец файла
				{
					word = fgetc(f); //считывание теста из файла

					if (strchr(symble, word) != NULL) //если символ конца предложения 
					{
						count++; //+1
					}
				}
			}
		}
		puts("\n"); //вывод на экран
		printf("%s", "Количество предложений:"); //вывод на экран
		printf("%d", count); //вывод на экран
		puts("\n"); //вывод на экран
	}
	else
	{
		puts("Файл пуст!"); //вывод на экран
	}

	fclose(f); //закрытие документа
	delete[]str; //удаление массива

	menu(); //переход в меню
}
// Функция открытия файла 
FILE* openFile(char* name)

{
	setlocale(LC_CTYPE, "Russian");
	system("cls");
	fflush(stdin);

	FILE* f; // объявление переменной
	if ((fopen_s(&f, name, "r")) != 0) //если не удалось открыть файл
	{
		printf("Ошибка открытия файла\n"); //вывод на экран
		menu(); //переход в меню
	}
	else
	{
		return f; //возвращение переменной с сылкой на открываемый файл
	}
}