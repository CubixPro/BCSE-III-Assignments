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
    size = 10;
    maxwidth = 500;
    maxheight = 500;
    visibleAxes = false;
    this->setMouseTracking(true) ;
    currentcol = QColor(Qt::red);
    circle_P = false;
    circle_MP = false;
    circle_BA = false;
    circle_PA = false;
    ellipse_MP = false;
    ellipse_P = false;
    RColor = 255;
    GColor = 0;
    BColor = 0;
    polygonVertices = 3;
    polygonStart = false;
    seed = false;
    createGrid();
}

void frame_widget::createGrid()
{
    points.clear();
    destroyPolygon(polygonVertices);
    img = QImage(maxwidth, maxheight, QImage::Format_RGB32);

    for(int i=0; i<maxwidth; i++) {
        for(int j=0;j<maxheight; j++)
            img.setPixel(i, j, qRgb(0, 0, 0));
    }
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
        paint.setPen(QPen(Qt::white));
        for(int i = 0 ; i < min(maxwidth, width()) ; i+=size){
            paint.drawLine(i, 0, i, min(maxheight, height()));
        }
        for(int j = 0 ; j < min(maxheight, height()) ; j+=size){
            paint.drawLine(0, j, min(maxwidth, width()), j);
        }
    }

    if(visibleAxes){
        QBrush qBrush(Qt::gray);
        paint.setBrush(qBrush);

        paint.drawRect((width()/(2*size))*size, 0, size, min(maxheight, height()));
        paint.drawRect(0, (height()/(2*size))*size,  min(maxwidth, width()), size);
    }

    if(circle_P) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = point1;
        int x_center = p.x();
        int y_center = p.y();

        int x, y;
        for(float i=0; i<=1.65; i= i+ (1/(float)radius)) {
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
        emit sendTime(time/1000);
    }

    if(circle_PA) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = point1;
        int x_center = p.x();
        int y_center = p.y();

        int y;
        for(int x=0; x<radius; x++) {
            y = round(sqrt(pow(radius,2) - pow(x,2)));

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
        circle_PA = false;
        int time = timer.nsecsElapsed();
        emit sendTime(time/1000);
    }

    if(circle_MP) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = point1;
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

            if (P <= 0)
                P = P + 2*y + 1;

            else
            {
                x--;
                P = P + 2*y - 2*x + 1;
            }

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
        emit sendTime(time/1000);
    }

    if(circle_BA) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = point1;
        int x_center = p.x();
        int y_center = p.y();

        int x = 0, y = radius;
        int d = 3 - 2 * radius;

        while (y >= x)
        {

            points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(y+ x_center, x+ y_center), currentcol});
            points.append({convertCoord(-y+ x_center, x+ y_center), currentcol});
            points.append({convertCoord(y+ x_center, -x+ y_center), currentcol});
            points.append({convertCoord(-y+ x_center, -x+ y_center), currentcol});

            x++;

            if (d > 0)
            {
                y--;
                d = d + 4 * (x - y) + 10;
            }
            else
                d = d + 4 * x + 6;
        }

        modified = true;
        circle_BA = false;
        int time = timer.nsecsElapsed();
        emit sendTime((time-20)/1000);
    }

    if(ellipse_P) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = point2;
        int x_center = p.x();
        int y_center = p.y();

        int x, y;
        for(float i=0; i<=1.6; i= i+ (1/(float)(major+minor)/2)) {
            x = round(major*cos(i));
            y = round(minor*sin(i));

            points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});
        }

        modified = true;
        ellipse_P = false;
        int time = timer.nsecsElapsed();
        emit sendTime(time/1000);
    }

    if(ellipse_MP) {

        QElapsedTimer timer;
        timer.start();
        QPoint p = point2;
        int x_center = p.x();
        int y_center = p.y();

        float dx, dy, d1, d2, x, y;
        x = 0;
        y = minor;

        d1 = (minor * minor) - (major * major * minor) + (0.25 * major * major);
        dx = 2 * minor * minor * x;
        dy = 2 * major * major * y;

        while (dx < dy)
        {
            points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});

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
        d2 = ((minor * minor) * ((x + 0.5) * (x + 0.5))) + ((major * major) * ((y - 1) * (y - 1))) - (major * major * minor * minor);

        while (y >= 0)
        {

            points.append({convertCoord(x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, y+ y_center), currentcol});
            points.append({convertCoord(x+ x_center, -y+ y_center), currentcol});
            points.append({convertCoord(-x+ x_center, -y+ y_center), currentcol});

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
        ellipse_MP = false;
        int time = timer.nsecsElapsed();
        emit sendTime(time/1000);
    }

    if(modified){
        QPair<QPoint, QColor> p;
        foreach (p , points ){
            paint.setBrush(p.second);
            int x = p.first.x();
            int y = p.first.y();
            QPoint newp((x/size)*size, (y/size)*size);
            paint.drawRect(newp.x(), newp.y(), size, size);

            for(int i=newp.x(); i<newp.x()+size; i++) {
                for(int j=newp.y(); j<newp.y()+size; j++) {
                    QRgb value = qRgb(p.second.red(), p.second.green(), p.second.blue());
                    img.setPixel(i, j, value);
                }
            }
        }
    }
}
void frame_widget::mousePressEvent(QMouseEvent *event)
{
       modified = true;
       lastpoint = event->pos();
       if(lastpoint.x() >= maxwidth || lastpoint.y() >= maxheight)
           return;

       if(polygonStart) {

           if(clickedPoints.size() != polygonVertices)
               clickedPoints.append(convertPixel(lastpoint));

           if(clickedPoints.size() == polygonVertices) {
               QPoint last = convertPixel(lastpoint);
               emit displayPolygonEnd(last.x(), last.y());
               polygonStart = false;
           }

           if(clickedPoints.size() == 1) {
               QPoint last = convertPixel(lastpoint);
               emit displayPolygonStart(last.x(), last.y());
           }
       }

       points.append({lastpoint, currentcol});QPoint last = convertPixel(lastpoint);
       emit sendPress(last.x(), last.y());

       if(seed) {
           points.append({lastpoint, QColor(Qt::white)});
           seed = false;
           QPoint last = convertPixel(lastpoint);
           emit sendSeed(last.x(), last.y());
           seedpoint = convertCoord(last.x(), last.y());
       }
       repaint();
}

QPoint frame_widget::setPoint1()
{
    point1 = convertPixel(lastpoint);
    return point1;
}

QPoint frame_widget::setPoint2()
{
    point2 = convertPixel(lastpoint);
    return point2;
}

void frame_widget::changeCurrentColour(int a, char c)
{
    QColor q(RColor, GColor, BColor);
    if(c == 'R') {
        q.setRed(a);
        RColor = a;
    }
    else if(c == 'G') {
        q.setGreen(a);
        GColor = a;
    }
    else {
        q.setBlue(a);
        BColor = a;
    }
    currentcol = q;
    emit sendColorLebel(RColor, GColor, BColor);
}

void frame_widget::drawLineDDA(QPoint temp1, QPoint temp2)
{
    double x = temp1.x();
    double y = temp1.y();
    double dx = (temp2.x() - temp1.x());
    double dy = (temp2.y() - temp1.y());
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
    }
    modified = true;
}

void frame_widget::drawLineBA(QPoint temp1, QPoint temp2)
{

    QPoint p1 = temp1;
    QPoint p2 = temp2;
    int x1=p1.x();
    int y1=p1.y();

    int x2=p2.x();
    int y2=p2.y();

    int dx=x2-x1;
    int dy=y2-y1;

    int xinc=(dx>0)?1:-1;
    int yinc=(dy>0)?1:-1;

    dx=abs(dx);
    dy=abs(dy);

    if(dx>dy)
    {
        int p=2*(dy)-dx;
        int y=y1;

        for(int x=x1; x!=x2; x+=xinc)
        {
            if (x != x1) points.append({convertCoord(x,y), currentcol});
            if(p>=0)
            {
                y+=yinc;
                p-=2*dx;
            }
            p+=2*dy;
        }
    }
    else
    {
        int p=2*(dx)-dy;
        int x=x1;

        for(int y=y1; y!=y2; y+=yinc)
        {
            if(y != y1) points.append({convertCoord(x,y), currentcol});
            if(p>=0)
            {
                x+=xinc;
                p-=2*(dy);
            }
            p+=2*(dx);
        }
    }
    modified = true;
}

void frame_widget::drawCircle(int x, int y)
{
    radius = y;
    if(x == 0) circle_PA = true;
    else if(x == 2) circle_MP = true;
    else if(x == 3) circle_BA = true;
    else circle_P = true;
    update();
}

void frame_widget::drawEllipse(int r1, int r2, int x)
{
    major = r1;
    minor = r2;
    if(x == 1) ellipse_MP = true;
    else ellipse_P = true;
    update();
}

void frame_widget::createPolygon(int x)
{
    while(clickedPoints.size() != 0)
        clickedPoints.pop_front();
    polygonVertices = x;
    polygonStart = true;
    emit startPolygon();
}

void frame_widget::destroyPolygon(int x)
{
    while(clickedPoints.size() != 0)
        clickedPoints.pop_front();
    polygonStart = false;
    polygonVertices = x;
    emit endPolygon();
}

void frame_widget::drawPolygon()
{
    QElapsedTimer timer;
    timer.start();

    for(int i=0; i<clickedPoints.size(); i++) {
        QPoint tempPoint1 = clickedPoints[i];
        QPoint tempPoint2 = clickedPoints[(i+1)%clickedPoints.size()];
        drawLineDDA(tempPoint1, tempPoint2);
    }

    int time = timer.nsecsElapsed();
    emit sendTime(time/1000);
    update();
}

void frame_widget::setSeed()
{
    seed = true;
}

void frame_widget::boundary_fill()
{
    QRgb edgeColor = qRgb(currentcol.red(), currentcol.green(), currentcol.blue());
    QRgb fillColor = qRgb(255, 255, 255);
    QTextStream out(stdout);

    QElapsedTimer timer;
    timer.start();

    QList<QPoint> q;
    int index = 0;
    q.append(seedpoint);
    int x = seedpoint.x();
    int y = seedpoint.y();

    for(int i=x; i<x+size; i++) {
        for(int j=y; j<y+size; j++) {
            img.setPixel(i, j, fillColor);
        }
    }

    while(q.size() != index) {
        QPoint curr = q[index];
        x = curr.x();
        y = curr.y();

        if(img.pixel(x + size, y) != edgeColor && img.pixel(x + size, y) != fillColor) {
            q.append(QPoint(x + size, y));
            for(int i=x+size; i<x+2*size; i++) {
                for(int j=y; j<y+size; j++) {
                    img.setPixel(i, j, fillColor);
                }
            }
        }
        if(img.pixel(x - size, y) != edgeColor && img.pixel(x - size, y) != fillColor) {
            q.append(QPoint(x - size, y));
            for(int i=x-size; i<x; i++) {
                for(int j=y; j<y+size; j++) {
                    img.setPixel(i, j, fillColor);
                }
            }
        }
        if(img.pixel(x, y + size) != edgeColor && img.pixel(x, y + size) != fillColor) {
            q.append(QPoint(x, y + size));
            for(int i=x; i<x+size; i++) {
                for(int j=y+size; j<y+2*size; j++) {
                    img.setPixel(i, j, fillColor);
                }
            }
        }
        if(img.pixel(x, y - size) != edgeColor && img.pixel(x, y - size) != fillColor) {
            q.append(QPoint(x, y - size));
            for(int i=x; i<x+size; i++) {
                for(int j=y-size; j<y; j++) {
                    img.setPixel(i, j, fillColor);
                }
            }
        }
        index++;
    }

    for(int i=0; i<q.size(); i++) {
        points.append({q[i], fillColor});
    }

    int time = timer.nsecsElapsed();
    emit sendTime(time/1000);
    update();
}

void frame_widget::flood_fill()
{
    QRgb prevColor = qRgb(0, 0, 0);
    QRgb fillColor = qRgb(255, 255, 255);
    QTextStream out(stdout);

    QElapsedTimer timer;
    timer.start();

    QList<QPoint> q;
    int index = 0;
    q.append(seedpoint);
    int x = seedpoint.x();
    int y = seedpoint.y();

    for(int i=x; i<x+size; i++) {
        for(int j=y; j<y+size; j++) {
            img.setPixel(i, j, fillColor);
        }
    }

    while(q.size() != index) {
        QPoint curr = q[index];
        x = curr.x();
        y = curr.y();

        if(img.pixel(x + size, y) == prevColor && img.pixel(x + size, y) != fillColor) {
            q.append(QPoint(x + size, y));
            for(int i=x+size; i<x+2*size; i++) {
                for(int j=y; j<y+size; j++) {
                    img.setPixel(i, j, fillColor);
                }
            }
        }
        if(img.pixel(x - size, y) == prevColor && img.pixel(x - size, y) != fillColor) {
            q.append(QPoint(x - size, y));
            for(int i=x-size; i<x; i++) {
                for(int j=y; j<y+size; j++) {
                    img.setPixel(i, j, fillColor);
                }
            }
        }
        if(img.pixel(x, y + size) == prevColor && img.pixel(x, y + size) != fillColor) {
            q.append(QPoint(x, y + size));
            for(int i=x; i<x+size; i++) {
                for(int j=y+size; j<y+2*size; j++) {
                    img.setPixel(i, j, fillColor);
                }
            }
        }
        if(img.pixel(x, y - size) == prevColor && img.pixel(x, y - size) != fillColor) {
            q.append(QPoint(x, y - size));
            for(int i=x; i<x+size; i++) {
                for(int j=y-size; j<y; j++) {
                    img.setPixel(i, j, fillColor);
                }
            }
        }
        index++;
    }

    for(int i=0; i<q.size(); i++) {
        points.append({q[i], fillColor});
    }

    int time = timer.nsecsElapsed();
    emit sendTime(time/1000);
    update();
}

void frame_widget::scanLine_fill()
{

}
