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
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPair>
#include <QTextStream>
#include <QElapsedTimer>
#include <QImage>
class frame_widget : public QFrame
{
    Q_OBJECT
private:
    int size;
    bool grid;
    bool modified;
    int maxwidth;
    int maxheight;
    int radius;
    int major;
    int minor;
    bool visibleAxes;
    bool circle_MP;
    bool circle_BA;
    bool circle_P;
    bool ellipse_MP;
    QList <QPair<QPoint, QColor> > points;
    QPoint point1;
    QPoint point2;
    QPoint lastpoint;
    QPoint convertPixel(QPoint p);
    QColor currentcol;
    QPoint convertCoord(int x, int y);
    QList <QPoint> clickedPoints;
    int polygonVertices;
    bool polygonStart;
    bool seed;
    QPoint seedpoint;
    QImage img;



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
    void drawPolarCircle(int r);
    void drawMidPointCircle(int r);
    void drawBresenhamCircle(int r);
    void drawEllipse(int r1, int r2);
    void drawLineDDA(QPoint p1, QPoint p2);
    void drawLineBA(QPoint p1, QPoint p2);
    void drawLine();
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
    void rotate(int x);
    void shear(double a,double b);
    void reflect();



signals:
    void sendCoord(int x, int y);
    void sendPress(int x, int y);
    void displayPolygonEnd(int x, int y);
    void displayPolygonStart(int x, int y);
    void startPolygon();
    void endPolygon();
    void sendSeed(int x, int y);

};

#endif // FRAME_WIDGET_H
