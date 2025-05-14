QT += core gui sql widgets

TARGET = LibraryManager
TEMPLATE = app

SOURCES += main.cpp \
           DBConnector.cpp \
           LoginWidget.cpp \
           RegisterWidget.cpp \
           MainWindow.cpp

HEADERS += DBConnector.h \
           LoginWidget.h \
           RegisterWidget.h \
           MainWindow.h

FORMS += LoginWidget.ui \
          RegisterWidget.ui \
          MainWindow.ui

# MySQL驱动配置
QMAKE_USE += mysql
LIBS += -L"C:/MySQL/lib" -llibmysql
INCLUDEPATH += "C:/MySQL/include"