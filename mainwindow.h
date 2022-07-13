#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <STRINGS.h>

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
#define  prev_ false
#define  next_ true
#define  find_ false
#define  repl_ true

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

void list_children(QWidget*);

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString opened_file;// Location of file being edited
    QString search_term;// Last used search term in find
    QString replace_term;// Last used word in replace
    bool search_direction;// Whether find was used for forward or reverse search
    bool search_operation;// Whether find was used for find or replace operation
    QStatusBar * s_bar;// The status bar at the bottom of the screen
    QTextBrowser * t_box;// The wall of text being edited

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupStatusBar(QStatusBar*);

    void setupShortcuts();

private slots:
    //TODO Ideas
    /* Add a statusbar button for next and previous find result
     * Setup the rest of the keyboard shortcuts
     * A tag system is required to make a automatic vaitalbe replacement system
     * Add a variable system that replaces keywords
     * Add a directory puller, scans directory for compatible files  // LATER
     * Add a command based filetype that takes actions based on file
     * Add a variable based filetype that matches variables to replaced from a list
     * Add a export feature, that applies variable replacement to a saved file.
     * Add a find->replace to variable feature
     * */

    void on_actionOpen_triggered();// OPENS A FILE BROWSER TO SELECT A FILE, THEN OPENS IT

    void on_actionSave_triggered();// QUICKLY SAVES A FILE TO THE OPENED FILE WITHOUT PROMPT

    void on_actionSave_As_triggered();// PROMPTS TO SAVE A FILE UNDER GIVEN NAME

    void on_textBox_textChanged();// IF t_box HAS BEEN EDITED, EXECUTE THIS

    void on_actionFont_List_triggered();// OPENS UP A FONT TYPE AND SIZE PROMPT

    void on_actionSelector_triggered();// TEST FOR FUTURE SELECTED TEXT ACTIONS

    void on_actionFind_triggered();// OPENS UP A FIND WORD PROMPT, FINDS NEXT WORD AFTER CURSOR

    void on_actionNew_triggered();// CREATES A NEW, BLANK DOCUMENT

    void on_actionFrom_Url_triggered();// PULLS DATA FROM A WEBPAGE'S ADDRESS

    void on_actionReplace_triggered();// REPLACES TEXT GIVENS ON THE NEXT INSTANCE

    void search_next();// REDOES THE PREVIOUS FIND/REPLACE OPERATION ON NEXT INSTANCE

    void search_prev();// REDOES THE PREVIOUS FIND/REPLACE OPERATION ON PREVIOUS INSTANCE

    void on_actionUndo_triggered();//UNDO TEXT OPERTAION

    void on_actionRedo_triggered();//REDO TEXT OPERATION

    void on_actionView_Help_triggered();//SHOW HELP DIALOGUE

    void on_actionAbout_triggered();//SHOW ABOUT DIALOGUE

private:
    Ui::MainWindow *ui;

    void update_word_count();// UPDATES STATUS BAR'S WORD COUNT

    QString get_Selected_Text();// FUNCTION THAT RETURNS HIGHLIGHTED TEXT

    bool word_Search(QString,bool = 1);// SEARCCHES FOR WORD IN DIRECTION LEFT(0) OR RIGHT(1)

    void push_message_box(QString,QString title = "Title");// DISPLAYS MESSAGE BOX SAYING ARG1

    void set_search_term(QString);// SAVES THE SEARCH TERM WHEN FIND IS USED

    void do_replace(QString, QString,bool=1);// SEARCHES FOR ARG1 AND REPLACES WITH ARG2
};
#endif // MAINWINDOW_H
