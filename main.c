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
}Item;

typedef struct {
    int size;  //������ ����Ʈ ũ��
    Item* itemList[ITEM+1];  //������ �迭
}ItemType;

//��������
bool isCaught;  //��ġ�� �ɷȴ��� Ȯ���ϴ� ����
bool isStolen; //���ƴ��� Ȯ���ϴ� ����
FILE* fp_gameover = NULL; //���ӿ��� �ƽ�Ű ��Ʈ ���� ������
FILE* fp_text = NULL; //�ؽ�Ʈ ���� ������
FILE* fp_closeEye = NULL;
FILE* fp_openEye = NULL;
FILE* fp_question = NULL;
char text[256]; //���Ͽ��� �о���� ���ڿ� ���� ����
int itemNum; //����ڰ� �����ϴ� ������ ��ȣ

ItemType bag;

//============���� �Լ� ����============
void init();
void print_title();
void in_game(ItemType* List);
void game_over(ItemType* List);

//===========������ ���� �Լ� ����============
Item* create_item(char* name, int p, int w, int d);
void insert_itemList(ItemType* head, Item* item);
void print_userItemList(ItemType* head);
void print_totalItemList(ItemType* head);
void selectToStealItem();

//===========���� ��� �Լ� ����==============
void print_monitoring(FILE* fp);
bool monitoringSystem(ItemType* head, FILE* fp1, FILE* fp2);

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
    return temp;
}
//===========������ ����Ʈ�� �߰�===========
void insert_itemList(ItemType* head,Item* item) {
    head->itemList[head->size++] = item;
}

//===========������ ����Ʈ ���===========
void print_userItemList(ItemType* head) {
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
//===========��ģ ������ ����Ʈ ���===========
void print_totalItemList(ItemType* head) {

    printf("===================��ǰ ���==================\n");
    for (int i = 1; i < head->size; i++) {
            printf("[%d]<%s>\n", i, head->itemList[i]->name);
            printf("###����:%d \n###���赵: %d \n###����: %d", head->itemList[i]->price, head->itemList[i]->difficulty, head->itemList[i]->weight);
            printf("\n\n");

    }

}
//void print_totalItemList(ItemType* head) {
//    int x, y;
//    system("cls");
//    x = 15; y = 15;
//    gotoxy(x, y);
//    for (int i = 1; i < ITEM + 1; i++) {
//        gotoxy(x, y);
//        for (int k = 0; k < 3; k++) {
//
//            printf("##########################\n");
//            printf("#                        #\n");
//            printf("#   %d.[%10s]            #\n", i, head->itemList[i]->name);
//            printf("#   ����:%3d             #\n", head->itemList[i]->price);
//            printf("#   ���̵�:%             #\n", head->itemList[i]->difficulty);
//            printf("#   ����:%3d             #\n", head->itemList[i]->weight);
//            printf("#                        #\n");
//            printf("##########################\n");
//            gotoxy(x + k*10, y);
//        }
//
//    }
//}
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
void game_over(ItemType* List) {
    char ch;
    system("cls");
    gotoxy(30, 15);
    printf("��Ҵ� ���!\n");
    Sleep(2000);
    print_monitoring(fp_gameover);
    exit(0);
    //retry�� �� �ֵ��� ����ٰ� �ߴ�
}
//===========���� �Լ�=============
bool monitoringSystem(ItemType* head,FILE* fp1,FILE*fp2) { //��ġ�� ����
    system("cls");

    gotoxy(0, 27);
    if (fgets(text, head->itemList[itemNum]->difficulty, fp_text) != NULL) {
        printf("��ȣ���� ������ �Ȱ��� �Է��ϼ���>>[%s]", text);
    }
    else {//���� �����Ͱ� ���� �����ϸ� ó������ �̵���Ű�� �ٽ� �ڱ� �ڽ� ȣ��
        rewind(fp_text); fgets(text, head->itemList[itemNum]->difficulty, fp_text);
    }

    char bar = '=';//�� ����
    char blank = ' ';//����
    const int LEN = 20; //�ۼ������� bar ����
    const int MAX = 500; //�ִ� ī��Ʈ ��
    const int SPEED = 35; //Ÿ�̸� ���ǵ�
    char* userInput = NULL; //������ �Է��ϴ� ���ڿ� ����
    int count = 0;  //Ÿ�̸� ī��Ʈ ����
    float tick = (float)100 / LEN; //1ƽ = 5�ۼ�Ʈ
    int bar_count;      //�� ����
    int blank_count = 0;//���� ����
    float percent; //�ۼ������� ����

    FILE* tmp = fp1;    //close Eye �ƽ�Ű ��Ʈ ȭ�� ���
    int endTime, startTime, monitorTime, random;

    srand(time(NULL));

    while (count<=MAX) { //Ÿ�̸Ӱ� ����Ǵ� ���� ����
        gotoxy(0, 0);
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
        printf("] %0.2f%%", 100-percent);

        Sleep(SPEED);
        //==============================================

        print_monitoring(tmp);//�ƽ�Ű ��Ʈ ȭ�� ���

        gotoxy(0, 27);  //�޾ƾ� ���ڿ� ���
        printf("��ȣ���� ������ �Ȱ��� �Է��ϼ���>>[%s]", text);
       

        random = rand() % DIFFICULTY + 1;//1~100�� 
        
        if (random == 100) {//100�� ������ ���� ���
            //while (_kbhit()) {  //���� ��忡�� kbhit ���� �˻縦 ���� ���۸� ������ ���� �۾�
            //    _getch();
            //}

            tmp = fp2;  //Open Eye �ƽ�Ű ��Ʈ ȭ������ ����
            //===========================================================
            endTime = (unsigned)time(NULL);

            monitorTime = rand() % 4 + 1; //1��~4�� ����

            endTime += monitorTime;
            print_monitoring(fp_question);
            while (_kbhit()) {  //���� ��忡�� kbhit ���� �˻縦 ���� ���۸� ������ ���� �۾�
                _getch();
            }

            do {            //���� ����
                startTime = (unsigned)time(NULL);

                Sleep(2000);//�÷��̾�� ������ �� �ִ� �ð��� �ο� (1��)
                print_monitoring(tmp);  //���� ȭ�� ��ȯ

                if (_kbhit()) { //Ű���尡 ������ �߰� ��
                    isCaught = true;
                    game_over(head);
                }
                if (endTime - startTime == 0) { //���� �ð��� ������ ���� ����
                    tmp = fp1;
                    system("cls");
                    break;
                }
            } while (endTime - startTime != 0);
            //============================================================
            }
        count++;

        if (isStolen || isCaught)
            break;
        }
    system("cls");
    isStolen = true;//�����
    return isStolen;
}
void init() {
    system("mode con cols =50 lines = 100 | title �Ͽ��� ��¯ �Ǳ�");
    //Ŀ�� ������ ���ֱ�
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    isCaught = false;
    isStolen = false;

}

void selectToStealItem() {
    do {
        gotoxy(25, 1);
        printf("������ ����: (1~12��)");
        scanf_s("%d", &itemNum);
    } while (itemNum < 0 || itemNum > 13);
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
void in_game(ItemType* List) {
    init_list(&bag);
    char c;
    while (1) {
        system("cls");
        print_totalItemList(List);//������ ��� ���
        selectToStealItem();//��ĥ ��ǰ ��ȣ �Է¹ޱ�
        if (monitoringSystem(List, fp_closeEye, fp_openEye)) {//��ģ ��ǰ�� ���� ��ġ�� ���� ����
            insert_itemList(&bag, List->itemList[itemNum]);
            gotoxy(15, 15);
            printf("[%s�� ���ƴ�!]", List->itemList[itemNum]->name);
            init();
        }
        else {
            printf("[%s�� ��ġ�� ���ߴ�.]", List->itemList[itemNum]->name);
        }

        system("pause");

        c = getchar();
        if (c == 'e') {
            break;
        }
    }
}


int main(void) {
    init();

    ItemType List;
    init_list(&List);
    //������ ����Ʈ ����
    insert_itemList(&List, create_item(" ", 0, 0,0));
    insert_itemList(&List, create_item("��Ƽ", 2, 1,15));
    insert_itemList(&List, create_item("����� ī��", 9, 4,17));
    insert_itemList(&List, create_item("������ ����", 3, 2,19));
    insert_itemList(&List, create_item("����", 3, 2,16));
    insert_itemList(&List, create_item("��ī��", 4, 4,20));
    insert_itemList(&List, create_item("������", 4, 3,20));
    insert_itemList(&List, create_item("BBź ����", 10, 10,30));
    insert_itemList(&List, create_item("���� ǳ��", 2, 2,18));
    insert_itemList(&List, create_item("��Ż ���� ���̵�", 8, 8,20));
    insert_itemList(&List, create_item("������ �˸���", 1, 4,15));
    insert_itemList(&List, create_item("�Ź� �ڼ�", 5, 4,12));
    insert_itemList(&List, create_item("�౸���� ����", 9, 7,15));


    //�̹��� ���� ����ü ������ ����

    fp_closeEye = fopen("ClosedEye.txt", "rt");
    fp_openEye = fopen("OpenEye.txt", "rt");
    fp_gameover = fopen("gameover.txt", "rt");
    fp_text = fopen("text.txt", "rt");
    fp_question = fopen("questionMark.txt", "rt");
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


    print_title();
    in_game(&List);




    int cost = 20;// 0/1�賶 �� ũ��(���)
    
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
