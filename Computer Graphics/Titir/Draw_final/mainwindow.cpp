
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QAction>
#include <bits/stdc++.h>
#include <ctime>
//add erase point features
MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent)    , ui(new Ui::MainWindow) //, gridFrame(new frame_widget(this))
{
    //setCentralWidget(gridFrame) ;

    //this->viewport()->setMouseTracking(true);
    ui->setupUi(this);
    setWindowTitle("Pixel Grid");
    r = 255;
    g = 0;
    b = 0;
    //resize(520, 550);
    ui->colour->setStyleSheet("background-color : red; border : 2px white ; border-radius : 5px");
    connect(ui->frame, &frame_widget::sendCoord, this, &MainWindow::showCoord);
    connect(ui->frame, &frame_widget::sendSeed, this, &MainWindow::showSeed);
    connect(this, &MainWindow::changeColour, ui->frame, &frame_widget::changeCurrentColour);
    connect(this, &MainWindow::drawLinePressed, ui->frame, &frame_widget::drawLineDDA);
    connect(this, &MainWindow::drawLineBA, ui->frame, &frame_widget::drawLineBA);
    //connect(this, &MainWindow::scanLineClicked, ui->frame, &frame_widget::on_fill_scan_clicked);
    //connect(this, &MainWindow::setVertexClicked, ui->frame, &frame_widget::on_set_vertex_clicked);
    //connect(this, &MainWindow::initializeScanLine, ui->frame, &frame_widget::on_scanline_clicked);

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


void MainWindow::showSeed(int x, int y){
    ui->seed->setText("X : "+QString::number(x) + " Y : " + QString::number(y));

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
  ui->time->setText("0.0");
   ui->time2->setText("0.0");
   ui->time_circle->setText("0.0");
   ui->time_ellipse->setText("0.0");
    ui->label_1->setText(QString("Point 1"));
    ui->label_2->setText(QString("Point 2"));
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
   emit changeColour(QColor(Qt::blue)) ;
}

void MainWindow::on_radioButton_5_clicked()
{
   emit changeColour(QColor(Qt::yellow));
}

void MainWindow::on_pushButton_3_clicked()
{
   emit drawLinePressed();
}

void MainWindow::on_pushButton_5_clicked()
{
   ui->frame->createGrid();
   ui->time->setText("0.0");
   ui->time2->setText("0.0");
   ui->time_circle->setText("0.0");
   ui->time_ellipse->setText("0.0");
    ui->label_1->setText(QString("Point 1"));
    ui->label_2->setText(QString("Point 2"));
}

void MainWindow::on_pushButton_4_clicked()
{
   emit drawLineBA();
}

void MainWindow::on_radioButton_6_clicked()
{
   emit changeColour(QColor(Qt::green));
}

void MainWindow::on_pushButton_6_clicked()
{
    std::ostringstream out ;
    out << ui->frame->elapsedda;
    std::string s = out.str();
   ui->time->setText(QString::fromStdString(s)) ;
}

void MainWindow::on_pushButton_7_clicked()
{
    std::ostringstream out ;
    out << ui->frame->elapsedba;
    std::string s = out.str();
   ui->time2->setText(QString::fromStdString(s)) ;
}

void MainWindow::on_r_slider_actionTriggered(int action)
{
   // r = action;
   // emit changeColour(QColor(r, g, b));
  //emit changeColour(QColor(action, ui->g_slider->value, ui->b_slider->value, 255));
}


void MainWindow::on_g_slider_actionTriggered(int action)
{
   //g = action;
   //emit changeColour(QColor(r, g, b));
}

void MainWindow::on_b_slider_actionTriggered(int action)
{
   //b = action;
   //emit changeColour(QColor(r, g, b));
}

void MainWindow::on_r_slider_sliderMoved(int position)
{
   r = position;
   QColor col(r, g, b);
   QString s = col.name();
   ui->colour->setStyleSheet("background-color: " + s + "; border : 2px white ; border-radius : 5px");
   update();
   emit changeColour(QColor(r, g, b));
}

void MainWindow::on_g_slider_sliderMoved(int position)
{
   g = position;
   QColor col(r, g, b);
   QString s = col.name();
    ui->colour->setStyleSheet("background-color: " + s + " ; border : 2px white ; border-radius : 5px");
    update();
//ui->colour->setBackground(QColor(r, g, b));
emit changeColour(QColor(r, g, b));
}

void MainWindow::on_b_slider_sliderMoved(int position)
{
    b = position;
   QColor col(r, g, b);
   QString s = col.name();
    ui->colour->setStyleSheet("background-color: " + s + "; border : 2px white ; border-radius : 5px");
    update();
//ui->colour->setBackground(QColor(r, g, b));
 emit changeColour(QColor(r, g, b));
}

void MainWindow::on_pushButton_8_clicked()
{
   ui->frame->drawCircle();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
   ui->frame->changeRadius(arg1);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
   ui->frame->setCircleDraw(index);
}

void MainWindow::on_pushButton_9_clicked()
{
     std::ostringstream out ;
    out << ui->frame->elapsedcircle;
    std::string s = out.str();
   ui->time_circle->setText(QString::fromStdString(s)) ;

}

void MainWindow::on_pushButton_10_clicked()
{
    ui->frame->drawEllipse();
  }

void MainWindow::on_rx_valueChanged(int arg1)
{
   ui->frame->setrx(arg1);
}

void MainWindow::on_ry_valueChanged(int arg1)
{
   ui->frame->setry(arg1);
}

void MainWindow::on_pushButton_11_clicked()
{
     std::ostringstream out ;
    out << ui->frame->elapsedellipse;
    std::string s = out.str();
    ui->time_ellipse->setText(QString::fromStdString(s)) ;

}

void MainWindow::on_pushButton_13_clicked()
{
   ui->frame->addPointToPolygon();
}

void MainWindow::on_pushButton_14_clicked()
{
   ui->frame->drawPolygon();
}

void MainWindow::on_pushButton_12_clicked()
{
   //ui->frame->startFillPolygon();
    //emit setVertexClicked();
    ui->frame->floodFill();
}

void MainWindow::on_pushButton_15_clicked()
{
   ui->frame->clearPolygon();
}

void MainWindow::on_comboBox_2_activated(int index)
{
    /*if(index != 2)
        ui->frame->startFillPolygon();
    else{
        //ui->frame->startScanLine();
        ui->frame->scanLine_fill();
    }*/
}



void MainWindow::on_pushButton_16_clicked()
{
   //emit initializeScanLine();
    ui->frame->setSeedColour();
}

void MainWindow::on_pushButton_17_clicked()
{
   //emit scanLineClicked();
    ui->frame->boundaryFill();
}

void MainWindow::on_pushButton_18_clicked()
{
   ui->frame->setBoundaryColour();
}

void MainWindow::on_pushButton_19_clicked()
{
   ui->frame->scanLineFill();
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
   ui->frame->settx(arg1);
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
   ui->frame->setty(arg1);
}

void MainWindow::on_pushButton_20_clicked()
{
   ui->frame->ontranslate();
}

void MainWindow::on_pushButton_24_clicked()
{
   ui->frame->setPivotPoint();
}

void MainWindow::on_pushButton_21_clicked()
{
    ui->frame->onscale();
}

void MainWindow::on_spinBox_5_valueChanged(int arg1)
{
   ui->frame->setAngle(arg1);
}

void MainWindow::on_pushButton_25_clicked()
{
   ui->frame->setPivotPoint();
}

void MainWindow::on_pushButton_22_clicked()
{
   ui->frame->onrotate();
}


void MainWindow::on_pushButton_23_clicked()
{
   ui->frame->reflect();
}
