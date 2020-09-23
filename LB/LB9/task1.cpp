//	12. Создать список из случайных целых чисел, разделить его на два:
//	в первый поместить все четные, а во второй – нечетные числа.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <process.h>
#include <conio.h>
#include <malloc.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>



struct SPIS
{
	int info;
	SPIS*next;
}
*begin, *end;

void create(SPIS**, SPIS**, int*);  //создание очереди
void view(SPIS*); //просмотр очереди
void task(SPIS**, SPIS**, int*); // выполнение задачи

int main()
{
	setlocale(LC_CTYPE, "Russian");
	system("cls");

	char*yn = (char*)malloc(2 * sizeof(char)); // да/нет
	int n; // номер меню case
	int quant = 0, *qu = &quant; //число элементов в списке

								 //создание очереди
	begin = NULL; //нет элементов
	printf("Создание очереди.\n");
	create(&begin, &end, &quant);

	while (yn[0] != 'д')
	{
		fflush(stdin);
		printf("\nВыберите пункт меню:\n 1) Просмотр списка");
		printf("\n 2) Добавление элементов в список;");
		printf("\n 3) Разделить список на два:в первый поместить все четные, а во второй–нечетные числа.\n ");

		scanf("%d", &n);

		switch (n)
		{
		case 1: view(begin);break;
		case 2: create(&begin, &end, &quant);
			break;
		case 3: task(&begin, &end, &quant);
			printf("\n	Четные и нечетные числа упорядочены\n");break;
		default: printf("Нет такого пункта в меню\n\n");
		}

	m1:
		fflush(stdin);
		printf("\n Выйти? д/н:");
		scanf("%c", yn);
		OemToCharA(yn, (LPSTR)yn);
		if (yn[0] != 'д'&&yn[0] != 'н') goto m1; //EXIT?
	}
	free(yn);
}

//создание/добавление очереди
void create(SPIS**begin, SPIS**end, int*qu)
{
	printf("\n Вводите целые числа (ESC-выход в меню): \n");

	while (1)
	{
		SPIS*t = (SPIS*)malloc(sizeof(SPIS));
		fflush(stdin);
		scanf("\n %d", &t->info); //ввод нового числа
		t->next = NULL; //элемент становится в конец очереди
		if (*begin == NULL) //если это первый и единственный элемент в очереди
			*begin = *end = t; //указатели начала и конца принимают адрес текущего элемента 
		else
		{
			(*end)->next = t; // иначе указатель на след элемент в конечном элементе приним. значение текущего
			*end = t;
		} // указатель конца очереди принимает адрес текущего элемента
		(*qu)++; // инкримент счетчика чисел в очереди
		if (_getch() == 27)	//ESC-выход из цикла
			break;
	}
}

//просмотр очереди
void view(SPIS*begin)
{
	SPIS*t = begin; // указатель на текущий элемент принял адрес начала очереди  
	if (begin == NULL) // проверка очереди
	{
		puts("\nСписок пуст!");
		_getch();
		return;
	}
	while (t != NULL) //пока t не достиг конца очереди
	{
		printf(" %d", t->info); // вывод данных
		t = t->next;
	} // t принимает адрес следущего элемента
}

//задача
void task(SPIS**begin, SPIS**end, int*qu)
{
	int i = 0;
	int*mas = (int*)malloc((*qu) * sizeof(int)); //буфферный массив
												 //проверка
	SPIS*t = *begin; //в начало
	if (begin == NULL)
	{
		puts("\nСписок пуст!");
		_getch();
		return;
	}
	//перенос элементов из списка в массив
	//нечетных чисел
	while (t != NULL)
	{
		if (!(t->info % 2))
		{
			*(mas + i) = t->info;
			i++;
		}
		t = t->next;
	}

	//четных чисел
	t = *begin; //снова в начало
	while (t != NULL)
	{
		if (t->info % 2)
		{
			*(mas + i) = t->info;
			i++;
		}
		t = t->next;
	}

	//запись новых значений в очередь
	t = *begin; //снова в начало

	for (int i = 0;i<*qu;i++)
	{
		t->info = *(mas + i);
		t = t->next;
	}

	free(mas);
}