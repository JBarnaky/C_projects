//12. ������� ������ �� ��������� ����� ����� � ������� ��� ��������, ������� 5.
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

	char*yn = (char*)malloc(2 * sizeof(char)); // ��/���
	int n; // ����� ���� case

		   //�������� �������
	printf("�������� �������.\n");
	create(&begin, &end);

	while (yn[0] != '�')
	{
		fflush(stdin);
		printf("\n�������� ����� ����:\n 1) �������� ������");
		printf("\n 2) ���������� ��������� � ������;");
		printf("\n 3) ������� ��� ��������, ������� 5.\n ");

		scanf("%d", &n);

		switch (n)
		{
		case 1: view(begin);break;
		case 2: create(&begin, &end);break;
		case 3: seek_n_destroy(&begin, &end);
			printf("\n	������� ��������, ������� 5��\n");break;
		default: printf("��� ������ ������ � ����\n\n");
		}

	m1:
		fflush(stdin);
		printf("\n �����? �/�:");
		scanf("%c", yn);
		OemToCharA(yn, (LPSTR)yn);
		if (yn[0] != '�'&&yn[0] != '�') goto m1; //EXIT?
	}

}

//�������� ������
void create(SPIS**begin, SPIS**end)
{
	printf("\n ������� ����� ����� (ESC-����� � ����): \n");
	//������ �������
	if (*begin == NULL) // ������ ����  
	{
		SPIS*t = (SPIS*)malloc(sizeof(SPIS));
		fflush(stdin);
		scanf("\n %d", &t->info); //���� ������ �����
		t->prev = t->next = NULL;
		*end = *begin = t;
		if (_getch() == 27) return;
	}

	//��� ��������� ��������
	while (1)
	{
		SPIS*t = (SPIS*)malloc(sizeof(SPIS));
		fflush(stdin);
		scanf("\n %d", &t->info); //���� ������ �����
		t->next = NULL; //������� ���������� � ����� �������
		t->prev = *end; //prev ��������� �� ������ ������
		(*end)->next = t; //��������� ��������� ����� ��������
		*end = t;
		if (_getch() == 27)	//ESC-����� �� �����
			break;
	}
}
//�������� � ������
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

//�������� ���������, ������� 5��
void seek_n_destroy(SPIS**begin, SPIS**end)
{
	SPIS*z; // �������� ����������
	SPIS*t = *begin;
	while (t != NULL)
	{
		if (!((t->info) % 5)) //����� ������ 5��
		{
			if (t == *begin) //����� ������� ������
			{
				*begin = (*begin)->next;
				(*begin)->prev = NULL;
				free(t);
				t = *begin;
			}

			if (t == *end) //����� � ����� ������
			{
				*end = (*end)->prev;
				(*end)->next = NULL;
				free(t);
				break;
			}

			if (t != *begin&&t != *end)//����� � �������� ������
			{
				(t->prev)->next = t->next; //������ next = �������� next
				z = t->next; //����� ��������� ��������
				(t->next)->prev = t->prev; //���� prev = �������� prev
				free(t);
				t = z;
			}
		}
		else t = t->next;
	}
}
