#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QBrush>
#include <QPoint>
#include <QPixmap>
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

    void on_spinBox_valueChanged(int arg1);
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_rSlider_valueChanged(int position);
    void on_gSlider_valueChanged(int position);
    void on_bSlider_valueChanged(int position);
    void on_rFill_valueChanged(int position);
    void on_gFill_valueChanged(int position);
    void on_bFill_valueChanged(int position);
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_vertices_valueChanged(int arg1);
    void on_pushButton_9_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_translate_clicked();
    void on_pushButton_scale_clicked();
    void on_pushButton_rotate_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_line_clicked();
    void on_pushButton_reflect_clicked();
    void on_pushButton_shear_clicked();
    void on_pushButton_rect_clicked();
    void on_pushButton_clipL_clicked();
    void on_pushButton_clipP_clicked();
    void on_pushButton_curve_clicked();

private:
    Ui::MainWindow *ui;

public slots:
    void showCoord(int x , int y );
    void showPress(int x, int y);
    void showColorLebel(int a, int b, int c);
    void showFillColorLebel(int a, int b, int c);
    void showTime(int a);
    void displayPolygonEnd(int x, int y);
    void displayPolygonStart(int x, int y);
    void startPolygon();
    void endPolygon();
    void showSeed(int x, int y);

};
#endif // MAINWINDOW_H
