#pragma once
#include "Building.h"
#include "Path.h"
#include <QMap>
#include <QList>

class CampusGraph {
public:
    void addBuilding(const Building& b) { buildings_[b.code] = b; }
    void addPath(const Path& p) { paths_.append(p); }
    
    Building building(const QString& code) const { return buildings_.value(code); }
    QList<Building> allBuildings() const { return buildings_.values(); }
    
    QList<Path> departures(const QString& code) const {
        QList<Path> res;
        for (const auto& p : paths_) if (p.from == code) res.append(p);
        return res;
    }
    QList<Path> arrivals(const QString& code) const {
        QList<Path> res;
        for (const auto& p : paths_) if (p.to == code) res.append(p);
        return res;
    }
private:
    QMap<QString, Building> buildings_;
    QList<Path> paths_;
};