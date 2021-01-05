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

    void on_actionDefault_triggered();

    void on_actionLarge_2_triggered();

    void on_frame_customContextMenuRequested(const QPoint &pos);

    void on_radioButton_toggled(bool checked);

    void on_spinBox_valueChanged(int arg1);

    void on_button_clicked();

    void on_button2_clicked();

    void on_radioButton_clicked();

    void on_spinBox_textChanged(const QString &arg1);

    void on_radioButton_2_clicked();

    void on_actionCreate_New_triggered();

    void on_radioButton_clicked(bool checked);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_r_slider_actionTriggered(int action);

    void on_g_slider_actionTriggered(int action);

    void on_b_slider_actionTriggered(int action);

    void on_r_slider_sliderMoved(int position);

    void on_g_slider_sliderMoved(int position);

    void on_b_slider_sliderMoved(int position);

    void on_pushButton_8_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_rx_valueChanged(int arg1);

    void on_ry_valueChanged(int arg1);

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_15_clicked();

    void on_comboBox_2_activated(int index);

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_pushButton_20_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_21_clicked();

    void on_spinBox_5_valueChanged(int arg1);

    void on_pushButton_25_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    //void on_radioButton_toggled(bool);
    void on_pushButton_29_clicked();

private:
    Ui::MainWindow *ui;
    //frame_widget *gridFrame;
    int r,  g,  b;

public slots:
    void showCoord(int x , int y );
    void showSeed(int x, int y);


signals:
    void drawLinePressed();
    void drawLineBA();
    void changeColour(QColor p);
    void scanLineClicked();
    void setVertexClicked();
    void initializeScanLine();


};
#endif // MAINWINDOW_H
