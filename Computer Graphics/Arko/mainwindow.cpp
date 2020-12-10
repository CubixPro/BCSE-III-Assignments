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
    connect(this, &MainWindow::changeColour, ui->frame, &frame_widget::changeCurrentColour);
    connect(this, &MainWindow::drawLineDDA, ui->frame, &frame_widget::drawLineDDA);
    connect(this, &MainWindow::drawLineBA, ui->frame, &frame_widget::drawLineBA);
    connect(this, &MainWindow::drawCircle, ui->frame, &frame_widget::drawCircle);
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
    ui->center->setText("Center-> (" + QString::number(x) + ", " + QString::number(y) + ")");
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

/*void MainWindow::on_radioButton_3_clicked()
{
   emit changeColour(QColor(Qt::red)) ;
}

void MainWindow::on_radioButton_4_clicked()
{
   emit changeColour(QColor(Qt::green)) ;
}*/

void MainWindow::on_pushButton_3_clicked()
{
   emit drawLineDDA();
}

void MainWindow::on_pushButton_5_clicked()
{
   ui->frame->createGrid();
}

void MainWindow::on_pushButton_4_clicked()
{
   emit drawLineBA();
}

void MainWindow::on_pushButton_6_clicked()
{
    int x = ui->comboBox->currentIndex();
    int y = ui->radius->value();
    emit drawCircle(x, y);
}

void MainWindow::on_rSlider_valueChanged(int pos)
{
    emit changeColour(pos, 'R');
}

void MainWindow::on_gSlider_valueChanged(int pos)
{
    emit changeColour(pos, 'G');
}

void MainWindow::on_bSlider_valueChanged(int pos)
{
    emit changeColour(pos, 'B');
}
