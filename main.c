#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define DIFFICULTY 100 //난이도(감시 확률)
#define ITEM 9 // 아이템 개수
#define LEN 20 // 타이머 바 개수
#define MAX_NUM(x,y)(x)>(y)? x:y //배낭 알고리즘 최대값 함수

#define SIZE 5 //정점개수
#define MAPCOL 90//맵크기
#define MAPROW 35 //맵크기
#define INF 1000

#define TRUE 1
#define FALSE 0

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

char* map_gc[GC_MAP_ROW] = {
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

typedef struct Point {
    int x;
    int y;
}Point;
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

typedef struct {
    char* name; //아이템 이름
    int price;  //아이템 가치
    int weight; //아이템 용량
    int difficulty; //아이템 난이도
    bool isStolen; //이미 훔친 아이템은 못훔치게 변수
}Item;

typedef struct {
    int size;  //아이템 리스트 크기
    Item* itemList[ITEM+1];  //아이템 배열
    int capacity; //남은 용량 
}ItemType;

//전역변수
//=============아스키 아트 파일 포인터===============
FILE* fp_gameover = NULL; //게임 오버
FILE* fp_closeEye = NULL; //비감시 모드
FILE* fp_openEye = NULL; //감시 모드
FILE* fp_question = NULL; //물음표
FILE* fp_happyEnding = NULL;//해피 엔딩
FILE* fp_badEnding = NULL;//배드엔딩

//============변수=================
char text[256]; //파일에서 읽어들인 문자열 저장 버퍼
int itemNum; //사용자가 선택하는 아이템 번호
int spaceCount;//스페이스 눌러야하는 개수
int cost = 10;// 0/1배낭 열 크기(비용)
int userSolution=0; //사용자 배낭의 총 가치
int userCap = 0;

int vertex_arr[SIZE] = { 0,1,2,3,4 };
int count = 0;
int tsp_sum = 0;
int player_path[SIZE + 1];
int player_sum = 0;
Point vertex_point[SIZE];

//텍스트 출력 함수
void introText();
void firstTest();
void secondTest();
void LastTest();

// 콘솔 텍스트 색상 변경해주는 함수
void setColor(unsigned short text);

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
void create_edgeList(EdgeList* edgeList);
// 맵 출력

void print_map(EdgeList* edgeList);

//MST구하는 함수들
void create_MST(EdgeList* edgeList, EdgeList* mst);
int getParent(int x);
int check_union_find(int v1, int v2);
void unionParent(int v1, int v2);

//TSP근사해 구하는 함수들
void create_TSP(EdgeList* edgeList, EdgeList* mst, EdgeList* stack, int path_arr[]);
void insert_edgeList_mst(EdgeList* edgeList, Edge* edge);
void print_path(int path_arr[], int size);

//메인 프로그램
void projectTSP();

//그래프 컬러링 함수들

int CheckAnswer(int* node_color, int* input_color);
void GC_PrintMap(int* input_color);
int GraphColoring(int* node_color, int node_index, int color);
void PrintPattern(int patternLength, char patternNum);
int GC();

//============게임 함수 모음============
void init();
void print_title();
void game_over();
void game_clear();
void game_fail();

//===========아이템 관련 함수 모음============
Item* create_item(char* name, int p, int w, int d);
void insert_itemList(ItemType* head, Item* item);
void print_userItemList(ItemType* head);
void print_totalItemList(ItemType* head);
int selectToStealItem(ItemType* head,ItemType* inventory);
void print_inventory();

//===========감시 모드 함수 모음==============
void print_monitoring(FILE* fp);

//===========배낭 알고리즘=================
int knapsack(ItemType* bag, ItemType* head, int cost);

void gotoxy(int x, int y)

{

    COORD pos = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void print_title() {
    gotoxy(0, 0);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
    printf("■　　　　                    　　　　　　　　 ■■　　　　　　　　　　　　　　　　　　　　　　 ■\n");
    printf("■　　　　　　　　　　　　                     ■■　　　　　　　　　　　　　　　　　　　　　　 ■\n");
    printf("■　　　　　　　　　　　　                     ■■　　　　　　　　　　　　　　　　　　　　　　 ■\n");
    printf("■　　　　　　　　　　　　                     ■■　　　　　　　　　　　　　　　　　　　　　　 ■\n");
    printf("■　　　　　　　　　　　　                     ■■　　　　　　　　　　　　　　　　　　　　　　 ■\n");
    printf("■　　　　　　　　　　　　                     ■■　　　　　　　　　　　　　　　　　　　　　　 ■\n");
    printf("■　　　　　　　                    ■■　　　 ■■　　　  ■■　　　　　　　　　　　　　       ■\n");
    printf("■　　　　　　                    ■■■■　　 ■■　　  ■■■■　　　　　　　　　　　　　　　 ■\n");
    printf("■　　　　　                    ■■■■■■　 ■■　  ■■■■■■　　　　　　　　　　　　　　 ■\n");
    printf("■　　　　　　                    ■■■■　■ ■■ ■　 ■■■■　　　　　　　　　　　　　     ■\n");
    printf("■　　　　                    ■　　■■　 ■■■■■■　  ■■　  ■　　　　　　　　　　　　　 ■\n");
    printf("■　　　　                      ■　　    ■■　　　■■　　　　 ■　　　　　　　　　　　　　　 ■\n");
    printf("■　　　　                        ■■■■　■　　　■　■■■■　　　　　　　　　　　　　　　　■\n");
    printf("■　　　　　　　　　　　                    ■　　　■　　　　　　　　　　　　　　　　　　　　　■\n");
    printf("■                                          ■      ■                                          ■\n");
    printf("■  　　　　　　　                          ■      ■                                          ■\n");
    printf("■     　　                                 ■      ■                                          ■\n");
    printf("■                                          ■      ■                                          ■\n");
    printf("■                                          ■      ■                                          ■\n");
    printf("■                                                                                              ■\n");
    printf("■                                    PRESS ANY KEY TO START                                    ■\n");
    printf("■                                                                                              ■\n");
    printf("■                                                                                              ■\n");
    printf("■                                                                                              ■\n");
    printf("■                                                                                              ■\n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

    getchar();
    system("cls");
}

//===========아이템 리스트 초기화===========
void init_list(ItemType* head) {
    head->size = 0;
    head->capacity = cost;
    for (int i = 0; i < ITEM+1; i++) {
        head->itemList[i] = NULL;
    }
}
//===========아이템 생성===========
Item* create_item(char* name,int p,int w,int d) {
    Item* temp = (Item*)malloc(sizeof(Item));
    temp->name = name;
    temp->price = p;
    temp->weight = w;
    temp->difficulty = d;
    temp->isStolen = false;
    return temp;
}
//===========아이템 리스트에 추가===========
void insert_itemList(ItemType* head,Item* item) {
    head->itemList[head->size++] = item;
    head->capacity -= item->weight;
}

//===========아이템 리스트 출력===========
void print_userItemList(ItemType* head) {
    userCap = 0;
    userSolution = 0;
    int x, y;
    x = 35;
    y = 12;
    gotoxy(x, y++);
    printf("================실내화 가방================\n");
    for (int i = 0; i < head->size; i++) {
        gotoxy(x, y++);
        printf("%d.[%s]",i+1,head->itemList[i]->name);
        userSolution += head->itemList[i]->price;
        userCap += head->itemList[i]->weight;
    }
    gotoxy(x, y++);
    printf("==================총 가치==================\n");
    gotoxy(x, y++);
    printf("총 가치: [%d]\n", userSolution);
    gotoxy(x, y++);
    printf("==================총 부피==================\n");
    gotoxy(x, y++);
    printf("총 무게: [%d]", userCap);
}
//===========훔칠 아이템 리스트 출력===========
void print_totalItemList(ItemType* head,ItemType* inventory) {
    int x, y;
    x = 0;
    y = 0;
    gotoxy(x, y++);
    printf("================<<딱따구리 문방구>>==============\n");
    for (int i = 1; i < head->size; i++) {

        if (head->itemList[i]->isStolen) {
            gotoxy(x, y++);
            printf("%d.[%s]◆", i, head->itemList[i]->name);
            }
        else {
            gotoxy(x, y++);
            printf("%d.[%s]◇", i, head->itemList[i]->name);
        }
            gotoxy(x, y++);
            printf("가치: (%d) 부피: (%d) 난이도: ", 
                head->itemList[i]->price, head->itemList[i]->weight);
            for (int j = 0; j < head->itemList[i]->difficulty; j++) {
                printf("★");
            }
            for (int k = 5 - head->itemList[i]->difficulty; k > 0; k--) {
                printf("☆");
            }
            y++;
            gotoxy(x, y++); printf("=================================================");
    }
    print_inventory(inventory);
}
void print_inventory(ItemType* inventory) {
    int sum_price = 0;
    int sum_weight = 0;
    int x, y;
    x = 70;
    y = 5;
    gotoxy(x,y++);
    printf("    #####");    gotoxy(x, y++);
    printf("  ##     ##");    gotoxy(x, y++);
    printf(" ###########");    gotoxy(x, y++);
    printf("##         ##");    gotoxy(x, y++);
    printf("#############");    
    for (int i = 0; i < inventory->size; i++) {
        sum_price += inventory->itemList[i]->price;
        sum_weight += inventory->itemList[i]->weight;
    }
    gotoxy(x, y++);
    printf("#용량:%2d/ %d#",sum_weight,cost );
    gotoxy(x, y++);
    printf("#가치:%2d    #", sum_price);
    gotoxy(x, y++);
    printf("#물건:%2d / %d#", inventory->size, ITEM);
    gotoxy(x, y++);
    printf("#############");

}
//===========배낭 알고리즘===========
int knapsack(ItemType* bag,ItemType* head,int cost) {
    int i, w;
    int bestSolution;
    int bestSolution_weight = 0;
    w = cost;
    //==========0/1배낭 2차원 배열 생성(동적할당)==========
    int** wp = (int**)malloc(sizeof(int*)*(ITEM+1));
    
    for(int i=0;i<ITEM+1;i++){
        wp[i] = (int*)malloc(sizeof(int)*(cost+1));
    }
    //==========배낭 초기화==========
    for(int i=0;i<ITEM+1;i++){
        for(int j=0;j<cost;j++){
            wp[i][j] = 0;
        }
    }
    //==========0/1 배낭 알고리즘==========
    for (i = 1; i < ITEM + 1; i++) {
        for (w = 1; w < cost+1; w++) {
            if (w - head->itemList[i]->weight < 0) {
                wp[i][w] = wp[i - 1][w];
            }
            else {
                wp[i][w] = MAX_NUM(wp[i - 1][w], wp[i - 1][w - head->itemList[i]->weight] + head->itemList[i]->price);
            }   
        }
    }

    bestSolution = wp[ITEM][cost];

    //==========0/1 배낭 알고리즘 결과 출력==========
    gotoxy(0, 1);
    printf(" ===0/1 배낭 알고리즘 결과===");
    for (i = 1; i < ITEM + 1; i++) {
        gotoxy(0, i+1);
        for (w = 1; w < cost+1; w++) {
            
            printf("%2d ", wp[i][w]);
        }
        
    }
    //==========배낭에 포함된 요소 확인 알고리즘==========

    w = cost;
    int include[ITEM + 1] = { 0 };//포함 미포함 리스트
    
    while(w){
        i = ITEM;
        if (wp[i][w] != wp[i][w - 1]) {
            while (i > 0) {
                if (wp[i - 1][w] != wp[i][w]) {
                    include[i] = 1;
                    w = w - head->itemList[i]->weight;
                    break;
                }
                i--;
            }
        }
        else {
            w--;
        }
    }
    //==========동적 배열 해제==========
    for(int i=0;i<ITEM+1;i++){
        free(wp[i]);
    }
    free(wp);
    //==========배낭 포함==========
    gotoxy(0, 20); printf("===최적 물건 리스트===");
    gotoxy(0, 21);
    printf("[1] [2] [3] [4] [5] [6]");
    gotoxy(0, 22);
    for (int j = 1; j < ITEM+1; j++) {
        if (include[j]) {
            printf(" 1 ");
            bestSolution_weight += head->itemList[j]->weight;
        }
        else {
            printf(" 0 ");
        }
        printf(" ");
    }
    //==========최적해와 유저 배낭 비교==========
    int iq =1;
    int x, y;
    
    x = 35;
    y = 1;
    
    gotoxy(x, y++); printf("==================최적해===================");
    for (int j = 0; j < ITEM + 1; j++) {
        if (include[j]) {
            gotoxy(x, y++);
            printf("%d.[%s]", iq,head->itemList[j]->name);
            iq++;
        }
    }
    y++;
    gotoxy(x, y++);
    printf("==================총 가치==================\n");
    gotoxy(x, y++);
    printf("총 가치: [%d]\n", bestSolution);
    gotoxy(x, y++);
    printf("==================총 무게==================\n");
    gotoxy(x, y++);
    printf("총 무게: [%d]", bestSolution_weight);
    gotoxy(x, y++); printf("===========================================");

    //===비교===
    if (userSolution >= bestSolution) { //유저의 해가 최적해이면 참 반환
        return 1;
    }
    return 0;
}

//============감시 화면 출력============
void print_monitoring(FILE* fp) {
    gotoxy(3, 3);
    char print_temp[256];
    while (fgets(print_temp, 255, fp) != NULL) {
        printf(print_temp);
    }
    puts("");
    rewind(fp);
}

//============게임 오버============
void game_over() {
    system("cls");
    gotoxy(30, 14);
    printf("얘야 여기서 뭐하니?");
    gotoxy(30, 15);
    printf("잡았다 요놈!\n");
    Sleep(2000);
    print_monitoring(fp_gameover);
    Sleep(2000);
    exit(0);
}
void game_clear() {
    int x = 1, y = 1;
    gotoxy(x, y++);
    printf("훔쳐간 물건들이 형택이를 만족시킨 것 같다."); 
    gotoxy(x, y++); getchar();
    printf("형택이가 슬며시 다가와 내 어깨를 가볍게 두드리며 말했다."); 
    gotoxy(x, y++); getchar();
    printf("[좋아, 너도 이제부터 우리 클랜이다!]");
    gotoxy(x, y++); getchar();
    printf("[쳇,,대단한 녀석이 들어왔군..]"); 
    gotoxy(x, y++); getchar();
    printf("모두가 보는 앞에서 일월초 일짱 클랜에 들어갔다..!");
    gotoxy(x, y++); getchar();
    printf("나도 이제 [험멜] 입을 수 있다구..!"); 
    gotoxy(x, y++); getchar();
    Sleep(1000);
    system("cls");
    print_monitoring(fp_happyEnding);
    Sleep(1000);
    exit(0);
}
void game_fail() {
    int x = 1, y = 1;
    gotoxy(x, y++);
    printf("실내화 가방 안을 들여다 본 형택이의 낯빛이 어두워졌다.\n"); 
    gotoxy(x, y++); getchar();
    printf("진짜 x됐다...\n"); 
    gotoxy(x, y++); getchar();
    printf("형택이가 깊은 한숨을 내뱉으며 말했다.\n"); 
    gotoxy(x, y++); getchar();
    printf("[넌 안되겠다, 앞으로 아침 우유 급식은 너가 가져와라]\n"); 
    gotoxy(x, y++); getchar();
    printf("[아 그리고~ 제티 없으면 뒤진다^^]\n"); 
    gotoxy(x, y++); getchar();
    printf("모두가 보는 앞에서 일월초 최고 존엄 찐따로 등극했다.\n"); 
    gotoxy(x, y++); getchar();
    Sleep(1000);
    system("cls");
    print_monitoring(fp_badEnding);
    Sleep(1000);
    exit(0);
}
void printSpaceCount() {
    gotoxy(0, 27);
    printf("!!!Type [Space Bar]!!!");
    gotoxy(0, 28);
    for (int i = 0; i < spaceCount; i++) {
        printf("◆");
    }

}
void keyIn() {
    int userInputKey;
    userInputKey = _getch();
    if (userInputKey == 32) {
        spaceCount--;
    }
}
//===========감시 함수=============
int monitoring() {

    system("cls");

    srand(time(NULL));

    int endTime, startTime, monitorTime, random;
    char bar = '=';//바 문자
    char blank = ' ';//공백
    const int MAX = 500; //최대 카운트 수
    const int SPEED = 35; //타이머 스피드
    int count_timer = 0;  //타이머 카운트 변수
    float tick = (float)100 / LEN; //1틱 = 5퍼센트
    int bar_count;      //바 갯수
    int blank_count = 0;//공백 갯수
    float percent; //퍼센테이지 변수



    while (count_timer <= MAX) {

        gotoxy(0, 0);
        //타이머가 진행되는 동안 수행

        //==============================================
        printf("\r%d/%d [", MAX, MAX - count_timer);
        percent = (float)count_timer / MAX * 100;
        bar_count = percent / tick;
        for (int i = 0; i < LEN; i++) {
            blank_count = LEN - bar_count;
            if (blank_count > i) {
                printf("%c", bar);
            }                       //타이머 계산 및 출력 부분
            else {
                printf("%c", blank);
            }
        }
        printf("] %0.2f%%", 100 - percent);

        Sleep(SPEED);

        print_monitoring(fp_closeEye);//아스키 아트 화면 출력
        printSpaceCount();
        if (_kbhit()) {
            keyIn();
        }
        random = rand() % DIFFICULTY + 1;//1~100중 
        //===========================================================
        if (random == 100) {//200이 나오면 감시 모드

            endTime = (unsigned)time(NULL);

            monitorTime = rand() % 4 + 1; //1초~4초 감시

            endTime += monitorTime;
            print_monitoring(fp_question);
            Sleep(250);
            while (_kbhit()) {  //감시 모드에서 kbhit 정상 검사를 위해 버퍼를 사전에 비우는 작업
                _getch();
            }

            do {            //감시 진행
                startTime = (unsigned)time(NULL);

                print_monitoring(fp_openEye);  //감시 화면 전환

                if (_kbhit()) { //키보드가 눌리면 발각 됨
                    game_over();
                }
                if (endTime - startTime <= 0) { //감시 시간이 끝나면 감시 종료
                    system("cls");
                    break;
                }
            } while (endTime - startTime != 0);
        
        }

        count_timer++;
        if (spaceCount <= 0) {
            return 1;//훔치기 성공
        }
    }
    
    return 0;
}

void init() {
    /* system("mode con cols =30 lines = 130 | title 일월초 일짱 되기");*/
    system("mode con cols=140 lines=100 | title 일월초 일짱 되기");
    //커서 깜빡임 없애기
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void introText() {
    int x, y;
    x = 1; y = 1;
    gotoxy(x, y);
    printf("2012년 7월 26일 여름...");     gotoxy(x, y++); getchar();
    printf("드디어 다음주면 고대하던 여름 방학..!");   gotoxy(x, y++); getchar();
    printf("지긋지긋한 학교 생활...");   gotoxy(x, y++); getchar();
    printf("반 애들은 벌써 다 친해져서 피시방도 같이 가던데..");   gotoxy(x, y++); getchar();
    printf("나는 아직도 혼자다..");   gotoxy(x, y++); getchar();
    printf("친구들이랑 피시방 가면 얼마나 재밌을까..?");   gotoxy(x, y++); getchar();
    printf("이대로면 여름 방학에도 할머니댁이나 가겠지..");   gotoxy(x, y++); getchar();
    printf("에휴...나도 삼선 슬리퍼 신고 싶다...");   gotoxy(x, y++); getchar();
    printf("<복도에 시끌시끌한 소리가 울려 퍼진다>");   gotoxy(x, y++); getchar();
    printf("일월초 일짱 김형택이다..!");   gotoxy(x, y++); getchar();
    printf("와...험멜 레인보우다..! 나...도 험멜 입고싶다..");   gotoxy(x, y++); getchar();
    printf("나는 언제쯤...ㅜ");   gotoxy(x, y++); getchar();
    printf("에이! 이딴 스누피 실내화!");   gotoxy(x, y++); getchar();
    printf("<땅에 던지려던 실내화가 일월초 삼짱 민규의 뒤통수에 꽂혔다>");   gotoxy(x, y++); getchar();
    printf("(퍽!)");   gotoxy(x, y++); getchar();
    printf("[아 XX, 어떤 새끼야!!]");   gotoxy(x, y++); getchar();
    printf("헉..");   gotoxy(x, y++); getchar();
    system("cls");
    x = 1; y = 1;
    gotoxy(x, y);
    printf("[야야,민규야 참아~ 뭐 별것도 아닌걸로 그래~]"); gotoxy(x, y++); getchar();
    printf("[아니 X만한 놈이 시비털잖아 지존 어이없어;;]"); gotoxy(x, y++); getchar();
    printf("[알았으니까 그만하라고]"); gotoxy(x, y++); getchar();
    printf("[ㅇ..어..알았어,, 너 운 좋은줄 알아라 찐따 새끼야]"); gotoxy(x, y++); getchar();
    printf("[미...미안해..정말...]"); gotoxy(x, y++); getchar();
    printf("[나는 김형택이야, 넌 이름이 뭐냐?]"); gotoxy(x, y++); getchar();
    printf("[ㄴ..나..나는 장..정욱...]"); gotoxy(x, y++); getchar();
    printf("[아 너가 걔구나~ 그 서든 스나 80퍼]"); gotoxy(x, y++); getchar();
    printf("[ㅇ..으..응 마..맞아..]"); gotoxy(x, y++); getchar();
    printf("[우리 클전하러 갈건데 너도 올래?]"); gotoxy(x, y++); getchar();
    printf("[야 형택아 이딴 ㅈ밥을 그냥 데려간다고?]"); gotoxy(x, y++); getchar();
    printf("[그니깐 우리 클랜이 가오가 있지 이런 찐따녀석이랑 피시방을 어떻게 가!]"); gotoxy(x, y++); getchar();
    printf("[당연히 그냥은 아니고ㅋㅋ]"); gotoxy(x, y++); getchar();
    printf("[세 가지 시험을 통과하면 널 받아주마]"); gotoxy(x, y++); getchar();
    printf("시험이라...무슨 시험일까..?"); gotoxy(x, y++); getchar();
}
void firstTest() {
    int x, y;
    x = 1; y = 1;
    gotoxy(x, y);
    printf("첫번째 테스트는 가볍게 달리기 시합");     gotoxy(x, y++); getchar();
    printf("일월초 삼짱과 달리기 시합을 해서 비기거나 이기면 된다.");   gotoxy(x, y++); getchar();
    printf("일월초 정문에서 시작해서");   gotoxy(x, y++); getchar();
    printf("정해진 건물들을 전부 찌고 다시 정문으로 돌아오면 된다.");   gotoxy(x, y++); getchar();
    printf("어떤 경로를 선택하느냐에 따라 승패가 갈릴 것 같다."); getchar();
}
void secondTest() {
    int x, y;
    x = 1; y = 1;
    gotoxy(x, y);
    printf("두번째 테스트는 땅따먹기 문제야");     gotoxy(x, y++); getchar();
    printf("너의 능지가 얼마나 좋은지 확인해야겠어");   gotoxy(x, y++); getchar();
    printf("서든 어택의 맵을 보여주고 각 구역이 나뉘어져 있을거야");   gotoxy(x, y++); getchar();
    printf("각 구역은 하나의 팀이 점령할 수 있어"); gotoxy(x, y++); getchar();
    printf("단 인접한 두 개 이상의 구역을 하나의 팀이 점령할 수는 없어"); gotoxy(x, y++); getchar();
    printf("단, 최소의 팀으로 모든 구역을 점령해야한다"); getchar();
}
void LastTest() {
    int x, y;
    x = 1; y = 1;
    gotoxy(x, y);
    printf("여기까지 올 줄은 몰랐는데..");     gotoxy(x, y++); getchar();
    printf("꽤나 놀랍군 후후");   gotoxy(x, y++); getchar();
    printf("자 그럼 마지막 시험도 통과할 수 있는지 한 번 지켜보도록 하지");   gotoxy(x, y++); getchar();
    printf("마지막 시험은 <딱따구리 문방구>에서 이 [실내화 가방]에 물건들을 훔쳐오는거다");   gotoxy(x, y++); getchar();
    printf("훔치다가 걸려도 난 모르는 일이고"); gotoxy(x, y++); getchar();
    printf("나는 돈을 제일 좋아하는거 알지?"); gotoxy(x, y++); getchar();
    printf("내 기준에 맞춰서 잘 가져오라고~"); gotoxy(x, y++); getchar();
    printf("배짱이 얼마나 두둑한가 볼까나~"); getchar();
}
int selectToStealItem(ItemType* head,ItemType* inventory) {
    while (_kbhit()) { 
        _getch();
    }
    while (1) {
        gotoxy(100, 1);
        printf("*훔치기 종료[0번]*");
        gotoxy(65, 3);
        printf(">>훔칠 물건의 번호 입력>>");
        scanf_s("%d", &itemNum);
        if (0 < itemNum && itemNum < 7) {
            if (head->itemList[itemNum]->isStolen) {
                gotoxy(65, 4);
                printf("*%s는 이미 훔친 물건입니다*", head->itemList[itemNum]->name);
                Sleep(1000);
                system("cls");
                print_totalItemList(head, inventory);
            }
            else if ((inventory->capacity - head->itemList[itemNum]->weight) < 0) { //배낭의 용량을 초과하면 예외처리
                gotoxy(65, 4);
                printf("*짐이 너무 많습니다*");
                Sleep(1000);
                system("cls");
                print_totalItemList(head, inventory);
            }
            else {
                return 0; //훔치기 모드 계속
            }
        }
        else if (itemNum == 0) {
            return 1; //훔치기 모드 종료
        }
        else {
            gotoxy(65, 4);
            printf("*유효한 번호를 입력하세요(1~6)*");
            Sleep(1000);
            system("cls");
            print_totalItemList(head, inventory);
        }

    }
}
void free_item(ItemType* head) {
    for (int i = 0; i < ITEM+1; i++) {
        free(head->itemList[i]);
    }
}
void itemGenerator(ItemType* List) {
    srand(time(NULL));
    int randomValue[9];
    int randomWeight[9];
    insert_itemList(List, create_item(" ", 0, 0, 0));

    for (int i = 0; i < 9; i++) {
        randomValue[i] = rand() % 7 + 1;
        randomWeight[i] = rand() % 5 + 1;
    }
    insert_itemList(List, create_item("제티", randomValue[0], randomWeight[0], 1));
    insert_itemList(List, create_item("유희왕 카드", randomValue[1], randomWeight[1], 4));
    insert_itemList(List, create_item("메이플 딱지", randomValue[2], randomWeight[2], 3));
    insert_itemList(List, create_item("차카니", randomValue[3], randomWeight[3], 4));
    insert_itemList(List, create_item("콩순이 일기장", randomValue[4], randomWeight[4], 2));
    insert_itemList(List, create_item("매미 자석", randomValue[5], randomWeight[5], 5));
    insert_itemList(List, create_item("맥주 사탕", randomValue[6], randomWeight[6], 2));
    insert_itemList(List, create_item("틴캐시 1만원", randomValue[7], randomWeight[7], 4));
    insert_itemList(List, create_item("메탈베이블레이드", randomValue[8], randomWeight[8], 5));
}

int main(void) {

    init();
    print_title();
   // introText(); //인트로 생략

    system("cls");

    firstTest(); //첫번째 시험 영준이와 달리기 시합

    system("cls");

    projectTSP();

    Sleep(3000);

    system("cls");

    secondTest(); //두번째 시험 최소값 땅따먹기

    Sleep(3000);

    system("cls");

    GC();

    Sleep(3000);

    system("cls");

    LastTest();//마지막 시험 도둑질 능력 테스트

    ItemType List;
    ItemType bag;

    init_list(&bag);

    //아이템 리스트 생성
    init_list(&List);

    itemGenerator(&List);


    //이미지 파일 구조체 포인터 생성

    fp_closeEye = fopen("ClosedEye.txt", "rt");
    fp_openEye = fopen("OpenEye.txt", "rt");
    fp_gameover = fopen("gameover.txt", "rt");
    fp_question = fopen("questionMark.txt", "rt");
    fp_happyEnding = fopen("HappyEnding.txt", "rt");
    fp_badEnding = fopen("BadEnding.txt", "rt");

    if (fp_closeEye == NULL) {
        fprintf(stderr, "파일1 불러오기 실패");
        return 1;
    }
    if (fp_openEye == NULL) {
        fprintf(stderr, "파일2 불러오기 실패");
        return 1;
    }
    if (fp_gameover == NULL) {
        fprintf(stderr, "파일3 불러오기 실패");
        return 1;
    }

    if (fp_question == NULL) {
        fprintf(stderr, "파일5 불러오기 실패");
        return 1;
    }
    if (fp_happyEnding == NULL) {
        fprintf(stderr, "파일6 불러오기 실패");
        return 1;
    }
    if (fp_badEnding == NULL) {
        fprintf(stderr, "파일7 불러오기 실패");
        return 1;
    }


    //훔치기 게임 진행
    while (1) {

        system("cls");

        print_totalItemList(&List,&bag);//아이템 목록 출력

        if (selectToStealItem(&List, &bag))//훔칠 상품 번호 입력받기
            break;
        spaceCount = 1 * List.itemList[itemNum]->difficulty;

        if (monitoring()) {
            system("cls");

            insert_itemList(&bag, List.itemList[itemNum]);

            print_userItemList(&bag);

            List.itemList[itemNum]->isStolen = true;
            gotoxy(35, 10);

            printf("%s를 훔치는데 성공했다!", List.itemList[itemNum]->name);
            Sleep(2000);
        }
        else {
            system("cls");
            gotoxy(35, 10);
            printf("%s를 훔치지 못했다..다음 기회를 노려보자", List.itemList[itemNum]->name);
            Sleep(2000);
        }

    }
    system("cls");
    //결과 보기
    int i = 0;
    while (i < 3) {
        gotoxy(35, 13); printf("소지품 검사중."); Sleep(500);
        gotoxy(35, 13); printf("소지품 검사중.."); Sleep(500);
        gotoxy(35, 13); printf("소지품 검사중..."); Sleep(500);
        system("cls");
        i++;
    }

    print_userItemList(&bag);
    
    int isClear = knapsack(&bag,&List, cost);
    Sleep(5000);

    fclose(fp_closeEye);
    fclose(fp_openEye);
    fclose(fp_gameover);

    free_item(&List); //동적할당 해제
    system("cls");
    if (isClear) {
        game_clear();
    }
    else {
        game_fail();
    }
    return 0;
}

void projectTSP() {
    for (int i = 0; i < SIZE; i++) {
        vertex_point[i].x = -10;
        vertex_point[i].y = -10;
    }


    srand(time(NULL)); // 매번 다른 시드값 생성

    EdgeList* edgeList = (EdgeList*)malloc(sizeof(EdgeList));

    init_edgeList(edgeList, SIZE);

    // edgelist 생성
    create_edgeList(edgeList);
    //print_edgeList(edgeList);

    // 맵 출력
    print_map(edgeList);



    //MST생성
    sort_edge(edgeList); // 가중치 순으로 정렬
    EdgeList* mst = (EdgeList*)malloc(sizeof(EdgeList));
    init_edgeList(mst, SIZE);
    create_MST(edgeList, mst);


    sort_edge_v1(mst);//MST에 대한 간선 정렬
    int path_arr[SIZE + 1];

    EdgeList* stack = (EdgeList*)malloc(sizeof(EdgeList)); //스택 생성
    init_edgeList(stack, 0);

    // **************TSP 근사해 계산*******************
    create_TSP(edgeList, mst, stack, path_arr);


    // **********************플레이어 경로 입력******************
    int player_input = 0;
    player_path[0] = 0;
    count = 1;
    while (count < SIZE) {
        system("cls");
        print_map(edgeList);
        system("cls");
        print_map(edgeList);
        int is_input = TRUE;
        printf("====================================이동 경로====================================\n");
        print_path(player_path, count);
        do {
            printf("\r이동 위치 : ");
            scanf("%d", &player_input);
            if (1 <= player_input && player_input <= SIZE)break;
        } while (1 <= player_input && player_input <= SIZE);


        for (int i = 0; i < SIZE; i++) {
            if (player_path[i] == player_input) {
                printf("이미 간 곳입니다.\n");
                is_input = FALSE;
                break;
            }
            else if (!(0 <= player_input && player_input <= SIZE)) {
                printf("잘못입력했습니다.");
                is_input = FALSE;
                break;
            }
        }
        if (is_input == TRUE) {
            player_path[count++] = player_input;
        }
    }
    system("cls");
    print_map(edgeList);
    system("cls");
    print_map(edgeList);
    player_path[count++] = 0;



    //************* 플레이어 선택 가중치 계산 *****************
    printf("===================================이동 경로===================================\n");
    print_path(player_path, count);
    for (int i = 1; i < count; i++) {
        for (int j = 0; j < edgeList->size; j++) {
            if ((player_path[i - 1] == edgeList->list[j]->v1 && player_path[i] == edgeList->list[j]->v2) ||
                player_path[i - 1] == edgeList->list[j]->v2 && player_path[i] == edgeList->list[j]->v1) {
                player_sum += edgeList->list[j]->weight;
                break;
            }
        }
    }


    Sleep(2000);
    system("cls");

    //여기 스토리 들어가야됨 *연결 부분
    int i = 0;
    while (i < 3) {
        gotoxy(35, 13); printf("결과 검사중."); Sleep(500);
        gotoxy(35, 13); printf("결과 검사중.."); Sleep(500);
        gotoxy(35, 13); printf("결과 검사중..."); Sleep(500);
        system("cls");
        i++;
    }
    gotoxy(35, 10); printf("====================================내 경로====================================");
    gotoxy(35, 11); print_path(player_path, count);
    gotoxy(35, 13); printf("==================================영준이 경로==================================");
    gotoxy(35, 14); print_path(path_arr, SIZE + 1);
    Sleep(3000);
    system("cls");
    if (player_sum > tsp_sum) {
        gotoxy(35, 13); printf("영준이보다 %d초 늦었군",player_sum - tsp_sum); Sleep(1000);
        gotoxy(35, 14); printf("시험은 끝났다"); Sleep(1000);
        gotoxy(35, 15); printf("앞으로 우리 앞에 얼씬 거리지 마라"); Sleep(1000);
        exit(0);
    }
    else if (player_sum == tsp_sum) {
        gotoxy(35, 13); printf("영준이랑 동시에 도착했군"); Sleep(1000);
        gotoxy(35, 14); printf("다음 시험으로 넘어가지"); Sleep(1000);
    }
    else {
        gotoxy(35, 13); printf("영준이보다 %d초 빨랐군",tsp_sum - player_sum); Sleep(1000);
        gotoxy(35, 14); printf("신체 능력은 영준이보다 낫군"); Sleep(1000);
        gotoxy(35, 15); printf("좋아 다음 시험으로 넘어가지"); Sleep(1000);
    }


    free(edgeList);
    free(mst);
    free(stack);

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
    edgeList->list = (Edge**)malloc(sizeof(Edge) * amount);
}

void sort_edge(EdgeList* edgeList) { // 간선에 대한 선택 정렬
    for (int i = 0; i < edgeList->size - 1; i++) {
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
            if (edgeList->list[i]->v1 > edgeList->list[j]->v1) {
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
            setColor(GRAY);
            for (int k = 0; k < count; k++) {
                if ((vertex_point[k].x - 1 <= i && i <= vertex_point[k].x + 1)
                    && (vertex_point[k].y - 3 <= j && j <= vertex_point[k].y + 3)) {
                    setColor(BLUE);
                }
            }

            switch (map[i][j])
            {
            case '0': printf("　"); break;
            case '2': printf("□"); break;
            case '3': printf("■"); break;
            case '1': printf("■"); break;
            default:
                if ('A' <= map[i][j] && map[i][j] <= 'Z') {
                    setColor(RED);
                    for (int k = 0; k < count; k++) {
                        if (player_path[k] == (map[i][j] - 'A')) {
                            vertex_point[map[i][j] - 'A'].x = i;
                            vertex_point[map[i][j] - 'A'].y = j;
                            setColor(BLUE);
                            break;
                        }
                    }
                    printf("%d ", (map[i][j]) - 'A');
                    setColor(GRAY);
                }
                if ('a' <= map[i][j] && map[i][j] <= 'z') {
                    setColor(GREEN);

                    printf("%d ", edgeList->list[map[i][j] - 'a']->weight);
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


void create_MST(EdgeList* edgeList, EdgeList* mst) {
    for (int i = 0; i < edgeList->size; i++) {
        Edge* tmp = (Edge*)malloc(sizeof(Edge));
        *tmp = *edgeList->list[i];
        if (check_union_find(tmp->v1, tmp->v2) != TRUE) {
            insert_edgeList_mst(mst, tmp);
            unionParent(tmp->v1, tmp->v2);
        }
    }
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
    mst->list[index]->v1 = -1;
    mst->list[index]->v2 = -1;

}

void create_edgeList(EdgeList* edgeList) {	//간선이 존재하면 1~10의 가중치를 갖는 간선 생성
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            if (weight_arr[i][j] == 1) {
                Edge* new_edge = (Edge*)malloc(sizeof(Edge));
                init_edge(new_edge, i, j, rand() % 9 + 1);
                insert_edgeList(edgeList, new_edge);
            }
        }
    }
}

void print_path(int path_arr[], int size) {
    for (int i = 0; i < size; i++) {
        switch (path_arr[i]) {
        case 0:
            printf("[일월초 정문]");
            break;
        case 1:
            printf("-[문구 팬시]->");
            break;
        case 2:
            printf("-[다농 마트]->");
            break;
        case 3:
            printf("-[김밥 나라]->");
            break;
        case 4:
            printf("-[딱따구리 문방구]->");
            break;
        default:
            printf("[일월초 정문]");
        }
    }
    printf("\n");
}
void setColor(unsigned short text) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void create_TSP(EdgeList* edgeList, EdgeList* mst, EdgeList* stack, int path_arr[]) {
    int cur_vertex = 0;
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

    //print_edgeList(edgeList);
    for (int i = 1; i <= SIZE + 1; i++) { // 경로 가중치 합 구하기
        for (int k = 0; k < edgeList->size; k++) {
            if (edgeList->list[k]->v2 == path_arr[i] && edgeList->list[k]->v1 == path_arr[i - 1]) {
                tsp_sum += edgeList->list[k]->weight;
                break;
            }
            if (edgeList->list[k]->v1 == path_arr[i] && edgeList->list[k]->v2 == path_arr[i - 1]) {
                tsp_sum += edgeList->list[k]->weight;
                break;

            }
        }
    }
    //print_path(path_arr, count);
    //printf("tsp_sum : %d\n", tsp_sum);
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
        if (connectionMatrix_3[node_index][j] == 1 && node_color[j] == color + 1) {
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
/// GC_Print 함수에서 patternLength만큼 patternNum을 setColor해서 출력
/// </summary>
/// <param name="patternLength">patternNum이 반복되는 횟수</param>
/// <param name="patternNum">출력할 값</param>
void PrintPattern(int patternLength, char patternNum) {

    for (int i = 0; i <= patternLength; i++) {
        printf("%c", patternNum);
    }

    return;
}

/// <summary>
/// 패턴 테이블을 이용하여 map을 color 배열에 따라 출력해준다.
/// </summary>
/// <param name="input_color">map의 색깔(0~12), 14:line color</param>
void GC_PrintMap(int* input_color) {
    for (int i = 0; i < GC_MAP_ROW; i++) {
        int currentCharPoint = 3;
        int patternTable[20] = { 0, };
        int patternTableIdx = 0;

        while (currentCharPoint + 1 <= GC_MAP_COL) {
            // 다음 인덱스 문자와 비교해서 같다면 패턴 테이블 += 1
            if (map_gc[i][currentCharPoint] == map_gc[i][currentCharPoint + 1]) {
                currentCharPoint++;
                patternTable[patternTableIdx]++;
            }
            else { // 같지 않다면
                setColor(input_color[map_gc[i][currentCharPoint] - 'a']);
                PrintPattern(patternTable[patternTableIdx], map_gc[i][currentCharPoint]);
                currentCharPoint++;
                patternTableIdx++;
            }

        }
        setColor(input_color[map_gc[i][currentCharPoint] - 'a']);
        PrintPattern(patternTable[patternTableIdx], map_gc[i][currentCharPoint]);
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

    for (int i = 0; i < NODE_NUM; i++) {
        if (node_color[i] != input_color[i])
            success = 0;
    }
    int i = 0;
    while (i < 3) {
        gotoxy(35, 13); printf("결과 검사중."); Sleep(500);
        gotoxy(35, 13); printf("결과 검사중.."); Sleep(500);
        gotoxy(35, 13); printf("결과 검사중..."); Sleep(500);
        system("cls");
        i++;
    }
    system("cls");
    if (success) {
        gotoxy(35, 13); printf("그래도 덜떨어진 놈은 아니군"); Sleep(1000);
        gotoxy(35, 14); printf("좋아 다음 시험으로 넘어가지"); Sleep(1000);
    }
    else {
        gotoxy(35, 13); printf("능지는 딸리는 녀석이군"); Sleep(1000);
        gotoxy(35, 14); printf("역시 우리 수준에는 안맞아"); Sleep(1000);
        gotoxy(35, 15); printf("가서 공부나 해라"); Sleep(1000);
        exit(0);
    }


    return success;
}

int GC() {
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
        GC_PrintMap(input_color);
        printf("%c 구역을 점령할 팀(0, 1, 2, 3, 4 ...)을 입력.단, a 구역은 0 번 팀을, b 구역은 1번 팀을 입력\n", i + 'a');
        printf("팀의 번호>> "); 
        scanf_s("%d", &input_color[i]);
        input_color[i]++;
        node_color[i] = -1;
        system("cls");
    }

    GraphColoring(node_color, 0, 0);

    CheckAnswer(node_color, input_color);

    return 0;
}