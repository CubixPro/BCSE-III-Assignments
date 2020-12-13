#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QAction>
#include <bits/stdc++.h>

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent)    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Drawing Pad");
    connect(ui->frame, &frame_widget::sendCoord, this, &MainWindow::showCoord);
    connect(ui->frame, &frame_widget::sendPress, this, &MainWindow::showPress);
    connect(this, &MainWindow::changeColour, ui->frame, &frame_widget::changeCurrentColour);
    connect(this, &MainWindow::drawPolarCircle, ui->frame, &frame_widget::drawPolarCircle);
    connect(this, &MainWindow::drawMidPointCircle, ui->frame, &frame_widget::drawMidPointCircle);
    connect(this, &MainWindow::drawBresenhamCircle, ui->frame, &frame_widget::drawBresenhamCircle);
    connect(this, &MainWindow::drawEllipse, ui->frame, &frame_widget::drawEllipse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{

}

void MainWindow::on_actionCreate_triggered()
{
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

void MainWindow::showCoord(int x, int y)
{
    ui->coord->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
}

void MainWindow::showPress(int x, int y)
{
    ui->press->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
    ui->center->setText("Center for  Circle: (" + QString::number(x) + ", " + QString::number(y) + ")");
    ui->center_2->setText("Center for Ellipse: (" + QString::number(x) + ", " + QString::number(y) + ")");
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
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


void MainWindow::on_pushButton_5_clicked()
{
   ui->frame->createGrid();
}

void MainWindow::on_pushButton_clicked()
{
    int y = ui->radius->value();
    emit drawPolarCircle(y);
}

void MainWindow::on_pushButton_2_clicked()
{
    int y = ui->radius->value();
    emit drawMidPointCircle(y);
}

void MainWindow::on_pushButton_3_clicked()
{
    int y = ui->radius->value();
    emit drawBresenhamCircle(y);
}


void MainWindow::on_radioButton_3_clicked()
{
   emit changeColour(QColor(Qt::green)) ;
}

void MainWindow::on_radioButton_4_clicked()
{
   emit changeColour(QColor(Qt::cyan)) ;
}

void MainWindow::on_radioButton_5_clicked()
{
   emit changeColour(QColor(Qt::yellow)) ;
}

void MainWindow::on_pushButton_7_clicked()
{
    int r1 = ui->major->value();
    int r2 = ui->minor->value();
    emit drawEllipse(r1, r2);
}
