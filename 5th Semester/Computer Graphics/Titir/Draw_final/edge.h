#ifndef EDGE_H
#define EDGE_H
#include <QPoint>


class Edge
{
public:
    QPoint p1, p2;
    double currX;
    double m;

public:
    Edge();
    Edge(QPoint p1, QPoint p2);
    void activate();
    void deactivate();
    void update();
};

#endif // EDGE_H
