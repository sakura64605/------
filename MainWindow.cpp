#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.connect("localhost", "root", "", "library_db");
    
    model = new QSqlTableModel(this, db.getDatabase());
    model->setTable("books");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddBook);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteBook);
}

MainWindow::~MainWindow() {
    delete ui;
    db.close();
}

void MainWindow::refreshTable() {
    model->select();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::onSearch() {
    QString keyword = ui->searchEdit->text().trimmed();
    if (keyword.isEmpty()) {
        model->setFilter("");
    } else {
        QString filter = QString("title LIKE '%%1%' OR author LIKE '%%1%' OR isbn LIKE '%%1%'").arg(keyword);
        model->setFilter(filter);
    }
    refreshTable();
}

void MainWindow::onAddBook() {
    bool ok;
    QString isbn = QInputDialog::getText(this, "添加图书", "ISBN:", QLineEdit::Normal, "", &ok);
    if (!ok || isbn.isEmpty()) return;

    QString title = QInputDialog::getText(this, "添加图书", "书名:", QLineEdit::Normal, "", &ok);
    if (!ok || title.isEmpty()) return;

    QString author = QInputDialog::getText(this, "添加图书", "作者:", QLineEdit::Normal, "", &ok);
    
    QSqlRecord record = model->record();
    record.setValue("isbn", isbn);
    record.setValue("title", title);
    record.setValue("author", author);
    record.setValue("quantity", 1);

    if (model->insertRecord(-1, record)) {
        model->submitAll();
        refreshTable();
        QMessageBox::information(this, "成功", "图书添加成功");
    } else {
        QMessageBox::critical(this, "错误", "添加失败: " + model->lastError().text());
    }
}

void MainWindow::onDeleteBook() {
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择要删除的图书");
        return;
    }

    int row = selected.first().row();
    QString isbn = model->data(model->index(row, 0)).toString();
    
    if (QMessageBox::question(this, "确认", "确定要删除 ISBN: " + isbn + " 吗?") == QMessageBox::Yes) {
        model->removeRow(row);
        model->submitAll();
        refreshTable();
    }
}