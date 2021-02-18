#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QAction>
#include <bits/stdc++.h>

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent)    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Pixel Grid");
    connect(ui->frame, &frame_widget::sendCoord, this, &MainWindow::showCoord);
    connect(ui->frame, &frame_widget::sendPress, this, &MainWindow::showPress);
    connect(ui->frame, &frame_widget::sendColorLebel, this, &MainWindow::showColorLebel);
    connect(ui->frame, &frame_widget::sendFillColorLebel, this, &MainWindow::showFillColorLebel);
    connect(ui->frame, &frame_widget::sendTime, this, &MainWindow::showTime);
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

void MainWindow::showCoord(int x, int y)
{
    ui->coord->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
}

void MainWindow::showPress(int x, int y)
{
    ui->press->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
}

void MainWindow::showSeed(int x, int y)
{
    ui->seed->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
}

void MainWindow::showColorLebel(int a, int b, int c)
{
    ui->color->setText("rgb(" + QString::number(a) + "," + QString::number(b) + "," + QString::number(c) + ")");
}

void MainWindow::showFillColorLebel(int a, int b, int c)
{
    ui->fillcolor->setText("rgb(" + QString::number(a) + "," + QString::number(b) + "," + QString::number(c) + ")");
}

void MainWindow::showTime(int a)
{
    ui->time->setText("Time taken : " + QString::number(a) + "μs");
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->frame->changeSize(arg1);
}

void MainWindow::on_radioButton_clicked()
{
   ui->frame->toggleAxes();
}

void MainWindow::on_radioButton_2_clicked()
{
   ui->frame->toggleGrid();
}

void MainWindow::on_pushButton_2_clicked()
{
    QPoint p = ui->frame->setPoint1();
    ui->center->setText("X : " + QString::number(p.x()) + " Y : "+ QString::number(p.y()));
    ui->point1->setText("Point 1");
    ui->point2->setText("Point 2");
}

void MainWindow::on_pushButton_clicked()
{
    QPoint p = ui->frame->setPoint2();
    ui->center_2->setText("X : " + QString::number(p.x()) + " Y : "+ QString::number(p.y()));
    ui->point1->setText("Point 1");
    ui->point2->setText("Point 2");
}

void MainWindow::on_pushButton_5_clicked()
{
   ui->frame->createGrid();
}

void MainWindow::on_pushButton_6_clicked()
{
    int x = ui->comboBox->currentIndex();
    int y = ui->radius->value();
    ui->frame->drawCircle(x, y);
}

void MainWindow::on_rSlider_valueChanged(int pos)
{
    ui->frame->changeCurrentColour(pos, 'R');
}

void MainWindow::on_gSlider_valueChanged(int pos)
{
    ui->frame->changeCurrentColour(pos, 'G');
}

void MainWindow::on_bSlider_valueChanged(int pos)
{
    ui->frame->changeCurrentColour(pos, 'B');
}

void MainWindow::on_rFill_valueChanged(int pos)
{
    ui->frame->changeCurrentFillColour(pos, 'R');
}

void MainWindow::on_gFill_valueChanged(int pos)
{
    ui->frame->changeCurrentFillColour(pos, 'G');
}

void MainWindow::on_bFill_valueChanged(int pos)
{
    ui->frame->changeCurrentFillColour(pos, 'B');
}

void MainWindow::on_pushButton_7_clicked()
{
    int r1 = ui->major->value();
    int r2 = ui->minor->value();
    int x = ui->comboBox_2->currentIndex();
    ui->frame->drawEllipse(r1, r2, x);
}

void MainWindow::on_pushButton_10_clicked()
{
    QPoint p = ui->frame->setPoint1();
    ui->point1->setText("X : "+QString::number(p.x()) + " Y : " + QString::number(p.y()));
    ui->center_2->setText("Ellipse Center");
}

void MainWindow::on_pushButton_11_clicked()
{
    QPoint p = ui->frame->setPoint2();
    ui->point2->setText("X : "+QString::number(p.x()) + " Y : " + QString::number(p.y()));
    ui->center->setText("Circle Center");
}

void MainWindow::on_pushButton_line_clicked()
{
    int x = ui->comboBox_4->currentIndex();
    ui->frame->drawLine(x);
}

void MainWindow::on_pushButton_8_clicked()
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
    ui->pushButton_8->setDisabled(false);
}

void MainWindow::displayPolygonStart(int x, int y)
{
    ui->polygonStart->setText("X : "+QString::number(x) + " Y : " + QString::number(y));
}

void MainWindow::endPolygon()
{
    ui->polygonStart->setText("Start Point");
    ui->polygonEnd->setText("End Point");
    ui->pushButton_8->setDisabled(false);
}

void MainWindow::startPolygon()
{
    ui->pushButton_8->setDisabled(true);
    ui->polygonStart->setText("Start Point");
    ui->polygonEnd->setText("End Point");
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->frame->drawPolygon();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->frame->setSeed();
}

void MainWindow::on_pushButton_4_clicked()
{
    int x = ui->comboBox_3->currentIndex();
    if(x == 0) ui->frame->boundary_fill();
    else if(x == 1) ui->frame->flood_fill();
    else ui->frame->scanLine_fill();
}

void MainWindow::on_pushButton_translate_clicked()
{
    int tx = ui->tranx->value();
    int ty = ui->trany->value();
    ui->frame->translate(tx, ty);
}

void MainWindow::on_pushButton_scale_clicked()
{
    double sx = ui->scalex->value();
    double sy = ui->scaley->value();
    ui->frame->scale(sx, sy);
}

void MainWindow::on_pushButton_rotate_clicked()
{
    int x = ui->rotate->value();
    ui->frame->rotate(x);
}

void MainWindow::on_pushButton_reflect_clicked()
{
    ui->frame->reflect();
}

void MainWindow::on_pushButton_shear_clicked()
{
    double shx = ui->shearx->value();
    double shy = ui->sheary->value();
    ui->frame->shear(shx, shy);
}

void MainWindow::on_pushButton_rect_clicked()
{
    ui->frame->drawRect();
}

void MainWindow::on_pushButton_clipL_clicked()
{
    ui->frame->clipLine();
}

void MainWindow::on_pushButton_clipP_clicked()
{
    ui->frame->clipPolygon();
}

void MainWindow::on_pushButton_curve_clicked()
{
    double delU = ui->curveU->value();
    ui->frame->drawCurve(delU);
}
