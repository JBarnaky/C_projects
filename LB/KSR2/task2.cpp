//39.Написать программу, в которой на основе разработанных функций осуществля¬ется 
//запись в двоичный файл данных только о тех ноутбуках, тактовая частота процессора которых больше 120 МГц, 
//отсортированные в порядке возрастания цены.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>

//отступы в файле
#define xx 58
#define yy 64 
#define ff 44
#define dd 51
#define pr 20
#define ww 25 
#define m 78 //длина строки в файле

struct NOTEBOOK
{
	struct dlisp_res {	// разрешающая способность дисплея
		int x;	// по горизонтали
		int у;	// по вертикали
	}	a;
	int f;        	// частота регенерации
	float d;       	// размер диагонали дисплея
	int price;     	// цена
	char model[21]; // наименование
}
b, z[16];	//b-буферная переменная для чтения строки из файла и сортировки данных
			//z[16]-массив для хранения и записи данных в bin-файл

char* buf(char*, char*, int); //запись в буф. строку данных о ноутбуке
NOTEBOOK wr_struct(char*, char*, NOTEBOOK*, int*); //запись данных в структуру
void write(int*, FILE*, NOTEBOOK*, char*, char*); //запись из структуры в файл
void read(int*, FILE*, NOTEBOOK); //считывание и вывод

void main()
{
	int n; //позиция параметра в строке списка note.txt
	int count = 0; //счетчик записей
	int*count1 = &count;
	char*mass; //массив для чтения строки из note.txt
	char*h; //массив для записи отдельного параметра ноутбука

	FILE*note, *ksr12;

	setlocale(LC_CTYPE, "Russian");

	if (!(note = fopen("d:\\note.txt", "r")))
	{
		printf("\nError opening file");
		_getch();
		exit(0);
	}

	if (!(ksr12 = fopen("d:\\ksr.bin", "wb")))
	{
		printf("\nError opening file");
		_getch();
		exit(0);
	}

	if (!((mass = new char[m]) && (h = new char[21])))
	{
		printf("\nCouldn't create string");
		_getch();
		exit(0);
	}

	//запись из файла note в структуру, а затем - в файл bin всех записей 
	while (!feof(note))
	{
		fgets(mass, m, note);
		write(&count, ksr12, z, mass, h);
	}

	fclose(ksr12);

	//чтение из bin файла всех записей и вывод на экран
	read(&count, ksr12, b);
	_getch();

	count = 0; //сброс счетчика

	if (!(ksr12 = fopen("d:\\ksr.bin", "wb")))
	{
		printf("\nError opening file");
		_getch();
		exit(0);
	}

	rewind(note); //указатель вначало файла note

//выполнение задачи 
	while (!feof(note))
	{
		fgets(mass, m, note);
		if ((atof(buf(mass, h, ff))>120)) //частота более 120 МГц
			write(&count, ksr12, z, mass, h);
	}

	fclose(ksr12);
	fclose(note);

	//чтение и вывод на экран результата задачи
	printf("\nС частатой более 120 МГц\n");
	read(&count, ksr12, b);
	_getch();

	//сортировка по возрастанию цены
	if (!(ksr12 = fopen("d:\\ksr.bin", "rb")))
	{
		printf("\nError opening file");
		_getch();
		exit(0);
	}

	fread(&count, 2, 1, ksr12);
	fclose(ksr12);

	for (int i = 0;i<count;i++)
		for (int j = i;j<count;j++)
		{
			if (z[i].price>z[j].price)
			{
				b = z[i];
				z[i] = z[j];
				z[j] = b;
			}
		}

	if (!(ksr12 = fopen("d:\\ksr.bin", "wb")))
	{
		printf("\nError opening file");
		_getch();
		exit(0);
	}

	rewind(ksr12); //вначало
	fwrite(count1, 2, 1, ksr12); //запись числа записей
	fseek(ksr12, 0, 2);

	for (int i = 0;i<count;i++)
		fwrite(z + i, sizeof(z[i]), 1, ksr12);

	fclose(ksr12);
	printf("\nОтсортированные по цене\n");
	read(&count, ksr12, b);

	delete(mass);
	delete(h);
	_getch();
}

//запись данных для структуры в буферную строку
char* buf(char*mass, char*h, int n)
{
	for (int i = 0;;i++)
	{
		if (*(mass + n + i) == ' ' || *(mass + n + i) == 'x' || *(mass + n + i) == '\0')
			break;
		*(h + i) = *(mass + n + i);
		*(h + i + 1) = '\0';
	}
	return h;
}

//запись данных в структуру
NOTEBOOK wr_struct(char*mass, char*h, NOTEBOOK*z, int*count1)
{
	for (int i = 0;i<20;i++)	//model
		z[*count1].model[i] = *(mass + i);
	z[*count1].a.x = atoi(buf(mass, h, xx)); //x
	z[*count1].a.у = atoi(buf(mass, h, yy)); //y	
	z[*count1].f = atoi(buf(mass, h, ff));	 //f
	z[*count1].d = atof(buf(mass, h, dd));	 //d
	z[*count1].price = atoi(buf(mass, h, pr)); //price

	return z[*count1];
}

//запись из файла note в структуру, а затем - в файл bin
void write(int*count1, FILE*ksr12, NOTEBOOK*z, char*mass, char*h)
{
	(*count1)++;
	rewind(ksr12); //смещение указателя вначало
	fwrite(count1, 2, 1, ksr12); //запись числа записей
	(*count1)--;

	fseek(ksr12, 0, 2); //сместить указатель вконец
	fwrite(&wr_struct(mass, h, z, count1), sizeof(NOTEBOOK), 1, ksr12);
	(*count1)++;
}

//считывание и вывод числа записей
void read(int*count1, FILE*ksr12, NOTEBOOK b)
{
	if (!(ksr12 = fopen("d:\\ksr.bin", "rb")))
	{
		printf("\nError opening file");
		_getch();
		exit(0);
	}

	fread(count1, 2, 1, ksr12); //чтение числа записей
	printf("%d\n", *count1);
	fseek(ksr12, 2, 0); //смещение на 2 байта

	printf("       model         d,in  x    y  f,Hz price,$\n");
	printf("----------------------------------------------\n");

	//считывание и вывод записей на экран
	while (*count1)
	{
		fread(&b, sizeof(NOTEBOOK), 1, ksr12);
		fflush(stdin);
		printf("%s %.1f %4d %d %d %d\n", b.model, b.d, b.a.x, b.a.у, b.f, b.price);
		(*count1)--;
	}

	fclose(ksr12);
}