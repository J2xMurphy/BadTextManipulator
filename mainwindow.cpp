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
    setWindowTitle("Text Manipulator");
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
    QString dir;
    dir = QFileDialog::getOpenFileName(this,
        "Open...", "", "Filetypes (*.txt)");

    QFile file(dir);
    if (file.open(QIODevice::ReadOnly)!=1){
        std::cout << dir.toStdString() << " could not be opened." << std::endl;
        return;
    }

    opened_file = dir;
    QDataStream f_in(&file);
    char n[file.size()];
    f_in.readRawData(n,file.size());
    file.close();

    setWindowTitle(dir);
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

    word_Search(lol);

    delete QI;
}

bool MainWindow::word_Search(QString word){
    QString text;
    int found_index;

    text = t_box->toPlainText();
    found_index = text.indexOf(word,t_box->textCursor().position());

    if (found_index == -1){
        push_message_box("'"+word+"' not found after cursor.");
        return false;
    }else{
        QTextCursor QTC = t_box->textCursor();
        QTC.setPosition(found_index);
        QTC.setPosition(found_index+(word.length()), QTextCursor::KeepAnchor);
        search_term = word;
        t_box->setTextCursor(QTC);
        return true;
    }

}

void MainWindow::push_message_box(QString message){
    QMessageBox * QMB = new QMessageBox;
    QMB->setWindowTitle("Find...");
    QMB->setText(message);
    QMB->exec();
    delete QMB;
}

void MainWindow::on_actionNew_triggered()
{
    t_box->clear();
    opened_file = "";
    setWindowTitle("Text Manipulator");
}


void MainWindow::on_actionFrom_Url_triggered()
{

    QInputDialog * QI = new QInputDialog;
    QString url = QI->getText(this,"From Url...","Webtext:",QLineEdit::Normal,"");
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));

    QEventLoop wait;
    connect(response, SIGNAL(finished()), &wait, SLOT(quit()));
    wait.exec();

    QString content = response->readAll();
    t_box->setPlainText(content);
    std::cout << content.toStdString() << std::endl;

    manager.deleteLater();

}

void MainWindow::on_actionReplace_triggered()
{

    QDialog replace_select(this);
    QFormLayout r_layout(&replace_select);

    QLineEdit * find = new QLineEdit;
    r_layout.addRow(new QLabel("Find:"),find);

    QLineEdit * replace = new QLineEdit;
    r_layout.addRow(new QLabel("Replace:"),replace);

    QPushButton * accept= new QPushButton("Accept");
    r_layout.addRow(accept);

    QObject::connect(accept,SIGNAL(clicked()),&replace_select,SLOT(accept()));

    replace_select.exec();

    if (word_Search(find->text())){
        int pos = t_box->textCursor().position();
        t_box->clearFocus();
        t_box->insertPlainText(replace->text());
        t_box->textCursor().setPosition(pos);
        t_box->textCursor().setPosition(pos+4,QTextCursor::KeepAnchor);
    }else{
        return;
    }

    delete find;
    delete replace;
    delete accept;

}

