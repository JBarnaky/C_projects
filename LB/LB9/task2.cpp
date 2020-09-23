//12. Создать список из случайных целых чисел и удалить все элементы, кратные 5.
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
	SPIS*prev;
}
*begin, *end;

void create(SPIS**, SPIS**);
void view(SPIS*);
void seek_n_destroy(SPIS**, SPIS**);

void main()
{
	setlocale(LC_CTYPE, "Russian");
	system("cls");

	char*yn = (char*)malloc(2 * sizeof(char)); // да/нет
	int n; // номер меню case

		   //создание очереди
	printf("Создание очереди.\n");
	create(&begin, &end);

	while (yn[0] != 'д')
	{
		fflush(stdin);
		printf("\nВыберите пункт меню:\n 1) Просмотр списка");
		printf("\n 2) Добавление элементов в список;");
		printf("\n 3) Удалить все элементы, кратные 5.\n ");

		scanf("%d", &n);

		switch (n)
		{
		case 1: view(begin);break;
		case 2: create(&begin, &end);break;
		case 3: seek_n_destroy(&begin, &end);
			printf("\n	Удалены элементы, кратные 5ти\n");break;
		default: printf("Нет такого пункта в меню\n\n");
		}

	m1:
		fflush(stdin);
		printf("\n Выйти? д/н:");
		scanf("%c", yn);
		OemToCharA(yn, (LPSTR)yn);
		if (yn[0] != 'д'&&yn[0] != 'н') goto m1; //EXIT?
	}

}

//создание списка
void create(SPIS**begin, SPIS**end)
{
	printf("\n Вводите целые числа (ESC-выход в меню): \n");
	//первый элемент
	if (*begin == NULL) // список пуст  
	{
		SPIS*t = (SPIS*)malloc(sizeof(SPIS));
		fflush(stdin);
		scanf("\n %d", &t->info); //ввод нового числа
		t->prev = t->next = NULL;
		*end = *begin = t;
		if (_getch() == 27) return;
	}

	//все остальные элементы
	while (1)
	{
		SPIS*t = (SPIS*)malloc(sizeof(SPIS));
		fflush(stdin);
		scanf("\n %d", &t->info); //ввод нового числа
		t->next = NULL; //элемент становится в конец очереди
		t->prev = *end; //prev указывает на бывший первый
		(*end)->next = t; //последний принимает адрес текущего
		*end = t;
		if (_getch() == 27)	//ESC-выход из цикла
			break;
	}
}
//просмотр с начала
void view(SPIS*begin)
{
	printf("\n");
	SPIS*t = begin;
	while (t != NULL)
	{
		printf("%d ", t->info);
		t = t->next;
	}
}

//удаление элементов, кратных 5ти
void seek_n_destroy(SPIS**begin, SPIS**end)
{
	SPIS*z; // буферная переменная
	SPIS*t = *begin;
	while (t != NULL)
	{
		if (!((t->info) % 5)) //число кратно 5ти
		{
			if (t == *begin) //число вначале списка
			{
				*begin = (*begin)->next;
				(*begin)->prev = NULL;
				free(t);
				t = *begin;
			}

			if (t == *end) //число в конце списка
			{
				*end = (*end)->prev;
				(*end)->next = NULL;
				free(t);
				break;
			}

			if (t != *begin&&t != *end)//число в середине списка
			{
				(t->prev)->next = t->next; //предыд next = текущему next
				z = t->next; //адрес следущего элемента
				(t->next)->prev = t->prev; //след prev = текущему prev
				free(t);
				t = z;
			}
		}
		else t = t->next;
	}
}
