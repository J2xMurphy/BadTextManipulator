#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

void MainWindow::on_actionOpen_triggered()
{
    QFile fileName;
    QString str;
    str = QFileDialog::getOpenFileName(this,
        tr("Open..."), "", tr("Filetypes (*.txt)"));

    std::cout << "open clicked" << std::endl;

    QFile file(str);
    if (file.open(QIODevice::ReadOnly)!=1){
        return;
    }

    QDataStream f_in(&file);
    char n[30];
    f_in.readRawData(n,30);

    std::cout << str.toStdString() << ":lol" << std::endl;

    QLabel * lab = findChild<QLabel *>("label");
    lab->setText(n);
}

