#include <stdio.h>
#include "AdjMatGraph.h"	// 그래프 클래스 포함

int main()
{
    SrchAMGraph g;	// 새로운 그래프 객체 생성

    for (int i = 0; i < 8; i++)
        g.insertVertex('A' + i);	// 정점 삽입: 'A' 'B', ...
    g.insertEdge(0, 1);      	// 간선 삽입
    g.insertEdge(0, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);
    g.insertEdge(2, 4);
    g.insertEdge(3, 5);
    g.insertEdge(4, 6);
    g.insertEdge(4, 7);
    g.insertEdge(6, 7);
   
    printf("인접 행렬로 표현한 그래프\n");
    g.display();
    
    //파일 출력
    FILE* fp;
    fopen_s(&fp, "../text_out.txt", "w");
    g.display(fp);
    fclose(fp);
    
    //DFS 탐색으로 방문
   
    printf("DFS ==> ");
    g.resetVisited();
    g.DFS(0);
    printf("\n");

    return 0;
}
