#pragma once
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <functional>
#include "CampusGraph.h"

// 캠퍼스 지도를 화면에 그리고 건물 선택 이벤트를 처리하는 위젯 클래스
class RouteMapWidget : public QWidget {
public:
    RouteMapWidget(QWidget* parent = nullptr) : QWidget(parent) {
        // 배경으로 사용할 school.png 파일이 프로젝트 폴더에 필요함
    }

    // 그래프 데이터를 연결하고 화면을 새로 그림
    void setGraph(const CampusGraph* g) { graph_ = g; update(); }

    // 건물 클릭 시 외부(MainWindow)에 알리기 위한 콜백 함수 설정
    void onClicked(std::function<void(QString)> cb) { callback_ = cb; }

protected:
    // 화면을 그릴 때 호출되는 이벤트 함수
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);

        // 배경 지도 이미지를 위젯 크기에 맞춰 그림
        QPixmap map("school.png");
        if (!map.isNull()) p.drawPixmap(rect(), map);

        if (!graph_) return;

        // 등록된 모든 건물들을 지도 위에 원(점)으로 표시
        for (const auto& b : graph_->allBuildings()) {
            int x = b.nx * width(), y = b.ny * height(); // 비율 좌표를 실제 픽셀 좌표로 변환
            p.setBrush(Qt::red);
            p.drawEllipse(x - 10, y - 10, 20, 20); // 건물 위치에 빨간 원 그리기
            p.setPen(Qt::black);
            p.drawText(x + 15, y + 5, b.name);      // 건물 이름 표시
        }
    }

    // 마우스를 클릭했을 때 호출되는 이벤트 함수
    void mousePressEvent(QMouseEvent* e) override {
        if (!graph_) return;

        // 클릭한 위치가 건물의 좌표 범위 내에 있는지 확인
        for (const auto& b : graph_->allBuildings()) {
            int x = b.nx * width(), y = b.ny * height();
            // 클릭 지점과 건물 중심의 거리가 일정 범위(20픽셀) 이내라면 클릭으로 간주
            if (abs(e->pos().x() - x) < 20 && abs(e->pos().y() - y) < 20) {
                if (callback_) callback_(b.code); // 등록된 콜백 함수 실행 (MainWindow로 신호 전달)
            }
        }
    }

private:
    const CampusGraph* graph_ = nullptr;        // 데이터 조회를 위한 그래프 포인터
    std::function<void(QString)> callback_;    // 클릭 시 실행할 함수 포인터 (이벤트 리스너)
};