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

//작업 스케줄링 기본 알고리즘 구현
//작업 스케줄링의 쓰임새 : 작업 배치, 스케줄하는 게임?


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
	int min = 0; //가장 빨리 작업이 끝나는 기계 맨 처음엔 첫번째 기계로 설정
	char person;

	for (int i = 0; i < machine_count; i++)
	{
		machine[i] = 0; //기계의 초기화를 먼저한다.
	}

	for (int j = 0; j < task_count; j++) //작업이 가장 빨리 끝나는 기계를 찾기
	{
		min = 0;

		for (int k = 0; k < machine_count; k++)
		{
			if (machine[k] < machine[min]) //현재 기계 작업시간과 현재 제일 빨리 끝나는 기계의 작업시간을 비교
			{
				min = k; //min값은 i로 조종해야하나?
			}
		}
		machine[min] += task[j]; //작업 배정 완료
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
	printf("일단 초짜니까 가벼운 것부터 시작해보자. 작업이랑 인원 붙여줄테니까 한번 해봐."); Sleep(100); gotoxy(x, y++);
	getchar(); gotoxy(x, y++);
	printf("■■■■■■■   작업 리스트  ■■■■■■■■"); gotoxy(x, y++);
	printf("■          인원 : A,B,C,D  총 4명          ■"); gotoxy(x, y++);
	printf("■   작업량 : 40시간을 10개로 나눠서 조율.  ■"); gotoxy(x, y++);
	printf("■      늦게 끝낸 사람 순으로 인원 정리     ■"); gotoxy(x, y++);
	printf("■   세부 작업 조율 : 5,2,4,3,4,7,8,2,4,1   ■"); gotoxy(x, y++);
	printf("■■■■■■■■■■■■■■■■■■■■■■■"); gotoxy(x, y++);

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
		printf("■■■■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 5);
		printf("■         작업 %d는 누구에게 맡길까?        ■", task[i]); gotoxy(0, 6);
		printf("■■■■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 7);

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

	printf("■■■■■■■ 내가 짠 결과 ■■■■■■■■■"); gotoxy(0, 4);
	printf("■■■■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 5);
	printf("■       가장 늦게 끝나는 시간 : %d         ■", result); gotoxy(0, 6);
	printf("■       가장 늦게 끝나는 사람 : %c         ■", person); gotoxy(0, 7);
	printf("■■■■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 8);
	gotoxy(0, 9);
	gotoxy(0, 10);
	printf("■■■■■■■ 기계가 짠 결과 ■■■■■■■■"); gotoxy(0, 11);
	printf("■■■■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 12);
	printf("■       가장 늦게 끝나는 시간 : %d         ■", alg_result); gotoxy(0, 13);
	printf("■■■■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 14);
	Sleep(10000);

	system("cls");

	if (result == alg_result || result < alg_result)
	{
		printf("■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 4);
		printf("■처음인데 잘하는데? 한번 더 시켜볼게 ■"); gotoxy(0, 5);
		printf("■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 6);
	}
	else
	{
		printf("■■■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 4);
		printf("■ 좀 아쉽다.. 다시 연습하고 와서 해보자  ■"); gotoxy(0, 5);
		printf("■■■■■■■■■■■■■■■■■■■■■■"); gotoxy(0, 6);
		exit(0);
	}
}

int main()
{
	Stage1();
}