#ifndef FRAME_WIDGET_H
#define FRAME_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QFrame>
#include <QList>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPair>
#include <bits/stdc++.h>
#include <chrono>

class frame_widget : public QFrame
{
    Q_OBJECT
private:
    int size;
    bool grid;
    bool modified;
    int maxwidth;
    int maxheight;
    bool visibleAxes;
    bool line_DDA;
    bool line_BA;
    bool circle;
    int radius;
    QList <QPair<QPoint, QColor> > points;
    QPoint point1;
    QPoint point2;
    QPoint lastpoint;
    QPoint convertPixel(QPoint p);
    QColor currentcol;
    QPoint convertCoord(int x, int y);
    int circleDrawMethod;//1 => midpoint 2 => Bresh 3=>polar
    int rx, ry;
    bool ellipse;


public:

    double elapsedda, elapsedba;
    double elapsedcircle;
    double elapsedellipse;



public:
    frame_widget(QWidget *parent = nullptr);

    void createGrid();
    void changeSize(int x);
    void showAxes();
    void changeGridSize(int x);
    void hideAxes();
    void toggleAxes();
    void toggleGrid();
    void mouseMoveEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *p) override;
    void mousePressEvent(QMouseEvent *ev) override;
    QPoint setPoint1();
    QPoint setPoint2();
    void changeCurrentColour(QColor q);
    void drawLineDDA();
    void drawLineBA();
    void drawCircle();
    void changeRadius(int size);
    void setCircleDraw(int val);
    void drawEllipse();
    void setRadiiEllipse(int rx, int ry);
    void setrx(int val);
    void setry(int val);

signals:

    void sendCoord(int x, int y);
};

#endif // FRAME_WIDGET_H
