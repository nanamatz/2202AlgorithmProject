#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>


#define DIFFICULTY 100
#define ITEM 6
#define LEN 20
#define MAX_NUM(x,y)(x)>(y)? x:y


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
    bool isStolen;
}Item;

typedef struct {
    int size;  //������ ����Ʈ ũ��
    Item* itemList[ITEM+1];  //������ �迭
}ItemType;

//��������
//bool isCaught;  //��ġ�� �ɷȴ��� Ȯ���ϴ� ����
bool isStolen; //���ƴ��� Ȯ���ϴ� ����
FILE* fp_gameover = NULL; //���ӿ��� �ƽ�Ű ��Ʈ ���� ������
FILE* fp_text = NULL; //�ؽ�Ʈ ���� ������
FILE* fp_closeEye = NULL;
FILE* fp_openEye = NULL;
FILE* fp_question = NULL;
FILE* fp_userInput = NULL;
char text[256]; //���Ͽ��� �о���� ���ڿ� ���� ����
int itemNum; //����ڰ� �����ϴ� ������ ��ȣ
int spaceCount;
int cost = 20;// 0/1�賶 �� ũ��(���)

//============���� �Լ� ����============
void init();
void print_title();
void game_over(ItemType* List);

//===========������ ���� �Լ� ����============
Item* create_item(char* name, int p, int w, int d);
void insert_itemList(ItemType* head, Item* item);
void print_userItemList(ItemType* head);
void print_totalItemList(ItemType* head);
void selectToStealItem();
void print_inventory();
//===========���� ��� �Լ� ����==============
void print_monitoring(FILE* fp);

//===========�賶 �˰���=================
void knapsack(ItemType* bag, ItemType* head, int cost);



void gotoxy(int x, int y)

{

    COORD pos = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

//===========������ ����Ʈ �ʱ�ȭ===========
void init_list(ItemType* head) {
    head->size = 0;
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
}

//===========������ ����Ʈ ���===========
void print_userItemList(ItemType* head) {
    int sum_price = 0;
    int sum_weight = 0;
    printf("===================��ǰ ���==================\n");
    for (int i = 0; i < head->size; i++) {
        printf("[%d]<%s>",i+1,head->itemList[i]->name);
        sum_price += head->itemList[i]->price;
        sum_weight += head->itemList[i]->weight;
        printf("\n");
    }
    printf("==================��ġ ����===================\n");
    printf("�� ��ġ: [%d]\n", sum_price);
    printf("==================��ġ ����===================\n");
    printf("�� ����: [%d]", sum_weight);
}
//===========��ĥ ������ ����Ʈ ���===========
void print_totalItemList(ItemType* head,ItemType* inventory) {

    printf("===================��ǰ ���==================\n");
    for (int i = 1; i < head->size; i++) {
            printf("[%d]<%s>\n", i, head->itemList[i]->name);
            printf("###����:   [%d] \n###����:   [%d] \n###���̵�: [%d]", head->itemList[i]->price, head->itemList[i]->weight, head->itemList[i]->difficulty);
            printf("\n\n");

    }
    print_inventory(inventory);

}
void print_inventory(ItemType* inventory) {
    int sum_price = 0;
    int sum_weight = 0;
    int x, y;
    x = 20;
    y = 15;
    gotoxy(x,y++);
    printf("    #####");    gotoxy(x, y++);
    printf("  ##     ##");    gotoxy(x, y++);
    printf(" ##       ##");    gotoxy(x, y++);
    printf("##         ##");    gotoxy(x, y++);
    printf("#############");    
    for (int i = 0; i < inventory->size; i++) {
        sum_price += inventory->itemList[i]->price;
        sum_weight += inventory->itemList[i]->weight;
    }
    gotoxy(x, y++);
    printf("#�뷮: %d/ %d#",sum_weight,cost );
    gotoxy(x, y++);
    printf("#��ġ: %d    #", sum_price);
    gotoxy(x, y++);
    printf("#����: %d / %d#", inventory->size, ITEM);
    gotoxy(x, y);
    printf("#############");
}
//===========�賶 �˰���===========
void knapsack(ItemType* bag,ItemType* head,int cost) {
    int i, w;
    w = cost;
    //==========0/1�賶 2���� �迭 ����(�����Ҵ�)==========
    int** wp = (int**)malloc(sizeof(int*)*(ITEM+1));
    
    for(int i=0;i<ITEM+1;i++){
        wp[i] = (int*)malloc(sizeof(int)*cost);
    }
    //==========�賶 �ʱ�ȭ==========
    for(int i=0;i<ITEM+1;i++){
        for(int j=0;j<cost;j++){
            wp[i][j] = 0;
        }
    }
    //==========0/1 �賶 �˰���==========
    for (i = 1; i < ITEM + 1; i++) {
        for (w = 0; w < cost; w++) {
            if (w - head->itemList[i]->weight < 0) {
                wp[i][w] = wp[i - 1][w];
            }
            else {
                wp[i][w] = MAX_NUM(wp[i - 1][w], wp[i - 1][w - head->itemList[i]->weight] + head->itemList[i]->price);
            }
        }
    }
    //==========0/1 �賶 �˰��� ��� ���==========
    for (i = 1; i < ITEM + 1; i++) {
        for (w = 0; w < cost; w++) {
            printf("%d ", wp[i][w]);
        }
        printf("\n");
    }
    //==========�賶�� ���Ե� ��� Ȯ�� �˰���==========
    w = cost-1;
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
    printf("\n");
    int iq=1;
    for (int j = 0; j < ITEM+1; j++) {
        if (include[j]) {
            printf("%d", include[j]);
            insert_itemList(&bag, head->itemList[j]);
            iq++;
        }
    }
    printf("\n");
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
    print_monitoring(fp_gameover);
    exit(0);
    //retry�� �� �ֵ��� ����ٰ� �ߴ�
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
        if (random == 100) {//100�� ������ ���� ���

            endTime = (unsigned)time(NULL);

            monitorTime = rand() % 4 + 1; //1��~4�� ����

            endTime += monitorTime;
            print_monitoring(fp_question);
            Sleep(200);
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
    system("mode con cols =50 lines = 100 | title �Ͽ��� ��¯ �Ǳ�");
    //Ŀ�� ������ ���ֱ�
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

}

void selectToStealItem(ItemType* head,ItemType* inventory) {

    while (1) {
        gotoxy(20, 1);
        printf("��ĥ ������ ��ȣ�� �Է�: ");
        scanf_s("%d", &itemNum);
        if (head->itemList[itemNum]->isStolen) {
            gotoxy(20, 2);
            printf("%s�� �̹� ��ģ �����Դϴ�.", head->itemList[itemNum]->name);
            Sleep(1000);
            system("cls");
            print_totalItemList(head,inventory);
        }
        else {
            return;
        }
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
    printf("��                                             START                                            ��\n");
    printf("��                                             _EXIT                                            ��\n");
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
    insert_itemList(&List, create_item("��Ƽ", 2, 1,10));
    insert_itemList(&List, create_item("����� ī��", 9, 4,30));
    insert_itemList(&List, create_item("������ ����", 3, 2,25));
    insert_itemList(&List, create_item("��ī��", 4, 4,20));
    insert_itemList(&List, create_item("���� ǳ��", 2, 2,50));
    insert_itemList(&List, create_item("�Ź� �ڼ�", 5, 4,40));



    //�̹��� ���� ����ü ������ ����

    fp_closeEye = fopen("ClosedEye.txt", "rt");
    fp_openEye = fopen("OpenEye.txt", "rt");
    fp_gameover = fopen("gameover.txt", "rt");
    fp_text = fopen("text.txt", "rt");
    fp_question = fopen("questionMark.txt", "rt");
    fp_userInput = fopen("userInput.txt", "wt");



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
    if (fp_text == NULL) {
        fprintf(stderr, "����4 �ҷ����� ����");
        return 1;
    }
    if (fp_question == NULL) {
        fprintf(stderr, "����5 �ҷ����� ����");
        return 1;
    }
    if (fp_userInput == NULL) {
        fprintf(stderr, "����6 �ҷ����� ����");
        return 1;
    }

    print_title();
    while (1) {

        system("cls");

        print_totalItemList(&List,&bag);//������ ��� ���

        selectToStealItem(&List,&bag);//��ĥ ��ǰ ��ȣ �Է¹ޱ�

        spaceCount = 10 * List.itemList[itemNum]->difficulty;

        if (monitoring()) {
            system("cls");

            insert_itemList(&bag, List.itemList[itemNum]);

            print_userItemList(&bag);

            List.itemList[itemNum]->isStolen = true;

            gotoxy(20, 15);

            printf("%s�� ��ġ�µ� �����ߴ�!", List.itemList[itemNum]->name);
            Sleep(2000);
        }

    }



    
    knapsack(&bag,&List,cost);
    print_userItemList(&bag);

    fclose(fp_closeEye);
    fclose(fp_openEye);
    fclose(fp_gameover);
 //[1]�������� : �������� ���汸 -  ���� ���{1.��Ƽ 2.����� ī�� 3.������ ����(����) 4.���� 5.��ī�� 6.������ 7.BBź ���� 8.����ǳ�� 9.��Ż���̺��̵� 10.�˸��� 11.�Ź� �ڼ� ���}
//[2]�������� : �ѹ̸� ��Ʈ - ���� ���{1.���ϸ� 2.500��(��ū�� ��) 3.�ﰢ ��� 4.�նѲ� 5.ƾĳ�� 6.��ī�ݶ� 1.5L 7.�ٳ����� ���� 8.����Ŷ �պ� 9.TOP ������ �� 10.��īĨ}
//[3]�������� : ���� ���� - ���� ���{1.�����佺 2.���ϵ� ����(���) 3.Ȩ���� 4.������ 5.���ϸ��� 6.���̽� 7.�ƽ� ȭ��Ʈ ��� 8.�ڿ��� ���� ���� ��Ʈ }



    return 0;
}
