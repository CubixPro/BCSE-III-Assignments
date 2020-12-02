
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
    setWindowTitle("Pixel Grid");
    //resize(520, 550);
    connect(ui->frame, &frame_widget::sendCoord, this, &MainWindow::showCoord);

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

