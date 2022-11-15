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

//===========아이템 리스트 초기화===========
void init_list(ItemType* head) {
    head->size = 0;
    for (int i = 0; i < ITEM+1; i++) {
        head->itemList[i] = NULL;
    }
}
//===========아이템 생성===========
Item* create_item(char* name,int p,int w) {
    Item* temp = (Item*)malloc(sizeof(Item));
    temp->name = name;
    temp->price = p;
    temp->weight = w;
    return temp;
}
//===========아이템 리스트에 추가===========
void insert_itemList(ItemType* head,Item* item) {
    head->itemList[head->size++] = item;
}
//===========아이템 리스트 출력===========
void print_itemList(ItemType* head) {
    int sum_price = 0;
    int sum_danger = 0;
    printf("===================상품 목록==================\n");
    for (int i = 0; i < head->size; i++) {
        printf("[%d]<%s>",i+1,head->itemList[i]->name);
        sum_price += head->itemList[i]->price;
        sum_danger += head->itemList[i]->weight;
        printf("\n");
    }
    printf("==================가치 총합===================\n");
    printf("총 가치: [%d]\n", sum_price);
    printf("==================가치 총합===================\n");
    printf("총 위험: [%d]", sum_danger);
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
    printf("잡았다 요놈!\n");
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
    int endTime, startTime, monitorTime, random, i = 0;//i는 그냥 테스트용 변수
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
        random = rand() % DIFFICULTY + 1;//1~200중 
        
        if (random == 100) {//200이 나오면 감시 모드

            while (_kbhit()) {  //감시 모드에서 kbhit 정상 검사를 위해 버퍼를 사전에 비우는 작업
                _getch();
            }
            tmp = fp2;

            endTime = (unsigned)time(NULL);

            monitorTime = rand() % 4 + 1; //1초~4초 감시

            endTime += monitorTime;
            
            do {            //감시 진행
                startTime = (unsigned)time(NULL);
                print_monitoring(tmp);  //감시 화면 전환
                Sleep(1000);    //플레이어에게 반응할 수 있는 시간을 부여 (1초)
                if (_kbhit()) { //키보드가 눌리면 발각 됨
                    isCaught = true;
                    game_over();
                }
                if (endTime - startTime == 0) { //감시 시간이 끝나면 감시 종료
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
    system("mode con cols =200 lines = 100 | title 일월초 일짱 되기");
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
}

int main(void) {
    init();
    //print_title();
    ItemType itemList;

    ItemType bag;
    init_list(&bag);
    init_list(&itemList);
    insert_itemList(&itemList, create_item(" ", 0, 0));
    insert_itemList(&itemList, create_item("제티", 2, 1));
    insert_itemList(&itemList, create_item("유희왕 카드", 9, 4));
    insert_itemList(&itemList, create_item("메이플 딱지(종이)", 3, 2));
    insert_itemList(&itemList, create_item("포포", 3, 2));
    insert_itemList(&itemList, create_item("차카니", 4, 4));
    insert_itemList(&itemList, create_item("아폴로", 4, 3));
    insert_itemList(&itemList, create_item("BB탄 권총", 10, 10));
    insert_itemList(&itemList, create_item("본드 풍선", 2, 2));
    insert_itemList(&itemList, create_item("메탈 베이 블레이드", 8, 8));
    insert_itemList(&itemList, create_item("스누피 알림장", 1, 4));
    insert_itemList(&itemList, create_item("매미 자석", 5, 4));
    insert_itemList(&itemList, create_item("파워레인저 축구게임 필통", 9, 7));

    FILE* fp_closeEye;

    FILE* fp_openEye;

    fp_closeEye = fopen("ClosedEye.txt", "rt");
    fp_openEye = fopen("OpenEye.txt", "rt");
    fp_gameover = fopen("gameover.txt", "rt");

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
    monitoringSystem(fp_closeEye,fp_openEye);



    int cost = 20;// 0/1배낭 열 크기(비용)
    
    knapsack(&bag,&itemList,cost);
    print_itemList(&bag);

    fclose(fp_closeEye);
    fclose(fp_openEye);
    fclose(fp_gameover);
 //[1]스테이지 : 딱따구리 문방구 -  물건 목록{1.제티 2.유희왕 카드 3.메이플 딱지(종이) 4.포포 5.차카니 6.아폴로 7.BB탄 권총 8.본드풍선 9.메탈베이블레이드 10.알림장 11.매미 자석 등등}
//[2]스테이지 : 훼미리 마트 - 물건 목록{1.포켓몬빵 2.500컵(얼큰한 맛) 3.삼각 김밥 4.왕뚜껑 5.틴캐시 6.코카콜라 1.5L 7.바나나맛 우유 8.쉐이킷 붐붐 9.TOP 마스터 라떼 10.포카칩}
//[3]스테이지 : 자하 수퍼 - 물건 목록{1.추파춥스 2.마일드 세븐(담배) 3.홈런볼 4.월드콘 5.자일리톨 6.참이슬 7.맥심 화이트 골드 8.자연은 종합 음료 세트 }



    return 0;
}
