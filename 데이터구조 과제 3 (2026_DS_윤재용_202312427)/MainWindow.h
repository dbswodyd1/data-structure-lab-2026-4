#pragma once
#include <QMainWindow>
#include <QHBoxLayout>
#include "CampusGraph.h"
#include "RouteMapWidget.h"
#include "BookingPanel.h"

// 프로그램의 메인 화면을 담당하는 클래스
class MainWindow : public QMainWindow {
public:
    // 생성자: 화면 구성 및 초기 설정 수행
    MainWindow() {
        setWindowTitle("전북대학교 캠퍼스 경로 안내");
        resize(1000, 700);

        // 캠퍼스 데이터(건물 및 경로) 구축
        buildGraph();

        // 중앙 위젯 설정 및 수평 레이아웃 생성
        auto* central = new QWidget(this);
        setCentralWidget(central);
        auto* layout = new QHBoxLayout(central);

        // 지도 위젯 추가 (화면의 3/4 차지)
        map_ = new RouteMapWidget;
        map_->setGraph(&graph_);
        layout->addWidget(map_, 3);

        // 정보 패널 위젯 추가 (화면의 1/4 차지)
        panel_ = new BookingPanel;
        panel_->setGraph(&graph_);
        layout->addWidget(panel_, 1);

        // 지도에서 건물을 클릭했을 때 패널의 정보를 갱신하는 연결 고리 설정
        map_->onClicked([this](QString code) { panel_->showBuilding(code); });
    }

private:
    CampusGraph graph_;        // 캠퍼스 데이터를 관리하는 그래프 객체
    RouteMapWidget* map_;      // 지도를 그리는 위젯
    BookingPanel* panel_;      // 건물 정보를 보여주는 패널 위젯

    // 캠퍼스 내 건물 정보와 이동 경로를 그래프에 추가하는 함수
    void buildGraph() {
        graph_.addBuilding({ "ENG", "공과대학", 0.61, 0.57 });
        graph_.addBuilding({ "LIB", "중앙도서관", 0.52, 0.39 });
        graph_.addBuilding({ "NEW", "신정문", 0.53, 0.95 });
        graph_.addBuilding({ "OLD", "구정문", 0.35, 0.7 });
        graph_.addBuilding({ "DORM", "기숙사", 0.3, 0.22 });

        // 각 건물 간 이동 가능한 경로들을 양방향으로 추가
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

    // 양방향 경로를 그래프에 등록하는 헬퍼 함수
    void addRoundTrip(QString a, QString b, int m) {
        graph_.addPath({ a, b, m });
        graph_.addPath({ b, a, m });
    }
};