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
#include <QTextStream>
#include <QElapsedTimer>
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
    bool line_DDA;
    bool line_BA;
    bool circle_MP;
    bool circle_BA;
    bool circle_P;
    bool ellipse_BA;
    QList <QPair<QPoint, QColor> > points;
    QPoint point1;
    QPoint point2;
    QPoint lastpoint;
    QPoint convertPixel(QPoint p);
    QColor currentcol;
    QPoint convertCoord(int x, int y);
    int RColor;
    int GColor;
    int BColor;

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
    void changeCurrentColour(int a, char c);
    void drawLineDDA();
    void drawLineBA();
    void drawCircle(int x, int y);
    void drawEllipse(int r1, int r2);

signals:
    void sendCoord(int x, int y);
    void sendPress(int x, int y);
    void sendColorLebel(int a, int b, int c);
};

#endif // FRAME_WIDGET_H
