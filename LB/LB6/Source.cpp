#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <ctype.h>

void mod(char* str)
{
	int i, len;
	char c = '&';

	len = strlen(str);

	for (i = 0; i<len; i+=2)
	
		if (str[i] == ' ')
			str[i] = c;
	
		printf("� ������� ��������: %s \n", str);

}

void main()
{
	setlocale(LC_CTYPE, "Russian");

	char *str;
	str = new char[100];

	printf("������� ������ str: \n");
	gets_s(str, 100);

	printf("�� �����: %s \n", str);
	mod(str);
	
	delete[]str;

	_getch();
}
