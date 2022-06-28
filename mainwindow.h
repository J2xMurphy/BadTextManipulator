#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QFontDatabase>
#include <QInputDialog>
#include <QTextBrowser>
#include <QFont>
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QFontComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

void list_children(QWidget*);

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString opened_file;
    QString search_term;
    QStatusBar * s_bar;
    QTextBrowser * t_box;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupStatusBar(QStatusBar*);

    void setupShortcuts();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_textBox_textChanged();

    void on_actionFont_List_triggered();

    void on_actionSelector_triggered();

    void on_actionFind_triggered();

    void on_actionNew_triggered();

    void on_actionFrom_Url_triggered();

    void on_actionReplace_triggered();

    void search_next();

    void search_prev();
    //TODO Ideas
    /* Add a statusbar button for next and previous find result
     * Setup the rest of the keyboard shortcuts
     * Add a help file
     * A tag system is required to make a automatic vaitalbe replacement system
     * Add a variable system that replaces keywords
     * Add a directory puller, scans directory for compatible files  // LATER
     * Add a command based filetype that takes actions based on file
     * Add a variable based filetype that matches variables to replaced from a list
     * Add a export feature, that applies variable replacement to a saved file.
     * Add a find->replace to variable feature
     * */

private:
    Ui::MainWindow *ui;

    void update_word_count();

    QString get_Selected_Text();

    bool word_Search(QString,bool = 1);

    void push_message_box(QString);

    void set_search_term(QString);

};
#endif // MAINWINDOW_H
