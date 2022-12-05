#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NODE_NUM_1 6
#define NODE_NUM_2 7
#define NODE_NUM 12
#define GC_MAP_ROW 26
#define GC_MAP_COL 98


// 인접행렬 인접해있다면 1, 그렇지 않으면 0으로 표시
int connectionMatrix_1[NODE_NUM_1][NODE_NUM_1] = {
		{0, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1},
		{0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0}

};
int connectionMatrix_2[NODE_NUM_2][NODE_NUM_2] = {
	{0, 1, 1, 1, 0, 0, 0},
	{1, 0, 1, 1, 1, 0, 0},
	{1, 1, 0, 0, 1, 0, 1},
	{1, 1, 0, 0, 1, 1, 1},
	{0, 1, 1, 1, 0, 1, 0},
	{0, 0, 0, 1, 1, 0, 0},
	{0, 0, 1, 1, 0, 0, 0}
};
int connectionMatrix_3[NODE_NUM][NODE_NUM] = {
	{0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
	{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0},
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0}
};

char* map[GC_MAP_ROW] = {
	("oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"),
	("oaaaaaaaaaaaaaaaaaaaaaaaaaaaaaogggggggggggggggggggggggggggggggggggggollllllllllllllllllllllllllllloo"),
	("oaaaaaaaaaaaaaaaaaaaaaaaaaaaaaogggggggggggggggggggggggggggggggggggggollllllllllllllllllllllllllllloo"),
	("oaaaaaaaaaaaaaaaaaaaaaaaaaaaaaoggggggggggggggggggggggggggggoooooooooooooooooooollllllllllllllllllloo"),
	("oaaaaaaaaaaaaaaaaaaaaaaooooooooooooggggggggggggggggggggggggojjjjjjjjjjjjjjjjjjollllllllllllllllllloo"),
	("oaaaaooooooooooooaaaaaaoffffffffffoggggggggggggggggggggggggojjjjjjjjjjjjjjjjjjollllllllllllllllllloo"),
	("oaaaaobbbbbbbbbbooooooooffffffffffoggggggggggggggggggggggggojjjjjjjjjjjjjjjjjjollllllllllllllllllloo"),
	("oaaaaobbbbbbbbbboeeeeeeoffffffffffoggggggggggggggggggggggggojjjjjjjjjjjjjjjjjjollllllllllllllllllloo"),
	("oaaaaobbbbbbbbbboeeeeeeooooooooooooggggggggggggggggggggggggojjjjjjjjjjjjjjjjjjollllllllllllllllllloo"),
	("oaaaaobbbbbbbbbboeeeeeeeeeeeeogggggggggggggggggggggggggggggoooooooooooooooooooollllllllllllllllllloo"),
	("oaaaaobbbbbbbbbboeeeeeeeeeeeeoggggggggggggggggggggggggggggggggggggggollllllllllllllllllllllllllllloo"),
	("oaaaaobbbbbbbbbboeeeeeeeeeeeeoggggggggggggggggggggggggggooooooooooooooooooooooooollllllllllllllllloo"),
	("oaaaaobbbbbbbbbboeeeeeeeeeeeeogggggggggggggoooooooooooggoiiiiiiiiiiiiiiiiiiiiiiiollllllllllllllllloo"),
	("oaaaaooooooooooooeeeeeeeeeeeeogggggggggggggohhhhhhhhhoggoiiiiiiiiiiiiiiiiiiiiiiiollllllllllllllllloo"),
	("oaaaaocccoddddddoeeeeeeeeeeeeooooooooooooooohhhhhhhhhooooiiiiiiiiiiiiiiiiiiiiiiioooooooooooooooooooo"),
	("oaaaaocccoddddddoeeeeeeeeeeeeeeeeeeeeeeeeeeohhhhhhhhhokkoiiiiiiiiiiiiiiiiiiiiiiiokkkkkkkkkkkkkkkkkoo"),
	("oaaaaocccoddddddoeeeeeeeeeeeeeeeeeeeeeeeeeeohhhhhhhhhokkoooooooooooooooooooooooookkkkkkkkkkkkkkkkkoo"),
	("oaaaaocccoddddddoeeeeeeeeeeeeeeeeeeeeeeeeeeohhhhhhhhhokkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkoo"),
	("oaaaaocccoddddddoeeeeeeeeeeeeeeeeeeeeeeeeeeohhhhhhhhhokkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkoo"),
	("oaaaaocccooooooooooooooooooooooooooooooooooohhhhhhhhhokkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkoo"),
	("oaaaaocccccccccccoaaaaaaaaaaaaaaaaaaaaaaaaaohhhhhhhhhokkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkoo"),
	("oaaaaoooooooooooooaaaaaaaaaaaaaaaaaaaaaaaaaohhhhhhhhhokkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkoo"),
	("oaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaoooooooooookkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkoo"),
	("oaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaokkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkoo"),
	("oaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaokkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkoo"),
	("oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"),
};

void setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

/// <summary>
/// node_color 배열에 color를 칠한다.
/// </summary>
/// <param name="node_color">칠한 color를 저장해두기 위한 배열</param>
/// <param name="node_index">칠할 node를 가르키기 위한 변수</param>
/// <param name="color">node에 칠할 색깔</param>
int GraphColoring(int* node_color, int node_index, int color) {
	int promise;
	for (int j = 0; j < NODE_NUM; j++) {
		// 인접 노드에 같은 색이 칠해져 있다면 return한다.
		if (connectionMatrix_3[node_index][j] == 1 && node_color[j] == color+1) {
			node_color[node_index] = -1;
			promise = 0;
			return promise;
		}
	}
	promise = 1;
	node_color[node_index] = color + 1;
	for (int i = 0; i < 10; i++) {
		if (node_color[NODE_NUM - 1] != -1 || GraphColoring(node_color, node_index + 1, i))
			break;
	}

	return promise;
}
/// <summary>
/// KMP 함수에서 patternLength만큼 patternNum을 setColor해서 출력
/// </summary>
/// <param name="patternLength">patternNum이 반복되는 횟수</param>
/// <param name="patternNum">출력할 값</param>
void print_KMP(int patternLength, char patternNum) {
	
	for (int i = 0; i <= patternLength; i++) {
		printf("%c", patternNum);
	}

	return;
}

/// <summary>
/// KMP 알고리즘 : 길이가 M인 문자열 내에 길이가 N인 단어가 있는지 확인하는 알고리즘
/// KMP 알고리즘을 이용해 map을 color 배열에 따라 출력해준다.
/// </summary>
/// <param name="input_color">map의 색깔(0~12), 14:line color</param>
void KMP(int* input_color) {
	for (int i = 0; i < GC_MAP_ROW; i++) {
		int currentCharPoint = 0;
		int dismatchPoint = 0;
		int patternTable[20] = {0, };
		int patternTableIdx = 0;

		while (currentCharPoint+1 <= GC_MAP_COL) {
			// 다음 인덱스 문자와 비교해서 같다면 패턴 테이블 += 1
			if (map[i][currentCharPoint] == map[i][currentCharPoint + 1]) {
				currentCharPoint++;
				patternTable[patternTableIdx]++;
			}
			else { // 같지 않다면
				setColor(input_color[map[i][currentCharPoint] - 'a']);
				print_KMP(patternTable[patternTableIdx], map[i][currentCharPoint]);
				currentCharPoint++;
				patternTableIdx++;
			}
			
		}
		setColor(input_color[map[i][currentCharPoint] - 'a']);
		print_KMP(patternTable[patternTableIdx], map[i][currentCharPoint]);
		setColor(15);
		printf("\n");
	}

	return;
}

/// <summary>
/// 플레이어가 입력한 input_color와 알고리즘을 통해 구한 node_color를 비교하며 정답인지 확인
/// </summary>
/// <param name="node_color">정답에 해당하는 node_color</param>
/// <param name="input_color">플레이어가 입력한 input_color</param>
/// <returns></returns>
int CheckAnswer(int* node_color, int* input_color) {
	int success = 1;
	printf("제출하신 정답입니다.\n");
	Sleep(1000);
	KMP(input_color);
	Sleep(1000);

	printf("정답은...\n");
	Sleep(1000);
	KMP(node_color);



	for (int i = 0; i < NODE_NUM; i++) {
		if (node_color[i] != input_color[i])
			success = 0;
	}

	Sleep(1000);
	if (success == 1)
		printf("축하드립니다! 정답입니다!");
	else
		printf("아쉽지만 오답입니다. 다시 생각해보세요.");

	return success;
}

int main() {
	int success = 1;

	int node_color[15];
	int input_color[15];

	// input_color를 진한 흰색(15)로 초기화
	for (int i = 0; i < 12; i++) {
		input_color[i] = 15;
	}

	input_color[14] = 187;
	node_color[14] = 187;

	for (int i = 0; i < 12; i++) {
		KMP(input_color);
		printf("%c번 칸에 색칠할 색깔(0, 1, 2, 3, 4 ...)을 입력해주세요. (단, 1번 칸에는 0을, 2번 칸에는 1을 칠해주세요.)\n", i + 'a');
		printf(">> ");
		scanf_s(" %d", &input_color[i]);
		input_color[i]++;
		node_color[i] = -1;
		system("cls");
	}

	GraphColoring(node_color, 0, 0);

	CheckAnswer(node_color, input_color);

	return 0;
}
