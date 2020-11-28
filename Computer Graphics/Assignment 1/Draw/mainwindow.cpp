#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QAction>


MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent)    , ui(new Ui::MainWindow), gridFrame(new frame_widget(this))
{
    ui->setupUi(this);
    setCentralWidget(gridFrame) ;

    createActions();
    //this->viewport()->setMouseTracking(true);
    setWindowTitle("Pixel Grid");
    resize(520, 550);
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
   gridFrame->createGrid();
}

void MainWindow::on_actionChange_Grid_Size_triggered()
{
    gridFrame->changeSize(1);
}

void MainWindow::on_actionSmall_triggered()
{
   gridFrame->changeSize(10);

}

void MainWindow::on_actionMedium_triggered()
{
   gridFrame->changeSize(25);
}

void MainWindow::on_actionLarge_triggered()
{
   gridFrame->changeSize(50);
}

void MainWindow::on_actionShow_Axes_triggered()
{
   gridFrame->showAxes();
}

void MainWindow::on_actionDefault_triggered()
{
   gridFrame->changeGridSize(500);
}

void MainWindow::on_actionLarge_2_triggered()
{
   gridFrame->changeGridSize(800);
}
