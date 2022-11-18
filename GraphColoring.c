#include <stdio.h>
#define NODE_NUM_1 6
#define NODE_NUM_2 7
#define NODE_NUM 12

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

/// <summary>
/// node_color 배열에 color를 칠한다.
/// </summary>
/// <param name="node_color">칠한 color를 저장해두기 위한 배열</param>
/// <param name="node_index">칠할 node를 가르키기 위한 변수</param>
int GraphColoring(int* node_color, int node_index, int color) {
	int promise;
	for (int j = 0; j < NODE_NUM; j++) {
		// 인접 노드에 같은 색이 칠해져 있다면 return한다.
		if (connectionMatrix_3[node_index][j] == 1 && node_color[j] == color) {
			node_color[node_index] = -1;
			promise = 0;
			return promise;
		}
	}
	promise = 1;
	node_color[node_index] = color;
	for (int i = 0; i < 10; i++) {
		if (node_color[NODE_NUM - 1] != -1 || GraphColoring(node_color, node_index + 1, i))
			break;
	}

	return promise;
}


int main() {



	// 각 그래프 노드가 가질 color 값, default = -1;
	int node_color[12];
	for (int i = 0; i < 12; i++)
		node_color[i] = -1;

	GraphColoring(node_color, 0, 0);
	for (int i = 0; i < NODE_NUM; i++) {
		printf("%d node : %d color\n", i, node_color[i]);
	}


	return 0;
}