#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define DIFFICULTY 100 //���̵�(���� Ȯ��)
#define ITEM 9 // ������ ����
#define LEN 20 // Ÿ�̸� �� ����
#define MAX_NUM(x,y)(x)>(y)? x:y //�賶 �˰��� �ִ밪 �Լ�

#define SIZE 5 //��������
#define MAPCOL 90//��ũ��
#define MAPROW 35 //��ũ��
#define INF 1000

#define TRUE 1
#define FALSE 0

#define NODE_NUM_1 6
#define NODE_NUM_2 7
#define NODE_NUM 12
#define GC_MAP_ROW 26
#define GC_MAP_COL 98


// ������� �������ִٸ� 1, �׷��� ������ 0���� ǥ��
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

//�� ���� ����ġ
int weight_arr[SIZE][SIZE] = {
{0,1,1,1,1},
{1,0,1,1,1},
{1,1,0,1,1},
{1,1,1,0,1},
{1,1,1,1,0}
};
//��� : 2, �� : 1, ���� : 0, ���� : A~Z, ����ġ : a~z
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
    char* name; //������ �̸�
    int price;  //������ ��ġ
    int weight; //������ �뷮
    int difficulty; //������ ���̵�
    bool isStolen; //�̹� ��ģ �������� ����ġ�� ����
}Item;

typedef struct {
    int size;  //������ ����Ʈ ũ��
    Item* itemList[ITEM + 1];  //������ �迭
    int capacity; //���� �뷮 
}ItemType;

//��������
//=============�ƽ�Ű ��Ʈ ���� ������===============
FILE* fp_gameover = NULL; //���� ����
FILE* fp_closeEye = NULL; //�񰨽� ���
FILE* fp_openEye = NULL; //���� ���
FILE* fp_question = NULL; //����ǥ
FILE* fp_happyEnding = NULL;//���� ����
FILE* fp_badEnding = NULL;//��忣��

//============����=================
char text[256]; //���Ͽ��� �о���� ���ڿ� ���� ����
int itemNum; //����ڰ� �����ϴ� ������ ��ȣ
int spaceCount;//�����̽� �������ϴ� ����
int cost = 10;// 0/1�賶 �� ũ��(���)
int userSolution = 0; //����� �賶�� �� ��ġ
int userCap = 0;
int userSpace = 0;

int vertex_arr[SIZE] = { 0,1,2,3,4 };
int count = 0;
int tsp_sum = 0;
int player_path[SIZE + 1];
int player_sum = 0;
Point vertex_point[SIZE];

//�ؽ�Ʈ ��� �Լ�
void introText();
void firstTest();
void secondTest();
void ThirdTest();
void LastTest();

//������ ��� �Լ�
void print_frame();

// �ܼ� �ؽ�Ʈ ���� �������ִ� �Լ�
void setColor(unsigned short text);

// edge �Լ�
void init_edge(Edge* edge, int v1, int v2, int weight);

// edgelist �Լ�
void insert_edgeList(EdgeList* edgeList, Edge* edge); // edgelist�� edge �߰�
void init_edgeList(EdgeList* edgeList, int amount); // edgelist �ʱ�ȭ (size = 0)
void print_edgeList(EdgeList* edgeList); // edgelist->list�� v1, v2, weight�� ���
void sort_edge(EdgeList* edgeList); // ����ġ �������� ����
int find_edgeList(EdgeList* edgeList, int v); //v���� ����ϴ� edge�� ã��
void sort_edge_v1(EdgeList* edgeList);
void delete_edgeList(EdgeList* mst, int index);
void create_edgeList(EdgeList* edgeList);
// �� ���

void print_map(EdgeList* edgeList);

//MST���ϴ� �Լ���
void create_MST(EdgeList* edgeList, EdgeList* mst);
int getParent(int x);
int check_union_find(int v1, int v2);
void unionParent(int v1, int v2);

//TSP�ٻ��� ���ϴ� �Լ���
void create_TSP(EdgeList* edgeList, EdgeList* mst, EdgeList* stack, int path_arr[]);
void insert_edgeList_mst(EdgeList* edgeList, Edge* edge);
void print_path(int path_arr[], int size);

//���� ���α׷�
void projectTSP();

//�׷��� �÷��� �Լ���

int CheckAnswer(int* node_color, int* input_color);
void GC_PrintMap(int* input_color);
int GraphColoring(int* node_color, int node_index, int color);
void PrintPattern(int patternLength, char patternNum);
int GC();

//�۾� �����ٸ� �Լ���
int JobSchedule(int machine[], int task[], int machine_count, int task_count);
int Bigger(int num[]);
char JobSchedule_person(int machine[], int task[], int machine_count, int task_count);
void print_Story();
void projectJS();

//============���� �Լ� ����============
void init();
void print_title();
void game_over();
void game_clear();
void game_fail();

//===========������ ���� �Լ� ����============
Item* create_item(char* name, int p, int w, int d);
void insert_itemList(ItemType* head, Item* item);
void print_userItemList(ItemType* head);
void print_totalItemList(ItemType* head);
int selectToStealItem(ItemType* head, ItemType* inventory);
void print_inventory();

//===========���� ��� �Լ� ����==============
void print_monitoring(FILE* fp);

//===========�賶 �˰���=================
int knapsack(ItemType* bag, ItemType* head, int cost);

void gotoxy(int x, int y)

{

    COORD pos = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}
void print_frame() {
    gotoxy(0, 20);
    printf("��������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ��������������������������������������������������������������������     Progress to Enter����\n");
    printf("��������������������������������������������������\n");
}
void print_title() {
    gotoxy(0, 0);
    printf("��������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ����������������������������������������������������������������������������������������������\n");
    printf("�ᡡ������                    ���������������� ��ᡡ������������������������������������������ ��\n");
    printf("�ᡡ����������������������                     ��ᡡ������������������������������������������ ��\n");
    printf("�ᡡ����������������������                     ��ᡡ������������������������������������������ ��\n");
    printf("�ᡡ����������������������                     ��ᡡ������������������������������������������ ��\n");
    printf("�ᡡ����������������������                     ��ᡡ������������������������������������������ ��\n");
    printf("�ᡡ����������������������                     ��ᡡ������������������������������������������ ��\n");
    printf("�ᡡ������������                    ��ᡡ���� ��ᡡ����  ��ᡡ������������������������       ��\n");
    printf("�ᡡ����������                    ����ᡡ�� ��ᡡ��  ����ᡡ���������������������������� ��\n");
    printf("�ᡡ��������                    ������ᡡ ��ᡡ  ������ᡡ�������������������������� ��\n");
    printf("�ᡡ����������                    ����ᡡ�� ��� �ᡡ ����ᡡ������������������������     ��\n");
    printf("�ᡡ������                    �ᡡ����ᡡ ������ᡡ  ��ᡡ  �ᡡ������������������������ ��\n");
    printf("�ᡡ������                      �ᡡ��    ��ᡡ������ᡡ������ �ᡡ�������������������������� ��\n");
    printf("�ᡡ������                        ����ᡡ�ᡡ�����ᡡ����ᡡ��������������������������������\n");
    printf("�ᡡ��������������������                    �ᡡ�����ᡡ������������������������������������������\n");
    printf("��                                          ��      ��                                          ��\n");
    printf("��  ��������������                          ��      ��                                          ��\n");
    printf("��     ����                                 ��      ��                                          ��\n");
    printf("��                                          ��      ��                                          ��\n");
    printf("��                                          ��      ��                                          ��\n");
    printf("��                                                                                              ��\n");
    printf("��                                    PRESS ANY KEY TO START                                    ��\n");
    printf("��                                                                                              ��\n");
    printf("��                                                                                              ��\n");
    printf("��                                                                                              ��\n");
    printf("��                                                                                              ��\n");
    printf("��������������������������������������������������\n");

    getchar();
    system("cls");
}

//===========������ ����Ʈ �ʱ�ȭ===========
void init_list(ItemType* head) {
    head->size = 0;
    head->capacity = cost;
    for (int i = 0; i < ITEM + 1; i++) {
        head->itemList[i] = NULL;
    }
}
//===========������ ����===========
Item* create_item(char* name, int p, int w, int d) {
    Item* temp = (Item*)malloc(sizeof(Item));
    temp->name = name;
    temp->price = p;
    temp->weight = w;
    temp->difficulty = d;
    temp->isStolen = false;
    return temp;
}
//===========������ ����Ʈ�� �߰�===========
void insert_itemList(ItemType* head, Item* item) {
    head->itemList[head->size++] = item;
    head->capacity -= item->weight;
}

//===========������ ����Ʈ ���===========
void print_userItemList(ItemType* head) {
    userCap = 0;
    userSolution = 0;
    int x, y;
    x = 35;
    y = 12;
    gotoxy(x, y++);
    printf("================�ǳ�ȭ ����================\n");
    for (int i = 0; i < head->size; i++) {
        gotoxy(x, y++);
        printf("%d.[%s]", i + 1, head->itemList[i]->name);
        userSolution += head->itemList[i]->price;
        userCap += head->itemList[i]->weight;
    }
    gotoxy(x, y++);
    printf("==================�� ��ġ==================\n");
    gotoxy(x, y++);
    printf("�� ��ġ: [%d]\n", userSolution);
    gotoxy(x, y++);
    printf("==================�� ����==================\n");
    gotoxy(x, y++);
    printf("�� ����: [%d]", userCap);
}
//===========��ĥ ������ ����Ʈ ���===========
void print_totalItemList(ItemType* head, ItemType* inventory) {
    int x, y;
    x = 0;
    y = 0;
    gotoxy(x, y++);
    printf("================<<�������� ���汸>>==============\n");
    for (int i = 1; i < head->size; i++) {

        if (head->itemList[i]->isStolen) {
            gotoxy(x, y++);
            printf("%d.[%s]��", i, head->itemList[i]->name);
        }
        else {
            gotoxy(x, y++);
            printf("%d.[%s]��", i, head->itemList[i]->name);
        }
        gotoxy(x, y++);
        printf("��ġ: (%d) ����: (%d) ���̵�: ",
            head->itemList[i]->price, head->itemList[i]->weight);
        for (int j = 0; j < head->itemList[i]->difficulty; j++) {
            printf("��");
        }
        for (int k = 5 - head->itemList[i]->difficulty; k > 0; k--) {
            printf("��");
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
    gotoxy(x, y++);
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
    printf("#�뷮:%2d/ %d#", sum_weight, cost);
    gotoxy(x, y++);
    printf("#��ġ:%2d    #", sum_price);
    gotoxy(x, y++);
    printf("#����:%2d / %d#", inventory->size, ITEM);
    gotoxy(x, y++);
    printf("#############");

}
//===========�賶 �˰���===========
int knapsack(ItemType* bag, ItemType* head, int cost) {
    int i, w;
    int bestSolution;
    int bestSolution_weight = 0;
    w = cost;
    //==========0/1�賶 2���� �迭 ����(�����Ҵ�)==========
    int** wp = (int**)malloc(sizeof(int*) * (ITEM + 1));

    for (int i = 0; i < ITEM + 1; i++) {
        wp[i] = (int*)malloc(sizeof(int) * (cost + 1));
    }
    //==========�賶 �ʱ�ȭ==========
    for (int i = 0; i < ITEM + 1; i++) {
        for (int j = 0; j < cost; j++) {
            wp[i][j] = 0;
        }
    }
    //==========0/1 �賶 �˰���==========
    for (i = 1; i < ITEM + 1; i++) {
        for (w = 1; w < cost + 1; w++) {
            if (w - head->itemList[i]->weight < 0) {
                wp[i][w] = wp[i - 1][w];
            }
            else {
                wp[i][w] = MAX_NUM(wp[i - 1][w], wp[i - 1][w - head->itemList[i]->weight] + head->itemList[i]->price);
            }
        }
    }

    bestSolution = wp[ITEM][cost];

    //==========0/1 �賶 �˰��� ��� ���==========
    gotoxy(0, 1);
    printf(" ===0/1 �賶 �˰��� ���===");
    for (i = 1; i < ITEM + 1; i++) {
        gotoxy(0, i + 1);
        for (w = 1; w < cost + 1; w++) {

            printf("%2d ", wp[i][w]);
        }

    }
    //==========�賶�� ���Ե� ��� Ȯ�� �˰���==========

    w = cost;
    int include[ITEM + 1] = { 0 };//���� ������ ����Ʈ

    while (w) {
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
    //==========���� �迭 ����==========
    for (int i = 0; i < ITEM + 1; i++) {
        free(wp[i]);
    }
    free(wp);
    //==========�賶 ����==========
    gotoxy(35, 25); printf("=============���� ���� ����Ʈ=============");
    gotoxy(35, 26);
    for (int i = 1; i < ITEM + 1; i++) {
        printf("[ %d ]", i);
    }
    gotoxy(35, 27);
    for (int j = 1; j < ITEM + 1; j++) {
        if (include[j]) {
            printf("  1 ");
            bestSolution_weight += head->itemList[j]->weight;
        }
        else {
            printf("  0 ");
        }
        printf(" ");
    }
    //==========�����ؿ� ���� �賶 ��==========
    int iq = 1;
    int x, y;

    x = 35;
    y = 1;

    gotoxy(x, y++); printf("==================������===================");
    for (int j = 0; j < ITEM + 1; j++) {
        if (include[j]) {
            gotoxy(x, y++);
            printf("%d.[%s]", iq, head->itemList[j]->name);
            iq++;
        }
    }
    y++;
    gotoxy(x, y++);
    printf("==================�� ��ġ==================\n");
    gotoxy(x, y++);
    printf("�� ��ġ: [%d]\n", bestSolution);
    gotoxy(x, y++);
    printf("==================�� ����==================\n");
    gotoxy(x, y++);
    printf("�� ����: [%d]", bestSolution_weight);
    gotoxy(x, y++); printf("===========================================");

    //===��===
    if (userSolution >= bestSolution) { //������ �ذ� �������̸� �� ��ȯ
        return 1;
    }
    return 0;
}

//============���� ȭ�� ���============
void print_monitoring(FILE* fp) {
    gotoxy(3, 3);
    char print_temp[256];
    while (fgets(print_temp, 255, fp) != NULL) {
        printf(print_temp);
    }
    puts("");
    rewind(fp);
}

//============���� ����============
void game_over() {
    system("cls");
    gotoxy(30, 14);
    printf("��� ���⼭ ���ϴ�?");
    Sleep(750);
    gotoxy(30, 15);
    printf("��Ҵ� ���!\n");
    Sleep(2000);
    print_monitoring(fp_gameover);
    Sleep(2000);
    exit(0);
}
void game_clear() {
    int x = 1, y = 1;
    gotoxy(x, y++);
    printf("���İ� ���ǵ��� �����̸� ������Ų �� ����.");
    gotoxy(x, y++); getchar();
    printf("�����̰� ����� �ٰ��� �� ����� ������ �ε帮�� ���ߴ�.");
    gotoxy(x, y++); getchar();
    printf("[����, �ʵ� �������� �츮 Ŭ���̴�!]");
    gotoxy(x, y++); getchar();
    printf("[��,,����� �༮�� ���Ա�..]");
    gotoxy(x, y++); getchar();
    printf("��ΰ� ���� �տ��� �Ͽ��� ��¯ Ŭ���� ����..!");
    gotoxy(x, y++); getchar();
    printf("���� ���� [���] ���� �� �ִٱ�..!");
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
    printf("�ǳ�ȭ ���� ���� �鿩�� �� �������� ������ ��ο�����.\n");
    gotoxy(x, y++); getchar();
    printf("��¥ x�ƴ�...\n");
    gotoxy(x, y++); getchar();
    printf("�����̰� ���� �Ѽ��� �������� ���ߴ�.\n");
    gotoxy(x, y++); getchar();
    printf("[�� �ȵǰڴ�, ������ ��ħ ���� �޽��� �ʰ� �����Ͷ�]\n");
    gotoxy(x, y++); getchar();
    printf("[�� �׸���~ ��Ƽ ������ ������^^]\n");
    gotoxy(x, y++); getchar();
    printf("��ΰ� ���� �տ��� �Ͽ��� �ְ� ���� ����� ����ߴ�.\n");
    gotoxy(x, y++); getchar();
    Sleep(1000);
    system("cls");
    print_monitoring(fp_badEnding);
    Sleep(1000);
    exit(0);
}
void printSpaceCount() {
    gotoxy(0, 27);
    printf("[Space Bar]");

    gotoxy(0, 28);
    for (int i = 0; i < spaceCount; i++) {
        printf("��");
    }
    for (int i = 0; i < userSpace; i++) {
        printf("  ");
    }

}
void keyIn() {
    int userInputKey;
    userInputKey = _getch();
    if (userInputKey == 32) {
        userSpace++;
        spaceCount--;
    }
}
//===========���� �Լ�=============
int monitoring() {

    system("cls");

    srand(time(NULL));

    int endTime, startTime, monitorTime, random;
    char bar = '=';//�� ����
    char blank = ' ';//����
    const int MAX = 500; //�ִ� ī��Ʈ ��
    const int SPEED = 35; //Ÿ�̸� ���ǵ�
    int count_timer = 0;  //Ÿ�̸� ī��Ʈ ����
    float tick = (float)100 / LEN; //1ƽ = 5�ۼ�Ʈ
    int bar_count;      //�� ����
    int blank_count = 0;//���� ����
    float percent; //�ۼ������� ����



    while (count_timer <= MAX) {

        gotoxy(0, 0);
        //Ÿ�̸Ӱ� ����Ǵ� ���� ����

        //==============================================
        printf("\r%d/%d [", MAX, MAX - count_timer);
        percent = (float)count_timer / MAX * 100;
        bar_count = percent / tick;
        for (int i = 0; i < LEN; i++) {
            blank_count = LEN - bar_count;
            if (blank_count > i) {
                printf("%c", bar);
            }                       //Ÿ�̸� ��� �� ��� �κ�
            else {
                printf("%c", blank);
            }
        }
        printf("] %0.2f%%", 100 - percent);

        Sleep(SPEED);

        print_monitoring(fp_closeEye);//�ƽ�Ű ��Ʈ ȭ�� ���
        printSpaceCount();
        if (_kbhit()) {
            keyIn();
        }
        random = rand() % DIFFICULTY + 1;//1~100�� 
        //===========================================================
        if (random == 100) {//100�� ������ ���� ���

            endTime = (unsigned)time(NULL);

            monitorTime = rand() % 4 + 1; //1��~4�� ����

            endTime += monitorTime;
            print_monitoring(fp_question);
            Sleep(500);
            while (_kbhit()) {  //���� ��忡�� kbhit ���� �˻縦 ���� ���۸� ������ ���� �۾�
                _getch();
            }

            do {            //���� ����
                startTime = (unsigned)time(NULL);

                print_monitoring(fp_openEye);  //���� ȭ�� ��ȯ

                if (_kbhit()) { //Ű���尡 ������ �߰� ��
                    game_over();
                }
                if (endTime - startTime <= 0) { //���� �ð��� ������ ���� ����
                    system("cls");
                    break;
                }
            } while (endTime - startTime != 0);

        }

        count_timer++;
        if (spaceCount <= 0) {

            return 1;//��ġ�� ����
        }
    }

    return 0;
}

void init() {
    /* system("mode con cols =30 lines = 130 | title �Ͽ��� ��¯ �Ǳ�");*/
    system("mode con cols=140 lines=50 | title �Ͽ��� ��¯ �Ǳ�");
    //Ŀ�� ������ ���ֱ�
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void introText() {
    int x, y;
    x = 3;
    y = 22;
    system("cls");
    print_frame();
    gotoxy(x, y++);
    printf("  2012�� 7�� 26�� ����..."); getchar(); gotoxy(x, y++);
    printf("  ���� �����ָ� ����ϴ� ���� ����..!");  getchar(); gotoxy(x, y++);
    printf("  ���������� �б� ��Ȱ..."); getchar();  gotoxy(x, y++);
    printf("  �� �ֵ��� ���� �� ģ������ �ǽù浵 ���� ������.."); getchar();  gotoxy(x, y++);
    printf("  ���� ������ ȥ�ڴ�..");  getchar();
    system("cls");
    print_frame();
    y = 22;
    gotoxy(x, y++);
    printf("  ģ�����̶� �ǽù� ���� �����ϱ�..?");  getchar(); gotoxy(x, y++);
    printf("  �̴�θ� ���� ���п��� �ҸӴϴ��̳� ������.."); getchar();  gotoxy(x, y++);
    printf("  �׸��� 2�б⵵ ���ݰ� �ٸ��� ������..");  getchar(); gotoxy(x, y++);
    printf("  <�ڿ��ڿ� ��������>");  getchar(); gotoxy(x, y++);
    printf("  ��,,�Ͽ��� ��¯ �������̴�..!");    getchar();
    system("cls");
    print_frame();
    y = 22;
    gotoxy(x, y++);
    printf("  [������]: �� �� ������ �츮 ������ ���ٰ�;;"); getchar();  gotoxy(x, y++);
    printf("  [�̹α�]: ������ �±ǵ� �±� �ɻ����� ������,,�̾���"); getchar();  gotoxy(x, y++);
    printf("  [������]: ����쳪 �ʷ϶쳪 �Ȱ����� �׳� °��;;"); getchar();  gotoxy(x, y++);
    printf("  [�̹α�]: �ȵ�,,,������ ���� �� ������..."); getchar();   gotoxy(x, y++);
    printf("  (��!����!)");    getchar();
    system("cls");
    print_frame();
    y = 22;
    gotoxy(x, y++);
    printf("  [������]: ��,,���� �׳�");   getchar(); gotoxy(x, y++);
    printf("  [�̹α�]: ��,,�̾��� ���þ�..����");   getchar(); gotoxy(x, y++);




    printf("  �Ͽ��� ��¯ �̹α԰� ������ �ο���� �������"); getchar(); gotoxy(x, y++);
    printf("  �̰� ��ȸ��..���Ե����� ��-�� �λ��� �����ٰž�"); getchar(); gotoxy(x, y++);
    printf("  [��]: ��,,��,,,����,,���þ�,,!");   getchar();
    system("cls");
    print_frame();
    y = 22;
    gotoxy(x, y++);
    printf("  [������]: ???");  getchar(); gotoxy(x, y++);
    printf("  [������]: ���� �� �� �˾�?");  getchar(); gotoxy(x, y++);
    printf("  [��]: ��,,�� ���� �翬�� �� �𸣴� �ְ� �����,,");  getchar(); gotoxy(x, y++);
    printf("  [������]: ��,,�׷��� ����?"); getchar();  gotoxy(x, y++);
    printf("  [��]: ��,,������,,,���� �ص� �ɱ�?");  getchar(); gotoxy(x, y++);
    system("cls");
    print_frame();
    y = 22;
    gotoxy(x, y++);
    printf("  [������]: ��?�� ��� ����� �־��� �̰�");  getchar(); gotoxy(x, y++);
    printf("  [������]: �� ���� �� �ݵ�?");  getchar(); gotoxy(x, y++);
    printf("  [��]: ��,,,65�ݵ�,,,���� �ǳ� ���濡�� ũī���ؼ�,,,,");  getchar(); gotoxy(x, y++);
    printf("  [������]: 65��,,,�� �ָ��ѵ�,,,");  getchar(); gotoxy(x, y++);
    printf("  [��]: �� �׷���..!�ﺸ �긮���̶�� �ֱ������� �� �θ� �� �־�!����!");  getchar();
    system("cls");
    print_frame();
    y = 22;
    gotoxy(x, y++);
    printf("  [������]: ���� �̸� ������..");   getchar(); gotoxy(x, y++);
    printf("  [������]: ���� �� ���� �ɷ��� �� �� ���� ���ϵ��� ����");  getchar(); gotoxy(x, y++);
    printf("  [������]: ZIZONE�Ͽ� Ŭ���� �������� �� ���� �׽�Ʈ�� ���� ����ؾߵ�");  getchar(); gotoxy(x, y++);
    printf("  [������]: ���������� ���� ������Ų�ٸ� ���� Ŭ�������� �޾�����");  getchar(); gotoxy(x, y++);
    printf("  [��]: ��..�׽�Ʈ..? �..."); getchar();
}
void firstTest() {
    int x, y;
    x = 3;
    y = 22;
    system("cls");
    print_frame();
    gotoxy(x, y++);
    printf("  ù��° �׽�Ʈ: ������� �������");    getchar(); gotoxy(x, y++);
    printf("  [������] �츮 Ŭ���� '�ڱ���'�� �� ����Ұž�"); getchar();  gotoxy(x, y++);
    printf("  [������] �׷� ��Ģ�� ����������"); getchar();  gotoxy(x, y++);
    printf("  <���� ���̽�>���� <A����>,<B����>,<��� ���̽�>,<�κ�>�� ���� ��� ���ƿ;��Ѵ�");  getchar(); gotoxy(x, y++);
    printf("  [������] ���º��� �ʰԿ����� �ʴ´ٸ� [���]��������"); getchar();
}
void secondTest() {
    int x, y;
    x = 3;
    y = 22;
    system("cls");
    print_frame();
    gotoxy(x, y++);
    printf("  �ι�° �׽�Ʈ: ������� ���� ����");    getchar(); gotoxy(x, y++);
    printf("  [������] ����� ���� ������ �׽�Ʈ����");  getchar(); gotoxy(x, y++);
    printf("  [������] �̹��� ���� ������ �� �� Ȯ���غ���");  getchar(); gotoxy(x, y++);
    printf("  [������] �̹� �׽�Ʈ�� ��Ģ�� ����������");  getchar(); gotoxy(x, y++);
    printf("  *������ ������� ���� ���õȴ�. ������� ���� �������� ���������ִ�."); getchar();
    y = 22;
    system("cls");
    print_frame();
    gotoxy(x, y++);
    printf("  *�� ������ ���� �����ϰ�, �� ���� �� �ϳ��� ���� ���� �����ϴ�.");   getchar();  gotoxy(x, y++);
    printf("  *������ ������ ������ ���� ������ �� ����."); getchar();  gotoxy(x, y++);
    printf("  *��� ������ �����ϸ� �׽�Ʈ�� ����ȴ�.");   getchar(); gotoxy(x, y++);
    printf("  [������] ���� ��� ������ �ּ��� ���� �̿��ؼ� �����Ѵٸ� [���]��������");  getchar();
}
void ThirdTest() {
    int x, y;
    x = 3;
    y = 22;
    system("cls");
    print_frame();
    gotoxy(x, y++);
    printf("  ����° �׽�Ʈ: ���� ���� �ɷ�");    getchar(); gotoxy(x, y++);
    printf("  [������] �Ƿ��� �� �������� ���� �� ����");  getchar(); gotoxy(x, y++);
    printf("  [������] ������ ���� ���� ������, �̹��� ȿ������ �Ǵܷ��� Ȯ���غ��ڴ�");  getchar(); gotoxy(x, y++);
    printf("  [������] ����� �۾��� �־��� ����Ʈ��. �������� ���� ���� ����� �� �ð��� �˾Ƴ���");  getchar(); gotoxy(x, y++);
    printf("  [������] ����� �°ų� �� ���� ����� �����ٸ� [���]��������");  getchar();  gotoxy(x, y++);
    y = 22;
    system("cls");
    print_frame();
    gotoxy(x, y++);
    printf("*��Ģ*");  getchar();  gotoxy(x, y++);
    printf("*�� �۾��� �ϳ��� ������Ը� ���������� ����˴ϴ�");  getchar();  gotoxy(x, y++);
    printf("*�� ����� �ϳ��� �۾����� �����մϴ�");  getchar();  gotoxy(x, y++);
}
void LastTest() {
    int x, y;
    x = 3;
    y = 22;
    system("cls");
    print_frame();
    gotoxy(x, y++);
    printf("  ������ �׽�Ʈ: ��¯ �׽�Ʈ");    getchar(); gotoxy(x, y++);
    printf("  [������] ������� �� ���� �����°�");  getchar(); gotoxy(x, y++);
    printf("  [������] ���� �������� �ϳ� �����"); getchar();  gotoxy(x, y++);
    printf("  [������] ������� �Ƿ��� �ռ� �׽�Ʈ���� Ȯ��������");   getchar(); gotoxy(x, y++);
    printf("  [������] �̹��� ���� ����� �󸶳� ������ �� �� Ȯ���غ���"); getchar();
    y = 22;
    system("cls");
    print_frame();
    gotoxy(x, y++);
    printf("  [������] �б� �տ� �ִ� <�������� ���汸> ����?");  getchar(); gotoxy(x, y++);
    printf("  [������] �ű⿡�� ���� �����ϴ� ���ǵ��� �� ���Ŀͺ�");   getchar(); gotoxy(x, y++);
    printf("  [������] ��ġ�� �ɸ��� �� �𸣴� ���̴ϱ� �˾Ƽ� �ϰ�"); getchar();  gotoxy(x, y++);
    printf("  [������] ���� <�ǳ�ȭ ����>�� �ִ��� ��ƿ���"); getchar();  gotoxy(x, y++);
    printf("  �����̴� �������� ���� �����Ѵ�. ��ġ�� ���� ������ �ִ��� ���� ì��°� �����̴�."); getchar();
}
int selectToStealItem(ItemType* head, ItemType* inventory) {
    while (_kbhit()) {
        _getch();
    }
    while (1) {
        gotoxy(100, 1);
        printf("*��ġ�� ����[0��]*");
        gotoxy(65, 3);
        printf(">>��ĥ ������ ��ȣ �Է�>>");
        scanf_s("%d", &itemNum);
        if (1 <= itemNum && itemNum <= ITEM) {
            if (head->itemList[itemNum]->isStolen) {
                gotoxy(65, 4);
                printf("*%s�� �̹� ��ģ �����Դϴ�*", head->itemList[itemNum]->name);
                Sleep(1000);
                system("cls");
                print_totalItemList(head, inventory);
            }
            else if ((inventory->capacity - head->itemList[itemNum]->weight) < 0) { //�賶�� �뷮�� �ʰ��ϸ� ����ó��
                gotoxy(65, 4);
                printf("*���� �ʹ� �����ϴ�*");
                Sleep(1000);
                system("cls");
                print_totalItemList(head, inventory);
            }
            else {
                return 0; //��ġ�� ��� ���
            }
        }
        else if (itemNum == 0) {
            return 1; //��ġ�� ��� ����
        }
        else {
            gotoxy(65, 4);
            printf("*��ȿ�� ��ȣ�� �Է��ϼ���(1~%d)*", ITEM);
            Sleep(1000);
            system("cls");
            print_totalItemList(head, inventory);
        }

    }
}
void free_item(ItemType* head) {
    for (int i = 0; i < ITEM + 1; i++) {
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
    insert_itemList(List, create_item("��Ƽ", randomValue[0], randomWeight[0], 1));
    insert_itemList(List, create_item("����� ī��", randomValue[1], randomWeight[1], 4));
    insert_itemList(List, create_item("������ ����", randomValue[2], randomWeight[2], 3));
    insert_itemList(List, create_item("��ī��", randomValue[3], randomWeight[3], 4));
    insert_itemList(List, create_item("����� �ϱ���", randomValue[4], randomWeight[4], 2));
    insert_itemList(List, create_item("�Ź� �ڼ�", randomValue[5], randomWeight[5], 5));
    insert_itemList(List, create_item("���� ����", randomValue[6], randomWeight[6], 2));
    insert_itemList(List, create_item("ƾĳ�� 1����", randomValue[7], randomWeight[7], 4));
    insert_itemList(List, create_item("��Ż���̺��̵�", randomValue[8], randomWeight[8], 5));
}

int main(void) {

    init();

    print_title();

    introText();

    firstTest(); //ù��° ���� �����̿� �޸��� ����
    Sleep(500);

    projectTSP();
    Sleep(500);

    secondTest(); //�ι�° ���� �ּҰ� �����Ա�
    Sleep(500);

    GC();
    Sleep(500);

    ThirdTest(); // ����° �۾� ������
    Sleep(500);

    projectJS();
    Sleep(500);

    LastTest();//������ ���� ������ �ɷ� �׽�Ʈ
    Sleep(500);

    ItemType List;
    ItemType bag;

    init_list(&bag);

    //������ ����Ʈ ����
    init_list(&List);

    itemGenerator(&List);


    //�̹��� ���� ����ü ������ ����

    fp_closeEye = fopen("ClosedEye.txt", "rt");
    fp_openEye = fopen("OpenEye.txt", "rt");
    fp_gameover = fopen("gameover.txt", "rt");
    fp_question = fopen("questionMark.txt", "rt");
    fp_happyEnding = fopen("HappyEnding.txt", "rt");
    fp_badEnding = fopen("BadEnding.txt", "rt");

    if (fp_closeEye == NULL) {
        fprintf(stderr, "����1 �ҷ����� ����");
        return 1;
    }
    if (fp_openEye == NULL) {
        fprintf(stderr, "����2 �ҷ����� ����");
        return 1;
    }
    if (fp_gameover == NULL) {
        fprintf(stderr, "����3 �ҷ����� ����");
        return 1;
    }

    if (fp_question == NULL) {
        fprintf(stderr, "����5 �ҷ����� ����");
        return 1;
    }
    if (fp_happyEnding == NULL) {
        fprintf(stderr, "����6 �ҷ����� ����");
        return 1;
    }
    if (fp_badEnding == NULL) {
        fprintf(stderr, "����7 �ҷ����� ����");
        return 1;
    }


    //��ġ�� ���� ����
    while (1) {

        system("cls");

        print_totalItemList(&List, &bag);//������ ��� ���

        if (selectToStealItem(&List, &bag))//��ĥ ��ǰ ��ȣ �Է¹ޱ�
            break;
        spaceCount = 20 * List.itemList[itemNum]->difficulty;

        if (monitoring()) {
            Sleep(500);
            system("cls");

            insert_itemList(&bag, List.itemList[itemNum]);

            print_userItemList(&bag);

            List.itemList[itemNum]->isStolen = true;
            gotoxy(35, 10);

            printf("%s�� ��ġ�µ� �����ߴ�!", List.itemList[itemNum]->name);
            Sleep(2000);
        }
        else {
            system("cls");
            gotoxy(35, 10);
            printf("%s�� ��ġ�� ���ߴ�..���� ��ȸ�� �������", List.itemList[itemNum]->name);
            Sleep(2000);
        }

    }
    system("cls");
    //��� ����
    int i = 0;
    while (i < 3) {
        gotoxy(35, 13); printf("����ǰ �˻���."); Sleep(500);
        gotoxy(35, 13); printf("����ǰ �˻���.."); Sleep(500);
        gotoxy(35, 13); printf("����ǰ �˻���..."); Sleep(500);
        system("cls");
        i++;
    }

    print_userItemList(&bag);

    int isClear = knapsack(&bag, &List, cost);
    Sleep(5000);

    fclose(fp_closeEye);
    fclose(fp_openEye);
    fclose(fp_gameover);

    free_item(&List); //�����Ҵ� ����
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


    srand(time(NULL)); // �Ź� �ٸ� �õ尪 ����

    EdgeList* edgeList = (EdgeList*)malloc(sizeof(EdgeList));

    init_edgeList(edgeList, SIZE);

    // edgelist ����
    create_edgeList(edgeList);
    //print_edgeList(edgeList);

    // �� ���
    print_map(edgeList);



    //MST����
    sort_edge(edgeList); // ����ġ ������ ����
    EdgeList* mst = (EdgeList*)malloc(sizeof(EdgeList));
    init_edgeList(mst, SIZE);
    create_MST(edgeList, mst);


    sort_edge_v1(mst);//MST�� ���� ���� ����
    int path_arr[SIZE + 1];

    EdgeList* stack = (EdgeList*)malloc(sizeof(EdgeList)); //���� ����
    init_edgeList(stack, 0);

    // **************TSP �ٻ��� ���*******************
    create_TSP(edgeList, mst, stack, path_arr);


    // **********************�÷��̾� ��� �Է�******************
    int player_input = 0;
    player_path[0] = 0;
    count = 1;
    while (count < SIZE) {
        system("cls");
        print_map(edgeList);
        system("cls");
        print_map(edgeList);
        int is_input = TRUE;
        printf("====================================�̵� ���====================================\n");
        print_path(player_path, count);
        printf("\r�̵� ��ġ : ");
        scanf("%d", &player_input);
        for (int i = 0; i < SIZE; i++) {
            if (player_path[i] == player_input) {
                printf("�̹� �� ���Դϴ�.\n");
                is_input = FALSE;
                break;
            }
            else if (!(0 <= player_input && player_input <= SIZE)) {
                printf("�߸��Է��߽��ϴ�.");
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



    //************* �÷��̾� ���� ����ġ ��� *****************
    printf("===================================�̵� ���===================================\n");
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

    //���� ���丮 ���ߵ� *���� �κ�
    int i = 0;
    while (i < 3) {
        gotoxy(35, 13); printf("��� �˻���."); Sleep(500);
        gotoxy(35, 13); printf("��� �˻���.."); Sleep(500);
        gotoxy(35, 13); printf("��� �˻���..."); Sleep(500);
        system("cls");
        i++;
    }
    gotoxy(35, 10); printf("====================================�� ���====================================");
    gotoxy(35, 11); print_path(player_path, count);
    gotoxy(35, 13); printf("==================================���� ���==================================");
    gotoxy(35, 14); print_path(path_arr, SIZE + 1);
    Sleep(3000);
    system("cls");
    if (player_sum > tsp_sum) {
        gotoxy(35, 13); printf("���º��� %d�� �ʾ���", player_sum - tsp_sum); Sleep(1000);
        gotoxy(35, 14); printf("�����ú��� �����µ�??"); Sleep(1000);
        gotoxy(35, 15); printf("�ٽ� �տ� ��� �Ÿ��� ����"); Sleep(1000);
        gotoxy(35, 16); printf("���� �ð� �����߳� ���� ��"); Sleep(1000);
        //exit(0);
    }
    else if (player_sum == tsp_sum) {
        gotoxy(35, 13); printf("���¶� ���ÿ� �����߱�"); Sleep(1000);
        gotoxy(35, 14); printf("���� �������� �Ѿ��"); Sleep(1000);
    }
    else {
        gotoxy(35, 13); printf("���º��� %d�� ������", tsp_sum - player_sum); Sleep(1000);
        gotoxy(35, 14); printf("�������� ���º��� ����"); Sleep(1000);
        gotoxy(35, 15); printf("���� ���� �������� �Ѿ��"); Sleep(1000);
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

void sort_edge(EdgeList* edgeList) { // ������ ���� ���� ����
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
            case '0': printf("��"); break;
            case '2': printf("��"); break;
            case '3': printf("��"); break;
            case '1': printf("��"); break;
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

void create_edgeList(EdgeList* edgeList) {	//������ �����ϸ� 1~10�� ����ġ�� ���� ���� ����
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
            printf("[���� ���̽�]");
            break;
        case 1:
            printf("-[A ����]->");
            break;
        case 2:
            printf("-[�κ�]->");
            break;
        case 3:
            printf("-[B ����]->");
            break;
        case 4:
            printf("-[��� ���̽�]->");
            break;
        default:
            printf("[���� ���̽�]");
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
        //�̹� �湮�ߴ� ���̸� ���X
        for (int i = 0; i <= count; i++) {
            if (path_arr[i] == cur_vertex) {
                is_path_input = FALSE;
                break;
            }
        }
        if (is_path_input == TRUE) {
            path_arr[count++] = cur_vertex;
        }
        // mst�� ���� ��ġ���� �� �� �ִ� ���� �ִٸ�
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
    for (int i = 1; i <= SIZE + 1; i++) { // ��� ����ġ �� ���ϱ�
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
/// node_color �迭�� color�� ĥ�Ѵ�.
/// </summary>
/// <param name="node_color">ĥ�� color�� �����صα� ���� �迭</param>
/// <param name="node_index">ĥ�� node�� ����Ű�� ���� ����</param>
/// <param name="color">node�� ĥ�� ����</param>
int GraphColoring(int* node_color, int node_index, int color) {
    int promise;
    for (int j = 0; j < NODE_NUM; j++) {
        // ���� ��忡 ���� ���� ĥ���� �ִٸ� return�Ѵ�.
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
/// GC_Print �Լ����� patternLength��ŭ patternNum�� setColor�ؼ� ���
/// </summary>
/// <param name="patternLength">patternNum�� �ݺ��Ǵ� Ƚ��</param>
/// <param name="patternNum">����� ��</param>
void PrintPattern(int patternLength, char patternNum) {

    for (int i = 0; i <= patternLength; i++) {
        printf("%c", patternNum);
    }

    return;
}

/// <summary>
/// ���� ���̺��� �̿��Ͽ� map�� color �迭�� ���� ������ش�.
/// </summary>
/// <param name="input_color">map�� ����(0~12), 14:line color</param>
void GC_PrintMap(int* input_color) {
    system("cls");
    gotoxy(0, 0);
    for (int i = 0; i < GC_MAP_ROW; i++) {
        int currentCharPoint = 3;
        int patternTable[20] = { 0, };
        int patternTableIdx = 0;

        while (currentCharPoint + 1 <= GC_MAP_COL) {
            // ���� �ε��� ���ڿ� ���ؼ� ���ٸ� ���� ���̺� += 1
            if (map_gc[i][currentCharPoint] == map_gc[i][currentCharPoint + 1]) {
                currentCharPoint++;
                patternTable[patternTableIdx]++;
            }
            else { // ���� �ʴٸ�
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
/// �÷��̾ �Է��� input_color�� �˰����� ���� ���� node_color�� ���ϸ� �������� Ȯ��
/// </summary>
/// <param name="node_color">���信 �ش��ϴ� node_color</param>
/// <param name="input_color">�÷��̾ �Է��� input_color</param>
/// <returns></returns>
int CheckAnswer(int* node_color, int* input_color) {
    int success = 1;

    for (int i = 0; i < NODE_NUM; i++) {
        if (node_color[i] != input_color[i])
            success = 0;
    }
    int i = 0;
    while (i < 3) {
        gotoxy(35, 13); printf("��� �˻���."); Sleep(500);
        gotoxy(35, 13); printf("��� �˻���.."); Sleep(500);
        gotoxy(35, 13); printf("��� �˻���..."); Sleep(500);
        system("cls");
        i++;
    }
    system("cls");
    if (success) {
        gotoxy(35, 13); printf("�׷��� �������� ���� �ƴϱ�"); Sleep(1000);
        gotoxy(35, 14); printf("���� ���� �������� �Ѿ��"); Sleep(1000);
    }
    else {
        gotoxy(35, 13); printf("������ ������ �༮�̱�"); Sleep(1000);
        gotoxy(35, 14); printf("���� �츮 ���ؿ��� �ȸ¾�"); Sleep(1000);
        gotoxy(35, 15); printf("���� ���γ� �ض�"); Sleep(1000);
        //exit(0);
    }


    return success;
}
int GC() {
    int success = 1;

    int node_color[15];
    int input_color[15];

    // input_color�� ���� ���(15)�� �ʱ�ȭ
    for (int i = 0; i < 12; i++) {
        input_color[i] = 15;
    }

    input_color[14] = 187;
    node_color[14] = 187;

    for (int i = 0; i < 12; i++) {
        GC_PrintMap(input_color);
        printf("%c ������ ������ ��(0, 1, 2, 3, 4 ...)�� �Է�.��, a ������ 0 �� ����, b ������ 1�� ���� �Է�\n", i + 'a');
        printf("���� ��ȣ>> ");
        scanf_s("%d", &input_color[i]);
        input_color[i]++;
        node_color[i] = -1;
        system("cls");
    }

    GraphColoring(node_color, 0, 0);

    CheckAnswer(node_color, input_color);

    return 0;
}
int JobSchedule(int machine[], int task[], int machine_count, int task_count)
{
    int min = 0; //���� ���� �۾��� ������ ��� �� ó���� ù��° ���� ����

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
char JobSchedule_person(int machine[], int task[], int machine_count, int task_count)
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

    for (int k = 0; k < machine_count; k++)
    {
        if (machine[k] == Bigger(machine))
        {
            person = k + 65;
            return person;
        }
    }
}
void print_Story()
{
    int x = 1, y = 1;
    gotoxy(x, y++);
    printf("��������   �۾� ����Ʈ  ���������"); gotoxy(x, y++);
    printf("��          �ο� : A,B,C,D  �� 4��          ��"); gotoxy(x, y++);
    printf("��   �۾��� : 40�ð��� 10���� ������ ����   ��"); gotoxy(x, y++);
    printf("��   ���� �۾� ���� : 5,2,4,3,4,7,8,2,4,1   ��"); gotoxy(x, y++);
    printf("������������������������"); gotoxy(x, y++);
}
int Bigger(int num[])
{

    for (int i = 0; i < num; i++)
    {
        if (num[i] > num[i + 1])
        {
            return num[i];
        }
    }
}
void projectJS()
{
    int Person[4] = { 0,0,0,0 };
    int task[10] = { 5,2,4,3,4,7,8,2,4,1 };
    char input;
    char person = '\0';
    int Person_count = 4;
    int task_count = 10;
    int result = 0;
    int alg_result = 0;
    char alg_person;
    int min = 0;
    int i = 0;
    int x = 1, y = 1;

    while (i < task_count)
    {
        print_Story();

        int x = 0, y = 10;
        gotoxy(x, y++);
        printf("������������������������"); gotoxy(x, y++);
        printf("��         �۾� %d�� �������� �ñ��?        ��", task[i]); gotoxy(x, y++);
        printf("������������������������"); gotoxy(x, y++);

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

    alg_person = JobSchedule_person(Person, task, Person_count, task_count);
    alg_result = JobSchedule(Person, task, Person_count, task_count);

    system("cls");

    printf(" �������� ���� § ��� ����������"); gotoxy(x, y++);
    printf("������������������������"); gotoxy(x, y++);
    printf("��       ���� �ʰ� ������ �ð� : %d          ��", result); gotoxy(x, y++);
    printf("��       ���� �ʰ� ������ ��� : %c          ��", person); gotoxy(x, y++);
    printf("������������������������"); gotoxy(x, y++);
    gotoxy(x, y++);
    gotoxy(x, y++);
    gotoxy(x, y++);
    printf("��������      ����      ���������"); gotoxy(x, y++);
    printf("������������������������"); gotoxy(x, y++);
    printf("��       ���� �ʰ� ������ �ð� : %d         ��", alg_result); gotoxy(x, y++);
    printf("��       ���� �ʰ� ������ �ð� : %c          ��", alg_person); gotoxy(x, y++);
    printf("������������������������"); gotoxy(x, y++);
    Sleep(10000);

    system("cls");

    if (result == alg_result || result < alg_result)
    {
        int x = 0, y = 4;
        gotoxy(x, y++);
        printf("���������������������"); gotoxy(x, y++);
        printf("��                                    ��"); gotoxy(x, y++);
        printf("��      ���! �������� �� �ϴ±�      ��"); gotoxy(x, y++);
        printf("��                                    ��"); gotoxy(x, y++);
        printf("���������������������"); gotoxy(x, y++);
        Sleep(5000);
    }
    else
    {
        int x = 0, y = 4;
        gotoxy(x, y++);
        printf("���������������������"); gotoxy(x, y++);
        printf("��                                    ��"); gotoxy(x, y++);
        printf("��   ����, �Ӹ��� �� �ȵ��ư�������   ��"); gotoxy(x, y++);
        printf("��                                    ��"); gotoxy(x, y++);
        printf("���������������������"); gotoxy(x, y++);
        Sleep(5000);
    }
}


