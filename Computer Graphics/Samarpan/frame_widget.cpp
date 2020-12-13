#include "frame_widget.h"
#include <bits/stdc++.h>

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
    size = 12;
    maxwidth = 500;
    maxheight = 500;
    visibleAxes = false;
    this->setMouseTracking(true) ;
    currentcol = QColor(Qt::green);
    circle_MP = false;
    circle_BA = false;
    ellipse_BA = false;
}

void frame_widget::createGrid()
{
    points.clear();
    update();
}

void frame_widget::changeSize(int x)
{
    size = x;
    maxwidth = (500/size) * size ;
    maxheight = (500/size)*size ;
    createGrid();
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

   pos = convertPixel(pos);
   emit sendCoord(pos.x(), pos.y());
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
    QPainter paint(this);
    QBrush qBrush(Qt::black);
    paint.setBrush(qBrush);
    paint.drawRect(0, 0, min(maxheight, 500), min(maxwidth, 500));

    if(grid){
        QColor goodColor(255, 187, 153);
        paint.setPen(QPen(goodColor));
        for(int i = 0 ; i < min(maxwidth, width()) ; i+=size){
            paint.drawLine(i, 0, i, min(maxheight, height()));
        }
        for(int j = 0 ; j < min(maxheight, height()) ; j+=size){
            paint.drawLine(0, j, min(maxwidth, width()), j);
        }
    }

    if(visibleAxes){
        QBrush qBrush(Qt::white);
        paint.setBrush(qBrush);

        paint.drawRect((width()/(2*size))*size, 0, size, min(maxheight, height()));
        paint.drawRect(0, (height()/(2*size))*size,  min(maxwidth, width()), size);
    }



    if(circle_P) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = convertPixel(lastpoint);
        int x_center = p.x();
        int y_center = p.y();

        int x, y;
        for(float i=0; i<=3.14; i= i+ (1/(float)radius)) {
            x = round(radius*cos(i));
            y = round(radius*sin(i));

            points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});
        }

        modified = true;
        circle_P = false;
        int time = timer.nsecsElapsed();
        QTextStream out(stdout);
        out << "Circle with Polar Algorithm : " << time/1000 << "microsecs\n";
    }

    if(circle_MP) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = convertPixel(lastpoint);
        int x_center = p.x();
        int y_center = p.y();

        int x = radius, y = 0;
        points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
        if (radius > 0)
        {
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(y+ x_center, x+ y_center), currentcol});
            points.append({convertCoord(y+ x_center, -x+ y_center), currentcol});
        }

        int P = 1 - radius;
        while (x > y)
        {
            y++;

            //Initialising the value of P
            if (P <= 0)
                P = P + 2*y + 1;

            // Mid-point is outside the perimeter
            else
            {
                x--;
                P = P + 2*y - 2*x + 1;
            }

            // All the perimeter points have already been printed
            if (x < y)
                break;

            points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});

            if (x != y)
            {
                points.append({convertCoord(y+ x_center, x+ y_center), currentcol});
                points.append({convertCoord(-y+ x_center, x+ y_center), currentcol});
                points.append({convertCoord(y+ x_center, -x+ y_center), currentcol});
                points.append({convertCoord(-y+ x_center, -x+ y_center), currentcol});
            }
        }
        modified = true;
        circle_MP = false;
        int time = timer.nsecsElapsed();
        QTextStream out(stdout);
        out << "Circle with Mid Point Algorithm : " << time/1000 << "microsecs\n";
    }

    if(circle_BA) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = convertPixel(lastpoint);
        int x_center = p.x();
        int y_center = p.y();

        int x = 0, y = radius;
        int d = 3 - 2 * radius;

        points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
        points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
        points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
        points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});
        points.append({convertCoord(y+ x_center, x+ y_center), currentcol});
        points.append({convertCoord(-y+ x_center, x+ y_center), currentcol});
        points.append({convertCoord(y+ x_center, -x+ y_center), currentcol});
        points.append({convertCoord(-y+ x_center, -x+ y_center), currentcol});

        while (y >= x)
        {
            // for each pixel we will
            // draw all eight pixels

            x++;

            // check for decision parameter
            // and correspondingly
            // update d, x, y
            if (d > 0)
            {
                y--;
                d = d + 4 * (x - y) + 10;
            }
            else
                d = d + 4 * x + 6;

            points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(y+ x_center, x+ y_center), currentcol});
            points.append({convertCoord(-y+ x_center, x+ y_center), currentcol});
            points.append({convertCoord(y+ x_center, -x+ y_center), currentcol});
            points.append({convertCoord(-y+ x_center, -x+ y_center), currentcol});
        }

        modified = true;
        circle_BA = false;
        int time = timer.nsecsElapsed();
        QTextStream out(stdout);
        out << "Circle with Bresenham Algorithm : " << time/1000 << "microsecs\n";
    }

    if(ellipse_BA) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = convertPixel(lastpoint);
        int x_center = p.x();
        int y_center = p.y();

        float dx, dy, d1, d2, x, y;
        x = 0;
        y = minor;

        // Initial decision parameter of region 1
        d1 = (minor * minor) - (major * major * minor) + (0.25 * major * major);
        dx = 2 * minor * minor * x;
        dy = 2 * major * major * y;

        // For region 1
        while (dx < dy)
        {
            // Print points based on 4-way symmetry
            points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});

            // Checking and updating value of
            // decision parameter based on algorithm
            if (d1 < 0)
            {
                x++;
                dx = dx + (2 * minor * minor);
                d1 = d1 + dx + (minor * minor);
            }
            else
            {
                x++;
                y--;
                dx = dx + (2 * minor * minor);
                dy = dy - (2 * major * major);
                d1 = d1 + dx - dy + (minor * minor);
            }
        }

        // Decision parameter of region 2
        d2 = ((minor * minor) * ((x + 0.5) * (x + 0.5))) + ((major * major) * ((y - 1) * (y - 1))) - (major * major * minor * minor);

        // Plotting points of region 2
        while (y >= 0)
        {

            // Print points based on 4-way symmetry
            points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});

            // Checking and updating parameter
            // value based on algorithm
            if (d2 > 0)
            {
                y--;
                dy = dy - (2 * major * major);
                d2 = d2 + (major * major) - dy;
            }
            else
            {
                y--;
                x++;
                dx = dx + (2 * minor * minor);
                dy = dy - (2 * major * major);
                d2 = d2 + dx - dy + (major * major);
            }
        }

        modified = true;
        ellipse_BA = false;
        int time = timer.nsecsElapsed();
        QTextStream out(stdout);
        out << "Ellipse with Bresenham Algorithm : " << time/1000 << "microsecs\n";
    }

    if(modified){
        QPair<QPoint, QColor> p;
        foreach (p , points ){
            paint.setBrush(p.second);
            int x = p.first.x();
            int y = p.first.y();
            QPoint newp((x/size)*size, (y/size)*size);
            paint.drawRect(newp.x(), newp.y(), size, size);
        }
    }
}
void frame_widget::mousePressEvent(QMouseEvent *event)
{
   modified = true;
   lastpoint = event->pos();
   if(lastpoint.x() >= maxwidth || lastpoint.y() >= maxheight)
       return;
   points.append({lastpoint, currentcol});
   QPoint last = convertPixel(lastpoint);
   emit sendPress(last.x(), last.y());
   repaint();
}


void frame_widget::changeCurrentColour(QColor q)
{
    currentcol = q;
}


void frame_widget::drawPolarCircle(int r)
{
    radius = r;
    circle_P = true;
    update();
}

void frame_widget::drawMidPointCircle(int r)
{
    radius = r;
    circle_MP = true;
    update();
}

void frame_widget::drawBresenhamCircle(int r)
{
    radius = r;
    circle_BA = true;
    update();
}

void frame_widget::drawEllipse(int r1, int r2)
{
    major = r1;
    minor = r2;
    ellipse_BA = true;
    update();
}
