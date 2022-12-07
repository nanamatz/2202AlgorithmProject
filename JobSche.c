#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "test.h"
#define MACHINE 100
#define TASK 100

//�۾� �����ٸ� �⺻ �˰��� ����
//�۾� �����ٸ��� ���ӻ� : �۾� ��ġ, �������ϴ� ����?


int Bigger(int num[])
{

	for (int i = 0; i < num; i++)
	{
		if(num[i] > num[i+1])
		{
			return num[i];
		}
	}
}

int JobSchedule(int machine[], int task[], int machine_count, int task_count)
{
	int min = 0; //���� ���� �۾��� ������ ��� �� ó���� ù��° ���� ����
	char person;

	for (int i = 0; i < machine_count; i++)
	{
		machine[i] = 0; //����� �ʱ�ȭ�� �����Ѵ�.
	}

	for (int j = 0; j < task_count; j++) //�۾��� ���� ���� ������ ��踦 ã��
	{
		min = 0;

		for (int k = 0; k < machine_count; k++)
		{
			if (machine[k] < machine[min]) //���� ��� �۾��ð��� ���� ���� ���� ������ ����� �۾��ð��� ��
			{
				min = k; //min���� i�� �����ؾ��ϳ�?
			}
		}
		machine[min] += task[j]; //�۾� ���� �Ϸ�
	}
	return Bigger(machine);
}


void gotoxy(int x, int y)

{
	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_Story()
{
	int x = 1, y = 1;
	gotoxy(x, y++);
	printf("�ϴ� ��¥�ϱ� ������ �ͺ��� �����غ���. �۾��̶� �ο� �ٿ����״ϱ� �ѹ� �غ�."); Sleep(100); gotoxy(x, y++);
	getchar(); gotoxy(x, y++);
	printf("��������   �۾� ����Ʈ  ���������"); gotoxy(x, y++);
	printf("��          �ο� : A,B,C,D  �� 4��          ��"); gotoxy(x, y++);
	printf("��   �۾��� : 40�ð��� 10���� ������ ����.  ��"); gotoxy(x, y++);
	printf("��      �ʰ� ���� ��� ������ �ο� ����     ��"); gotoxy(x, y++);
	printf("��   ���� �۾� ���� : 5,2,4,3,4,7,8,2,4,1   ��"); gotoxy(x, y++);
	printf("������������������������"); gotoxy(x, y++);

}

void Stage1()
{
	int Person[4] = { 0,0,0,0 };
	int task[10] = { 5,2,4,3,4,7,8,2,4,1 };
	char input;
	char person = '\0';
	int Person_count = 4;
	int task_count = 10;
	int result = 0;
	int alg_result = 0;
	int min = 0;
	int i = 0;
	int x = 1, y = 1;

	alg_result = JobSchedule(Person, task, Person_count, task_count);

	print_Story(); Sleep(500);
	system("cls");
	while (i < task_count)
	{
		printf("������������������������"); gotoxy(0, 5);
		printf("��         �۾� %d�� �������� �ñ��?        ��", task[i]); gotoxy(0, 6);
		printf("������������������������"); gotoxy(0, 7);

		input = getchar();
		getchar();

		switch (input)
		{
		case 'A':
			Person[0] += task[i];
			break;
		case 'B':
			Person[1] += task[i];
			break;
		case 'C':
			Person[2] += task[i];
			break;
		case 'D':
			Person[3] += task[i];
			break;
		default:
			break;
		}
		i++;

		system("cls");
	}

	result = Bigger(Person);

	if (result == Person[0])
	{
		person = 'A';
	}
	else if (result == Person[1])
	{
		person = 'B';
	}
	else if (result == Person[2])
	{
		person = 'C';
	}
	else if (result == Person[3])
	{
		person = 'D';
	}

	printf("�������� ���� § ��� ����������"); gotoxy(0, 4);
	printf("������������������������"); gotoxy(0, 5);
	printf("��       ���� �ʰ� ������ �ð� : %d         ��", result); gotoxy(0, 6);
	printf("��       ���� �ʰ� ������ ��� : %c         ��", person); gotoxy(0, 7);
	printf("������������������������"); gotoxy(0, 8);
	gotoxy(0, 9);
	gotoxy(0, 10);
	printf("�������� ��谡 § ��� ���������"); gotoxy(0, 11);
	printf("������������������������"); gotoxy(0, 12);
	printf("��       ���� �ʰ� ������ �ð� : %d         ��", alg_result); gotoxy(0, 13);
	printf("������������������������"); gotoxy(0, 14);
	Sleep(10000);

	system("cls");

	if (result == alg_result || result < alg_result)
	{
		printf("���������������������"); gotoxy(0, 4);
		printf("��ó���ε� ���ϴµ�? �ѹ� �� ���Ѻ��� ��"); gotoxy(0, 5);
		printf("���������������������"); gotoxy(0, 6);
	}
	else
	{
		printf("�����������������������"); gotoxy(0, 4);
		printf("�� �� �ƽ���.. �ٽ� �����ϰ� �ͼ� �غ���  ��"); gotoxy(0, 5);
		printf("�����������������������"); gotoxy(0, 6);
		exit(0);
	}
}

int main()
{
	Stage1();
}