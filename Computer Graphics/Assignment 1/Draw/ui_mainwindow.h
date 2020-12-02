/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart_New_Grid;
    QAction *actionCreate;
    QAction *actionShow_Axes;
    QAction *actionSmall;
    QAction *actionMedium;
    QAction *actionLarge;
    QAction *actionDefault;
    QAction *actionLarge_2;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuStart;
    QMenu *menuChange_Grid_Size;
    QMenu *menuChange_Grid_Size_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionStart_New_Grid = new QAction(MainWindow);
        actionStart_New_Grid->setObjectName(QString::fromUtf8("actionStart_New_Grid"));
        actionCreate = new QAction(MainWindow);
        actionCreate->setObjectName(QString::fromUtf8("actionCreate"));
        actionShow_Axes = new QAction(MainWindow);
        actionShow_Axes->setObjectName(QString::fromUtf8("actionShow_Axes"));
        actionSmall = new QAction(MainWindow);
        actionSmall->setObjectName(QString::fromUtf8("actionSmall"));
        actionMedium = new QAction(MainWindow);
        actionMedium->setObjectName(QString::fromUtf8("actionMedium"));
        actionLarge = new QAction(MainWindow);
        actionLarge->setObjectName(QString::fromUtf8("actionLarge"));
        actionDefault = new QAction(MainWindow);
        actionDefault->setObjectName(QString::fromUtf8("actionDefault"));
        actionLarge_2 = new QAction(MainWindow);
        actionLarge_2->setObjectName(QString::fromUtf8("actionLarge_2"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuStart = new QMenu(menubar);
        menuStart->setObjectName(QString::fromUtf8("menuStart"));
        menuChange_Grid_Size = new QMenu(menuStart);
        menuChange_Grid_Size->setObjectName(QString::fromUtf8("menuChange_Grid_Size"));
        menuChange_Grid_Size_2 = new QMenu(menuStart);
        menuChange_Grid_Size_2->setObjectName(QString::fromUtf8("menuChange_Grid_Size_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuStart->menuAction());
        menuStart->addAction(actionCreate);
        menuStart->addSeparator();
        menuStart->addAction(menuChange_Grid_Size->menuAction());
        menuStart->addAction(actionShow_Axes);
        menuStart->addAction(menuChange_Grid_Size_2->menuAction());
        menuChange_Grid_Size->addAction(actionSmall);
        menuChange_Grid_Size->addAction(actionMedium);
        menuChange_Grid_Size->addAction(actionLarge);
        menuChange_Grid_Size_2->addAction(actionDefault);
        menuChange_Grid_Size_2->addAction(actionLarge_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionStart_New_Grid->setText(QCoreApplication::translate("MainWindow", "Start New Grid", nullptr));
        actionCreate->setText(QCoreApplication::translate("MainWindow", "Create New", nullptr));
        actionShow_Axes->setText(QCoreApplication::translate("MainWindow", "Show Axes", nullptr));
        actionSmall->setText(QCoreApplication::translate("MainWindow", "Small", nullptr));
        actionMedium->setText(QCoreApplication::translate("MainWindow", "Medium", nullptr));
        actionLarge->setText(QCoreApplication::translate("MainWindow", "Large", nullptr));
        actionDefault->setText(QCoreApplication::translate("MainWindow", "Default", nullptr));
        actionLarge_2->setText(QCoreApplication::translate("MainWindow", "Large", nullptr));
        menuStart->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuChange_Grid_Size->setTitle(QCoreApplication::translate("MainWindow", "Change Pixel Size", nullptr));
        menuChange_Grid_Size_2->setTitle(QCoreApplication::translate("MainWindow", "Change Grid Size", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
