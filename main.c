//
//  main.c
//  AlgorithmProject
//
//  Created by 김동규 on 2022/11/03.
//
#include <stdio.h>
#include <stdlib.h>

#define COUNTRY 8
#define MAX 10
#define MAX_NUM(x,y)(x)>(y)? x:y

typedef struct {
    int departTime;
    int arriveTime;
}Air;
typedef enum {
    S = 5, A = 4, B = 3, C = 2, D = 1
}Rank;

int W[COUNTRY + 1] = {0,2,6,4,3,1,7,2,3};
int V[COUNTRY + 1] = { 0,S,S,B,A,C,S,D,B };
char* BAG[COUNTRY + 1] = {NULL,"JAPAN","CHINA","TAIWAN","THAILAND","KHAMBODIA","TURKEY"
                    ,"VIETNAM","MALAYSIA" };


typedef int element;
typedef struct{
    int size;
    element heap[MAX];
}Heap;

Heap* create(Heap* h){
    return (Heap*)malloc(sizeof(Heap));
}
void init(Heap* h){
    h->size = 0;
}
    
void insert_min(Heap* h,element key){
    int i;
    i = ++h->size;
    
    while(i!=1 && key<h->heap[i/2]){
        h->heap[i] = h->heap[i/2];
        i /=2;
    }
    h->heap[i] = key;
}
element delete_min(Heap* h){
    element temp = h->heap[h->size--];
    element item = h->heap[1];
    int child=2;
    int parent=1;
    
    while(child <= h->size){
        if(child<h->size && h->heap[child]>h->heap[child+1]){
            child++;
        }
        if(temp<=h->heap[child]){
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child*=2;
    }
    h->heap[parent] = temp;
    return item;
    
}

void HeapSortMin(int arr[],Heap* h){
    for(int i=1;i<MAX;i++){
        arr[i] = delete_min(h);
    }
}


void knapsack(int cost) {
    int i, w;
    w = cost;
    //==========0/1배낭 2차원 배열 생성(동적할당)==========
    int** wp = (int**)malloc(sizeof(int*)*COUNTRY);
    
    for(int i=0;i<COUNTRY+1;i++){
        wp[i] = (int*)malloc(sizeof(int)*cost);
    }
    //==========배낭 초기화==========
    for(int i=0;i<COUNTRY+1;i++){
        for(int j=0;j<cost;j++){
            wp[i][j] = 0;
        }
    }
    //==========0/1 배낭 알고리즘==========
    for (i = 1; i < COUNTRY + 1; i++) {
        for (w = 0; w < cost; w++) {
            if (w - W[i] < 0) {
                wp[i][w] = wp[i - 1][w];
            }
            else {
                wp[i][w] = MAX_NUM(wp[i - 1][w], wp[i - 1][w - W[i]] + V[i]);
            }
        }
    }
    //==========0/1 배낭 알고리즘 결과 출력==========
    for (i = 1; i < COUNTRY + 1; i++) {
        for (w = 0; w < cost; w++) {
            printf("%d ", wp[i][w]);
        }
        printf("\n");
    }
    //==========배낭에 포함된 요소 확인 알고리즘==========
    w = cost-1;
    int include[COUNTRY + 1] = { 0 };//포함 미포함 리스트
    
    while(w){
        i = COUNTRY;
        if (wp[i][w] != wp[i][w - 1]) {
            while (i > 0) {
                if (wp[i - 1][w] != wp[i][w]) {
                    include[i] = 1;
                    w = w - W[i];
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
    for(int i=0;i<COUNTRY+1;i++){
        free(wp[i]);
    }
    free(wp);
    //==========배낭 출력==========
    printf("\n");
    int iq=1;
    for (int j = 0; j < COUNTRY+1; j++) {
        if (include[j]) {
            printf("%d.%s ",iq, BAG[j]);
            iq++;
        }
    }
    printf("\n");
    for(int i=0;i<COUNTRY+1;i++){
        if(include[i]){ //가방에 포함되어 있다면
            insert_min(h, airTime[i].departTime);
        }
    }

}
int main(void) {
    
    int cost=0;// 0/1배낭 열 크기(비용)
    printf("여행 비용을 입력하세요>> ");
    scanf("%d",&cost);
    
    knapsack(cost);
    //machineScehduling
    return 0;
}
