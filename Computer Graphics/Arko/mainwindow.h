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
    void on_actionCreate_New_triggered();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    //void on_radioButton_3_clicked();
    //void on_radioButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_rSlider_valueChanged(int position);
    void on_gSlider_valueChanged(int position);
    void on_bSlider_valueChanged(int position);

private:
    Ui::MainWindow *ui;

public slots:
    void showCoord(int x , int y );
    void showPress(int x, int y);

signals:
    void drawLineDDA();
    void drawLineBA();
    void drawCircle(int x, int y);
    void changeColour(int a, char c);
};
#endif // MAINWINDOW_H
