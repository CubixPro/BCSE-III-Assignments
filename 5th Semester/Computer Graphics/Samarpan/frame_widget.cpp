#include "frame_widget.h"
#include <bits/stdc++.h>
#include <unistd.h>
#include "time.h"
#include <chrono>
#include <QMessageBox>
#include <ctime>
#include <ratio>
#include <QTextStream>

using namespace std;

#define maxHt 500
#define maxWd 500
#define maxVer 250000

vector<pair<int, int>> edgeList;
vector<pair<int,int>> edges;

bool sortDef(pair<int, int> a, pair<int,int> b) {
    if(a.second > b.second) return true;
    else if(a.second == b.second) {
        return (a.first < b.first);
    }
    else return false;
}



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
    size = 5;
    maxwidth = 500;
    maxheight = 500;
    visibleAxes = false;
    this->setMouseTracking(true) ;
    currentcol = QColor(Qt::green);
    circle_MP = false;
    circle_BA = false;
    ellipse_MP = false;
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
        QBrush qBrush(Qt::gray);
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

    if(ellipse_MP) {

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
        ellipse_MP = false;
        int time = timer.nsecsElapsed();
        QTextStream out(stdout);
        out << "Ellipse with MidPoint Algorithm : " << time/1000 << "microsecs\n";
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


   points.append({lastpoint, currentcol});
   QPoint last = convertPixel(lastpoint);
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
    ellipse_MP = true;
    update();
}

void frame_widget::drawLineDDA(QPoint temp1, QPoint temp2)
{
    QRgb fillColor = qRgb(255, 255, 255);
    QRgb edgeColor = qRgb(currentcol.red(), currentcol.green(), currentcol.blue());
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
    for(int i = 0 ; i < steps- 1 ; i++){
        x = x + (inc_x);
        y = y + (inc_y);
        QPoint p0 = convertCoord(round(x), round(y));
        if(img.pixel(p0.x(), p0.y()) != edgeColor)
        {
            points.append({p0, fillColor});
            //usleep(20000);
            //repaint();
        }
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
            points.append({convertCoord(x,y), currentcol});
            edgeList.push_back({x,y});
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
            points.append({convertCoord(x,y), currentcol});
            edgeList.push_back({x, y});
            if(p>=0)
            {
                x+=xinc;
                p-=2*(dy);
            }
            p+=2*(dx);
        }
    }
    points.append({convertCoord(x2,y2), currentcol});
    edgeList.push_back({x2, y2});
    modified = true;
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
    edges.clear();
    emit endPolygon();
}


void frame_widget::drawPolygon()
{
    QElapsedTimer timer;
    timer.start();

    for(int i=0; i<clickedPoints.size(); i++) {
        edgeList.clear();
        QPoint tempPoint1 = clickedPoints[i];
        QPoint tempPoint2 = clickedPoints[(i+1)%clickedPoints.size()];
        drawLineBA(tempPoint1, tempPoint2);
        sort(edgeList.begin(), edgeList.end(), sortDef);
        edges.push_back({edgeList[0].first, edgeList[0].second});
        for(int i=0; i<edgeList.size()-1; i++) {
            if(edgeList[i].second == edgeList[i+1].second) {
                if(edgeList[i].first+1 != edgeList[i+1].first) {
                    edges.push_back({edgeList[i+1].first, edgeList[i+1].second});
                }
            }
            else
                edges.push_back({edgeList[i+1].first, edgeList[i+1].second});
        }
    }

    int time = timer.nsecsElapsed();
    QTextStream out(stdout);
    out << "Drawing the polygon took : " << time/1000 << " microsecs\n";
    update();
}

void frame_widget::setSeed()
{
    seed = true;
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

void frame_widget::drawLine()
{
    drawLineBA(point1, point2);
    update();
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
        //usleep(20000);
        //repaint();
    }

    int time = timer.nsecsElapsed();
    out << "Boundary fill algorithm took : " << abs(time/1000) <<" microsecs\n";
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
        //usleep(20000);
        //repaint();
    }


    int time = timer.nsecsElapsed();
    out << "Flood fill algorithm took : " << abs(time/1000) <<" microsecs\n";
    update();
}

void frame_widget::isMinMax(int i) {
    int prev = (i-1 + clickedPoints.size()) % clickedPoints.size();
    int next = (i+1) % clickedPoints.size();
    if(clickedPoints[i].y() > clickedPoints[prev].y() && clickedPoints[i].y() > clickedPoints[next].y())
        edges.push_back({clickedPoints[i].x(), clickedPoints[i].y()});
    if(clickedPoints[i].y() < clickedPoints[prev].y() && clickedPoints[i].y() < clickedPoints[next].y())
        edges.push_back({clickedPoints[i].x(), clickedPoints[i].y()});
}

void frame_widget::scanLine_fill()
{
    QTextStream out(stdout);
    QElapsedTimer timer;
    timer.start();
    for(int j=0; j<clickedPoints.size(); j++) {
        for(int i=0;i<edges.size();i++) {
            if(edges[i].first == clickedPoints[j].x() && edges[i].second == clickedPoints[j].y()) {
                edges.erase(edges.begin()+ i);
                break;
            }
        }
    }

    for(int i=0; i<clickedPoints.size(); i++)
        isMinMax(i);
    sort(edges.begin(), edges.end(), sortDef);

    for(int i=0; i<edges.size()-1; i=i+2) {
        if(edges[i].second == edges[i+1].second){
            drawLineDDA(QPoint(edges[i].first, edges[i].second), QPoint(edges[i+1].first, edges[i+1].second));
        }
        else i--;
    }
    int time = timer.nsecsElapsed();
    out << "Scan Line fill algorithm took : " << abs(time/1000) <<" microsecs\n";
    update();
}

void frame_widget::translate(int x, int y)
{
    for(int i=0; i<clickedPoints.size(); i++) {
        clickedPoints[i].setX(clickedPoints[i].x() + x);
        clickedPoints[i].setY(clickedPoints[i].y() + y);
    }
    drawPolygon();
}

void frame_widget::scale(double x, double y)
{
    int center_x, center_y;
    QPoint p = convertPixel(lastpoint);
    center_x = p.x();
    center_y = p.y();

    for(int i=0; i<clickedPoints.size(); i++) {
        clickedPoints[i].setX(round(center_x + (clickedPoints[i].x() - center_x)* x));
        clickedPoints[i].setY(round(center_y + (clickedPoints[i].y() - center_y)* y));
    }
    drawPolygon();
}

void frame_widget::rotate(int x)
{
    int center_x, center_y;
    QPoint p = convertPixel(lastpoint);
    center_x = p.x();
    center_y = p.y();

    double angle = (x * 3.14)/180;
    QTextStream out(stdout);

    for(int i=0; i<clickedPoints.size(); i++) {
        int tempx = clickedPoints[i].x();
        int tempy = clickedPoints[i].y();

        clickedPoints[i].setX(round(center_x + ((tempx - center_x) * cos(angle)) - ((tempy - center_y) * sin(angle))));
        clickedPoints[i].setY(round(center_y + ((tempx - center_x) * sin(angle)) + ((tempy - center_y) * cos(angle))));
    }
    drawPolygon();
}

void frame_widget::shear(double x, double y)
{
    int center_x, center_y;
    QPoint p = convertPixel(lastpoint);
    center_x = p.x();
    center_y = p.y();

    for(int i=0; i<clickedPoints.size(); i++) {
        int tempx = clickedPoints[i].x();
        int tempy = clickedPoints[i].y();

        clickedPoints[i].setX(round(tempx + (tempy - center_y)* x));
        clickedPoints[i].setY(round(tempy + (tempx - center_x)* y));
    }
    drawPolygon();
}


void frame_widget::reflect()
{
    double dx = point1.x() - point2.x();
    double dy = point1.y() - point2.y();

    double a = -dy;
    double b = dx;
    double c = point1.x()*dy - point1.y()*dx;

    for(int i=0; i<clickedPoints.size(); i++) {
        double tempx = clickedPoints[i].x();
        double tempy = clickedPoints[i].y();

        clickedPoints[i].setX(round(tempx - (2*a*(a*tempx + b*tempy + c))/(a*a + b*b)));
        clickedPoints[i].setY(round(tempy - (2*b*(a*tempx + b*tempy + c))/(a*a + b*b)));
    }
    drawPolygon();
}





