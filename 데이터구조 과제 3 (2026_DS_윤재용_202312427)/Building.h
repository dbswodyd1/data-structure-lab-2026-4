#pragma once
#include <QString>

struct Building {
    QString code; // 건물 코드 (예: "ENG", "LIB")
    QString name; // 건물 이름 (예: "공과대학")
    double  nx;   // 지도상 X 좌표 (0.0 ~ 1.0)
    double  ny;   // 지도상 Y 좌표 (0.0 ~ 1.0)
};
