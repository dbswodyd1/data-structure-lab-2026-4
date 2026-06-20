#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include "CampusGraph.h"

// 건물 정보를 표시하고 경로를 리스트로 보여주는 우측 패널 클래스
class BookingPanel : public QWidget {
public:
    // 생성자: 패널의 레이아웃과 기본 UI 구성
    BookingPanel(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumWidth(300);
        setStyleSheet("background:white; color:black;");
        auto* layout = new QVBoxLayout(this);
        
        // 건물 이름을 표시할 라벨
        title_ = new QLabel("건물을 선택하세요");
        layout->addWidget(title_);
        
        // 주변 경로를 보여줄 리스트 위젯
        list_ = new QListWidget;
        layout->addWidget(list_);
    }

    // 그래프 데이터 객체를 받아옴
    void setGraph(const CampusGraph* g) { graph_ = g; }

    // 건물을 클릭했을 때 호출되는 함수
    void showBuilding(const QString& code) {
        if (!graph_) return;
        // 클릭한 건물의 정보를 가져와 제목 업데이트
        auto b = graph_->building(code);
        title_->setText("<h2>" + b.name + "</h2>");
        list_->clear();

        // 해당 건물에서 출발하는 모든 경로를 찾아 리스트에 추가
        for (const auto& p : graph_->departures(code)) {
            list_->addItem(QString("%1 - %2분 소요")
                .arg(graph_->building(p.to).name)
                .arg(p.minutes));
        }
    }

private:
    QLabel* title_;                         // 건물 이름 표시용 라벨
    QListWidget* list_;                     // 경로 목록 표시용 위젯
    const CampusGraph* graph_ = nullptr;    // 데이터 관리를 위한 그래프 객체 포인터
};