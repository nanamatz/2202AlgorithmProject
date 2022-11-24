/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

typedef struct Edge {
    int start;
    int end;
    int weight;
}Edge;

typedef struct MST {
    Edge** edgelist;
    int size;
}MST;

void init_edge(Edge* e, int start, int end, int weight);
void sort_edge(Edge* e[]);
void insert_MST(MST* mst, Edge* e);
void print_MST(MST* mst);
void delete_MST(MST* mst, int index);

int vertex_arr[4] = { -1, -1, -1, -1 };

int main()
{
    Edge* e[SIZE];
    for (int i = 0; i < SIZE; i++) {
        e[i] = (Edge*)malloc(sizeof(Edge));
    }

    init_edge(e[0], 1, 2, 8);
    init_edge(e[1], 1, 3, 6);
    init_edge(e[2], 1, 4, 8);
    init_edge(e[3], 2, 3, 5);
    init_edge(e[4], 2, 4, 6);
    init_edge(e[5], 3, 4, 10);

    sort_edge(e);

    for (int i = 0; i < SIZE; i++) {
        printf("%d %d : %d\n", e[i]->start, e[i]->end, e[i]->weight);
    }

    MST* mst = (MST*)malloc(sizeof(MST));
    mst->edgelist = (Edge**)malloc(sizeof(Edge));
    mst->size = 0;

    int vertex_count = 4;
    int edge_count = 0;
    insert_MST(mst, e[0]);
    edge_count++;


    //최소신장
    while (mst->size < vertex_count - 1) {
        Edge* tmp = e[edge_count++];
        //사이클이 생기지않으면
        if (vertex_arr[tmp->end] != vertex_arr[tmp->start]) {
            insert_MST(mst, tmp);
        }
    }
    print_MST(mst);

    int start_vertex = 1;
    int vertex_num = start_vertex;
    Edge* start_edge;
    printf("===TSP===\n");
    for (int i = 0; i < mst->size; i++) {
        for (int j = 0; j < mst->size; j++) {
            if (vertex_num == mst->edgelist[j]->start) {
                printf("%d ", vertex_num);
                vertex_num = mst->edgelist[j]->end;
                delete_MST(mst, j);
                break;
            }
            else if (vertex_num == mst->edgelist[j]->end) {
                printf("%d ", vertex_num);
                vertex_num = mst->edgelist[j]->start;
                delete_MST(mst, j);
                break;
            }
        }
    }
    printf("%d %d\n", vertex_num, start_vertex);


    return 0;
}

void init_edge(Edge* e, int start, int end, int weight) {
    e->start = start;
    e->end = end;
    e->weight = weight;
}

void sort_edge(Edge* e[]) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            if (e[i]->weight > e[j]->weight) {
                Edge tmp = *e[i];
                *e[i] = *e[j];
                *e[j] = tmp;
            }
        }
    }
}

void insert_MST(MST* mst, Edge* e) {
    int index = mst->size++;
    mst->edgelist[index] = e;
    vertex_arr[mst->edgelist[index]->end] = mst->edgelist[index]->start;
    for (int i = 0; i < 4; i++) {
        if (vertex_arr[i] == mst->edgelist[index]->end) {
            vertex_arr[i] = mst->edgelist[index]->start;
        }
    }
}

void delete_MST(MST* mst, int index) {
    mst->edgelist[index]->start = -1;
    mst->edgelist[index]->end = -1;

}


void print_MST(MST* mst) {
    printf("==MST==\n");
    for (int i = 0; i < mst->size; i++) {
        printf("%d %d : %d\n", mst->edgelist[i]->start, mst->edgelist[i]->end, mst->edgelist[i]->weight);
    }
}
