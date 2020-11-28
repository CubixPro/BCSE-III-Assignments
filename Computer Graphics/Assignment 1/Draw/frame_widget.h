#ifndef FRAME_WIDGET_H
#define FRAME_WIDGET_H
#include <QPoint>
#include <QList>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QMainWindow>
#include <QObject>
#include <QPen>

class frame_widget : public QWidget
{
        Q_OBJECT
public:
    void paintEvent(QPaintEvent *p) override ;
     void mousePressEvent(QMouseEvent *event) override ;
     frame_widget(QWidget *parent = 0);
     void createGrid();
     void changeSize(int s);
     void showAxes();
     void changeGridSize(int x);
private:
    frame_widget();
    bool grid;
    bool modified;
    QPoint lastpoint;
    QList<QPoint> points;
    int size;
    int maxwidth;
    int maxheight;
    bool visibleAxes;


};

#endif // FRAME_WIDGET_H
