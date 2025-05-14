#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DBConnector.h"
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearch();
    void onAddBook();
    void onDeleteBook();

private:
    Ui::MainWindow *ui;
    DBConnector db;
    QSqlTableModel *model;
    void refreshTable();
};

#endif // MAINWINDOW_H