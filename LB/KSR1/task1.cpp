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

	menu(); //����� ������� 
}
//���� ���������
void menu()
{
	int n = 0; //������������� ����������
	puts("�������� ��������� ��������:\n 1 - ����� ������ �� ����� �� �����. ����� ���������� ���� � �����. \n 2 - �����");//����� ��������� �� �����
	scanf_s("%d", &n);//���� ������ �������

	switch (n)//����� ��������� ���������
	{
	case 1: {readAndWriteword(); break; } //����� ������ � ������� ����
	case 2: {return; }//�����
	default: menu(); //����������� � ����
	}
}

// ������� ��������� � ������� ���������� �����, � ��� �� ������� ���������� �����������
void readAndWriteword()
{
	fflush(stdin);
	char word; //���������� ����������
	int count = 0; //������������� ����������
	char symble[70] = ".?!"; //������ � ��������
	FILE *f; // ���������� ����������
	char *str = new char[70]; //������ ��������
	
	f = openFile("d:\\asd.dat"); //����� ������� ��� �������� �����



	puts("\n ���������� ����� \n"); //����� �� �����
	
	if (!feof(f)) //���� ����� �����
	{
		word = fgetc(f); //���������� ������� �� �����

		if (strchr(symble, word) != NULL) //����� �������� ����� �����������
		{
			count++; //+1
		}
		while (!feof(f)) //���� �� ����� �����
		{
			printf("%c", word); //����� �������
			{
				if (!feof(f)) //���� �� ����� �����
				{
					word = fgetc(f); //���������� ����� �� �����

					if (strchr(symble, word) != NULL) //���� ������ ����� ����������� 
					{
						count++; //+1
					}
				}
			}
		}
		puts("\n"); //����� �� �����
		printf("%s", "���������� �����������:"); //����� �� �����
		printf("%d", count); //����� �� �����
		puts("\n"); //����� �� �����
	}
	else
	{
		puts("���� ����!"); //����� �� �����
	}

	fclose(f); //�������� ���������
	delete[]str; //�������� �������

	menu(); //������� � ����
}
// ������� �������� ����� 
FILE* openFile(char* name)

{
	setlocale(LC_CTYPE, "Russian");
	system("cls");
	fflush(stdin);

	FILE* f; // ���������� ����������
	if ((fopen_s(&f, name, "r")) != 0) //���� �� ������� ������� ����
	{
		printf("������ �������� �����\n"); //����� �� �����
		menu(); //������� � ����
	}
	else
	{
		return f; //����������� ���������� � ������ �� ����������� ����
	}
}