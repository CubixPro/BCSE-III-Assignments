#include "edge.h"

Edge::Edge()
{

}

Edge::Edge(QPoint p1, QPoint p2)
{
   this->p1 = p1;
    this->p2 = p2;
   m = (0.0 + p2.y() - p1.y())/(0.0 + p2.x() - p1.x());
   currX = p1.x();
}

void Edge::activate()
{

    currX = p1.x();
}

void Edge::deactivate()
{
    currX = p2.x();

}

void Edge::update()
{
    currX = currX + 1/m;

}
