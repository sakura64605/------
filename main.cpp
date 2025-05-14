#include "LoginWidget.h"
#include "RegisterWidget.h"
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 初始化数据库连接
    DBConnector db;
    if (!db.connect("localhost", "root", "", "library_db")) {
        return 1;
    }

    LoginWidget login;
    RegisterWidget registerWidget;
    MainWindow mainWindow;

    QObject::connect(&login, &LoginWidget::loginSuccess, &mainWindow, &MainWindow::show);
    QObject::connect(&registerWidget, &RegisterWidget::registered, &login, &LoginWidget::show);

    login.show();
    
    return a.exec();
}