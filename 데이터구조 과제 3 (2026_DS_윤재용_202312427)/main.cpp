#include <QApplication>
#include "MainWindow.h"

// 프로그램이 시작되는 메인 함수
int main(int argc, char* argv[]) {
    // Qt 애플리케이션 객체 생성 (GUI 환경 설정)
    QApplication app(argc, argv);

    // 메인 화면(MainWindow) 객체 생성
    MainWindow w;

    // 메인 화면을 화면에 표시
    w.show();

    // 프로그램 실행 루프 시작 (종료 시까지 대기)
    return app.exec();
}