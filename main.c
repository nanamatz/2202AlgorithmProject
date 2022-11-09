//
//  main.c
//  AlgorithmProject
//
//  Created by �赿�� on 2022/11/03.
//
#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
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

    int cost = 0;// 0/1�賶 �� ũ��(���)
    printf("���� �뷮�� �Է��ϼ���>> ");
    scanf_s("%d", &cost);

    knapsack(&bag,&itemList,cost);
    print_itemList(&bag);

 //[1]�������� : �������� ���汸 -  ���� ���{1.��Ƽ 2.����� ī�� 3.������ ����(����) 4.���� 5.��ī�� 6.������ 7.BBź ���� 8.����ǳ�� 9.��Ż���̺��̵� 10.�˸��� 11.�Ź� �ڼ� ���}
//[2]�������� : �ѹ̸� ��Ʈ - ���� ���{1.���ϸ� 2.500��(��ū�� ��) 3.�ﰢ ��� 4.�նѲ� 5.ƾĳ�� 6.��ī�ݶ� 1.5L 7.�ٳ����� ���� 8.����Ŷ �պ� 9.TOP ������ �� 10.��īĨ}
//[3]�������� : ���� ���� - ���� ���{1.�����佺 2.���ϵ� ����(���) 3.Ȩ���� 4.������ 5.���ϸ��� 6.���̽� 7.�ƽ� ȭ��Ʈ ��� 8.�ڿ��� ���� ���� ��Ʈ }



    return 0;
}
