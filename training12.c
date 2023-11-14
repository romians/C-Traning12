#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF 1000000

//그래프 구조체 
typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];

//ployd 알고리즘 함수
void ployd(GraphType* g) {
    int i, j, k;
    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->n; j++) {
            A[i][j] = g->weight[i][j];
            path[i][j] = -1; // 초기값으로 -1을 설정합니다.
        }
    }

    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++) {
            for (j = 0; j < g->n; j++) {
                if (A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k; // 중간 경로를 저장합니다.
                }
            }
        }
    }
}

//최단 경로 출력 함수
void printPath(int start, int end) {
    if (path[start][end] == -1) {
        printf("%d ", start + 1);
    }

    else {
        printPath(start, path[start][end]);
        printf("%d ", path[start][end] + 1);
        printPath(path[start][end], end);
    }
}

int main(void) {

    //시작 노드와 끝 노드 넣을 변수 선언
    int start, end;

    GraphType g = { 10, {
            {0, 3, INF, INF, INF, 11, 12, INF, INF, INF},
            {3, 0, 5, 4, 1, 7, 8, INF, INF, INF},
            {INF, 5, 0, 2, INF, INF, 6, 5, INF, INF},
            {INF, 4, 2, 0, 13, INF, INF, 14, INF, 16},
            {INF, 1, INF, 13, 0, 9, INF, INF, 18, 17},
            {11, 7, INF, INF, 9, 0, INF, INF, INF, INF},
            {12, 8, 6, INF, INF, INF, 0, 13, INF, INF},
            {INF, INF, 5, 14, INF, INF, 13, 0, INF, 15},
            {INF, INF, INF, INF, 18, INF, INF, INF, 0, 10},
            {INF, INF, INF, 16, 17, INF, INF, 15, 10, 0}
        }
    };

    //ployd 알고리즘 함수 호출
    ployd(&g);

    printf("Ployd-Warshall Algorithm\n");
    for (int i = 0; i <= 6; i++) {
        start = 0;
        end = 0;

        printf("\nStart Node : ");
        scanf("%d", &start);
        printf("End Node : ");
        scanf("%d", &end);

        if (start < 1 || start > g.n || end < 1 || end > g.n) {
            printf("Invalid input.\n");
        }
        else {
            printf("Shortest Distance : %d\n", A[start - 1][end - 1]);
            printf("Shortest Path : ");
            printPath(start - 1, end - 1);
            printf("\n");
        }
    }

    return 0;
}