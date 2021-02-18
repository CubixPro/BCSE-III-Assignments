#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QBrush>
#include <QPoint>
#include <QPixmap>
#include <QColor>
#include <QPainter>
#include <QList>
#include "frame_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void showMousePosition(QPoint &pos);
    ~MainWindow();
    void createActions();

private slots:

    void on_actionCreate_triggered();
    void on_actionChange_Grid_Size_triggered();
    void on_actionSmall_triggered();
    void on_actionMedium_triggered();
    void on_actionLarge_triggered();
    void on_actionShow_Axes_triggered();
    void on_spinBox_valueChanged(int arg1);
    void on_button_clicked();
    void on_button2_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
    void on_radioButton_6_clicked();
    void on_radioButton_7_clicked();
    void on_actionCreate_New_triggered();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_vertices_valueChanged(int arg1);
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();


private:
    Ui::MainWindow *ui;

public slots:
    void showCoord(int x , int y );
    void showPress(int x, int y);
    void displayPolygonEnd(int x, int y);
    void displayPolygonStart(int x, int y);
    void startPolygon();
    void endPolygon();
    void showSeed(int x, int y);


signals:
    void drawPolarCircle(int r);
    void drawMidPointCircle(int r);
    void drawBresenhamCircle(int r);
    void drawEllipse(int r1, int r2);
    void changeColour(QColor p);

};
#endif // MAINWINDOW_H
