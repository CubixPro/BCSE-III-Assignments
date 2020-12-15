
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QAction>
#include <bits/stdc++.h>

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent)    , ui(new Ui::MainWindow) //, gridFrame(new frame_widget(this))
{
    //setCentralWidget(gridFrame) ;

    //this->viewport()->setMouseTracking(true);
    ui->setupUi(this);
    setWindowTitle("Grid");
    //setAutoFillBackground(true);
    //resize(520, 550);
    setStyleSheet("background-color:pink;");
    connect(ui->frame, &frame_widget::sendCoord, this, &MainWindow::showCoord);

    // all times showns here
    connect(ui->frame, &frame_widget::sendTimeDDA, this, &MainWindow::showDDATime);
    connect(ui->frame, &frame_widget::sendTimeBresh, this, &MainWindow::showBreshTime);
    connect(ui->frame, &frame_widget::sendCircleTime, this, &MainWindow::showCircleTime);
    connect(ui->frame, &frame_widget::sendEllipseTime, this, &MainWindow::showEllipseTime);




    connect(ui->frame, &frame_widget::sendCoordForMousePress, this, &MainWindow::showCoordForMousePressEvent);
    connect(ui->frame, &frame_widget::sendColorLabel, this, &MainWindow::showColorLabel);
    connect(this, &MainWindow::changeTheColour, ui->frame, &frame_widget::changeCurrentColour);


    // all drawings
    connect(this, &MainWindow::drawLinePressedDDA, ui->frame, &frame_widget::drawLineDDA);
    connect(this, &MainWindow::drawLinePressedBresh, ui->frame, &frame_widget::drawLineBresh);
    connect(this, &MainWindow::drawCircle, ui->frame, &frame_widget::drawCircle);
    connect(this, &MainWindow::drawEllipse, ui->frame, &frame_widget::drawEllipse);

  }

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::createActions()
//{

//}








void MainWindow::on_actionCreate_triggered()
{
   //ui->centralwidgetgridFrame->createGrid();
    ui->frame->createGrid();

}

void MainWindow::on_actionChange_Grid_Size_triggered()
{
    ui->frame->changeSize(1);
}

void MainWindow::on_actionSmall_triggered()
{
   ui->frame->changeSize(10);

}

void MainWindow::on_actionMedium_triggered()
{
   ui->frame->changeSize(25);
}

void MainWindow::on_actionLarge_triggered()
{
   ui->frame->changeSize(50);
}

void MainWindow::on_actionShow_Axes_triggered()
{
   ui->frame->showAxes();
}

void MainWindow::on_actionDefault_triggered()
{
  // gridFrame->changeGridSize(500);
}

void MainWindow::on_actionLarge_2_triggered()
{
    //gridFrame->changeGridSize(800);
}

void MainWindow::showCoord(int x, int y)
{
    //std::cout << "hi";
    ui->coord->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
}


void MainWindow::showCoordForMousePressEvent(int x, int y)
{
    //std::cout << "hi I am from hyd mama";
    ui->label_3->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
    ui->label_9->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
    ui->label_24->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
}

void MainWindow::showDDATime(double time)
{
    time = time/1000;
    ui->label_5->setText(QString::number(time) + " ms");
}

void MainWindow::showBreshTime(double time)
{
    time = time/1000;
    ui->label_6->setText(QString::number(time) +" ms");
}


void MainWindow::showCircleTime(double val)
{
    double time = val/1000;
    ui->label_16->setText(QString::number(time) +" ms");
}
void MainWindow::showEllipseTime(double val)
{
    double time = val/1000;
    ui->label_20->setText(QString::number(time) +" ms");
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->label_1->setText(QString("Point 1"));
    ui->label_2->setText(QString("Point 2"));
   ui->frame->changeSize(arg1);
}

void MainWindow::on_button_clicked()
{
    ui->frame->toggleAxes();
}

void MainWindow::on_button2_clicked()
{
   ui->frame->toggleGrid();
}

void MainWindow::on_radioButton_clicked()
{
   ui->frame->toggleAxes();
}


void MainWindow::on_radioButton_2_clicked()
{
   ui->frame->toggleGrid();
}

void MainWindow::on_actionCreate_New_triggered()
{
   ui->frame->createGrid();
}


void MainWindow::on_pushButton_2_clicked()
{
    QPoint p = ui->frame->setPoint1();
   ui->label_1->setText("X : " + QString::number(p.x()) + " Y : "+ QString::number(p.y()));
}

void MainWindow::on_pushButton_clicked()
{
    QPoint p = ui->frame->setPoint2();

 ui->label_2->setText("X : " + QString::number(p.x()) + " Y : "+ QString::number(p.y()));

}

void MainWindow::on_radioButton_3_clicked()
{
   emit changeColour(QColor(Qt::red)) ;
}

void MainWindow::on_radioButton_4_clicked()
{
   emit changeColour(QColor(Qt::green)) ;
}

void MainWindow::on_radioButton_5_clicked()
{
   emit changeColour(QColor(Qt::blue));
}

void MainWindow::on_pushButton_3_clicked()
{
   emit drawLinePressedDDA();
}

void MainWindow::on_pushButton_4_clicked(bool checked)
{
    ui->frame->createGrid();
    // its the reset button at the bottom
}

void MainWindow::on_pushButton_5_clicked()
{
    emit drawLinePressedBresh();

}

void MainWindow::showColorLabel(int a, int b, int c)
{
    ui->showColor->setText("(" + QString::number(a) + "," + QString::number(b) + "," + QString::number(c) + ")");
}
void MainWindow::on_rSlider_valueChanged(int pos)
{
    emit changeTheColour(pos,'R');
}
void MainWindow::on_bSlider_valueChanged(int pos)
{
    emit changeTheColour(pos, 'B');
}

void MainWindow::on_gSlider_valueChanged(int pos)
{
    emit changeTheColour(pos, 'G');
}

void MainWindow::on_pushButton_6_clicked()
{
    int x = ui->comboBox->currentIndex();
    int y = ui->spinBox_2->value();
    emit drawCircle(x,y);
}

void MainWindow::on_pushButton_7_clicked()
{
    int major = ui->spinBox_3->value();
    int minor = ui->spinBox_4->value();
    emit drawEllipse(major,minor);
}
