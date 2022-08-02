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
#include <QListWidget>
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
#include <QHash>
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
    QString * export_text;
    bool search_direction;// Whether find was used for forward or reverse search
    bool search_operation;// Whether find was used for find or replace operation
    QStatusBar * s_bar;// The status bar at the bottom of the screen
    QTextBrowser * t_box;// The wall of text being edited
    int argc;//           Count of args passed into QApplication
    char ** argv;//       Args passed into QApplication
    QHash<QString,QString> varlist;// A hash map of varname and value
    QListWidget * var_box; // Saves pointer of variables in var list
    QTextEdit * value_box;// Saves pointer of values in var list

public:
    MainWindow(int,char*[],QWidget* parent = nullptr);
    ~MainWindow();

    void setupStatusBar(QStatusBar*);

    void setupShortcuts();

    void addvar(QString,QString);

    void var_edited_text();

    void args_handler();

    void open_file(QString);

    QString downloader(QString);
signals:
    void varlist_edited();

    void export_finished(int);

private slots:
    //TODO Ideas
    /* Setup the rest of the keyboard shortcuts
     * Add a directory puller, scans directory for compatible files  // LATER
     * Add a command based filetype that takes actions based on file
     * Add a variable based filetype that matches variables to replaced from a list
     * Add a export feature, that applies variable replacement to a saved file.
     * Add a tag to pull text from internet for export
     * Add a dictionary feature to search for a word's meaning
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

    void on_actionAdd_Variable_triggered();//SHOWS NEW VARAIBLE DIALOGUE

    void on_actionVariables_triggered();//TELLS USER ALL VARIABLE KEY-PAIRS

    void on_actionExport_triggered();//SAVE AS WITH PAIRS OVER VARIABLES

    void refresh_vblist();//REPOPULATE THE LIST OF VARIABLES

    void populate_valuebox(QListWidgetItem*);//SETS THE VAR VALUE BOX

    void reset_key();//CHANGES THE SELECTED KEY'S VALUE TO THE VALUE BOX

    void remove_key();//REMOVES THE SELECTED KEY FROM THE LIST

    void export_save();//SAVES THE OUTPUT OF EXPORT

    void on_actionDefine_Selction_triggered();//PULLS DEFINITION OF SELECTED WORD

private:
    Ui::MainWindow *ui;

    void update_word_count();// UPDATES STATUS BAR'S WORD COUNT

    QString get_Selected_Text();// FUNCTION THAT RETURNS HIGHLIGHTED TEXT

    bool word_Search(QString,bool = 1);// SEARCCHES FOR WORD IN DIRECTION LEFT(0) OR RIGHT(1)

    void push_message_box(QString,QString title = "Title");// DISPLAYS MESSAGE BOX SAYING ARG1

    void set_search_term(QString);// SAVES THE SEARCH TERM WHEN FIND IS USED

    bool do_replace(QString, QString,bool=1);// SEARCHES FOR ARG1 AND REPLACES WITH ARG2

};
#endif // MAINWINDOW_H
