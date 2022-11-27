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


//2011년 여름, 플레이어 = 잼민이(12세), 
// 
//잼민이 특: 학원 상가 건물 지하 1층에 있는 하나로 마트에서 물건 훔치기를 잘함.
//잼민이의 꿈: 일월초 자타 공인 일짱 형택이와 친해지는 것.
// 
//스테이지(3): [1]스테이지: 영준이의 심부름 완수하기(유희왕 카드)
             //[2]스테이지: 동혁이의 심부름 완수하기(틴캐시 1만원권)
             //[3]스테이지: 형택이의 심부름 완수하기(담배)
             // 
//[1]스테이지 : 딱따구리 문방구 -  물건 목록{1.제티 2.유희왕 카드 3.메이플 딱지(종이) 4.포포 5.차카니 6.아폴로 7.BB탄 권총 8.본드풍선 9.메탈베이블레이드 10.알림장 11.매미 자석 등등}
//[2]스테이지 : 훼미리 마트 - 물건 목록{1.포켓몬빵 2.500컵(얼큰한 맛) 3.삼각 김밥 4.왕뚜껑 5.틴캐시 6.코카콜라 1.5L 7.바나나맛 우유 8.쉐이킷 붐붐 9.TOP 마스터 라떼 10.포카칩}
//[3]스테이지 : 자하 수퍼 - 물건 목록{1.추파춥스 2.마일드 세븐(담배) 3.홈런볼 4.월드콘 5.자일리톨 6.참이슬 7.맥심 화이트 골드 8.자연은 종합 음료 세트 }

// 각 물건에는 선호도(가치)와 발각 계수(무게)가 존재.
// 
// 가방의 부피보다 가방 내 물건들의 발각 계수 합이 클 경우 -> 도둑질 발각 당해서 게임 오버
// 
// 심부름 주인의 일정 선호도보다 가방 내 물건들의 선호도 합이 작을 경우 -> 심부름 주인과 친해지기 실패해서 게임 오버
// 
//가방 {1.실내화 가방 2.책가방}

typedef struct {
    char* name; //아이템 이름
    int price;  //아이템 가치
    int weight; //아이템 용량
    int difficulty; //아이템 난이도
    bool isStolen;
}Item;

typedef struct {
    int size;  //아이템 리스트 크기
    Item* itemList[ITEM+1];  //아이템 배열
}ItemType;

//전역변수
//bool isCaught;  //훔치다 걸렸는지 확인하는 변수
bool isStolen; //훔쳤는지 확인하는 변수
FILE* fp_gameover = NULL; //게임오버 아스키 아트 파일 포인터
FILE* fp_text = NULL; //텍스트 파일 포인터
FILE* fp_closeEye = NULL;
FILE* fp_openEye = NULL;
FILE* fp_question = NULL;
FILE* fp_userInput = NULL;
char text[256]; //파일에서 읽어들인 문자열 저장 버퍼
int itemNum; //사용자가 선택하는 아이템 번호
int spaceCount;
int cost = 20;// 0/1배낭 열 크기(비용)

//============게임 함수 모음============
void init();
void print_title();
void game_over(ItemType* List);

//===========아이템 관련 함수 모음============
Item* create_item(char* name, int p, int w, int d);
void insert_itemList(ItemType* head, Item* item);
void print_userItemList(ItemType* head);
void print_totalItemList(ItemType* head);
void selectToStealItem();
void print_inventory();
//===========감시 모드 함수 모음==============
void print_monitoring(FILE* fp);

//===========배낭 알고리즘=================
void knapsack(ItemType* bag, ItemType* head, int cost);



void gotoxy(int x, int y)

{

    COORD pos = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

//===========아이템 리스트 초기화===========
void init_list(ItemType* head) {
    head->size = 0;
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
}

//===========아이템 리스트 출력===========
void print_userItemList(ItemType* head) {
    int sum_price = 0;
    int sum_weight = 0;
    printf("===================상품 목록==================\n");
    for (int i = 0; i < head->size; i++) {
        printf("[%d]<%s>",i+1,head->itemList[i]->name);
        sum_price += head->itemList[i]->price;
        sum_weight += head->itemList[i]->weight;
        printf("\n");
    }
    printf("==================가치 총합===================\n");
    printf("총 가치: [%d]\n", sum_price);
    printf("==================가치 총합===================\n");
    printf("총 부피: [%d]", sum_weight);
}
//===========훔칠 아이템 리스트 출력===========
void print_totalItemList(ItemType* head,ItemType* inventory) {

    printf("===================상품 목록==================\n");
    for (int i = 1; i < head->size; i++) {
            printf("[%d]<%s>\n", i, head->itemList[i]->name);
            printf("###가격:   [%d] \n###부피:   [%d] \n###난이도: [%d]", head->itemList[i]->price, head->itemList[i]->weight, head->itemList[i]->difficulty);
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
    printf("#용량: %d/ %d#",sum_weight,cost );
    gotoxy(x, y++);
    printf("#가치: %d    #", sum_price);
    gotoxy(x, y++);
    printf("#물건: %d / %d#", inventory->size, ITEM);
    gotoxy(x, y);
    printf("#############");
}
//===========배낭 알고리즘===========
void knapsack(ItemType* bag,ItemType* head,int cost) {
    int i, w;
    w = cost;
    //==========0/1배낭 2차원 배열 생성(동적할당)==========
    int** wp = (int**)malloc(sizeof(int*)*(ITEM+1));
    
    for(int i=0;i<ITEM+1;i++){
        wp[i] = (int*)malloc(sizeof(int)*cost);
    }
    //==========배낭 초기화==========
    for(int i=0;i<ITEM+1;i++){
        for(int j=0;j<cost;j++){
            wp[i][j] = 0;
        }
    }
    //==========0/1 배낭 알고리즘==========
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
    //==========0/1 배낭 알고리즘 결과 출력==========
    for (i = 1; i < ITEM + 1; i++) {
        for (w = 0; w < cost; w++) {
            printf("%d ", wp[i][w]);
        }
        printf("\n");
    }
    //==========배낭에 포함된 요소 확인 알고리즘==========
    w = cost-1;
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
    gotoxy(30, 15);
    printf("잡았다 요놈!\n");
    Sleep(2000);
    print_monitoring(fp_gameover);
    exit(0);
    //retry할 수 있도록 만들다가 중단
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
//===========감시 함수=============
int monitoring() {

    system("cls");

    srand(time(NULL));

    int endTime, startTime, monitorTime, random;
    char bar = '=';//바 문자
    char blank = ' ';//공백
    const int MAX = 500; //최대 카운트 수
    const int SPEED = 35; //타이머 스피드
    int count = 0;  //타이머 카운트 변수
    float tick = (float)100 / LEN; //1틱 = 5퍼센트
    int bar_count;      //바 갯수
    int blank_count = 0;//공백 갯수
    float percent; //퍼센테이지 변수



    while (count <= MAX) {

        gotoxy(0, 0);
        //타이머가 진행되는 동안 수행

        //==============================================
        printf("\r%d/%d [", MAX, MAX - count);
        percent = (float)count / MAX * 100;
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
        if (random == 100) {//100이 나오면 감시 모드

            endTime = (unsigned)time(NULL);

            monitorTime = rand() % 4 + 1; //1초~4초 감시

            endTime += monitorTime;
            print_monitoring(fp_question);
            Sleep(200);
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

        count++;
        if (spaceCount <= 0) {
            return 1;//훔치기 성공
        }
    }
    
    return 0;
}

void init() {
    system("mode con cols =50 lines = 100 | title 일월초 일짱 되기");
    //커서 깜빡임 없애기
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

}

void selectToStealItem(ItemType* head,ItemType* inventory) {

    while (1) {
        gotoxy(20, 1);
        printf("훔칠 물건의 번호를 입력: ");
        scanf_s("%d", &itemNum);
        if (head->itemList[itemNum]->isStolen) {
            gotoxy(20, 2);
            printf("%s는 이미 훔친 물건입니다.", head->itemList[itemNum]->name);
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
    printf("■                                             START                                            ■\n");
    printf("■                                             _EXIT                                            ■\n");
    printf("■                                                                                              ■\n");
    printf("■                                                                                              ■\n");
    printf("■                                                                                              ■\n");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

    getchar();
    system("cls");
}

int main(void) {
    init();

    ItemType List;
    ItemType bag;
    init_list(&bag);
    init_list(&List);
    //아이템 리스트 생성
    insert_itemList(&List, create_item(" ", 0, 0,0));
    insert_itemList(&List, create_item("제티", 2, 1,10));
    insert_itemList(&List, create_item("유희왕 카드", 9, 4,30));
    insert_itemList(&List, create_item("메이플 딱지", 3, 2,25));
    insert_itemList(&List, create_item("차카니", 4, 4,20));
    insert_itemList(&List, create_item("본드 풍선", 2, 2,50));
    insert_itemList(&List, create_item("매미 자석", 5, 4,40));



    //이미지 파일 구조체 포인터 생성

    fp_closeEye = fopen("ClosedEye.txt", "rt");
    fp_openEye = fopen("OpenEye.txt", "rt");
    fp_gameover = fopen("gameover.txt", "rt");
    fp_text = fopen("text.txt", "rt");
    fp_question = fopen("questionMark.txt", "rt");
    fp_userInput = fopen("userInput.txt", "wt");



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
    if (fp_text == NULL) {
        fprintf(stderr, "파일4 불러오기 실패");
        return 1;
    }
    if (fp_question == NULL) {
        fprintf(stderr, "파일5 불러오기 실패");
        return 1;
    }
    if (fp_userInput == NULL) {
        fprintf(stderr, "파일6 불러오기 실패");
        return 1;
    }

    print_title();
    while (1) {

        system("cls");

        print_totalItemList(&List,&bag);//아이템 목록 출력

        selectToStealItem(&List,&bag);//훔칠 상품 번호 입력받기

        spaceCount = 10 * List.itemList[itemNum]->difficulty;

        if (monitoring()) {
            system("cls");

            insert_itemList(&bag, List.itemList[itemNum]);

            print_userItemList(&bag);

            List.itemList[itemNum]->isStolen = true;

            gotoxy(20, 15);

            printf("%s를 훔치는데 성공했다!", List.itemList[itemNum]->name);
            Sleep(2000);
        }

    }



    
    knapsack(&bag,&List,cost);
    print_userItemList(&bag);

    fclose(fp_closeEye);
    fclose(fp_openEye);
    fclose(fp_gameover);
 //[1]스테이지 : 딱따구리 문방구 -  물건 목록{1.제티 2.유희왕 카드 3.메이플 딱지(종이) 4.포포 5.차카니 6.아폴로 7.BB탄 권총 8.본드풍선 9.메탈베이블레이드 10.알림장 11.매미 자석 등등}
//[2]스테이지 : 훼미리 마트 - 물건 목록{1.포켓몬빵 2.500컵(얼큰한 맛) 3.삼각 김밥 4.왕뚜껑 5.틴캐시 6.코카콜라 1.5L 7.바나나맛 우유 8.쉐이킷 붐붐 9.TOP 마스터 라떼 10.포카칩}
//[3]스테이지 : 자하 수퍼 - 물건 목록{1.추파춥스 2.마일드 세븐(담배) 3.홈런볼 4.월드콘 5.자일리톨 6.참이슬 7.맥심 화이트 골드 8.자연은 종합 음료 세트 }



    return 0;
}
