#include <stdio.h>
#define COST 10
#define COUNTRY 8
#define MAX(x,y)(x)>(y)? x:y
typedef enum {
	S = 5, A = 4, B = 3, C = 2, D = 1
}Rank;
int WP[COUNTRY][COST] = { 0 };

int W[COUNTRY + 1] = {0,2,6,4,3,1,7,2,3};
int V[COUNTRY + 1] = { 0,S,S,B,A,C,S,D,B };
char* BAG[COUNTRY + 1] = { NULL,"JAPAN","CHINA","TAIWAN","THAILAND","KHAMBODIA","TURKEY"
					,"VIETNAM","MALAYSIA" };


void knapsack() {
	int i, w;
	for (i = 1; i < COUNTRY + 1; i++) {
		for (w = 0; w < COST; w++) {
			if (w - W[i] < 0) {
				WP[i][w] = WP[i - 1][w];
			}
			else {
				WP[i][w] = MAX(WP[i - 1][w], WP[i - 1][w - W[i]] + V[i]);
			}
		}
	}
	for (i = 1; i < COUNTRY + 1; i++) {
		for (w = 0; w < COST; w++) {
			printf("%d ", WP[i][w]);
		}
		printf("\n");
	}
	w = COST-1;
	int include[COUNTRY + 1] = { 0 };
	while(w){
		i = COUNTRY;
		if (WP[i][w] != WP[i][w - 1]) {
			while (i > 0) {
				if (WP[i - 1][w] != WP[i][w]) {
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
	printf("\n");
	for (int j = 0; j < COUNTRY+1; j++) {
		if (include[j]) {
			printf(" %s ", BAG[j]);
		}
	}


}
int main(void) {
	knapsack();
	return 0;
}
