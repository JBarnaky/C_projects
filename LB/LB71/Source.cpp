#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>

void fwr(char* str);
void frd(char* str);
void enc(char* str, char* key);
void dec(char* str, char* key);
void end();

void main()
{
	setlocale(LC_CTYPE, "Russian");

	int num;
	char *str;
	str = new char[100];
	char *key;
	key = new char[100];

	printf("������� �����: \n 1 - ������������ � ���������� ������  � �������� � ���� \n 2 - ������� ������ �� ����� � ����������� \n 3 - ����������� ������ � �������� � ���� \n 4 - ������������ ������ � �������� � ���� \n 5 - ����� \n");
	scanf("%d", &num);
	
	switch (num)
	{
	case 1:fwr(str);
		break;
	case 2:frd(str);
		break;
	case 3:enc(str, key);
		break;
	case 4:dec(str, key);
		break;
	case 5:end();
		break;
	default:
		break;
	}

	_getch();
}

void fwr(char* str)
{
	char sent[100];
	FILE *f;

	if ((f = fopen("I:\\text.txt", "wt"))==NULL)
		printf("���� ���������� ������� \n");
	else
	{
		printf("������� ������ : \n");
		scanf("%s", &sent);

		fgets(sent, 100, stdin);
		fputs(sent, f);
		fclose(f);
	}
}
void frd(char* str)
{
	FILE *f;
	if ((f = fopen("I:\\text.txt", "rt")) == NULL)
		printf("���� ���������� ������� \n");
	else
	{
		fgets(str, 100, f);
		puts(str);
		fclose(f);
	}
}

void enc(char* str, char* key)
{
	int i, len;
	char c = '1';
	char *sent;
	sent = new char[100];

	len = strlen(sent);

	FILE *f = fopen("I:\\text.txt", "wt");

	printf("������� ������ ��� ����������: \n");
	scanf("%s", &sent);

	for (i = 0; i < len; i += 2)
		sent[i] = c;
	
	fgets(sent, 100, stdin);
	fputs(sent, f);

	fclose(f);
}
void dec(char* str, char* key)
{
	int i, len;
	char c = '1';

	len = strlen(str);

	FILE *f;

	if ((f = fopen("I:\\text.txt", "rt")) == NULL)
		printf("���� ���������� ������� \n");
	else
	{
		fgets(str, 100, f);

		for (i = 0; i < len; i += 2)
		{
			if (str[i] = c)
			{
				str[i] = key[i];
			}
		}
	}

	puts(str);

	fclose(f);
}
void end()
{
	printf("����� �� ��������� \n");
	_getch();
	exit(0);
}