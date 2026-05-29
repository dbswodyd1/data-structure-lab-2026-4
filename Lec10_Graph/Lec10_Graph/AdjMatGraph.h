#pragma once
#include <stdio.h>
#include "HeapNode.h"
#include "VertexSets.h"
#include "MinHeap.h"

#define MAX_VTXS 100
#define INF 9999

class AdjMatGraph {
protected:
    int    size;
    char   vertices[MAX_VTXS];
    int    adj[MAX_VTXS][MAX_VTXS];
public:
    AdjMatGraph() { reset(); }
    char getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX_VTXS; }

    // 그래프 초기화 ==> 공백 상태의 그래프
    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, 0);
    }
    // 정점 삽입
    void insertVertex(char name) {
        if (!isFull()) vertices[size++] = name;
        else printf("Error: 그래프 정점 개수 초과\n");
    }
    // 간선 삽입: 무방향 그래프의 경우임. (방향, 가중치 그래프에서는 수정)
    void insertEdge(int u, int v) {
        setEdge(u, v, 1);
        setEdge(v, u, 1); // 방향 그래프에서는 삭제됨(<u,v>만 존재)
    }
    // 그래프 정보 출력 (화면이나 파일에 출력)
    void display(FILE* fp = stdout) {
        fprintf(fp, "%d\n", size);		// 정점의 개수 출력
        for (int i = 0; i < size; i++) {		// 각 행의 정보 출력
            fprintf(fp, "%c", getVertex(i));	// 정점의 이름 출력
            for (int j = 0; j < size; j++)	// 간선 정보 출력
                fprintf(fp, "%5d", getEdge(i, j));
            fprintf(fp, "\n");
        }
    }
};

    // 탐색 기능이 추가된 인접 행렬 기반 그래프 클래스
    class SrchAMGraph : public AdjMatGraph //자식 클래스로 상습받음
    {
        bool visited[MAX_VTXS];	 // 정점의 방문 정보
    public:
        void resetVisited() {	// 모든 정점을 방문하지 않았다고 설정
            for (int i = 0; i < size; i++)
                visited[i] = false; //모든 칸 F로 초기화시켜줌
        }
        bool isLinked(int u, int v) { return getEdge(u, v) != 0; } //연결=true

        // 깊이 우선 탐색 함수
        void DFS(int v) {
            visited[v] = true;	 // 현재 정점을 방문함
            printf("%c ", getVertex(v)); // 정점의 이름 출력

            for (int w = 0; w < size; w++)
                if (isLinked(v, w) && visited[w] == false)
                    DFS(w);	 // 연결 + 방문X => 순환호출로 방문
        }
    };

    class WGraph : public AdjMatGraph {
    public:
        void insertEdge(int u, int v, int weight) {
            if (weight > INF) weight = INF;
            setEdge(u, v, weight);
        }
        bool hasEdge(int i, int j) {
            return (getEdge(i, j) < INF);
        }
        void load(const char* filename) {
            FILE* fp;
            fopen_s(&fp, filename, "r");
            if (fp != NULL) {
                int n, val;
                fscanf_s(fp, "%d", &n); // 정점의 전체 개수
                for (int i = 0; i < n; i++) {
                    char str[80];
                    fscanf_s(fp, "%s", str, unsigned(sizeof(str))); // 정점의 이름
                    insertVertex(str[0]); // 정점 삽입
                    for (int j = 0; j < n; j++) {
                        fscanf_s(fp, "%d", &val); // 간선 정보
                        insertEdge(i, j, val); // 간선 삽입
                    }
                }
            }
            fclose(fp);
        }
    };

    class WGraphMST : public WGraph {
    public:
        void Kruskal() { // kruskal의 최소 비용 신장 트리 프로그램
            MinHeap heap;
            for (int i = 0; i < size - 1; i++)
                for (int j = i + 1; j < size; j++)
                    if (hasEdge(i, j))
                        heap.insert(getEdge(i, j), i, j); // 모든 간선 삽입
            VertexSets set(size); // size개의 집합을 만듦
            int edgeAccepted = 0; // 선택된 간선의 수
            while (edgeAccepted < size - 1) { // 간선의 수 < (size-1)
                HeapNode e = heap.remove();
                int uset = set.findSet(e.getV1());
                int vset = set.findSet(e.getV2());
                if (uset != vset) {
                    printf("간선 추가 : %c - %c (비용:%d)\n",
                    getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());
                    set.unionSets(uset, vset); // 두개의 집합을 합함.
                    edgeAccepted++;
                }
            }
        }
    };
