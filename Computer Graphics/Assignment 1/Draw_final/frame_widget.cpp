#include "frame_widget.h"
#include <bits/stdc++.h>
#include "time.h"
#include <chrono>
QPoint frame_widget::convertPixel(QPoint p)
{
    QPoint pos = p;
   int x = pos.x();
   int y = pos.y();
   if(x >= (width()/(2*size))*size  && x <= ((width()/(2*size))*size  + size)){
        x = 0;
   }
   else if(x >= width()/2)
    x = (x - (width()/(2*size))*size - size)/size + 1 ;
   else{
        x = -(((width()/(2*size))*size  - x)/size + 1) ;
   }
   if(y >= (height()/(2*size))*size && y <= ((height()/(2*size))*size + size)  )
       y = 0;
   else if(y >= height()/2)
    y = -((y - (height()/(2*size))*size - size)/size + 1);
   else{
       y = ((height()/(2*size))*size - y)/size + 1;
   }
   QPoint pf(x, y);
   return pf;
}

QPoint frame_widget::convertCoord(int x, int y)
{
   QPoint p((width()/(2 * size))*size, (height()/(2 * size))*size);
   p.setX(p.x() + size*x);
   p.setY(p.y() - size*y);
   return p;


}

frame_widget::frame_widget(QWidget *parent):
    QFrame(parent)
{
    size = 100;
    grid = false;
    modified = false;
    size = 25;
    maxwidth = 500;
    maxheight = 500;
    visibleAxes = false;
    this->setMouseTracking(true) ;
    currentcol = QColor(Qt::red);
    line_DDA = false;
    line_BA = false;
}




void frame_widget::createGrid()
{
    //grid = true;
    points.clear();
    update();
}

void frame_widget::changeSize(int x)
{
    size = x;
    maxwidth = (500/size) * size ;
    maxheight = (500/size)*size ;
    createGrid();
    //update();
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

void frame_widget::hideAxes()
{
   visibleAxes = false;
   update();
}

void frame_widget::toggleAxes()
{
    if(visibleAxes == true)
        visibleAxes = false;
    else
        visibleAxes = true;


   update();
}

void frame_widget::toggleGrid()
{
   grid = !grid;
   update();
}

void frame_widget::mouseMoveEvent(QMouseEvent *ev)
{
   QPoint pos = ev->pos();
   int x = pos.x();
   int y = pos.y();
   if(x >= (width()/(2*size))*size  && x <= ((width()/(2*size))*size  + size)){
        x = 0;
   }
   else if(x >= width()/2)
    x = (x - (width()/(2*size))*size - size)/size + 1 ;
   else{
        x = -(((width()/(2*size))*size  - x)/size + 1) ;
   }
   if(y >= (height()/(2*size))*size && y <= ((height()/(2*size))*size + size)  )
       y = 0;
   else if(y >= height()/2)
    y = -((y - (height()/(2*size))*size - size)/size + 1);
   else{
       y = ((height()/(2*size))*size - y)/size + 1;
   }

       emit sendCoord(x, y);
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
    paint.drawRect(0, 0, min(maxheight, 500), min(maxwidth, 500));

    if(grid){
        paint.setPen(QPen(Qt::gray));
        for(int i = 0 ; i < min(maxwidth, width()) ; i+=size){
            paint.drawLine(i, 0, i, min(maxheight, height()));
        }
        for(int j = 0 ; j < min(maxheight, height()) ; j+=size){
            paint.drawLine(0, j, min(maxwidth, width()), j);

        }
        paint.drawLine(min(maxwidth, width()) - 1, 0, min(maxwidth, min(maxwidth, width())), min(maxheight,  height()));
        paint.drawLine( 0, min(maxheight, height()) - 1,min(maxwidth, width()), min(maxheight, height())- 1);

    }
    if(visibleAxes){
        QBrush qBrush(Qt::white);
        paint.setBrush(qBrush);

        paint.drawRect((width()/(2*size))*size, 0, size, min(maxheight, height()));
        paint.drawRect(0, (height()/(2*size))*size,  min(maxwidth, width()), size);
    }if(line_DDA){
        paint.setBrush(QBrush(currentcol));
        auto time1 = std::chrono::high_resolution_clock::now();
        //DDA ALGORITHM FOR LINE DRAWING
        double x = point1.x();
        double y = point1.y();
        double dx = (point2.x() - point1.x());
        double dy = (point2.y() - point1.y());
        double steps;
        if(abs(dx) > abs(dy)){
            steps = abs(dx);
        }
        else{
            steps = abs(dy);
        }
        double inc_x = dx/(float)steps;
        double inc_y = dy/(float)steps;
        for(int i = 0 ; i < steps ; i++){

            x = x + (inc_x);
            y = y + (inc_y);
            QPoint p0 = convertCoord(round(x), round(y));
            if(QPoint(round(x), round(y)) == point2){
                continue;
            }
            points.append({p0, currentcol});
            modified = true;
            //paint.drawRect(p0.x(), p0.y(), size, size);
        }
        line_DDA = false;
        auto time2 = std::chrono::high_resolution_clock::now();
        std::cout << (time2 - time1).count() << '\n';
    }
    if(line_BA){

        //Breshenham Algorithm for LINE DRAWING
        /*if(point1.x() > point2.x()){
                QPoint temp = point2;
                point2 = point1;
                point1 = temp;
            }
            int x = point1.x();
            int y = point1.y();
            int dx = (point2.x() - point1.x());
            int dy = (point2.y() - point1.y());
            int parameter = 2 * dy - dx;
            for (;x < point2.x() ; x++ ) {
                QPoint p0;
                if(parameter < 0){
                     p0 = convertCoord(x , y);
                     parameter = parameter + 2 * dy;
               }
                else{
                    p0 = convertCoord(x , y );
                    y = y + 1;
                    parameter = parameter  + 2 * dy - 2 * dx;
                }
                points.append({p0, currentcol});
                modified = true;

            }
           */

        int x, y, dx, dy, s1, s2, e, flag, i;
        auto time1 = std::chrono::high_resolution_clock::now();
        i = 1;
        x = point1.x();
        y = point1.y();
        dx = point2.x() - point1.x();
        dy = point2.y() - point1.y();
        s1 = dx > 0 ? 1 : -1;
        s2 = dy > 0 ? 1 : -1;
        dx *= s1;
        dy *= s2;

        e = (dy << 1) - dx;
        if(dy > dx){
            int temp = dx;
            dx = dy;
            dy = temp;
            flag = 1;
        }
        else{
            flag = 0;
        }

        while(i <= dx){
            points.append({convertCoord(x, y), currentcol});
            if(e >= 0){
                if(flag)
                    x += s1;
                else
                    y+=s2;
                e-=(dx<<1);
            }
            if(flag)
                y+=s2;
            else
                x+=s1;
            e+=(dy<<1);
            ++i;
        }

        modified = true;
        line_BA = false;
        auto time2 = std::chrono::high_resolution_clock::now();
        std::cout << (time2 - time1).count() << '\n';
    }
    if(modified){
        QPair<QPoint, QColor> p;
        foreach (p   , points ){
            paint.setBrush(p.second);
            int x = p.first.x();
            int y = p.first.y();
            QPoint newp((x/size)*size, (y/size)*size);
            paint.drawRect(newp.x(), newp.y(), size,  size);
        }

    }


}
void frame_widget::mousePressEvent(QMouseEvent *event)
{
     modified = true;
   lastpoint = event->pos();
   if(lastpoint.x() >= maxwidth || lastpoint.y() >= maxheight)
       return;
   //QColor colour(Qt::red);
   points.append({lastpoint, currentcol});
   repaint();

}

QPoint frame_widget::setPoint1()
{
    point1 = convertPixel(lastpoint);
    return (point1);

}

QPoint frame_widget::setPoint2()
{
    point2 = convertPixel(lastpoint);
    return point2;

}

void frame_widget::changeCurrentColour(QColor q)
{
    currentcol = q;

}

void frame_widget::drawLineDDA()
{
    line_DDA = true;
    update();

}
void frame_widget::drawLineBA(){
    line_BA = true;
    update();
}




