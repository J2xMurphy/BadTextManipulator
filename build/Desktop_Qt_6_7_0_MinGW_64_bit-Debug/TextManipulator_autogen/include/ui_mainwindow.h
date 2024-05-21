/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionFont_List;
    QAction *actionSelector;
    QAction *actionFind;
    QAction *actionNew;
    QAction *actionFrom_Url;
    QAction *actionReplace;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionView_Help;
    QAction *actionAbout;
    QAction *actionAdd_Variable;
    QAction *actionVariables;
    QAction *actionExport;
    QAction *actionDefine_Selction;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextBrowser *textBox;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTest;
    QMenu *menuTest_2;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(909, 581);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName("actionSave_As");
        actionFont_List = new QAction(MainWindow);
        actionFont_List->setObjectName("actionFont_List");
        actionSelector = new QAction(MainWindow);
        actionSelector->setObjectName("actionSelector");
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName("actionFind");
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionFrom_Url = new QAction(MainWindow);
        actionFrom_Url->setObjectName("actionFrom_Url");
        actionReplace = new QAction(MainWindow);
        actionReplace->setObjectName("actionReplace");
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName("actionRedo");
        actionView_Help = new QAction(MainWindow);
        actionView_Help->setObjectName("actionView_Help");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionAdd_Variable = new QAction(MainWindow);
        actionAdd_Variable->setObjectName("actionAdd_Variable");
        actionVariables = new QAction(MainWindow);
        actionVariables->setObjectName("actionVariables");
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName("actionExport");
        actionDefine_Selction = new QAction(MainWindow);
        actionDefine_Selction->setObjectName("actionDefine_Selction");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setAutoFillBackground(false);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        textBox = new QTextBrowser(centralwidget);
        textBox->setObjectName("textBox");
        textBox->setMouseTracking(true);
        textBox->setAcceptDrops(false);
        textBox->setUndoRedoEnabled(true);
        textBox->setReadOnly(false);
        textBox->setOverwriteMode(false);
        textBox->setOpenLinks(false);

        gridLayout->addWidget(textBox, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 909, 21));
        menubar->setDefaultUp(false);
        menubar->setNativeMenuBar(true);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuTest = new QMenu(menubar);
        menuTest->setObjectName("menuTest");
        menuTest_2 = new QMenu(menubar);
        menuTest_2->setObjectName("menuTest_2");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setAcceptDrops(true);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuTest->menuAction());
        menubar->addAction(menuTest_2->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionFrom_Url);
        menuFile->addAction(actionExport);
        menuTest->addAction(actionFont_List);
        menuTest_2->addAction(actionSelector);
        menuTest_2->addAction(actionVariables);
        menuTest_2->addAction(actionDefine_Selction);
        menuEdit->addAction(actionFind);
        menuEdit->addAction(actionReplace);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addAction(actionAdd_Variable);
        menuHelp->addAction(actionView_Help);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open...", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save...", nullptr));
        actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save As...", nullptr));
        actionFont_List->setText(QCoreApplication::translate("MainWindow", "Font List", nullptr));
        actionSelector->setText(QCoreApplication::translate("MainWindow", "Selector", nullptr));
        actionFind->setText(QCoreApplication::translate("MainWindow", "Find...", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New...", nullptr));
        actionFrom_Url->setText(QCoreApplication::translate("MainWindow", "From Url...", nullptr));
        actionReplace->setText(QCoreApplication::translate("MainWindow", "Replace...", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        actionView_Help->setText(QCoreApplication::translate("MainWindow", "View Help", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About...", nullptr));
        actionAdd_Variable->setText(QCoreApplication::translate("MainWindow", "Add Variable...", nullptr));
        actionVariables->setText(QCoreApplication::translate("MainWindow", "Variables", nullptr));
        actionExport->setText(QCoreApplication::translate("MainWindow", "Export...", nullptr));
        actionDefine_Selction->setText(QCoreApplication::translate("MainWindow", "Define Selction", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuTest->setTitle(QCoreApplication::translate("MainWindow", "Format", nullptr));
        menuTest_2->setTitle(QCoreApplication::translate("MainWindow", "Test", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
