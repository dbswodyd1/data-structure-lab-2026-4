#pragma once
#include "Building.h"
#include "Path.h"
#include <QMap>
#include <QList>

// 캠퍼스 전체의 건물과 경로 데이터를 관리하는 그래프 자료구조 클래스
class CampusGraph {
public:
    // 건물 데이터를 추가 (코드와 건물 정보를 맵에 저장)
    void addBuilding(const Building& b) { buildings_[b.code] = b; }

    // 경로 데이터를 추가 (출발/도착 정보가 담긴 경로를 리스트에 저장)
    void addPath(const Path& p) { paths_.append(p); }

    // 건물 코드로 건물 정보 하나를 가져오는 함수
    Building building(const QString& code) const { return buildings_.value(code); }

    // 등록된 모든 건물들의 리스트를 반환
    QList<Building> allBuildings() const { return buildings_.values(); }

    // 특정 건물에서 출발하는 모든 경로를 찾아 반환 (나가는 길)
    QList<Path> departures(const QString& code) const {
        QList<Path> res;
        for (const auto& p : paths_) if (p.from == code) res.append(p);
        return res;
    }

    // 특정 건물로 도착하는 모든 경로를 찾아 반환 (들어오는 길)
    QList<Path> arrivals(const QString& code) const {
        QList<Path> res;
        for (const auto& p : paths_) if (p.to == code) res.append(p);
        return res;
    }

private:
    QMap<QString, Building> buildings_; // 건물 코드(Key)와 건물 정보(Value)를 저장하는 맵
    QList<Path> paths_;                 // 모든 경로 정보들을 저장하는 리스트
};