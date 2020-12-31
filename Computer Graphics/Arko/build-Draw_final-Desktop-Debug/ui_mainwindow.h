/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
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
    QLabel *label_12;
    QLabel *fillcolor;
    QSlider *rFill;
    QSlider *gFill;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QSlider *bFill;
    QWidget *horizontalLayoutWidget_10;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_15;
    QSpinBox *tranx;
    QWidget *horizontalLayoutWidget_11;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_19;
    QSpinBox *trany;
    QPushButton *pushButton_translate;
    QLabel *label_20;
    QWidget *horizontalLayoutWidget_12;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_21;
    QDoubleSpinBox *scalex;
    QWidget *horizontalLayoutWidget_13;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_22;
    QDoubleSpinBox *scaley;
    QPushButton *pushButton_scale;
    QWidget *horizontalLayoutWidget_14;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_23;
    QSpinBox *rotate;
    QPushButton *pushButton_rotate;
    QPushButton *pushButton_11;
    QPushButton *pushButton_10;
    QPushButton *pushButton_line;
    QPushButton *pushButton_reflect;
    QLabel *point1;
    QLabel *point2;
    QLabel *label_26;
    QComboBox *comboBox_4;
    QWidget *horizontalLayoutWidget_15;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_24;
    QDoubleSpinBox *shearx;
    QWidget *horizontalLayoutWidget_16;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_25;
    QDoubleSpinBox *sheary;
    QPushButton *pushButton_shear;
    QPushButton *pushButton_rect;
    QPushButton *pushButton_clipL;
    QPushButton *pushButton_clipP;
    QMenuBar *menubar;
    QMenu *menuCreate_New;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1210, 630);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(217, 243, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new frame_widget(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(16, 26, 530, 530));
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
        pushButton_5->setGeometry(QRect(180, 560, 171, 21));
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
        label_2->setGeometry(QRect(600, 0, 131, 16));
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
        label_11->setGeometry(QRect(600, 160, 141, 20));
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
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(830, 0, 121, 20));
        label_13->setStyleSheet(QString::fromUtf8("text-decoration: underline;\n"
"font-size: 13px;\n"
"color: rgb(122, 13, 5);"));
        label_13->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget_7 = new QWidget(centralwidget);
        horizontalLayoutWidget_7->setObjectName(QString::fromUtf8("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(820, 30, 131, 31));
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
        pushButton_8->setGeometry(QRect(800, 110, 171, 21));
        horizontalLayoutWidget_8 = new QWidget(centralwidget);
        horizontalLayoutWidget_8->setObjectName(QString::fromUtf8("horizontalLayoutWidget_8"));
        horizontalLayoutWidget_8->setGeometry(QRect(800, 70, 171, 31));
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
        pushButton_9->setGeometry(QRect(800, 140, 171, 21));
        horizontalLayoutWidget_9 = new QWidget(centralwidget);
        horizontalLayoutWidget_9->setObjectName(QString::fromUtf8("horizontalLayoutWidget_9"));
        horizontalLayoutWidget_9->setGeometry(QRect(800, 200, 171, 31));
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
        pushButton_4->setGeometry(QRect(800, 240, 171, 21));
        comboBox_3 = new QComboBox(centralwidget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(800, 170, 171, 21));
        comboBox_3->setStyleSheet(QString::fromUtf8("border: 0.5px solid rgb(100, 100, 100)\n"
""));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(810, 280, 61, 20));
        label_12->setAlignment(Qt::AlignCenter);
        fillcolor = new QLabel(centralwidget);
        fillcolor->setObjectName(QString::fromUtf8("fillcolor"));
        fillcolor->setGeometry(QRect(870, 280, 101, 21));
        fillcolor->setAlignment(Qt::AlignCenter);
        rFill = new QSlider(centralwidget);
        rFill->setObjectName(QString::fromUtf8("rFill"));
        rFill->setGeometry(QRect(860, 310, 111, 21));
        rFill->setMaximum(255);
        rFill->setPageStep(15);
        rFill->setValue(255);
        rFill->setOrientation(Qt::Horizontal);
        gFill = new QSlider(centralwidget);
        gFill->setObjectName(QString::fromUtf8("gFill"));
        gFill->setGeometry(QRect(860, 340, 111, 21));
        gFill->setMaximum(255);
        gFill->setPageStep(15);
        gFill->setValue(255);
        gFill->setOrientation(Qt::Horizontal);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(800, 310, 41, 20));
        label_16->setAlignment(Qt::AlignCenter);
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(800, 340, 51, 20));
        label_17->setAlignment(Qt::AlignCenter);
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(800, 370, 51, 21));
        label_18->setAlignment(Qt::AlignCenter);
        bFill = new QSlider(centralwidget);
        bFill->setObjectName(QString::fromUtf8("bFill"));
        bFill->setGeometry(QRect(860, 370, 111, 21));
        bFill->setMaximum(255);
        bFill->setPageStep(15);
        bFill->setValue(255);
        bFill->setOrientation(Qt::Horizontal);
        horizontalLayoutWidget_10 = new QWidget(centralwidget);
        horizontalLayoutWidget_10->setObjectName(QString::fromUtf8("horizontalLayoutWidget_10"));
        horizontalLayoutWidget_10->setGeometry(QRect(990, 30, 101, 31));
        horizontalLayout_12 = new QHBoxLayout(horizontalLayoutWidget_10);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(horizontalLayoutWidget_10);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(label_15);

        tranx = new QSpinBox(horizontalLayoutWidget_10);
        tranx->setObjectName(QString::fromUtf8("tranx"));
        tranx->setMinimum(-50);
        tranx->setMaximum(50);

        horizontalLayout_12->addWidget(tranx);

        horizontalLayoutWidget_11 = new QWidget(centralwidget);
        horizontalLayoutWidget_11->setObjectName(QString::fromUtf8("horizontalLayoutWidget_11"));
        horizontalLayoutWidget_11->setGeometry(QRect(1090, 30, 101, 31));
        horizontalLayout_13 = new QHBoxLayout(horizontalLayoutWidget_11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(horizontalLayoutWidget_11);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(label_19);

        trany = new QSpinBox(horizontalLayoutWidget_11);
        trany->setObjectName(QString::fromUtf8("trany"));
        trany->setMinimum(-50);
        trany->setMaximum(50);

        horizontalLayout_13->addWidget(trany);

        pushButton_translate = new QPushButton(centralwidget);
        pushButton_translate->setObjectName(QString::fromUtf8("pushButton_translate"));
        pushButton_translate->setGeometry(QRect(1000, 70, 181, 21));
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(1035, 3, 111, 21));
        label_20->setStyleSheet(QString::fromUtf8("text-decoration: underline;\n"
"font-size: 13px;\n"
"color: rgb(122, 13, 5);"));
        label_20->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget_12 = new QWidget(centralwidget);
        horizontalLayoutWidget_12->setObjectName(QString::fromUtf8("horizontalLayoutWidget_12"));
        horizontalLayoutWidget_12->setGeometry(QRect(990, 110, 101, 31));
        horizontalLayout_14 = new QHBoxLayout(horizontalLayoutWidget_12);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(horizontalLayoutWidget_12);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_21);

        scalex = new QDoubleSpinBox(horizontalLayoutWidget_12);
        scalex->setObjectName(QString::fromUtf8("scalex"));
        scalex->setDecimals(1);
        scalex->setMaximum(10.000000000000000);
        scalex->setSingleStep(0.300000000000000);
        scalex->setValue(1.000000000000000);

        horizontalLayout_14->addWidget(scalex);

        horizontalLayoutWidget_13 = new QWidget(centralwidget);
        horizontalLayoutWidget_13->setObjectName(QString::fromUtf8("horizontalLayoutWidget_13"));
        horizontalLayoutWidget_13->setGeometry(QRect(1090, 110, 101, 31));
        horizontalLayout_15 = new QHBoxLayout(horizontalLayoutWidget_13);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        label_22 = new QLabel(horizontalLayoutWidget_13);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(label_22);

        scaley = new QDoubleSpinBox(horizontalLayoutWidget_13);
        scaley->setObjectName(QString::fromUtf8("scaley"));
        scaley->setDecimals(1);
        scaley->setMaximum(10.000000000000000);
        scaley->setSingleStep(0.300000000000000);
        scaley->setValue(1.000000000000000);

        horizontalLayout_15->addWidget(scaley);

        pushButton_scale = new QPushButton(centralwidget);
        pushButton_scale->setObjectName(QString::fromUtf8("pushButton_scale"));
        pushButton_scale->setGeometry(QRect(1000, 150, 181, 20));
        horizontalLayoutWidget_14 = new QWidget(centralwidget);
        horizontalLayoutWidget_14->setObjectName(QString::fromUtf8("horizontalLayoutWidget_14"));
        horizontalLayoutWidget_14->setGeometry(QRect(1010, 180, 161, 31));
        horizontalLayout_16 = new QHBoxLayout(horizontalLayoutWidget_14);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(horizontalLayoutWidget_14);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(label_23);

        rotate = new QSpinBox(horizontalLayoutWidget_14);
        rotate->setObjectName(QString::fromUtf8("rotate"));
        rotate->setMinimum(-180);
        rotate->setMaximum(180);
        rotate->setSingleStep(5);

        horizontalLayout_16->addWidget(rotate);

        pushButton_rotate = new QPushButton(centralwidget);
        pushButton_rotate->setObjectName(QString::fromUtf8("pushButton_rotate"));
        pushButton_rotate->setGeometry(QRect(1000, 220, 181, 21));
        pushButton_11 = new QPushButton(centralwidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(890, 470, 75, 23));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(890, 440, 75, 23));
        pushButton_line = new QPushButton(centralwidget);
        pushButton_line->setObjectName(QString::fromUtf8("pushButton_line"));
        pushButton_line->setGeometry(QRect(800, 530, 171, 21));
        pushButton_reflect = new QPushButton(centralwidget);
        pushButton_reflect->setObjectName(QString::fromUtf8("pushButton_reflect"));
        pushButton_reflect->setGeometry(QRect(1000, 320, 181, 21));
        point1 = new QLabel(centralwidget);
        point1->setObjectName(QString::fromUtf8("point1"));
        point1->setGeometry(QRect(800, 440, 81, 21));
        point1->setAlignment(Qt::AlignCenter);
        point2 = new QLabel(centralwidget);
        point2->setObjectName(QString::fromUtf8("point2"));
        point2->setGeometry(QRect(800, 470, 81, 21));
        point2->setAlignment(Qt::AlignCenter);
        label_26 = new QLabel(centralwidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(800, 410, 171, 21));
        label_26->setStyleSheet(QString::fromUtf8("text-decoration: underline;\n"
"font-size: 13px;\n"
"color: rgb(122, 13, 5);\n"
""));
        label_26->setAlignment(Qt::AlignCenter);
        comboBox_4 = new QComboBox(centralwidget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(800, 500, 171, 21));
        comboBox_4->setStyleSheet(QString::fromUtf8("border: 0.5px solid rgb(100, 100, 100)\n"
""));
        horizontalLayoutWidget_15 = new QWidget(centralwidget);
        horizontalLayoutWidget_15->setObjectName(QString::fromUtf8("horizontalLayoutWidget_15"));
        horizontalLayoutWidget_15->setGeometry(QRect(990, 250, 101, 31));
        horizontalLayout_17 = new QHBoxLayout(horizontalLayoutWidget_15);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(0, 0, 0, 0);
        label_24 = new QLabel(horizontalLayoutWidget_15);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(label_24);

        shearx = new QDoubleSpinBox(horizontalLayoutWidget_15);
        shearx->setObjectName(QString::fromUtf8("shearx"));
        shearx->setDecimals(1);
        shearx->setSingleStep(0.500000000000000);

        horizontalLayout_17->addWidget(shearx);

        horizontalLayoutWidget_16 = new QWidget(centralwidget);
        horizontalLayoutWidget_16->setObjectName(QString::fromUtf8("horizontalLayoutWidget_16"));
        horizontalLayoutWidget_16->setGeometry(QRect(1090, 250, 101, 31));
        horizontalLayout_18 = new QHBoxLayout(horizontalLayoutWidget_16);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        label_25 = new QLabel(horizontalLayoutWidget_16);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setAlignment(Qt::AlignCenter);

        horizontalLayout_18->addWidget(label_25);

        sheary = new QDoubleSpinBox(horizontalLayoutWidget_16);
        sheary->setObjectName(QString::fromUtf8("sheary"));
        sheary->setDecimals(1);
        sheary->setSingleStep(0.500000000000000);

        horizontalLayout_18->addWidget(sheary);

        pushButton_shear = new QPushButton(centralwidget);
        pushButton_shear->setObjectName(QString::fromUtf8("pushButton_shear"));
        pushButton_shear->setGeometry(QRect(1000, 290, 181, 20));
        pushButton_rect = new QPushButton(centralwidget);
        pushButton_rect->setObjectName(QString::fromUtf8("pushButton_rect"));
        pushButton_rect->setGeometry(QRect(800, 560, 171, 21));
        pushButton_clipL = new QPushButton(centralwidget);
        pushButton_clipL->setObjectName(QString::fromUtf8("pushButton_clipL"));
        pushButton_clipL->setGeometry(QRect(1000, 390, 181, 21));
        pushButton_clipP = new QPushButton(centralwidget);
        pushButton_clipP->setObjectName(QString::fromUtf8("pushButton_clipP"));
        pushButton_clipP->setGeometry(QRect(1000, 420, 181, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1210, 21));
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
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "   ScanLine Fill", nullptr));

        label_12->setText(QCoreApplication::translate("MainWindow", "Fill Color ->", nullptr));
        fillcolor->setText(QCoreApplication::translate("MainWindow", "rbg(255,255,255)", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Red", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Green", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Blue", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "TransX ", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "TransY ", nullptr));
        pushButton_translate->setText(QCoreApplication::translate("MainWindow", "Translate Polygon", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Transformation", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "ScaleX ", nullptr));
        scalex->setPrefix(QString());
        label_22->setText(QCoreApplication::translate("MainWindow", "ScaleY ", nullptr));
        pushButton_scale->setText(QCoreApplication::translate("MainWindow", "Scale Polygon", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Rotation Angle", nullptr));
        pushButton_rotate->setText(QCoreApplication::translate("MainWindow", "Rotate Polygon", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Set Point 2", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Set Point 1", nullptr));
        pushButton_line->setText(QCoreApplication::translate("MainWindow", "Draw Line", nullptr));
        pushButton_reflect->setText(QCoreApplication::translate("MainWindow", "Reflect Polygon", nullptr));
        point1->setText(QCoreApplication::translate("MainWindow", "Point 1", nullptr));
        point2->setText(QCoreApplication::translate("MainWindow", "Point 2", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Line and Rectangle Drawing", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "   Bresenham", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "   DDA", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("MainWindow", "   Parametric", nullptr));

        label_24->setText(QCoreApplication::translate("MainWindow", "ShearX", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "ShearY", nullptr));
        pushButton_shear->setText(QCoreApplication::translate("MainWindow", "Shear Polygon", nullptr));
        pushButton_rect->setText(QCoreApplication::translate("MainWindow", "Draw Rectangle", nullptr));
        pushButton_clipL->setText(QCoreApplication::translate("MainWindow", "Clip Line", nullptr));
        pushButton_clipP->setText(QCoreApplication::translate("MainWindow", "Clip Polygon", nullptr));
        menuCreate_New->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
