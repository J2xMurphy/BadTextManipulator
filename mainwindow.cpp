#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    opened_file = "";
    ui->setupUi(this);
    s_bar = this->findChild<QStatusBar *>("statusbar");
    setupStatusBar(s_bar);
    t_box = findChild<QTextBrowser *>("textBox");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupStatusBar(QStatusBar * stabar){
    stabar->showMessage("0");
    QLabel * s_info = new QLabel("Information");
    s_info->objectName() = "s_info";
    stabar->addPermanentWidget(s_info);
}

void MainWindow::on_actionOpen_triggered()
{
    QString str;
    str = QFileDialog::getOpenFileName(this,
        "Open...", "", "Filetypes (*.txt)");

    QFile file(str);
    if (file.open(QIODevice::ReadOnly)!=1){
        std::cout << str.toStdString() << " could not be opened." << std::endl;
        return;
    }

    opened_file = str;
    QDataStream f_in(&file);
    char n[file.size()];
    f_in.readRawData(n,file.size());
    file.close();

    t_box->clear();
    t_box->setPlainText(n);
    update_word_count();
}


void MainWindow::on_actionSave_triggered()
{
    if (opened_file=="")return;
    QFile file(opened_file);
    if (file.open(QIODevice::WriteOnly)!=1){
        std::cout << "There was an error saving the file." << std::endl;
        return;
    }

    QByteArray text = t_box->toPlainText().toLocal8Bit();
    file.write(text);
}


void MainWindow::on_actionSave_As_triggered()
{
    opened_file = QFileDialog::getSaveFileName(this,"Save as...","","*.txt");
    on_actionSave_triggered();

}


void ::MainWindow::update_word_count(){
    s_bar->showMessage(
        QString::number(findChild<QTextBrowser *>("textBox")->toPlainText().length())
                );
}


void MainWindow::on_textBox_textChanged()
{
    update_word_count();
}


void MainWindow::on_actionFont_List_triggered()
{
    QDialog font_select(this);
    QFormLayout f_layout(&font_select);

    QFontComboBox * font_scroll = new QFontComboBox;
    font_scroll->setCurrentFont(t_box->currentFont());
    f_layout.addRow(new QLabel("Font Type:"),font_scroll);

    QSpinBox * font_spin = new QSpinBox;
    font_spin->setRange(4,50);
    font_spin->setValue(t_box->font().pointSize());
    f_layout.addRow(new QLabel("Font size:"),font_spin);

    QPushButton * accept= new QPushButton("Apply");
    f_layout.addRow(accept);

    QObject::connect(accept,SIGNAL(clicked()),&font_select,SLOT(accept()));

    font_select.exec();

    QFont q;
    q.setFamily(font_scroll->currentFont().toString());
    q.setPointSize(font_spin->value());
    t_box->setFont(q);

    delete font_scroll;
    delete font_spin;
    delete accept;
}


void MainWindow::on_actionSelector_triggered()
{
    QDialog show_results(this);
    QFormLayout f_layout(&show_results);

    f_layout.addWidget(new QLabel(get_Selected_Text()));

    show_results.exec();
}

QString MainWindow::get_Selected_Text(){
    return t_box->textCursor().selectedText();
}

void MainWindow::on_actionFind_triggered()
{
    QInputDialog * QI = new QInputDialog;
    QString lol = QI->getText(this,"Find...","Find text:",QLineEdit::Normal,search_term);
    QString text;
    int found_index;

    text = t_box->toPlainText();
    found_index = text.indexOf(lol,t_box->textCursor().position());

    if (found_index == -1){
        QMessageBox * QMB = new QMessageBox;
        QMB->setWindowTitle("Find...");
        QMB->setText("'"+lol+"' not found.");
        QMB->exec();
    }else{
        QTextCursor QTC = t_box->textCursor();
        QTC.setPosition(found_index);
        QTC.setPosition(found_index+(lol.length()), QTextCursor::KeepAnchor);
        search_term = lol;
        t_box->setTextCursor(QTC);
    }

    delete QI;

}

