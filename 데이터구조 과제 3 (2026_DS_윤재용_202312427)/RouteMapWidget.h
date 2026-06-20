#pragma once
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <functional>
#include "CampusGraph.h"

class RouteMapWidget : public QWidget {
public:
    RouteMapWidget(QWidget* parent = nullptr) : QWidget(parent) {
        // school.png 파일이 프로젝트 폴더에 있어야 함
    }
    void setGraph(const CampusGraph* g) { graph_ = g; update(); }
    void onClicked(std::function<void(QString)> cb) { callback_ = cb; }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        // 배경 지도 그리기 (school.png가 존재할 경우)
        QPixmap map("school.png");
        if(!map.isNull()) p.drawPixmap(rect(), map);

        if(!graph_) return;
        for(const auto& b : graph_->allBuildings()) {
            int x = b.nx * width(), y = b.ny * height();
            p.setBrush(Qt::red);
            p.drawEllipse(x-10, y-10, 20, 20);
            p.setPen(Qt::black); // 글씨 검은색
            p.drawText(x+15, y+5, b.name);
        }
    }
    void mousePressEvent(QMouseEvent* e) override {
        if(!graph_) return;
        for(const auto& b : graph_->allBuildings()) {
            int x = b.nx * width(), y = b.ny * height();
            if(abs(e->pos().x()-x) < 20 && abs(e->pos().y()-y) < 20) callback_(b.code);
        }
    }
private:
    const CampusGraph* graph_ = nullptr;
    std::function<void(QString)> callback_;
};