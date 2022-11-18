#include <stdio.h>
#include <windows.h>

#define NODE_NUM_1 6
#define NODE_NUM_2 7
#define NODE_NUM 12

// 인접행렬 인접해있다면 1, 그렇지 않으면 0으로 표시
int connectionMatrix_1[NODE_NUM_1][NODE_NUM_1] = {
		{0, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1},
		{0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0}

};
int connectionMatrix_2[NODE_NUM_2][NODE_NUM_2] = {
	{0, 1, 1, 1, 0, 0, 0},
	{1, 0, 1, 1, 1, 0, 0},
	{1, 1, 0, 0, 1, 0, 1},
	{1, 1, 0, 0, 1, 1, 1},
	{0, 1, 1, 1, 0, 1, 0},
	{0, 0, 0, 1, 1, 0, 0},
	{0, 0, 1, 1, 0, 0, 0}
};
int connectionMatrix_3[NODE_NUM][NODE_NUM] = {
	{0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
	{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0},
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0}
};
/// <summary>
/// node_color 배열에 color를 칠한다.
/// </summary>
/// <param name="node_color">칠한 color를 저장해두기 위한 배열</param>
/// <param name="node_index">칠할 node를 가르키기 위한 변수</param>
int GraphColoring(int* node_color, int node_index, int color) {
	int promise;
	for (int j = 0; j < NODE_NUM; j++) {
		// 인접 노드에 같은 색이 칠해져 있다면 return한다.
		if (connectionMatrix_3[node_index][j] == 1 && node_color[j] == color) {
			node_color[node_index] = -1;
			promise = 0;
			return promise;
		}
	}
	promise = 1;
	node_color[node_index] = color;
	for (int i = 0; i < 10; i++) {
		if (node_color[NODE_NUM - 1] != -1 || GraphColoring(node_color, node_index + 1, i))
			break;
	}

	return promise;
}


int main() {
	int success = 1;

	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$                             $$                                     $$                            $\n");
	printf("$                             $$                                     $$                            $\n");
	printf("$                             ,.                                     !.                            $\n");
	printf("$           1                 ,.                            $$$$$$$$$-$$$$$$$$$~                   $\n");
	printf("$                       ------:~---,                        $                  *                   $\n");
	printf("$                      -:          *                        $                  *                   $\n");
	printf("$                      -:          *                        $                  *                   $\n");
	printf("$    !$$$$$$$$$$$;     -:          *                        $                  *                   $\n");
	printf("$    *          .*,,,,,::          *       7                $          10      *                   $\n");
	printf("$    *          .$;;;;;*:    6     *                        $                  *         12        $\n");
	printf("$    *          .!     -:          *                        $                  *                   $\n");
	printf(";    *          .!     -:          *                        $                  *                   $\n");
	printf(";    *          .!     -:          *                        $                  *                   $\n");
	printf(";    *    2     .!      $$$$$$$$$$$$                        $                  *                   $\n");
	printf(";    *          .!            ,.                            $........,.........!                   $\n");
	printf(";    *          .!            ,.                                     !.                            $\n");
	printf(";    *          .!            ,.                         *$$$$$$$$$$$@#$$$$$$$$$$!                 $\n");
	printf(";    *          .!            ,.            .,,,,,,,,,,  $                       $                 $\n");
	printf(";    *          .!            ,.            $;;;;;;;;;!  $                       $                 $\n");
	printf("$    $$$$$$$$$$$$$            $$            $         $  $                       $                 $\n");
	printf("$ 1  $   $      $$            $$$$$$$$$$$$$$$         $$$$           9           $$$$$$$$$$$$$$$$$$$\n");
	printf("$    $   @      .!                          $         ,  $                       $                 #\n");
	printf("$    $   @      .!                          $         ,  $                       $                 $\n");
	printf(";    $   @      .!                          $         ,  *$$$$$$$$$$$$$$$$$$$$$$$!                 $\n");
	printf(";    $   @      .!                          $         ,                                            $\n");
	printf(";    $   @      .!        5                 $         ,                                            $\n");
	printf(";    $ 3 @   4  .!                          $    8    ,                                            $\n");
	printf(";    $   @      .!                          $         ,                                            $\n");
	printf(";    $   @      .!                          $         ,                                            $\n");
	printf(";    $   @      .!                          $         ,                                            $\n");
	printf(";    $   @$$$$$$.!$$$$$$$$$$$$$$$$$$$$$$$$$$$         ,                                            $\n");
	printf(";    $          .!                          $         ,                                            $\n");
	printf(";    $,,,,,,,,,,-!                          $         ,                                            $\n");
	printf(";    $;;;;;;;;;;;-                          $         ,                                            $\n");
	printf(";                                           $$$$$$$$$$#                 11                         $\n");
	printf(";                        1                      @                                                  $\n");
	printf(";                                               @                                                  $\n");
	printf(";                                               @                                                  $\n");
	printf(";                                               @                                                  $\n");
	printf(";                                               @                                                  $\n");
	printf(";:::::::::::::::::::::::::::::::::::::::::::::::!::::::::::::::::::::::::::::::::::::::::::::::::::!\n");

	// 각 그래프 노드가 가질 color 값, default = -1;
	int node_color[12];
	int input_color[12];
	for (int i = 0; i < 12; i++) {
		printf("%d번 칸에 색칠할 색깔(0, 1, 2, 3, 4 ...)을 입력해주세요. (단, 1번 칸에는 0을, 2번 칸에는 1을 칠해주세요.)\n", i + 1);
		printf(">> ");
		scanf_s(" %d", &input_color[i]);
		node_color[i] = -1;
	}

	GraphColoring(node_color, 0, 0);

	for (int i = 0; i < NODE_NUM; i++) {
		printf("%d번 칸에 색칠해야되는 색은 %d색이었습니다.\n", i + 1, node_color[i]);
		Sleep(5);
		printf("%d번 칸에 %d색을 칠하셨습니다.\n", i + 1, input_color[i]);
		Sleep(5);
		if (node_color[i] != input_color[i])
			success = 0;
	}

	if (success == 1)
		printf("축하드립니다! 정답입니다!");
	else
		printf("아쉽지만 오답입니다. 다시 생각해보세요.");


	return 0;
}