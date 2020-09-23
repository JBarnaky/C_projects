//	12. ������� ������ �� ��������� ����� �����, ��������� ��� �� ���:
//	� ������ ��������� ��� ������, � �� ������ � �������� �����.
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

void create(SPIS**, SPIS**, int*);  //�������� �������
void view(SPIS*); //�������� �������
void task(SPIS**, SPIS**, int*); // ���������� ������

int main()
{
	setlocale(LC_CTYPE, "Russian");
	system("cls");

	char*yn = (char*)malloc(2 * sizeof(char)); // ��/���
	int n; // ����� ���� case
	int quant = 0, *qu = &quant; //����� ��������� � ������

								 //�������� �������
	begin = NULL; //��� ���������
	printf("�������� �������.\n");
	create(&begin, &end, &quant);

	while (yn[0] != '�')
	{
		fflush(stdin);
		printf("\n�������� ����� ����:\n 1) �������� ������");
		printf("\n 2) ���������� ��������� � ������;");
		printf("\n 3) ��������� ������ �� ���:� ������ ��������� ��� ������, � �� �������������� �����.\n ");

		scanf("%d", &n);

		switch (n)
		{
		case 1: view(begin);break;
		case 2: create(&begin, &end, &quant);
			break;
		case 3: task(&begin, &end, &quant);
			printf("\n	������ � �������� ����� �����������\n");break;
		default: printf("��� ������ ������ � ����\n\n");
		}

	m1:
		fflush(stdin);
		printf("\n �����? �/�:");
		scanf("%c", yn);
		OemToCharA(yn, (LPSTR)yn);
		if (yn[0] != '�'&&yn[0] != '�') goto m1; //EXIT?
	}
	free(yn);
}

//��������/���������� �������
void create(SPIS**begin, SPIS**end, int*qu)
{
	printf("\n ������� ����� ����� (ESC-����� � ����): \n");

	while (1)
	{
		SPIS*t = (SPIS*)malloc(sizeof(SPIS));
		fflush(stdin);
		scanf("\n %d", &t->info); //���� ������ �����
		t->next = NULL; //������� ���������� � ����� �������
		if (*begin == NULL) //���� ��� ������ � ������������ ������� � �������
			*begin = *end = t; //��������� ������ � ����� ��������� ����� �������� �������� 
		else
		{
			(*end)->next = t; // ����� ��������� �� ���� ������� � �������� �������� ������. �������� ��������
			*end = t;
		} // ��������� ����� ������� ��������� ����� �������� ��������
		(*qu)++; // ��������� �������� ����� � �������
		if (_getch() == 27)	//ESC-����� �� �����
			break;
	}
}

//�������� �������
void view(SPIS*begin)
{
	SPIS*t = begin; // ��������� �� ������� ������� ������ ����� ������ �������  
	if (begin == NULL) // �������� �������
	{
		puts("\n������ ����!");
		_getch();
		return;
	}
	while (t != NULL) //���� t �� ������ ����� �������
	{
		printf(" %d", t->info); // ����� ������
		t = t->next;
	} // t ��������� ����� ��������� ��������
}

//������
void task(SPIS**begin, SPIS**end, int*qu)
{
	int i = 0;
	int*mas = (int*)malloc((*qu) * sizeof(int)); //��������� ������
												 //��������
	SPIS*t = *begin; //� ������
	if (begin == NULL)
	{
		puts("\n������ ����!");
		_getch();
		return;
	}
	//������� ��������� �� ������ � ������
	//�������� �����
	while (t != NULL)
	{
		if (!(t->info % 2))
		{
			*(mas + i) = t->info;
			i++;
		}
		t = t->next;
	}

	//������ �����
	t = *begin; //����� � ������
	while (t != NULL)
	{
		if (t->info % 2)
		{
			*(mas + i) = t->info;
			i++;
		}
		t = t->next;
	}

	//������ ����� �������� � �������
	t = *begin; //����� � ������

	for (int i = 0;i<*qu;i++)
	{
		t->info = *(mas + i);
		t = t->next;
	}

	free(mas);
}