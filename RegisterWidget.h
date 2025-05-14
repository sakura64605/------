#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include "DBConnector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterWidget; }
QT_END_NAMESPACE

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    ~RegisterWidget();

private slots:
    void onRegisterClicked();

private:
    Ui::RegisterWidget *ui;
    DBConnector db;
};

#endif // REGISTERWIDGET_H