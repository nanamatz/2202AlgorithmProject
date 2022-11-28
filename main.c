#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>


#define DIFFICULTY 200 //난이도(감시 확률)
#define ITEM 6 // 아이템 개수
#define LEN 20 // 타이머 바 개수
#define MAX_NUM(x,y)(x)>(y)? x:y //배낭 알고리즘 최대값 함수


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
int userCap=0; //사용자 배낭의 총 무게

//============게임 함수 모음============
void init();
void print_title();
void game_over(ItemType* List);

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

void game_clear();
void game_fail();

void gotoxy(int x, int y)

{

    COORD pos = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

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
    gotoxy(0, 9); printf("===최적 물건 리스트===");
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
    if (userSolution == bestSolution && userCap <= bestSolution_weight) { //유저의 해가 최적해이면 참 반환
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
    gotoxy(30, 15);
    printf("잡았다 요놈!\n");
    Sleep(2000);
    gotoxy(30, 16);
    printf("처음부터 다시하세요");
    Sleep(2000);
    print_monitoring(fp_gameover);
    Sleep(2000);
    main();
    //retry할 수 있도록 만들다가 중단
}
void game_clear() {
    gotoxy(1, 1);
    printf("훔쳐간 물건들이 형택이를 만족시킨 것 같다."); getchar();
    printf("형택이가 슬며시 다가와 내 어깨를 가볍게 두드리며 말했다."); getchar();
    printf("너도 이제 내일부터 피방 가자"); getchar();
    printf("모두가 보는 앞에서 일월초 일짱 클럽에 들어갔다..!"); getchar();
    printf("나도 [험멜] 입을 수 있다구..!"); getchar();
    Sleep(1000);
    system("cls");
    exit(0);
}
void game_fail() {
    gotoxy(1, 1);
    printf("실내화 가방 안을 들여다 본 형택이의 낯빛이 어두워졌다.\n"); getchar();
    printf("진짜 x됐다...\n"); getchar();
    printf("형택이가 깊은 한숨을 내뱉으며 말했다.\n"); getchar();
    printf("[넌 안되겠다, 앞으로 아침 우유 급식은 너가 가져와라]\n"); getchar();
    printf("[제티 없으면 뒤진다]\n"); getchar();
    printf("모두가 보는 앞에서 일월초 최고 존엄 찐따로 등극했다.\n"); getchar();
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
        if (random == 200) {//200이 나오면 감시 모드

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

        count++;
        if (spaceCount <= 0) {
            return 1;//훔치기 성공
        }
    }
    
    return 0;
}

void init() {
    system("mode con cols =30 lines = 130 | title 일월초 일짱 되기");
    //커서 깜빡임 없애기
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
        printf("*훔치기 종료[0번]*");
        gotoxy(65, 3);
        printf(">>훔칠 물건의 번호 입력>>");
        scanf_s("%d", &itemNum);
        if (0 < itemNum && itemNum < 7) {
            if (head->itemList[itemNum]->isStolen) {
                gotoxy(65, 4);
                printf("%s는 이미 훔친 물건입니다.", head->itemList[itemNum]->name);
                Sleep(1000);
                system("cls");
                print_totalItemList(head, inventory);
            }
            else if ((inventory->capacity - head->itemList[itemNum]->weight) < 0) { //배낭의 용량을 초과하면 예외처리
                gotoxy(65, 4);
                printf("짐이 너무 많습니다.");
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
            printf("유효한 번호를 입력하세요.(1~6)");
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

int main(void) {
    init();

    ItemType List;
    ItemType bag;
    init_list(&bag);
    init_list(&List);

    //아이템 리스트 생성
    insert_itemList(&List, create_item(" ", 0, 0,0));
    insert_itemList(&List, create_item("제티", 2, 1,1));
    insert_itemList(&List, create_item("유희왕 카드", 5, 4,4));
    insert_itemList(&List, create_item("메이플 딱지", 3, 2,3));
    insert_itemList(&List, create_item("차카니", 4, 4,4));
    insert_itemList(&List, create_item("콩순이 일기장", 2, 3,2));
    insert_itemList(&List, create_item("매미 자석", 6, 5,5));


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

    print_title();
    //훔치기 게임 진행
    while (1) {

        system("cls");

        print_totalItemList(&List,&bag);//아이템 목록 출력

        if (selectToStealItem(&List, &bag))//훔칠 상품 번호 입력받기
            break;
        spaceCount = 20 * List.itemList[itemNum]->difficulty;

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
    if (isClear) {
        system("cls");
    }
    fclose(fp_closeEye);
    fclose(fp_openEye);
    fclose(fp_gameover);

    free_item(&List); //동적할당 해제
    system("cls");
    Sleep(1000);
    int x = 1;
    int y = 1;
    gotoxy(x, y);
    printf("훔쳐간 물건들이 형택이를 만족시킨 것 같다."); Sleep(3000);
    y += 2;
    gotoxy(x, y);
    printf("형택이가 슬며시 다가와 내 어깨를 가볍게 두드리며 말했다."); Sleep(3000);
    y += 2;
    gotoxy(x, y);
    printf("[오늘 학교 끝나고 인터팡으로 와]");  Sleep(3000);
    y += 2;
    gotoxy(x, y);
    printf("모두가 보는 앞에서 일월초 일짱 클럽에 들어갔다..!"); Sleep(3000);
    y += 2;
    gotoxy(x, y);
    printf("나도 [험멜] 입을 수 있다구..!"); Sleep(3000);
    Sleep(1000);
    system("cls");
    print_monitoring(fp_happyEnding);
    Sleep(3000);
    print_monitoring(fp_badEnding);
    exit(0);

    //게임 엔딩 미구현
   /* if (isClear) {
        game_clear();
    }
    game_fail();*/
    return 0;
}
