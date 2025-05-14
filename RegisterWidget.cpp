#include "RegisterWidget.h"
#include "ui_RegisterWidget.h"
#include <QMessageBox>
#include <QCryptographicHash>

RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
    db.connect("localhost", "root", "", "library_db");
    connect(ui->registerButton, &QPushButton::clicked, this, &RegisterWidget::onRegisterClicked);
}

RegisterWidget::~RegisterWidget() {
    delete ui;
    db.close();
}

void RegisterWidget::onRegisterClicked() {
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();
    QString confirm = ui->confirmEdit->text();

    if (password != confirm) {
        QMessageBox::warning(this, "错误", "两次密码输入不一致");
        return;
    }

    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString hashedPass = QString(hash.toHex());

    QSqlQuery check = db.executeQuery(
        QString("SELECT id FROM users WHERE username = '%1'").arg(username));
    
    if (check.next()) {
        QMessageBox::warning(this, "错误", "用户名已存在");
        return;
    }

    QString query = QString("INSERT INTO users(username, password) VALUES('%1', '%2')")
        .arg(username).arg(hashedPass);

    if (db.executeQuery(query).lastError().type() == QSqlError::NoError) {
        QMessageBox::information(this, "成功", "注册成功");
        emit registered();
        close();
    } else {
        QMessageBox::critical(this, "错误", "注册失败");
    }
}