#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <windows.h>

#define SIZE 5 //정점개수
#define MAPCOL 90//맵크기
#define MAPROW 35 //맵크기
#define INF 1000

#define TRUE 1
#define FALSE 0

//색상
enum {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VOILET,
	DAKR_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;

typedef struct EdgeList {
	Edge** list;
	int size;
}EdgeList; 

//각 정점 가중치
int weight_arr[SIZE][SIZE] = {
{0,1,1,1,1},
{1,0,1,1,1},
{1,1,0,1,1},
{1,1,1,0,1},
{1,1,1,1,0}
};

//통로 : 2, 벽 : 1, 공백 : 0, 정점 : A~Z, 가중치 : a~z
char map[MAPROW][MAPCOL] = {
	{"11111111111111111111111111111111111111111111111111111"},
	{"10000000000000000000000000000000000000000000000000001"},
	{"10000000000000000000000011111000000000000000000000001"},
	{"10000000000000000000002210A01220000000000000000000001"},
	{"10000000000000000000022011111022000000000000000000001"},
	{"10000000000000000000220002020002200000000000000000001"},
	{"10000000000000000002200022022000220000000000000000001"},
	{"10000000000000000022000220002200022000000000000000001"},
	{"10000000000000000220002200000220002200000000000000001"},
	{"10000000000000002200022000000022000222200000000000001"},
	{"100000000000000a20002200000000022000002b0000000000001"},
	{"10000000000000220002200000000000220000022220000000001"},
	{"10000000000002200022000000000000022000000022000000001"},
	{"10000000000022000220000000000000002200000002200000001"},
	{"10000000002220000200000000000000000220000000220000001"},
	{"10000011111000000200000000000000000020000001111100001"},
	{"10000010B01222222222222222e222222222222222210C0100001"},
	{"10000011111000000200000000000000000020000001111100001"},
	{"100000002022000002000000000000000000d0022222020000001"},
	{"10000000200220000c00000000000000000020220000020000001"},
	{"10000000200022000200000000000022222222200000020000001"},
	{"10000000200002200200000000000220000020000000020000001"},
	{"1000000020000022222222g20022h200000020000000020000001"},
	{"10000000200000000200000200200000000020000000020000001"},
	{"100000002000000022000002222220000000200000000i0000001"},
	{"10000000f00000022000000000202222000022000000020000001"},
	{"10000000220000020022222222200002200002000000220000001"},
	{"10000000022000020220000000000000222202000002200000001"},
	{"10000000002201111100000000000000000111110022000000001"},
	{"100000000002210D0122222222j2222222210E012220000000001"},
	{"10000000000001111100000000000000000111110000000000001"},
	{"10000000000000000000000000000000000000000000000000001"},
	{"10000000000000000000000000000000000000000000000000001"},
	{"10000000000000000000000000000000000000000000000000001"},
	{"11111111111111111111111111111111111111111111111111111"}
};

//MST만들 때 root값 저장
int vertex_arr[SIZE] = { 0,1,2,3,4};


// 콘솔 텍스트 색상 변경해주는 함수
void setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}


// edge 함수
void init_edge(Edge* edge, int v1, int v2, int weight);

// edgelist 함수
void insert_edgeList(EdgeList* edgeList, Edge* edge); // edgelist에 edge 추가
void init_edgeList(EdgeList* edgeList, int amount); // edgelist 초기화 (size = 0)
void print_edgeList(EdgeList* edgeList); // edgelist->list의 v1, v2, weight를 출력
void sort_edge(EdgeList* edgeList); // 가중치 기준으로 정렬
int find_edgeList(EdgeList* edgeList, int v); //v에서 출발하는 edge를 찾음
void sort_edge_v1(EdgeList* edgeList);
void delete_edgeList(EdgeList* mst, int index);
// 맵 출력
void print_map(EdgeList* edgeList);

//MST구하는 함수들
int getParent(int x);
int check_union_find(int v1, int v2);
void unionParent(int v1, int v2);
//TSP근사해 구하는 함수들
void insert_edgeList_mst(EdgeList* edgeList, Edge* edge);
void print_path(int path_arr[], int size);

int main() {
	srand(time(NULL)); // 매번 다른 시드값 생성

	system("mode con cols=140 lines=100");

	EdgeList* edgeList = (EdgeList*)malloc(sizeof(EdgeList));

	init_edgeList(edgeList, SIZE);

	// edge 생성
	for (int i = 0; i < SIZE - 1; i++) {
		for (int j = i + 1; j < SIZE; j++) {
			if (weight_arr[i][j] == 1) {
				Edge* new_edge = (Edge*)malloc(sizeof(Edge));
				init_edge(new_edge, i, j, rand() % 9 + 1);
				insert_edgeList(edgeList, new_edge);
			}
		}
	}
	print_edgeList(edgeList);
	print_map(edgeList);

	//MST생성
	sort_edge(edgeList); // 가중치 순으로 정렬
	EdgeList* mst = (EdgeList*)malloc(sizeof(EdgeList));
	init_edgeList(mst, SIZE);
	for (int i = 0; i < edgeList->size; i++) {
		Edge* tmp = edgeList->list[i];
		if (check_union_find(tmp->v1, tmp->v2) != TRUE) {
			insert_edgeList_mst(mst, tmp);
			unionParent(tmp->v1, tmp->v2);
		}
	}
	
	printf("===TSP===\n");
	sort_edge_v1(mst);\
	int path_arr[SIZE];

	EdgeList* stack = (EdgeList*)malloc(sizeof(EdgeList));
	init_edgeList(stack, 0);
	init_edgeList(edgeList, SIZE);
	int cur_vertex = 0;
	int count = 0;
	int tsp_sum = 0;
	while (stack->size >= 0) {
		int index = 0;
		int is_path_input = TRUE;
		//이미 방문했던 곳이면 기록X
		for (int i = 0; i <= count; i++) {
			if (path_arr[i] == cur_vertex) {
				is_path_input = FALSE;
				break;
			}
		}
		if (is_path_input == TRUE) {
			path_arr[count++] = cur_vertex;
		}
		// mst에 현재 위치에서 갈 수 있는 곳이 있다면
		if ((index = find_edgeList(mst, cur_vertex)) != -1) {
			Edge* new_edge = (Edge*)malloc(sizeof(Edge));
			*new_edge = *(mst->list[index]);
			insert_edgeList(stack, new_edge);
			insert_edgeList(edgeList, new_edge);
			cur_vertex = mst->list[index]->v2;
			delete_edgeList(mst, index);
		}
		else {
			if (--stack->size != -1) {
				cur_vertex = stack->list[stack->size]->v1;
			}
		}
	}
	path_arr[count++] = 0;
	print_edgeList(edgeList);
	for (int i = 1; i <= SIZE+1; i++) {
		for (int k = 0; k < edgeList->size; k++) {
			if (edgeList->list[k]->v2 == path_arr[i] && edgeList->list[k]->v1 == path_arr[i - 1]) {
				tsp_sum += edgeList->list[k]->weight;
			}
			if (edgeList->list[k]->v1 == path_arr[i] && edgeList->list[k]->v2 == path_arr[i - 1]) {
				tsp_sum += edgeList->list[k]->weight;
			}
		}
	}

	print_path(path_arr, count);
	printf("tsp_sum : %d\n", tsp_sum);
	int player_input = 0;
	int player_path[SIZE];
	int player_sum = 0;
	player_path[0] = 0;
	count = 1;
	while (count < SIZE) {
		int is_input = TRUE;
		printf("===현재 이동 경로===\n");
		print_path(player_path, count);
		printf("이동 위치 : ");
		scanf("%d", &player_input);
		for (int i = 0; i < SIZE; i++) {
			if (player_path[i] == player_input) {
				printf("이미 간 곳입니다.\n");
				is_input = FALSE;
				break;
			}
		}
		if (is_input == TRUE) {
			player_path[count++] = player_input;
		}
	}
	printf("===현재 이동 경로===\n");
	print_path(player_path, count);
	printf("tsp_sum : %d\n", tsp_sum);
	free(edgeList);
	free(mst);
	free(stack);

	return 0;
 }

void init_edge(Edge* edge, int v1, int v2, int weight) {
	edge->v1 = v1;
	edge->v2 = v2;
	edge->weight = weight;
}

void insert_edgeList(EdgeList* edgeList, Edge* edge) {
	edgeList->list[edgeList->size++] = edge;
}


void init_edgeList(EdgeList* edgeList, int amount) {
	edgeList->size = 0;
	edgeList->list = (Edge**)malloc(sizeof(Edge)*amount);
}

void sort_edge(EdgeList* edgeList) {
	for (int i = 0; i < edgeList->size- 1; i++) {
		for (int j = i + 1; j < edgeList->size; j++) {
			if (edgeList->list[i]->weight > edgeList->list[j]->weight) {
				Edge tmp = *edgeList->list[i];
				*edgeList->list[i] = *edgeList->list[j];
				*edgeList->list[j] = tmp;
			}
		}
	}
}

void sort_edge_v1(EdgeList* edgeList) {
	for (int i = 0; i < edgeList->size - 1; i++) {
		for (int j = i + 1; j < edgeList->size; j++) {
			if (edgeList->list[i]->v1> edgeList->list[j]->v1) {
				Edge tmp = *edgeList->list[i];
				*edgeList->list[i] = *edgeList->list[j];
				*edgeList->list[j] = tmp;
			}
		}
	}
}

void print_edgeList(EdgeList* edgeList) { 
	for (int i = 0; i < edgeList->size; i++) {
		printf("[%d] : %d %d %d\n", i, edgeList->list[i]->v1, edgeList->list[i]->v2, edgeList->list[i]->weight);
	}
}

void print_map(EdgeList* edgeList) {
    int vertex_num = 0;

    for (int i = 0; i < MAPROW; i++) {
        for (int j = 0; j < MAPCOL - 1; j++) {
            vertex_num = map[i][j] - 1;

            switch (map[i][j])
            {
            case '0': printf("　"); break;
            case '2': printf("□"); break;
            case '3': printf("■"); break;
            case '1': printf("■"); break;
            default:
                if ('A' <= map[i][j] && map[i][j] <= 'Z') {
					setColor(RED);
                    printf("%d ", (map[i][j]) - 'A');
					setColor(GRAY);
                }
				if ('a' <= map[i][j] && map[i][j] <= 'z') {
					setColor(GREEN);

					printf("%d ", edgeList->list[map[i][j]-'a']->weight);
					setColor(GRAY);
				}
            }
        }
        printf("\n");
    }

}

int find_edgeList(EdgeList* edgeList, int v) {
	for (int i = 0; i < edgeList->size; i++) {
		if (edgeList->list[i]->v1 == v) {
			return i;
		}
		if (edgeList->list[i]->v2 == v) {
			int tmp = edgeList->list[i]->v1;
			edgeList->list[i]->v1 = edgeList->list[i]->v2;
			edgeList->list[i]->v2 = tmp;
			return i;
		}
	}
	return -1;
}

void insert_edgeList_mst(EdgeList* edgeList, Edge* edge) {
	edgeList->list[edgeList->size++] = edge;
}

int getParent(int x) {
	if (vertex_arr[x] == x) return x;
	return vertex_arr[x] = getParent(vertex_arr[x]);
}

void unionParent(int v1, int v2) {
	v1 = getParent(v1);
	v2 = getParent(v2);
	if (v1 < v2) vertex_arr[v2] = v1;
	else vertex_arr[v1] = v2;
}

int check_union_find(int v1, int v2) {
	v1 = getParent(v1);
	v2 = getParent(v2);
	if (v1 == v2) return 1;
	else return 0;
}

void delete_edgeList(EdgeList* mst, int index) {
	mst->list[index]->v1= -1;
	mst->list[index]->v2= -1;

}

void print_path(int path_arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", path_arr[i]);
	}
	printf("\n");
}