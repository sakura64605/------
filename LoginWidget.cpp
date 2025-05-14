#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include <QMessageBox>
#include <QCryptographicHash>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    db.connect("localhost", "root", "", "library_db");
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);
}

LoginWidget::~LoginWidget() {
    delete ui;
    db.close();
}

void LoginWidget::onLoginClicked() {
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "错误", "用户名或密码不能为空");
        return;
    }

    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString hashedPass = QString(hash.toHex());

    QSqlQuery query = db.executeQuery(
        QString("SELECT password FROM users WHERE username = '%1'").arg(username));

    if (query.next()) {
        if (query.value(0).toString() == hashedPass) {
            QMessageBox::information(this, "成功", "登录成功");
            emit loginSuccess();
            close();
            return;
        }
    }
    
    QMessageBox::critical(this, "错误", "用户名或密码错误");
}