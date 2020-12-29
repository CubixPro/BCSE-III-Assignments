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
#include <QMap>
#include <QVector>
#include <bits/stdc++.h>
#include <QImage>
#include <QtDebug>
#define maxVer 360000
#define maxHt 600
#include<unistd.h>
#include <edge.h>

using namespace std;


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
    bool fill;
    QPoint seed;
    QColor fill_colour;
    QColor seed_colour;
    QColor boundary_fill_colour;
    bool seednow ;
    bool delay;
    QVector<QPoint> polygon;
    QColor polygoncolour;
    QVector<Edge> sortededges;
    void drawDelayLine(int x1, int y1, int x2, int y2);
    vector<int> matMult3_1(vector<vector<int>> mat, vector<int> coords);
    vector<double> matMult3_1D(vector<vector<double>> mat, vector<double> coords);
    vector<vector<int>> matMult3_3(vector<vector<int>> x, vector<vector<int>> y);
    void translate(int tx, int ty);
    void scale(int sx, int sy);
    void rotate(int angle, int piv_x, int piv_y);
    void shear(int shr_x, int shr_y);
    int tx;
    int ty;
    int angle;
    QPoint pivot;
    QPoint cPoint1;
    QPoint cPoint2;


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
    void floodFill();
    void setSeedColour();
    void startfloodFill();
    void boundaryFill();
    void startboundaryFill();
    void addPointToPolygon();
    void drawPolygon();
    void setBoundaryColour();
    void clearPolygon();
    void scanLineFill();

    void settx(int x);
    void setty(int y);
    void setAngle(int ang);

    void ontranslate();
    void setPivotPoint();
    void onscale();
    void onrotate();
    void onreflect();

    void reflect();
signals:

    void sendCoord(int x, int y);
    void sendSeed(int x, int y);
};

#endif // FRAME_WIDGET_H
