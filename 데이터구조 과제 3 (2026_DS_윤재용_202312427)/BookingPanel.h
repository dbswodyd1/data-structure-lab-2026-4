#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include "CampusGraph.h"

class BookingPanel : public QWidget {
public:
    BookingPanel(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumWidth(300);
        setStyleSheet("background:white; color:black;");
        auto* layout = new QVBoxLayout(this);
        
        title_ = new QLabel("건물을 선택하세요");
        layout->addWidget(title_);
        
        list_ = new QListWidget;
        layout->addWidget(list_);
    }

    void setGraph(const CampusGraph* g) { graph_ = g; }

    void showBuilding(const QString& code) {
        if (!graph_) return;
        auto b = graph_->building(code);
        title_->setText("<h2>" + b.name + "</h2>");
        list_->clear();

        for (const auto& p : graph_->departures(code)) {
            list_->addItem(QString("%1 - %2분 소요")
                .arg(graph_->building(p.to).name)
                .arg(p.minutes));
        }
    }

private:
    QLabel* title_;
    QListWidget* list_;
    const CampusGraph* graph_ = nullptr;
};