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
    connect(ui->frame, &frame_widget::displayPolygonEnd, this, &MainWindow::displayPolygonEnd);
    connect(ui->frame, &frame_widget::displayPolygonStart, this, &MainWindow::displayPolygonStart);
    connect(ui->frame, &frame_widget::startPolygon, this, &MainWindow::startPolygon);
    connect(ui->frame, &frame_widget::endPolygon, this, &MainWindow::endPolygon);
    connect(ui->frame, &frame_widget::sendSeed, this, &MainWindow::showSeed);

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

void MainWindow::showSeed(int x, int y)
{
    ui->seed->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
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
   ui->seed->setText("Seed Point");
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

void MainWindow::on_radioButton_6_clicked()
{
    emit changeColour(QColor(Qt::blue));
}


void MainWindow::on_radioButton_7_clicked()
{
    emit changeColour(QColor(Qt::red));
}

void MainWindow::on_pushButton_7_clicked()
{
    int r1 = ui->major->value();
    int r2 = ui->minor->value();
    emit drawEllipse(r1, r2);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->frame->createPolygon(ui->vertices->value());
}

void MainWindow::on_vertices_valueChanged(int arg1)
{
    ui->frame->destroyPolygon(arg1);
}

void MainWindow::displayPolygonEnd(int x, int y)
{
    ui->polygonEnd->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
    ui->pushButton_4->setDisabled(false);
}

void MainWindow::displayPolygonStart(int x, int y)
{
    ui->polygonStart->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
}

void MainWindow::endPolygon()
{
    ui->polygonStart->setText("Start Point");
    ui->polygonEnd->setText("End Point");
    ui->pushButton_4->setDisabled(false);
}

void MainWindow::startPolygon()
{
    ui->pushButton_4->setDisabled(true);
    ui->polygonStart->setText("Start Point");
    ui->polygonEnd->setText("End Point");
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->frame->drawPolygon();
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->frame->setSeed();
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->frame->boundary_fill();
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->frame->scanLine_fill();
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->frame->flood_fill();
}

void MainWindow::on_pushButton_12_clicked()
{
    int tx = ui->transx->value();
    int ty = ui->transy->value();
    ui->frame->translate(tx, ty);
}

void MainWindow::on_pushButton_13_clicked()
{
    double sx = ui->scalex->value();
    double sy = ui->scaley->value();
    ui->frame->scale(sx, sy);
}

void MainWindow::on_pushButton_14_clicked()
{
    int x = ui->rotate->value();
    ui->frame->rotate(x);
}

void MainWindow::on_pushButton_15_clicked()
{
    double shx = ui->shearx->value();
    double shy = ui->sheary->value();
    ui->frame->shear(shx, shy);
}

void MainWindow::on_pushButton_16_clicked()
{
    QPoint p = ui->frame->setPoint1();
    ui->point1->setText("X : "+QString::number(p.x()) + " Y : " + QString::number(p.y()));
}

void MainWindow::on_pushButton_17_clicked()
{
    QPoint p = ui->frame->setPoint2();
    ui->point2->setText("X : "+QString::number(p.x()) + " Y : " + QString::number(p.y()));
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->frame->drawLine();
}

void MainWindow::on_pushButton_19_clicked()
{
    ui->frame->reflect();
}



