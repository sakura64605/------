#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "DBConnector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

signals:
    void loginSuccess();

private slots:
    void onLoginClicked();

private:
    Ui::LoginWidget *ui;
    DBConnector db;
};

#endif // LOGINWIDGET_H