#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>r 
#include <windows.h>

#define DIFFICULTY 100
#define ITEM 12
#define MAX_NUM(x,y)(x)>(y)? x:y

bool isCaught = false;
bool isStolen = false;
FILE* fp_gameover = NULL;
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
    char* name;
    int price;
    int weight;
}Item;

typedef struct {
    int size;
    Item* itemList[ITEM+1];
}ItemType;

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
Item* create_item(char* name,int p,int w) {
    Item* temp = (Item*)malloc(sizeof(Item));
    temp->name = name;
    temp->price = p;
    temp->weight = w;
    return temp;
}
//===========������ ����Ʈ�� �߰�===========
void insert_itemList(ItemType* head,Item* item) {
    head->itemList[head->size++] = item;
}
//===========������ ����Ʈ ���===========
void print_itemList(ItemType* head) {
    int sum_price = 0;
    int sum_danger = 0;
    printf("===================��ǰ ���==================\n");
    for (int i = 0; i < head->size; i++) {
        printf("[%d]<%s>",i+1,head->itemList[i]->name);
        sum_price += head->itemList[i]->price;
        sum_danger += head->itemList[i]->weight;
        printf("\n");
    }
    printf("==================��ġ ����===================\n");
    printf("�� ��ġ: [%d]\n", sum_price);
    printf("==================��ġ ����===================\n");
    printf("�� ����: [%d]", sum_danger);
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
            insert_itemList(bag, head->itemList[j]);
            iq++;
        }
    }
    printf("\n");
}

void print_monitoring(FILE* fp) {
    gotoxy(3, 5);
    char print_temp[256];
    while (fgets(print_temp, 255, fp) != NULL) {
        printf(print_temp);
    }
    puts("");
    rewind(fp);
}
void game_over() {
    system("cls");
    gotoxy(30, 15);
    printf("��Ҵ� ���!\n");
    Sleep(2000);
    print_monitoring(fp_gameover);
    exit(0);
}
void monitoringSystem(FILE* fp1,FILE*fp2) {
    system("cls");

    char bar = '=';
    char blank = ' ';
    const int LEN = 20;
    const int MAX = 500;
    const int SPEED = 35;
    int count = 0;
    float tick = (float)100 / LEN;
    int bar_count;
    int blank_count = 0;
    float percent;

    FILE* tmp = fp1;
    int endTime, startTime, monitorTime, random, i = 0;//i�� �׳� �׽�Ʈ�� ����
    double timer;
    srand(time(NULL));

    while (count<=MAX) {
        gotoxy(0, 0);

        printf("\r%d/%d [", MAX, MAX - count);
        percent = (float)count / MAX * 100;
        bar_count = percent / tick;
        for (int i = 0; i < LEN; i++) {
            blank_count = LEN - bar_count;
            if (blank_count > i) {
                printf("%c", bar);
            }
            else {
                printf("%c", blank);
            }
        }
        printf("] %0.2f%%", percent);

        Sleep(SPEED);

        print_monitoring(tmp);
        random = rand() % DIFFICULTY + 1;//1~200�� 
        
        if (random == 100) {//200�� ������ ���� ���

            while (_kbhit()) {  //���� ��忡�� kbhit ���� �˻縦 ���� ���۸� ������ ���� �۾�
                _getch();
            }
            tmp = fp2;

            endTime = (unsigned)time(NULL);

            monitorTime = rand() % 4 + 1; //1��~4�� ����

            endTime += monitorTime;
            
            do {            //���� ����
                startTime = (unsigned)time(NULL);
                print_monitoring(tmp);  //���� ȭ�� ��ȯ
                Sleep(1000);    //�÷��̾�� ������ �� �ִ� �ð��� �ο� (1��)
                if (_kbhit()) { //Ű���尡 ������ �߰� ��
                    isCaught = true;
                    game_over();
                }
                if (endTime - startTime == 0) { //���� �ð��� ������ ���� ����
                    tmp = fp1;
                    system("cls");
                    break;
                }
            } while (endTime - startTime != 0);

            }
        count++;
        if (isStolen || isCaught)
            break;
        }

}
void init() {
    system("mode con cols =200 lines = 100 | title �Ͽ��� ��¯ �Ǳ�");
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
}

int main(void) {
    init();
    //print_title();
    ItemType itemList;

    ItemType bag;
    init_list(&bag);
    init_list(&itemList);
    insert_itemList(&itemList, create_item(" ", 0, 0));
    insert_itemList(&itemList, create_item("��Ƽ", 2, 1));
    insert_itemList(&itemList, create_item("����� ī��", 9, 4));
    insert_itemList(&itemList, create_item("������ ����(����)", 3, 2));
    insert_itemList(&itemList, create_item("����", 3, 2));
    insert_itemList(&itemList, create_item("��ī��", 4, 4));
    insert_itemList(&itemList, create_item("������", 4, 3));
    insert_itemList(&itemList, create_item("BBź ����", 10, 10));
    insert_itemList(&itemList, create_item("���� ǳ��", 2, 2));
    insert_itemList(&itemList, create_item("��Ż ���� ���̵�", 8, 8));
    insert_itemList(&itemList, create_item("������ �˸���", 1, 4));
    insert_itemList(&itemList, create_item("�Ź� �ڼ�", 5, 4));
    insert_itemList(&itemList, create_item("�Ŀ������� �౸���� ����", 9, 7));

    FILE* fp_closeEye;

    FILE* fp_openEye;

    fp_closeEye = fopen("ClosedEye.txt", "rt");
    fp_openEye = fopen("OpenEye.txt", "rt");
    fp_gameover = fopen("gameover.txt", "rt");

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
    monitoringSystem(fp_closeEye,fp_openEye);



    int cost = 20;// 0/1�賶 �� ũ��(���)
    
    knapsack(&bag,&itemList,cost);
    print_itemList(&bag);

    fclose(fp_closeEye);
    fclose(fp_openEye);
    fclose(fp_gameover);
 //[1]�������� : �������� ���汸 -  ���� ���{1.��Ƽ 2.����� ī�� 3.������ ����(����) 4.���� 5.��ī�� 6.������ 7.BBź ���� 8.����ǳ�� 9.��Ż���̺��̵� 10.�˸��� 11.�Ź� �ڼ� ���}
//[2]�������� : �ѹ̸� ��Ʈ - ���� ���{1.���ϸ� 2.500��(��ū�� ��) 3.�ﰢ ��� 4.�նѲ� 5.ƾĳ�� 6.��ī�ݶ� 1.5L 7.�ٳ����� ���� 8.����Ŷ �պ� 9.TOP ������ �� 10.��īĨ}
//[3]�������� : ���� ���� - ���� ���{1.�����佺 2.���ϵ� ����(���) 3.Ȩ���� 4.������ 5.���ϸ��� 6.���̽� 7.�ƽ� ȭ��Ʈ ��� 8.�ڿ��� ���� ���� ��Ʈ }



    return 0;
}
