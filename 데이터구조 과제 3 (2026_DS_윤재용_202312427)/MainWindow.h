#pragma once
#include <QMainWindow>
#include <QHBoxLayout>
#include "CampusGraph.h"
#include "RouteMapWidget.h"
#include "BookingPanel.h"

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        setWindowTitle("전북대학교 캠퍼스 경로 안내");
        resize(1000, 700);
        
        // 1. 데이터 구축 함수 호출
        buildGraph();

        auto* central = new QWidget(this);
        setCentralWidget(central);
        auto* layout = new QHBoxLayout(central);

        map_ = new RouteMapWidget;
        map_->setGraph(&graph_);
        layout->addWidget(map_, 3);

        panel_ = new BookingPanel;
        panel_->setGraph(&graph_);
        layout->addWidget(panel_, 1);

        map_->onClicked([this](QString code) { panel_->showBuilding(code); });
    }

private:
    CampusGraph graph_;
    RouteMapWidget* map_;
    BookingPanel* panel_;

    // 2. buildGraph 함수 생성
    void buildGraph() {
        graph_.addBuilding({"ENG", "공과대학", 0.61, 0.57});
        graph_.addBuilding({"LIB", "중앙도서관", 0.52, 0.39});
        graph_.addBuilding({"NEW", "신정문", 0.53, 0.95});
        graph_.addBuilding({"OLD", "구정문", 0.35, 0.7});
        graph_.addBuilding({"DORM", "기숙사", 0.3, 0.22});
        
        addRoundTrip("ENG", "LIB", 7);
        addRoundTrip("ENG", "NEW", 15);
        addRoundTrip("ENG", "OLD", 12);
        addRoundTrip("ENG", "DORM", 17);
        addRoundTrip("LIB", "NEW", 16);
        addRoundTrip("LIB", "OLD", 11);
        addRoundTrip("LIB", "DORM", 9);
        addRoundTrip("NEW", "OLD", 11);
        addRoundTrip("NEW", "DORM", 20);
        addRoundTrip("OLD", "DORM", 15);
    }

    void addRoundTrip(QString a, QString b, int m) {
        graph_.addPath({a, b, m}); 
        graph_.addPath({b, a, m});
    }
};