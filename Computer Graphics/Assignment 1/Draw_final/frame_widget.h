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
    QList<QPoint> points;
    QPoint lastpoint;




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

signals:
    void sendCoord(int x, int y);
};

#endif // FRAME_WIDGET_H
