#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculate_clicked()
{
    bool ok;
    int value = ui->value->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(0,"Error","Number is not valid");
        return;
    }
    if (abs(value) < 10 || abs(value) > 99) {
        QMessageBox::warning(0,"Error","Number should be in range [10,99]");
        return;
    }
    int first = abs(value) / 10;
    int last = abs(value) % 10;
    ui->sum->setNum(first + last);
    ui->mult->setNum(first * last);
}


void MainWindow::on_open_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(),"Текстові файли (*.txt);;Усі файли (*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(0,"Error","Can not open file!");
        } else {
            QTextStream in(&file);
            QString num, sum, mult;
            in >> num >> sum >> mult;
            ui->value->setText(num);
            ui->sum->setText(sum);
            ui->mult->setText(mult);
        }
    } else {
        QMessageBox::warning(0,"Error","Unknown filename!");
    }
}


void MainWindow::on_save_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Save File", QDir::currentPath(),"Текстові файли (*.txt);;Усі файли (*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr,"Error","Can not open file:\n"+file.errorString());
        } else {
            QTextStream out(&file);
            out << ui->value->text() << "\n";
            out << ui->sum->text() << "\n";
            out << ui->mult->text() << "\n";
        }
    } else {
        QMessageBox::warning(0,"Error","Unknown filename!");
    }
}

