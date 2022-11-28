#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>


#define DIFFICULTY 200 //���̵�(���� Ȯ��)
#define ITEM 6 // ������ ����
#define LEN 20 // Ÿ�̸� �� ����
#define MAX_NUM(x,y)(x)>(y)? x:y //�賶 �˰��� �ִ밪 �Լ�


//2011�� ����, �÷��̾� = �����(12��), 
// 
//����� Ư: �п� �� �ǹ� ���� 1���� �ִ� �ϳ��� ��Ʈ���� ���� ��ġ�⸦ ����.
//������� ��: �Ͽ��� ��Ÿ ���� ��¯ �����̿� ģ������ ��.
// 
//��������(3): [1]��������: �������� �ɺθ� �ϼ��ϱ�(����� ī��)
             //[2]��������: �������� �ɺθ� �ϼ��ϱ�(ƾĳ�� 1������)
             //[3]��������: �������� �ɺθ� �ϼ��ϱ�(���)
             // 
//[1]�������� : �������� ���汸 -  ���� ���{1.��Ƽ 2.����� ī�� 3.������ ����(����) 4.���� 5.��ī�� 6.������ 7.BBź ���� 8.����ǳ�� 9.��Ż���̺��̵� 10.�˸��� 11.�Ź� �ڼ� ���}
//[2]�������� : �ѹ̸� ��Ʈ - ���� ���{1.���ϸ� 2.500��(��ū�� ��) 3.�ﰢ ��� 4.�նѲ� 5.ƾĳ�� 6.��ī�ݶ� 1.5L 7.�ٳ����� ���� 8.����Ŷ �պ� 9.TOP ������ �� 10.��īĨ}
//[3]�������� : ���� ���� - ���� ���{1.�����佺 2.���ϵ� ����(���) 3.Ȩ���� 4.������ 5.���ϸ��� 6.���̽� 7.�ƽ� ȭ��Ʈ ��� 8.�ڿ��� ���� ���� ��Ʈ }

// �� ���ǿ��� ��ȣ��(��ġ)�� �߰� ���(����)�� ����.
// 
// ������ ���Ǻ��� ���� �� ���ǵ��� �߰� ��� ���� Ŭ ��� -> ������ �߰� ���ؼ� ���� ����
// 
// �ɺθ� ������ ���� ��ȣ������ ���� �� ���ǵ��� ��ȣ�� ���� ���� ��� -> �ɺθ� ���ΰ� ģ������ �����ؼ� ���� ����
// 
//���� {1.�ǳ�ȭ ���� 2.å����}

typedef struct {
    char* name; //������ �̸�
    int price;  //������ ��ġ
    int weight; //������ �뷮
    int difficulty; //������ ���̵�
    bool isStolen; //�̹� ��ģ �������� ����ġ�� ����
}Item;

typedef struct {
    int size;  //������ ����Ʈ ũ��
    Item* itemList[ITEM+1];  //������ �迭
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
int userSolution=0; //����� �賶�� �� ��ġ
int userCap=0; //����� �賶�� �� ����

//============���� �Լ� ����============
void init();
void print_title();
void game_over(ItemType* List);

//===========������ ���� �Լ� ����============
Item* create_item(char* name, int p, int w, int d);
void insert_itemList(ItemType* head, Item* item);
void print_userItemList(ItemType* head);
void print_totalItemList(ItemType* head);
int selectToStealItem(ItemType* head,ItemType* inventory);
void print_inventory();
//===========���� ��� �Լ� ����==============
void print_monitoring(FILE* fp);

//===========�賶 �˰���=================
int knapsack(ItemType* bag, ItemType* head, int cost);

void game_clear();
void game_fail();

void gotoxy(int x, int y)

{

    COORD pos = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

//===========������ ����Ʈ �ʱ�ȭ===========
void init_list(ItemType* head) {
    head->size = 0;
    head->capacity = cost;
    for (int i = 0; i < ITEM+1; i++) {
        head->itemList[i] = NULL;
    }
}
//===========������ ����===========
Item* create_item(char* name,int p,int w,int d) {
    Item* temp = (Item*)malloc(sizeof(Item));
    temp->name = name;
    temp->price = p;
    temp->weight = w;
    temp->difficulty = d;
    temp->isStolen = false;
    return temp;
}
//===========������ ����Ʈ�� �߰�===========
void insert_itemList(ItemType* head,Item* item) {
    head->itemList[head->size++] = item;
    head->capacity -= item->weight;
}

//===========������ ����Ʈ ���===========
void print_userItemList(ItemType* head) {

    int x, y;
    x = 35;
    y = 12;
    gotoxy(x, y++);
    printf("================�ǳ�ȭ ����================\n");
    for (int i = 0; i < head->size; i++) {
        gotoxy(x, y++);
        printf("%d.[%s]",i+1,head->itemList[i]->name);
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
void print_totalItemList(ItemType* head,ItemType* inventory) {
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
    printf("#�뷮:%2d/ %d#",sum_weight,cost );
    gotoxy(x, y++);
    printf("#��ġ:%2d    #", sum_price);
    gotoxy(x, y++);
    printf("#����:%2d / %d#", inventory->size, ITEM);
    gotoxy(x, y++);
    printf("#############");

}
//===========�賶 �˰���===========
int knapsack(ItemType* bag,ItemType* head,int cost) {
    int i, w;
    int bestSolution;
    int bestSolution_weight = 0;
    w = cost;
    //==========0/1�賶 2���� �迭 ����(�����Ҵ�)==========
    int** wp = (int**)malloc(sizeof(int*)*(ITEM+1));
    
    for(int i=0;i<ITEM+1;i++){
        wp[i] = (int*)malloc(sizeof(int)*(cost+1));
    }
    //==========�賶 �ʱ�ȭ==========
    for(int i=0;i<ITEM+1;i++){
        for(int j=0;j<cost;j++){
            wp[i][j] = 0;
        }
    }
    //==========0/1 �賶 �˰���==========
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

    //==========0/1 �賶 �˰��� ��� ���==========
    gotoxy(0, 1);
    printf(" ===0/1 �賶 �˰��� ���===");
    for (i = 1; i < ITEM + 1; i++) {
        gotoxy(0, i+1);
        for (w = 1; w < cost+1; w++) {
            
            printf("%2d ", wp[i][w]);
        }
        
    }
    //==========�賶�� ���Ե� ��� Ȯ�� �˰���==========

    w = cost;
    int include[ITEM + 1] = { 0 };//���� ������ ����Ʈ
    
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
    //==========���� �迭 ����==========
    for(int i=0;i<ITEM+1;i++){
        free(wp[i]);
    }
    free(wp);
    //==========�賶 ����==========
    gotoxy(0, 9); printf("===���� ���� ����Ʈ===");
    gotoxy(0, 10);
    printf("[1] [2] [3] [4] [5] [6]");
    gotoxy(0, 11);
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
    //==========�����ؿ� ���� �賶 ��==========
    int iq =1;
    int x, y;
    
    x = 35;
    y = 1;
    
    gotoxy(x, y++); printf("==================������===================");
    for (int j = 0; j < ITEM + 1; j++) {
        if (include[j]) {
            gotoxy(x, y++);
            printf("%d.[%s]", iq,head->itemList[j]->name);
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
    if (userSolution == bestSolution && userCap <= bestSolution_weight) { //������ �ذ� �������̸� �� ��ȯ
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
    gotoxy(30, 15);
    printf("��Ҵ� ���!\n");
    Sleep(2000);
    gotoxy(30, 16);
    printf("ó������ �ٽ��ϼ���");
    Sleep(2000);
    print_monitoring(fp_gameover);
    Sleep(2000);
    main();
    //retry�� �� �ֵ��� ����ٰ� �ߴ�
}
void game_clear() {
    gotoxy(1, 1);
    printf("���İ� ���ǵ��� �����̸� ������Ų �� ����."); getchar();
    printf("�����̰� ����� �ٰ��� �� ����� ������ �ε帮�� ���ߴ�."); getchar();
    printf("�ʵ� ���� ���Ϻ��� �ǹ� ����"); getchar();
    printf("��ΰ� ���� �տ��� �Ͽ��� ��¯ Ŭ���� ����..!"); getchar();
    printf("���� [���] ���� �� �ִٱ�..!"); getchar();
    Sleep(1000);
    system("cls");
    exit(0);
}
void game_fail() {
    gotoxy(1, 1);
    printf("�ǳ�ȭ ���� ���� �鿩�� �� �������� ������ ��ο�����.\n"); getchar();
    printf("��¥ x�ƴ�...\n"); getchar();
    printf("�����̰� ���� �Ѽ��� �������� ���ߴ�.\n"); getchar();
    printf("[�� �ȵǰڴ�, ������ ��ħ ���� �޽��� �ʰ� �����Ͷ�]\n"); getchar();
    printf("[��Ƽ ������ ������]\n"); getchar();
    printf("��ΰ� ���� �տ��� �Ͽ��� �ְ� ���� ����� ����ߴ�.\n"); getchar();
    Sleep(1000);
    system("cls");
    exit(0);
}
void printSpaceCount() {
    gotoxy(0, 27);
    printf("%d", spaceCount);
}
void keyIn() {
    int userInputKey;
    userInputKey = _getch();
    if (userInputKey == 32) {
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
    int count = 0;  //Ÿ�̸� ī��Ʈ ����
    float tick = (float)100 / LEN; //1ƽ = 5�ۼ�Ʈ
    int bar_count;      //�� ����
    int blank_count = 0;//���� ����
    float percent; //�ۼ������� ����



    while (count <= MAX) {

        gotoxy(0, 0);
        //Ÿ�̸Ӱ� ����Ǵ� ���� ����

        //==============================================
        printf("\r%d/%d [", MAX, MAX - count);
        percent = (float)count / MAX * 100;
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
        if (random == 200) {//200�� ������ ���� ���

            endTime = (unsigned)time(NULL);

            monitorTime = rand() % 4 + 1; //1��~4�� ����

            endTime += monitorTime;
            print_monitoring(fp_question);
            Sleep(250);
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

        count++;
        if (spaceCount <= 0) {
            return 1;//��ġ�� ����
        }
    }
    
    return 0;
}

void init() {
    system("mode con cols =30 lines = 130 | title �Ͽ��� ��¯ �Ǳ�");
    //Ŀ�� ������ ���ֱ�
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

}

int selectToStealItem(ItemType* head,ItemType* inventory) {
    while (_kbhit()) { 
        _getch();
    }
    while (1) {
        gotoxy(100, 1);
        printf("*��ġ�� ����[0��]*");
        gotoxy(65, 3);
        printf(">>��ĥ ������ ��ȣ �Է�>>");
        scanf_s("%d", &itemNum);
        if (0 < itemNum && itemNum < 7) {
            if (head->itemList[itemNum]->isStolen) {
                gotoxy(65, 4);
                printf("%s�� �̹� ��ģ �����Դϴ�.", head->itemList[itemNum]->name);
                Sleep(1000);
                system("cls");
                print_totalItemList(head, inventory);
            }
            else if ((inventory->capacity - head->itemList[itemNum]->weight) < 0) { //�賶�� �뷮�� �ʰ��ϸ� ����ó��
                gotoxy(65, 4);
                printf("���� �ʹ� �����ϴ�.");
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
            printf("��ȿ�� ��ȣ�� �Է��ϼ���.(1~6)");
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

int main(void) {
    init();

    ItemType List;
    ItemType bag;
    init_list(&bag);
    init_list(&List);

    //������ ����Ʈ ����
    insert_itemList(&List, create_item(" ", 0, 0,0));
    insert_itemList(&List, create_item("��Ƽ", 2, 1,1));
    insert_itemList(&List, create_item("����� ī��", 5, 4,4));
    insert_itemList(&List, create_item("������ ����", 3, 2,3));
    insert_itemList(&List, create_item("��ī��", 4, 4,4));
    insert_itemList(&List, create_item("����� �ϱ���", 2, 3,2));
    insert_itemList(&List, create_item("�Ź� �ڼ�", 6, 5,5));


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

    print_title();
    //��ġ�� ���� ����
    while (1) {

        system("cls");

        print_totalItemList(&List,&bag);//������ ��� ���

        if (selectToStealItem(&List, &bag))//��ĥ ��ǰ ��ȣ �Է¹ޱ�
            break;
        spaceCount = 20 * List.itemList[itemNum]->difficulty;

        if (monitoring()) {
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
    int isClear = knapsack(&bag,&List, cost);
    Sleep(5000);
    if (isClear) {
        system("cls");
    }
    fclose(fp_closeEye);
    fclose(fp_openEye);
    fclose(fp_gameover);

    free_item(&List); //�����Ҵ� ����
    system("cls");
    Sleep(1000);
    int x = 1;
    int y = 1;
    gotoxy(x, y);
    printf("���İ� ���ǵ��� �����̸� ������Ų �� ����."); Sleep(3000);
    y += 2;
    gotoxy(x, y);
    printf("�����̰� ����� �ٰ��� �� ����� ������ �ε帮�� ���ߴ�."); Sleep(3000);
    y += 2;
    gotoxy(x, y);
    printf("[���� �б� ������ ���������� ��]");  Sleep(3000);
    y += 2;
    gotoxy(x, y);
    printf("��ΰ� ���� �տ��� �Ͽ��� ��¯ Ŭ���� ����..!"); Sleep(3000);
    y += 2;
    gotoxy(x, y);
    printf("���� [���] ���� �� �ִٱ�..!"); Sleep(3000);
    Sleep(1000);
    system("cls");
    print_monitoring(fp_happyEnding);
    Sleep(3000);
    print_monitoring(fp_badEnding);
    exit(0);

    //���� ���� �̱���
   /* if (isClear) {
        game_clear();
    }
    game_fail();*/
    return 0;
}
