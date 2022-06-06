#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    opened_file = "";
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString str;
    str = QFileDialog::getOpenFileName(this,
        tr("Open..."), "", tr("Filetypes (*.txt)"));

    std::cout << "open clicked" << std::endl;

    QFile file(str);
    if (file.open(QIODevice::ReadOnly)!=1){
        std::cout << str.toStdString() << " could not be opened." << std::endl;
        return;
    }

    opened_file = str;
    QDataStream f_in(&file);
    char n[file.size()];
    f_in.readRawData(n,file.size());

    std::cout << str.toStdString() << ":lol" << std::endl;
    std::cout << file.size() << ":size" << std::endl;

    file.close();

    QTextBrowser * t_box = findChild<QTextBrowser *>("textBox");
    t_box->clear();
    t_box->setPlainText(n);

}


void MainWindow::on_actionSave_triggered()
{
    if (opened_file=="")return;
    QTextBrowser *  t_box = findChild<QTextBrowser *>("textBox");
    QFile file(opened_file);
    if (file.open(QIODevice::WriteOnly)!=1){
        std::cout << "There was an error saving the file." << std::endl;
        return;
    }

    QByteArray text = t_box->toPlainText().toLocal8Bit();
    file.write(text);
}

