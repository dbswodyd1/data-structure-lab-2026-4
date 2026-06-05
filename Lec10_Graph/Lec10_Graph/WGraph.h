#pragma once
#include "AdjMatGraph.h"

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