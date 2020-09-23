//39.�������� ���������, � ������� �� ������ ������������� ������� ��������������� 
//������ � �������� ���� ������ ������ � ��� ���������, �������� ������� ���������� ������� ������ 120 ���, 
//��������������� � ������� ����������� ����.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>

//������� � �����
#define xx 58
#define yy 64 
#define ff 44
#define dd 51
#define pr 20
#define ww 25 
#define m 78 //����� ������ � �����

struct NOTEBOOK
{
	struct dlisp_res {	// ����������� ����������� �������
		int x;	// �� �����������
		int �;	// �� ���������
	}	a;
	int f;        	// ������� �����������
	float d;       	// ������ ��������� �������
	int price;     	// ����
	char model[21]; // ������������
}
b, z[16];	//b-�������� ���������� ��� ������ ������ �� ����� � ���������� ������
			//z[16]-������ ��� �������� � ������ ������ � bin-����

char* buf(char*, char*, int); //������ � ���. ������ ������ � ��������
NOTEBOOK wr_struct(char*, char*, NOTEBOOK*, int*); //������ ������ � ���������
void write(int*, FILE*, NOTEBOOK*, char*, char*); //������ �� ��������� � ����
void read(int*, FILE*, NOTEBOOK); //���������� � �����

void main()
{
	int n; //������� ��������� � ������ ������ note.txt
	int count = 0; //������� �������
	int*count1 = &count;
	char*mass; //������ ��� ������ ������ �� note.txt
	char*h; //������ ��� ������ ���������� ��������� ��������

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

	//������ �� ����� note � ���������, � ����� - � ���� bin ���� ������� 
	while (!feof(note))
	{
		fgets(mass, m, note);
		write(&count, ksr12, z, mass, h);
	}

	fclose(ksr12);

	//������ �� bin ����� ���� ������� � ����� �� �����
	read(&count, ksr12, b);
	_getch();

	count = 0; //����� ��������

	if (!(ksr12 = fopen("d:\\ksr.bin", "wb")))
	{
		printf("\nError opening file");
		_getch();
		exit(0);
	}

	rewind(note); //��������� ������� ����� note

//���������� ������ 
	while (!feof(note))
	{
		fgets(mass, m, note);
		if ((atof(buf(mass, h, ff))>120)) //������� ����� 120 ���
			write(&count, ksr12, z, mass, h);
	}

	fclose(ksr12);
	fclose(note);

	//������ � ����� �� ����� ���������� ������
	printf("\n� �������� ����� 120 ���\n");
	read(&count, ksr12, b);
	_getch();

	//���������� �� ����������� ����
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

	rewind(ksr12); //�������
	fwrite(count1, 2, 1, ksr12); //������ ����� �������
	fseek(ksr12, 0, 2);

	for (int i = 0;i<count;i++)
		fwrite(z + i, sizeof(z[i]), 1, ksr12);

	fclose(ksr12);
	printf("\n��������������� �� ����\n");
	read(&count, ksr12, b);

	delete(mass);
	delete(h);
	_getch();
}

//������ ������ ��� ��������� � �������� ������
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

//������ ������ � ���������
NOTEBOOK wr_struct(char*mass, char*h, NOTEBOOK*z, int*count1)
{
	for (int i = 0;i<20;i++)	//model
		z[*count1].model[i] = *(mass + i);
	z[*count1].a.x = atoi(buf(mass, h, xx)); //x
	z[*count1].a.� = atoi(buf(mass, h, yy)); //y	
	z[*count1].f = atoi(buf(mass, h, ff));	 //f
	z[*count1].d = atof(buf(mass, h, dd));	 //d
	z[*count1].price = atoi(buf(mass, h, pr)); //price

	return z[*count1];
}

//������ �� ����� note � ���������, � ����� - � ���� bin
void write(int*count1, FILE*ksr12, NOTEBOOK*z, char*mass, char*h)
{
	(*count1)++;
	rewind(ksr12); //�������� ��������� �������
	fwrite(count1, 2, 1, ksr12); //������ ����� �������
	(*count1)--;

	fseek(ksr12, 0, 2); //�������� ��������� ������
	fwrite(&wr_struct(mass, h, z, count1), sizeof(NOTEBOOK), 1, ksr12);
	(*count1)++;
}

//���������� � ����� ����� �������
void read(int*count1, FILE*ksr12, NOTEBOOK b)
{
	if (!(ksr12 = fopen("d:\\ksr.bin", "rb")))
	{
		printf("\nError opening file");
		_getch();
		exit(0);
	}

	fread(count1, 2, 1, ksr12); //������ ����� �������
	printf("%d\n", *count1);
	fseek(ksr12, 2, 0); //�������� �� 2 �����

	printf("       model         d,in  x    y  f,Hz price,$\n");
	printf("----------------------------------------------\n");

	//���������� � ����� ������� �� �����
	while (*count1)
	{
		fread(&b, sizeof(NOTEBOOK), 1, ksr12);
		fflush(stdin);
		printf("%s %.1f %4d %d %d %d\n", b.model, b.d, b.a.x, b.a.�, b.f, b.price);
		(*count1)--;
	}

	fclose(ksr12);
}