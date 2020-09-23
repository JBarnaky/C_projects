//15. ����� ������ � ������, ��������� � �������� �������� �����
//������������ � ����������� ���������� ������.
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

//��������� ���������
struct Buffer
{
	int key_b;
	float z; //������� ����� � �������� �������� ����� �� ������ z=|x-key|
	char fio_b[20];
	int pas_num_b;
} pas_data_b[30], b;

Tree* List(int); //���������� ����� ������
Tree* Make(Tree*); //�������� ������
void Find(Tree*, int); //����� ���������� �� �����
void View(Tree*, int); //�������� ����������
Tree* Del(Tree*, int); //�������� ���� �� �����
void Middle(Tree*, int*, int*); //������ ��� �������� �������� �����
void Task(Tree*, float, Buffer*, int*);
int FindMax(Tree*, int);
int FindMin(Tree*, int);

void main()
{
	setlocale(LC_CTYPE, "Russian");
	system("cls");
	char*yn = (char*)malloc(2 * sizeof(char)); // ��/���
	int n; //����� ���� case
	int level = 0; //������� �����
	int fkey; //���� ������
	int key_sum = 0, *ukey_sum = &key_sum;
	int quant = 0, *uquant = &quant;
	Tree*Root = NULL; //��������� �����

	while (yn[0] != '�')
	{
		fflush(stdin);
		puts("1 � �������� ������");
		puts("2 � ���������� ����� ������");
		puts("3 � ����� ���������� �� ��������� �����");
		puts("4 � �������� ���� � �������� ������");
		puts("5 � ����� ����������");
		puts("6 � ����� ������ � ������, ��������� � �������� �������� ����� ������������ � ����������� ���������� ������.");
		scanf("%d", &n);

		switch (n)
		{
		case 1: Root = Make(Root); break;
		case 2: Make(Root); break;
		case 3:
		{	fflush(stdin);
		printf("������� ���� ����: ");
		scanf("%d", &fkey);
		Find(Root, fkey);
		break;	}
		case 4:
		{	fflush(stdin);
		printf("������� ���� ���������� ����: ");
		scanf("%d", &fkey);
		Del(Root, fkey);
		break;	}
		case 5: View(Root, level); break;
		case 6:
		{	Middle(Root, &key_sum, &quant); //������ ��� �������� �������� �����
		float x = (float)key_sum / (float)quant; //���������� �������� �������� �����
		fflush(stdin);
		printf("\n������� �������� �����: %.2f", x);
		quant = 0;
		Task(Root, x, pas_data_b, &quant);

		//���������� �� z=|x-key|
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

		printf("\nC����� � ��������� � �������� �������� ������ %d:\n ���:%s | ���������:%d", pas_data_b[0].key_b, pas_data_b[0].fio_b, pas_data_b[0].pas_num_b);
		break;	}
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

//�������� ������ �������� � �����: 
Tree* List(int i)
{
	Tree*t = (Tree*)malloc(sizeof(Tree)); //����� ������ ��������
	fflush(stdin);
	t->key = i; //��������� ���� � ����� �������
	printf("������� ���: ");
	scanf("%s", t->pas_data.fio); //��������� ��� � ����� �������
	OemToCharA(t->pas_data.fio, (LPSTR)t->pas_data.fio);
	printf("\n������� ����� ��������: ");
	scanf("%d", &t->pas_data.pas_num); //��������� � �������� � ����� �������
	t->Left = t->Right = NULL; //������ ���� ���
	return t;
}

//�������� ������/���������� ��������
Tree* Make(Tree*Root)
{
	Tree* Prev, *t; //Prev �������� �������� �������� t (����������)
	int b, find; //b-���� ��������, find-��������� ����, ��� ������ ���������� ����� ��� ������ ��������
	char*yn = (char*)malloc(2 * sizeof(char)); //��/���

	if (Root == NULL) //���� ������ �� ������� 
	{
		printf("\n������� ����: ");
		scanf("%d", &b);
		Root = List(b);
	m2:
		fflush(stdin);
		printf("���? �/�: ");
		scanf("%s", yn);
		OemToCharA(yn, (LPSTR)yn);
		if (*yn == '�')
			goto m3;
		else
		{
			if (*yn != '�') goto m2;
		}
	} //���������� ��������� �� ������

	while (1) //��������� ��������� �������� ������
	{
		printf("\n������� ����: ");
		scanf("%d", &b);
		if (b<0) break; //������� ������ ����� <0
		t = Root; //������� ��������� �� ������
		find = 0; // ������� ������

		while (t && !find) //���� �� ������� � ������� ��� �����
		{
			Prev = t;
			if (b == t->key) 	find = 1; //����� ������ ���� ���������
			else
				if (b<t->key) t = t->Left;
				else   t = t->Right;
		}

		if (!find) //����� ����� � ������� Prev
		{
			Prev = t;
			t = List(b); //������� ����� ����
			if (b<Prev->key) //� ������������ ���, ����
				Prev->Left = t; //�� ����� �����,
			else Prev->Right = t;
		} //���� �� ������ �����
	m1:
		fflush(stdin);
		printf("���? �/�: ");
		scanf("%s", yn);
		OemToCharA(yn, (LPSTR)yn);
		if (*yn == '�')
			break;
		else
		{
			if (*yn != '�') goto m1;
		}
	} //����� �����
m3:
	delete(yn);
	return Root;
}

//����� � ����� ���������� �� �����
void Find(Tree*t, int fkey)
{
	if (t)
	{
		Find(t->Right, fkey);
		if (t->key == fkey)
			printf("\n������� � ������ %d: %d %s %d\n", fkey, t->key, t->pas_data.fio, t->pas_data.pas_num);
		Find(t->Left, fkey);
	} //����� ������ ���������
}

//�������� ���� �� �����
Tree* Del(Tree*Root, int fkey)
{
	Tree*Del, *Prev_Del, *R, *Prev_R; //Del, Prev_Del � ��������� ������� � ��� ���������� (��������); 
									  //R, Prev_R � �������, �� ������� ���������� ���������, � ��� ��������;
	Del = Root;
	Prev_Del = NULL;
	// ===== ����� ���������� �������� � ��� �������� �� ����� key =====
	while (Del != NULL&&Del->key != fkey)
	{
		Prev_Del = Del;
		if (Del->key>fkey)
			Del = Del->Left;
		else Del = Del->Right;
	}

	if (Del == NULL) //������� �� ������
	{
		puts("\n NO Key!");
		return Root;
	}
	// ============ ����� �������� R ��� ������ =================
	if (Del->Right == NULL)
		R = Del->Left;
	else
		if (Del->Left == NULL)
			R = Del->Right;
		else
		{
			Prev_R = Del; //���� ����� ������ ���� � ����� ���������
			R = Del->Left;
			while (R->Right != NULL)
			{
				Prev_R = R;
				R = R->Right;
			}
			if (Prev_R == Del) //����� ������� ��� ������ R � ��� �������� Prev_R
				R->Right = Del->Right;
			else
			{
				R->Right = Del->Right;
				Prev_R->Right = R->Left;
				R->Left = Prev_R;
			}
		}

	if (Del == Root)
		Root = R; //������ ������, �������� ��� �� R
	else
		if (Del->key<Prev_Del->key)
			Prev_Del->Left = R; //�� ����� �����
		else
			Prev_Del->Right = R; //�� ������ �����

	printf("\n������ ������� � ������ %d\n", Del->key);
	free(Del);
	return Root;
}

//����� ����������
void View(Tree*t, int level)
{
	if (t)
	{
		View(t->Right, level + 1); //����� ������� ���������
		for (int i = 0; i<level; i++)
			printf("    ");
		printf("����:%d | ���:%s | ���������:%d\n", t->key, t->pas_data.fio, t->pas_data.pas_num);
		View(t->Left, level + 1);
	} //����� ������ ���������
}

//���������� �������� �������� �����
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

//�������
void Task(Tree*t, float x, Buffer*pas_data_b, int*uquant)
{
	if (t)
	{
		Task(t->Right, x, pas_data_b, uquant);
		pas_data_b[*(uquant)].z = fabs(x - (float)t->key); //�������� �� �������� �������� ������ �������� �����, ����� �� ������ � ���������� � �������
														   //���������� ������ �� �������� ������ � �������� ���������
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