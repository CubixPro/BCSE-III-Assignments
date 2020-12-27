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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "frame_widget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    frame_widget *frame;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLabel *coord;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *spinBox;
    QPushButton *pushButton_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLabel *press;
    QComboBox *comboBox;
    QPushButton *pushButton_6;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QSpinBox *radius;
    QSlider *rSlider;
    QLabel *R;
    QSlider *gSlider;
    QSlider *bSlider;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *color;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_9;
    QSpinBox *major;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QSpinBox *minor;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_10;
    QLabel *center_2;
    QPushButton *pushButton;
    QPushButton *pushButton_7;
    QLabel *label_2;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *center;
    QPushButton *pushButton_2;
    QLabel *label_11;
    QLabel *time;
    QComboBox *comboBox_2;
    QLabel *label_12;
    QLabel *label_13;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_14;
    QSpinBox *vertices;
    QPushButton *pushButton_8;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *polygonStart;
    QLabel *polygonEnd;
    QPushButton *pushButton_9;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *horizontalLayout_11;
    QLabel *seed;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QComboBox *comboBox_3;
    QMenuBar *menubar;
    QMenu *menuCreate_New;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(217, 243, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new frame_widget(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(39, 29, 500, 500));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(570, 330, 201, 21));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        coord = new QLabel(layoutWidget);
        coord->setObjectName(QString::fromUtf8("coord"));

        horizontalLayout_2->addWidget(coord);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(570, 350, 201, 74));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton = new QRadioButton(layoutWidget1);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setAutoExclusive(false);

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget1);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setAutoExclusive(false);

        verticalLayout->addWidget(radioButton_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        spinBox = new QSpinBox(layoutWidget1);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(150);
        spinBox->setValue(10);

        horizontalLayout_3->addWidget(spinBox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(200, 530, 171, 21));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(570, 310, 201, 21));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        press = new QLabel(horizontalLayoutWidget);
        press->setObjectName(QString::fromUtf8("press"));

        horizontalLayout_6->addWidget(press);

        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(570, 30, 201, 21));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setLayoutDirection(Qt::LeftToRight);
        comboBox->setAutoFillBackground(false);
        comboBox->setStyleSheet(QString::fromUtf8("border: 0.5px solid rgb(100, 100, 100)\n"
""));
        comboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(570, 120, 201, 21));
        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(610, 90, 121, 28));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_4);

        radius = new QSpinBox(horizontalLayoutWidget_2);
        radius->setObjectName(QString::fromUtf8("radius"));
        radius->setValue(15);

        horizontalLayout_8->addWidget(radius);

        rSlider = new QSlider(centralwidget);
        rSlider->setObjectName(QString::fromUtf8("rSlider"));
        rSlider->setGeometry(QRect(620, 460, 121, 21));
        rSlider->setMaximum(255);
        rSlider->setPageStep(15);
        rSlider->setValue(255);
        rSlider->setOrientation(Qt::Horizontal);
        R = new QLabel(centralwidget);
        R->setObjectName(QString::fromUtf8("R"));
        R->setGeometry(QRect(600, 430, 51, 21));
        R->setAlignment(Qt::AlignCenter);
        gSlider = new QSlider(centralwidget);
        gSlider->setObjectName(QString::fromUtf8("gSlider"));
        gSlider->setGeometry(QRect(620, 490, 121, 21));
        gSlider->setMaximum(255);
        gSlider->setPageStep(15);
        gSlider->setOrientation(Qt::Horizontal);
        bSlider = new QSlider(centralwidget);
        bSlider->setObjectName(QString::fromUtf8("bSlider"));
        bSlider->setGeometry(QRect(620, 520, 121, 21));
        bSlider->setMaximum(255);
        bSlider->setPageStep(15);
        bSlider->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(559, 460, 41, 20));
        label_3->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(559, 490, 41, 20));
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(559, 520, 41, 20));
        label_8->setAlignment(Qt::AlignCenter);
        color = new QLabel(centralwidget);
        color->setObjectName(QString::fromUtf8("color"));
        color->setGeometry(QRect(660, 430, 71, 21));
        horizontalLayoutWidget_4 = new QWidget(centralwidget);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(560, 220, 109, 28));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(horizontalLayoutWidget_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_9);

        major = new QSpinBox(horizontalLayoutWidget_4);
        major->setObjectName(QString::fromUtf8("major"));
        major->setValue(18);

        horizontalLayout->addWidget(major);

        horizontalLayoutWidget_5 = new QWidget(centralwidget);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(670, 220, 107, 28));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(horizontalLayoutWidget_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_10);

        minor = new QSpinBox(horizontalLayoutWidget_5);
        minor->setObjectName(QString::fromUtf8("minor"));
        minor->setValue(12);

        horizontalLayout_7->addWidget(minor);

        horizontalLayoutWidget_6 = new QWidget(centralwidget);
        horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(570, 250, 201, 28));
        horizontalLayout_10 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        center_2 = new QLabel(horizontalLayoutWidget_6);
        center_2->setObjectName(QString::fromUtf8("center_2"));
        center_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(center_2);

        pushButton = new QPushButton(horizontalLayoutWidget_6);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_10->addWidget(pushButton);

        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(570, 280, 201, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(590, 0, 131, 16));
        label_2->setStyleSheet(QString::fromUtf8("text-decoration: underline;\n"
"font-size: 13px;\n"
"color: rgb(122, 13, 5);"));
        label_2->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget_3 = new QWidget(centralwidget);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(570, 60, 201, 28));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        center = new QLabel(horizontalLayoutWidget_3);
        center->setObjectName(QString::fromUtf8("center"));
        center->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(center);

        pushButton_2 = new QPushButton(horizontalLayoutWidget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(590, 160, 141, 20));
        label_11->setStyleSheet(QString::fromUtf8("text-decoration: underline;\n"
"font-size: 13px;\n"
"color: rgb(122, 13, 5);"));
        label_11->setAlignment(Qt::AlignCenter);
        time = new QLabel(centralwidget);
        time->setObjectName(QString::fromUtf8("time"));
        time->setGeometry(QRect(230, 0, 111, 21));
        time->setAlignment(Qt::AlignCenter);
        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(570, 190, 201, 21));
        comboBox_2->setStyleSheet(QString::fromUtf8("border: 0.5px solid rgb(100, 100, 100)\n"
""));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(840, 10, 91, 20));
        label_12->setStyleSheet(QString::fromUtf8("text-decoration: underline;\n"
"font-size: 13px;\n"
"color: rgb(122, 13, 5);"));
        label_12->setAlignment(Qt::AlignCenter);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(835, 170, 121, 20));
        label_13->setStyleSheet(QString::fromUtf8("text-decoration: underline;\n"
"font-size: 13px;\n"
"color: rgb(122, 13, 5);"));
        label_13->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget_7 = new QWidget(centralwidget);
        horizontalLayoutWidget_7->setObjectName(QString::fromUtf8("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(829, 200, 131, 31));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(horizontalLayoutWidget_7);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_14);

        vertices = new QSpinBox(horizontalLayoutWidget_7);
        vertices->setObjectName(QString::fromUtf8("vertices"));
        vertices->setMinimum(3);
        vertices->setMaximum(20);
        vertices->setValue(3);

        horizontalLayout_5->addWidget(vertices);

        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(810, 280, 171, 21));
        horizontalLayoutWidget_8 = new QWidget(centralwidget);
        horizontalLayoutWidget_8->setObjectName(QString::fromUtf8("horizontalLayoutWidget_8"));
        horizontalLayoutWidget_8->setGeometry(QRect(810, 240, 171, 31));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_8);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        polygonStart = new QLabel(horizontalLayoutWidget_8);
        polygonStart->setObjectName(QString::fromUtf8("polygonStart"));
        polygonStart->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(polygonStart);

        polygonEnd = new QLabel(horizontalLayoutWidget_8);
        polygonEnd->setObjectName(QString::fromUtf8("polygonEnd"));
        polygonEnd->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(polygonEnd);

        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(810, 310, 171, 21));
        horizontalLayoutWidget_9 = new QWidget(centralwidget);
        horizontalLayoutWidget_9->setObjectName(QString::fromUtf8("horizontalLayoutWidget_9"));
        horizontalLayoutWidget_9->setGeometry(QRect(810, 370, 171, 31));
        horizontalLayout_11 = new QHBoxLayout(horizontalLayoutWidget_9);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        seed = new QLabel(horizontalLayoutWidget_9);
        seed->setObjectName(QString::fromUtf8("seed"));
        seed->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(seed);

        pushButton_3 = new QPushButton(horizontalLayoutWidget_9);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_11->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(810, 410, 171, 21));
        comboBox_3 = new QComboBox(centralwidget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(810, 340, 171, 21));
        comboBox_3->setStyleSheet(QString::fromUtf8("border: 0.5px solid rgb(100, 100, 100)\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuCreate_New = new QMenu(menubar);
        menuCreate_New->setObjectName(QString::fromUtf8("menuCreate_New"));
        menuCreate_New->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuCreate_New->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Mouse Position", nullptr));
        coord->setText(QString());
        radioButton->setText(QCoreApplication::translate("MainWindow", "Show Axis", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Show Grid", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Pixel Size", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Clear Grid", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Last Mouse Pressed", nullptr));
        press->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "   Parametric", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "   Polar Coordinates", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "   Mid Point", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "   Bresenham's Midpoint", nullptr));

        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Draw Circle", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Radius", nullptr));
        R->setText(QCoreApplication::translate("MainWindow", "Color ->", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Red", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Green", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Blue", nullptr));
        color->setText(QCoreApplication::translate("MainWindow", "rbg(255,0,0)", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Major-R", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Minor-R", nullptr));
        center_2->setText(QCoreApplication::translate("MainWindow", "Ellipse Center", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Set Center", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Draw Ellipse", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Circle Drawing", nullptr));
        center->setText(QCoreApplication::translate("MainWindow", "Circle Center", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Set Center", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Ellipse Drawing", nullptr));
        time->setText(QCoreApplication::translate("MainWindow", "Time taken : ", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "   Polar Coordinate", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "   Midpoint", nullptr));

        label_12->setText(QCoreApplication::translate("MainWindow", "Line Drawing", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Polygon Drawing", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Vertices", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Set Vertices", nullptr));
        polygonStart->setText(QCoreApplication::translate("MainWindow", "Start Point", nullptr));
        polygonEnd->setText(QCoreApplication::translate("MainWindow", "End Point", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Draw Polygon", nullptr));
        seed->setText(QCoreApplication::translate("MainWindow", "Seed", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Set Seed", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Fill Polygon", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "   Boundary Fill", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "   Flood Fill ", nullptr));

        menuCreate_New->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
