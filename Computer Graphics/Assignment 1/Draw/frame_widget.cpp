#include "frame_widget.h"
frame_widget::frame_widget(QWidget *parent):
    QWidget(parent)
{
    size = 100;
    grid = false;
    modified = false;
    size = 25;
    maxwidth = 500;
    maxheight = 500;
    visibleAxes = false;

}




void frame_widget::createGrid()
{
    grid = true;
    points.clear();
    update();
}

void frame_widget::changeSize(int x)
{
    size = x;
    update();
}

void frame_widget::showAxes()
{
   visibleAxes = true;
   update();
}

void frame_widget::changeGridSize(int x)
{
   maxheight = maxwidth = x;
   update();
}

int min(int a, int b){
    if(a > b){
        return b;
    }
    else{
        return a;
    }
}
void frame_widget::paintEvent(QPaintEvent *p)
{
    QPixmap pix(500, 500);
    QPainter paint(this);
    pix.fill(Qt::white);
    if(grid){
        for(int i = 0 ; i < min(maxwidth, width()) ; i+=size){
            paint.drawLine(i, 0, i, min(maxheight, height()));
        }
        for(int j = 0 ; j < min(maxheight, height()) ; j+=size){
            paint.drawLine(0, j, min(maxwidth, width()), j);
        }
        paint.drawLine(min(maxwidth, width()) - 1, 0, min(maxwidth, min(maxwidth, width())), min(maxheight,  height()));
        paint.drawLine( 0, min(maxheight, height()) - 1,min(maxwidth, width()), min(maxheight, height())- 1);

    }
    if(modified){
        foreach (QPoint p , points ){
            paint.setBrush(Qt::cyan);
            int x = p.x();
            int y = p.y();
            QPoint newp((x/size)*size, (y/size)*size);
            paint.drawRect(newp.x(), newp.y(), size,  size);
        }

    }
    if(visibleAxes){
        QPen qp(Qt::red);
        paint.setPen(qp);
        paint.drawLine(maxwidth/2, 0, maxwidth/2, maxheight);
        paint.drawLine(0, maxheight/2, maxwidth, maxheight/2);
    }
}
void frame_widget::mousePressEvent(QMouseEvent *event)
{
     modified = true;
   lastpoint = event->pos();
   if(lastpoint.x() >= maxwidth || lastpoint.y() >= maxheight)
       return;
   points.append(lastpoint);
   repaint();

}




