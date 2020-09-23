//15. Найти запись с ключом, ближайшим к среднему значению между
//максимальным и минимальным значениями ключей.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <process.h>
#include <conio.h>
#include <io.h>
#include <malloc.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

struct Tree
{
	struct info
	{
		char fio[20];
		int pas_num;
	} pas_data;
	int key;
	Tree *Left, *Right;
};

//Буфферная структура
struct Buffer
{
	int key_b;
	float z; //разница ключа и среднего значения ключа по модулю z=|x-key|
	char fio_b[20];
	int pas_num_b;
} pas_data_b[30], b;

Tree* List(int); //добавление листа дерева
Tree* Make(Tree*); //создание дерева
void Find(Tree*, int); //поиск информации по ключу
void View(Tree*, int); //просмотр информации
Tree* Del(Tree*, int); //удаление узла по ключу
void Middle(Tree*, int*, int*); //данные для среднего значения ключа
void Task(Tree*, float, Buffer*, int*);
int FindMax(Tree*, int);
int FindMin(Tree*, int);

void main()
{
	setlocale(LC_CTYPE, "Russian");
	system("cls");
	char*yn = (char*)malloc(2 * sizeof(char)); // да/нет
	int n; //номер меню case
	int level = 0; //уровень корня
	int fkey; //ключ поиска
	int key_sum = 0, *ukey_sum = &key_sum;
	int quant = 0, *uquant = &quant;
	Tree*Root = NULL; //Указатель корня

	while (yn[0] != 'д')
	{
		fflush(stdin);
		puts("1 – создание дерева");
		puts("2 – добавление новой записи");
		puts("3 – поиск информации по заданному ключу");
		puts("4 – удаление узла с заданным ключом");
		puts("5 – вывод информации");
		puts("6 – Найти запись с ключом, ближайшим к среднему значению между максимальным и минимальным значениями ключей.");
		scanf("%d", &n);

		switch (n)
		{
		case 1: Root = Make(Root); break;
		case 2: Make(Root); break;
		case 3:
		{	fflush(stdin);
		printf("Введите ключ узла: ");
		scanf("%d", &fkey);
		Find(Root, fkey);
		break;	}
		case 4:
		{	fflush(stdin);
		printf("Введите ключ удаляемого узла: ");
		scanf("%d", &fkey);
		Del(Root, fkey);
		break;	}
		case 5: View(Root, level); break;
		case 6:
		{	Middle(Root, &key_sum, &quant); //данные для среднего значения ключа
		float x = (float)key_sum / (float)quant; //вычисление среднего значения ключа
		fflush(stdin);
		printf("\nСреднее значение ключа: %.2f", x);
		quant = 0;
		Task(Root, x, pas_data_b, &quant);

		//сортировка по z=|x-key|
		for (int i = 0; i<quant; i++)
		{
			for (int j = i; j<quant; j++)
				if (pas_data_b[i].z>pas_data_b[j].z)
				{
					b = pas_data_b[i];
					pas_data_b[i] = pas_data_b[j];
					pas_data_b[j] = b;
				}
		}

		printf("\nCтрока с ближайшим к среднему значению ключом %d:\n ФИО:%s | №Паспорта:%d", pas_data_b[0].key_b, pas_data_b[0].fio_b, pas_data_b[0].pas_num_b);
		break;	}
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

//создание нового элемента – листа: 
Tree* List(int i)
{
	Tree*t = (Tree*)malloc(sizeof(Tree)); //адрес нового элемента
	fflush(stdin);
	t->key = i; //вставляем ключ в новый элемент
	printf("Введите ФИО: ");
	scanf("%s", t->pas_data.fio); //вставляем ФИО в новый элемент
	OemToCharA(t->pas_data.fio, (LPSTR)t->pas_data.fio);
	printf("\nВведите номер паспорта: ");
	scanf("%d", &t->pas_data.pas_num); //вставляем № паспорта в новый элемент
	t->Left = t->Right = NULL; //ветвей пока нет
	return t;
}

//создание дерева/добавление элемента
Tree* Make(Tree*Root)
{
	Tree* Prev, *t; //Prev родитель текущего элемента t (предыдущий)
	int b, find; //b-ключ элемента, find-индикатор того, что наёдено подходящее место для нового элемента
	char*yn = (char*)malloc(2 * sizeof(char)); //да/нет

	if (Root == NULL) //Если дерево не создано 
	{
		printf("\nВведите ключ: ");
		scanf("%d", &b);
		Root = List(b);
	m2:
		fflush(stdin);
		printf("Еще? д/н: ");
		scanf("%s", yn);
		OemToCharA(yn, (LPSTR)yn);
		if (*yn == 'н')
			goto m3;
		else
		{
			if (*yn != 'д') goto m2;
		}
	} //Установили указатель на корень

	while (1) //Формируем остальные элементы дерева
	{
		printf("\nВведите ключ: ");
		scanf("%d", &b);
		if (b<0) break; //Признак выхода число <0
		t = Root; //Текущий указатель на корень
		find = 0; // Признак поиска

		while (t && !find) //пока не упремся в элемент без ветви
		{
			Prev = t;
			if (b == t->key) 	find = 1; //Ключи должны быть уникальны
			else
				if (b<t->key) t = t->Left;
				else   t = t->Right;
		}

		if (!find) //Нашли место с адресом Prev
		{
			Prev = t;
			t = List(b); //Создаем новый узел
			if (b<Prev->key) //и присоединяем его, либо
				Prev->Left = t; //на левую ветвь,
			else Prev->Right = t;
		} //либо на правую ветвь
	m1:
		fflush(stdin);
		printf("Еще? д/н: ");
		scanf("%s", yn);
		OemToCharA(yn, (LPSTR)yn);
		if (*yn == 'н')
			break;
		else
		{
			if (*yn != 'д') goto m1;
		}
	} //Конец цикла
m3:
	delete(yn);
	return Root;
}

//поиск и вывод информации по ключу
void Find(Tree*t, int fkey)
{
	if (t)
	{
		Find(t->Right, fkey);
		if (t->key == fkey)
			printf("\nЭлемент с ключом %d: %d %s %d\n", fkey, t->key, t->pas_data.fio, t->pas_data.pas_num);
		Find(t->Left, fkey);
	} //Вывод левого поддерева
}

//удаление узла по ключу
Tree* Del(Tree*Root, int fkey)
{
	Tree*Del, *Prev_Del, *R, *Prev_R; //Del, Prev_Del – удаляемый элемент и его предыдущий (родитель); 
									  //R, Prev_R – элемент, на который заменяется удаленный, и его родитель;
	Del = Root;
	Prev_Del = NULL;
	// ===== Поиск удаляемого элемента и его родителя по ключу key =====
	while (Del != NULL&&Del->key != fkey)
	{
		Prev_Del = Del;
		if (Del->key>fkey)
			Del = Del->Left;
		else Del = Del->Right;
	}

	if (Del == NULL) //Элемент не найден
	{
		puts("\n NO Key!");
		return Root;
	}
	// ============ Поиск элемента R для замены =================
	if (Del->Right == NULL)
		R = Del->Left;
	else
		if (Del->Left == NULL)
			R = Del->Right;
		else
		{
			Prev_R = Del; //Ищем самый правый узел в левом поддереве
			R = Del->Left;
			while (R->Right != NULL)
			{
				Prev_R = R;
				R = R->Right;
			}
			if (Prev_R == Del) //Нашли элемент для замены R и его родителя Prev_R
				R->Right = Del->Right;
			else
			{
				R->Right = Del->Right;
				Prev_R->Right = R->Left;
				R->Left = Prev_R;
			}
		}

	if (Del == Root)
		Root = R; //Удаляя корень, заменяем его на R
	else
		if (Del->key<Prev_Del->key)
			Prev_Del->Left = R; //на левую ветвь
		else
			Prev_Del->Right = R; //на правую ветвь

	printf("\nУдален элемент с ключом %d\n", Del->key);
	free(Del);
	return Root;
}

//вывод информации
void View(Tree*t, int level)
{
	if (t)
	{
		View(t->Right, level + 1); //Вывод правого поддерева
		for (int i = 0; i<level; i++)
			printf("    ");
		printf("ключ:%d | ФИО:%s | №Паспорта:%d\n", t->key, t->pas_data.fio, t->pas_data.pas_num);
		View(t->Left, level + 1);
	} //Вывод левого поддерева
}

//вычисление среднего значения ключа
void Middle(Tree*t, int*ukey_sum, int*uquant)
{
	if (t)
	{
		Middle(t->Right, ukey_sum, uquant);
		*(ukey_sum) += t->key;
		*(uquant) = *(uquant)+1;
		Middle(t->Left, ukey_sum, uquant);
	}
	//return (float)(*(ukey_sum))/(float)(*(uquant));
}

//задание
void Task(Tree*t, float x, Buffer*pas_data_b, int*uquant)
{
	if (t)
	{
		Task(t->Right, x, pas_data_b, uquant);
		pas_data_b[*(uquant)].z = fabs(x - (float)t->key); //вычитаем от среднего значения ключей значение ключа, берем по модулю и записываем в элемент
														   //записываем данные из элемента дерева в буферную структуру
		pas_data_b[*(uquant)].key_b = t->key;
		strcpy(pas_data_b[*(uquant)].fio_b, t->pas_data.fio);
		pas_data_b[*(uquant)].pas_num_b = t->pas_data.pas_num;

		*(uquant) = *(uquant)+1;
		Task(t->Left, x, pas_data_b, uquant);
	}
	printf("max: %d\n", FindMax(t, t->key));
	printf("min: %d\n", FindMin(t, t->key));
}

int FindMax(Tree*t, int max)
{
	if (t->key > max) max = t->key;
	if (t->Left != NULL)
		max = FindMax(t->Left, max);
	if (t->Right != NULL)
		max = FindMax(t->Right, max);
	return max;
}

int FindMin(Tree*t, int min)
{
	if (t->key < min) min = t->key;
	if (t->Left != NULL)
		min = FindMax(t->Left, min);
	if (t->Right != NULL)
		min = FindMax(t->Right, min);
	return min;
}