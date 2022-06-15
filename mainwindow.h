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



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void update_word_count();

    void on_textBox_textChanged();

    void on_actionFont_List_triggered();

    void on_actionSelector_triggered();

    QString get_Selected_Text();

    //TODO Ideas
    /* Add a Find text feature
     * Add a replace text feature
     * Add a get web text feature
     * Add a new document feature
     * Add a directory puller, scans directory for compatible files
     *
     * */

    void on_actionFind_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
