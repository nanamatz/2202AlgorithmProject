//
//  main.c
//  AlgorithmProject
//
//  Created by 김동규 on 2022/11/03.
//
#include <stdio.h>
#include <stdlib.h>

#define ITEM 12
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
    char* name;
    int price;
    int weight;
}Item;

typedef struct {
    int size;
    Item* itemList[ITEM+1];
}ItemType;

//typedef enum {
//    S = 5, A = 4, B = 3, C = 2, D = 1
//}Rank;

//typedef int element;
//typedef struct{
//    int size;
//    element heap[MAX];
//}Heap;
//
//Heap* create(Heap* h){
//    return (Heap*)malloc(sizeof(Heap));
//}
//void init(Heap* h){
//    h->size = 0;
//}
//    
//void insert_min(Heap* h,element key){
//    int i;
//    i = ++h->size;
//    
//    while(i!=1 && key<h->heap[i/2]){
//        h->heap[i] = h->heap[i/2];
//        i /=2;
//    }
//    h->heap[i] = key;
//}
//element delete_min(Heap* h){
//    element temp = h->heap[h->size--];
//    element item = h->heap[1];
//    int child=2;
//    int parent=1;
//    
//    while(child <= h->size){
//        if(child<h->size && h->heap[child]>h->heap[child+1]){
//            child++;
//        }
//        if(temp<=h->heap[child]){
//            break;
//        }
//        h->heap[parent] = h->heap[child];
//        parent = child;
//        child*=2;
//    }
//    h->heap[parent] = temp;
//    return item;
//    
//}
//
//void HeapSortMin(int arr[],Heap* h){
//    for(int i=1;i<MAX;i++){
//        arr[i] = delete_min(h);
//    }
//}
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

int main(void) {
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

    int cost = 0;// 0/1배낭 열 크기(비용)
    printf("가방 용량을 입력하세요>> ");
    scanf_s("%d", &cost);

    knapsack(&bag,&itemList,cost);
    print_itemList(&bag);

 //[1]스테이지 : 딱따구리 문방구 -  물건 목록{1.제티 2.유희왕 카드 3.메이플 딱지(종이) 4.포포 5.차카니 6.아폴로 7.BB탄 권총 8.본드풍선 9.메탈베이블레이드 10.알림장 11.매미 자석 등등}
//[2]스테이지 : 훼미리 마트 - 물건 목록{1.포켓몬빵 2.500컵(얼큰한 맛) 3.삼각 김밥 4.왕뚜껑 5.틴캐시 6.코카콜라 1.5L 7.바나나맛 우유 8.쉐이킷 붐붐 9.TOP 마스터 라떼 10.포카칩}
//[3]스테이지 : 자하 수퍼 - 물건 목록{1.추파춥스 2.마일드 세븐(담배) 3.홈런볼 4.월드콘 5.자일리톨 6.참이슬 7.맥심 화이트 골드 8.자연은 종합 음료 세트 }



    return 0;
}
