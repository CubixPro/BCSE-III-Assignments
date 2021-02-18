#ifndef FRAME_WIDGET_H
#define FRAME_WIDGET_H

#include <bits/stdc++.h>
using namespace std;

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
#include <QTextStream>
#include <QElapsedTimer>
#include <QTimer>
#include <QRgb>
#include <QImage>

class frame_widget : public QFrame
{
    Q_OBJECT
private:

    int size;
    bool grid;
    int maxwidth;
    int maxheight;
    int radius;
    int major;
    int minor;
    bool visibleAxes;
    bool circle_MP;
    bool circle_BA;
    bool circle_P;
    bool circle_PA;
    bool ellipse_MP;
    bool ellipse_P;
    QPoint point1;
    QPoint point2;
    QList <QPair<QPoint, QColor> > points;
    QPoint lastpoint;
    QPoint convertPixel(QPoint p);
    QColor currentcol;
    QColor fillColor;
    QPoint convertCoord(int x, int y);
    int RColor;
    int GColor;
    int BColor;
    int RFillColor;
    int GFillColor;
    int BFillColor;
    QList <QPoint> clickedPoints;
    int polygonVertices;
    bool polygonStart;
    bool seed;
    QPoint seedpoint;
    QImage img;
    vector <pair<int, int>> edgeList;
    vector <pair<int, int>> edges;
    int clip_points[4][2];
    QPoint endPoint1;
    QPoint endPoint2;
    bool accept;

public:

    frame_widget(QWidget *parent = nullptr);
    void createGrid();
    void changeSize(int x);
    void changeGridSize(int x);
    void toggleAxes();
    void toggleGrid();
    void mouseMoveEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *p) override;
    void mousePressEvent(QMouseEvent *ev) override;
    QPoint setPoint1();
    QPoint setPoint2();
    void changeCurrentColour(int a, char c);
    void changeCurrentFillColour(int a, char c);
    void drawLineDDA(QPoint p1, QPoint p2);
    void drawLineBA(QPoint p1, QPoint p2, QRgb col);
    void drawLine(int x);
    void lineWithDelay(QPoint p1, QPoint p2);
    void drawCircle(int x, int y);
    void drawEllipse(int r1, int r2, int x);
    void destroyPolygon(int x);
    void createPolygon(int x);
    void drawPolygon();
    void setSeed();
    void boundary_fill();
    void flood_fill();
    void scanLine_fill();
    void isMinMax(int a);
    void translate(int x, int y);
    void scale(double a, double b);
    void shear(double a, double b);
    void rotate(int x);
    void reflect();
    void drawRect();
    void clipLine();
    void clipPolygon();
    void getEndPoints(int x1, int y1, int x2, int y2);
    int computeCode(int a, int b, int x_min, int x_max, int y_min, int y_max);
    void clipAlongSide(int x1, int y1, int x2, int y2);
    void clearWindow();
    void drawCurve(double delU);

signals:
    void sendCoord(int x, int y);
    void sendPress(int x, int y);
    void sendColorLebel(int a, int b, int c);
    void sendFillColorLebel(int a, int b, int c);
    void sendTime(int a);
    void displayPolygonEnd(int x, int y);
    void displayPolygonStart(int x, int y);
    void startPolygon();
    void endPolygon();
    void sendSeed(int x, int y);
};

#endif // FRAME_WIDGET_H
