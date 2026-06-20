#pragma once
#include <QString>

struct Path {
    QString from;    // 출발 건물 코드
    QString to;      // 도착 건물 코드
    int minutes; // 소요 시간 (가중치)
};