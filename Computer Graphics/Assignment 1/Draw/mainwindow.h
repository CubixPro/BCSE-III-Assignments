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

private:
    Ui::MainWindow *ui;
    frame_widget *gridFrame;
};
#endif // MAINWINDOW_H
