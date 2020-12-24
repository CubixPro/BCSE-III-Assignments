#include "frame_widget.h"
#include <bits/stdc++.h>
#include "time.h"
#include <chrono>
#include <QMessageBox>
#include <ctime>
#include <ratio>
#include <QTextStream>

vector<pair<int, int>> myedgeList;
vector<pair<int, int>> edges;
bool sortDef(pair<int, int> a, pair<int, int> b)
{
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

void frame_widget::drawDelayLine(int x1, int y1, int x2, int y2)
{
         int dx=x2-x1;
        int dy=y2-y1;



        int xinc=(dx>0)?1:-1;
        int yinc=(dy>0)?1:-1;

        dx=abs(dx);
        dy=abs(dy);

        //Case for gentle slope
        if(dx>dy)
        {
            int p=2*(dy)-dx;
            int y=y1;

            for(int x=x1; x!=x2; x+=xinc)

            {
                if(x != x1)

               {     points.append({convertCoord(x,y), currentcol});
                    //myedgeList.push_back({x, y});
                    modified = true;
                    usleep(90000);
                    repaint();


                }
                if(p>=0)
                {
                    y+=yinc;
                    p-=2*dx;
                }
                p+=2*dy;
            }
        }
        //Case for steep slope
        else
        {
            int p=2*(dx)-dy;
            int x=x1;

            for(int y=y1; y!=y2; y+=yinc)
            {
                if(y != y1)
                {

                    points.append({convertCoord(x,y), currentcol});
                    modified = true;
                    usleep(90000);
                    repaint();
                    myedgeList.push_back({x, y});

                        }
                if(p>=0)
                {
                    x+=xinc;
                    p-=2*(dy);
                }
                p+=2*(dx);
            }
        }



}

frame_widget::frame_widget(QWidget *parent):
    QFrame(parent)
{
    grid = false;
    modified = false;
    size = 10;
    maxwidth = 500;
    maxheight = 500;
    visibleAxes = false;
    this->setMouseTracking(true) ;
    currentcol = QColor(Qt::red);
    line_DDA = false;
    line_BA = false;
    circle = false;
    radius = 5;
    ellipse = false;
    circleDrawMethod = 0;
    rx = ry = 5;
    fill = false;
    seednow = false;
    delay = false;

}




void frame_widget::createGrid()
{
    //grid = true;
    //img = QImage(width(), height(), QImage::Format_RGB32);
    points.clear();
    clearPolygon();
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
        std::cout << "DDA : ";

        std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1).count() << '\n';
        elapsedda = (time2 - time1).count();
    }
    if(line_BA){

        //Bresenham Algorithm for Line Drawing
        auto time1 = std::chrono::high_resolution_clock::now();
        QPoint p1 = point1;
        QPoint p2 = point2;
        //QMessageBox msgbox;

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

        //Case for gentle slope
        if(dx>dy)
        {
            int p=2*(dy)-dx;
            int y=y1;

            for(int x=x1; x!=x2; x+=xinc)

            {
                if(x != x1)

               {     points.append({convertCoord(x,y), currentcol});
                    myedgeList.push_back({x, y});


                }
                if(p>=0)
                {
                    y+=yinc;
                    p-=2*dx;
                }
                p+=2*dy;
            }
        }
        //Case for steep slope
        else
        {
            int p=2*(dx)-dy;
            int x=x1;

            for(int y=y1; y!=y2; y+=yinc)
            {
                if(y != y1)
                {

                    points.append({convertCoord(x,y), currentcol});
                    myedgeList.push_back({x, y});

                        }
                if(p>=0)
                {
                    x+=xinc;
                    p-=2*(dy);
                }
                p+=2*(dx);
            }
        }


        modified = true;
        myedgeList.push_back({point2.x(), point2.y()});
        line_BA = false;
        auto time2 = std::chrono::high_resolution_clock::now();
        std::cout << "BA : ";
        //std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1).count() << '\n';
        elapsedba = (time2 - time1).count();
    }
    if(circle){
        auto time1 = std::chrono::high_resolution_clock::now();

        if(circleDrawMethod == 0){//draw using midpoint method
        int x_centre = point1.x();
        int y_centre = point1.y();
        int r = radius;
        int x = r, y = 0;

            // Printing the initial point on the axes
            // after translation
            if (r > 0)
            {
                points.append({convertCoord(x + x_centre, -y + y_centre), currentcol});
                points.append({convertCoord(y + x_centre, x + y_centre), currentcol});
                points.append({convertCoord(-y + x_centre, -x + y_centre), currentcol});
                points.append({convertCoord(-x + x_centre, y_centre), currentcol});
            }

            // Initialising the value of P
            int P = 1 - r;
            while (x > y)
            {
                y++;

                // Mid-point is inside or on the perimeter
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

                // Printing the generated point and its reflection
                // in the other octants after translation
                points.append({convertCoord(x + x_centre, y + y_centre), currentcol});
                points.append({convertCoord(-x + x_centre, y + y_centre), currentcol});
                points.append({convertCoord(x + x_centre, -y + y_centre), currentcol});
                points.append({convertCoord(-x + x_centre, -y + y_centre), currentcol});

                // If the generated point is on the line x = y then
                // the perimeter points have already been printed
                if (x != y)
                {
                points.append({convertCoord(y + x_centre, x + y_centre), currentcol});
                points.append({convertCoord(-y + x_centre, x + y_centre), currentcol});
                points.append({convertCoord(y + x_centre, -x + y_centre), currentcol});
                points.append({convertCoord(-y + x_centre, -x + y_centre), currentcol});
                }
            }
        }
        else if(circleDrawMethod == 1){//draw using breshenham
            int xc = point1.x();
            int yc = point1.y();
            int x = 0, y = radius;
            int d = 3 - 2 * radius;
                points.append({convertCoord(xc + x, yc + y), currentcol});
                points.append({convertCoord(xc - x, yc + y), currentcol});
                points.append({convertCoord(xc + x, yc - y), currentcol});
                points.append({convertCoord(xc - x, yc - y), currentcol});
                points.append({convertCoord(xc + y, yc + x), currentcol});
                points.append({convertCoord(xc - y, yc + x), currentcol});
                points.append({convertCoord(xc + y, yc - x), currentcol});
                points.append({convertCoord(xc - y, yc - x), currentcol});

            while(y >= x){
                x++;
                if(d > 0){
                    y--;
                    d = d + 4 * (x - y) + 10;
                }
                else
                {
                    d = d + 4 * x + 6;
                }
                points.append({convertCoord(xc + x, yc + y), currentcol});
                points.append({convertCoord(xc - x, yc + y), currentcol});
                points.append({convertCoord(xc + x, yc - y), currentcol});
                points.append({convertCoord(xc - x, yc - y), currentcol});
                points.append({convertCoord(xc + y, yc + x), currentcol});
                points.append({convertCoord(xc - y, yc + x), currentcol});
                points.append({convertCoord(xc + y, yc - x), currentcol});
                points.append({convertCoord(xc - y, yc - x), currentcol});




            }

           }
        else if(circleDrawMethod == 2){//draw using cartesian coordiantes
            int xc = point1.x();
            int yc = point1.y();


            for(int x = 0 ; x <= radius/sqrt(2)  ; x++){
                int y = round(sqrt(radius * radius - x * x));
                points.append({convertCoord(xc + x, yc + y), currentcol});
                points.append({convertCoord(xc + x, yc - y), currentcol});
                points.append({convertCoord(xc - x, yc - y), currentcol});
                points.append({convertCoord(xc - x, yc + y), currentcol});
                points.append({convertCoord(xc + y, yc + x), currentcol});
                points.append({convertCoord(xc + y, yc - x), currentcol});
                points.append({convertCoord(xc - y, yc - x), currentcol});
                points.append({convertCoord(xc - y, yc + x), currentcol});

            }
        }
        else if(circleDrawMethod == 3){//draw using polar coordinates
                double pi = 2*acos(0.0);
                int xc = point1.x();
                int yc = point1.y();
                for(double i = 0 ; i <= pi/4  + 0.1  ; i += 1.0/(float)radius)
                {
                    double y = round(radius * cos(i));
                    double x = round(radius * sin(i));
                    points.append({convertCoord(xc + x, yc + y), currentcol});
                    points.append({convertCoord(xc + x, yc - y), currentcol});
                    points.append({convertCoord(xc - x, yc - y), currentcol});
                    points.append({convertCoord(xc - x, yc + y), currentcol});
                    points.append({convertCoord(xc + y, yc + x), currentcol});
                    points.append({convertCoord(xc + y, yc - x), currentcol});
                    points.append({convertCoord(xc - y, yc - x), currentcol});
                    points.append({convertCoord(xc - y, yc + x), currentcol});

                }
           }
            auto time2 = std::chrono::high_resolution_clock::now();
            elapsedcircle = (time2 - time1).count();

            modified = true;
            circle = false;

    }
    if(ellipse){
         auto time1 = std::chrono::high_resolution_clock::now();

        int x_centre = point1.x();
        int y_centre = point1.y();

        int x = 0;
        int y = ry;

        int rx2=rx*rx;
        int ry2=ry*ry;
        int tworx2=2*rx2;
        int twory2=2*ry2;
        int px=0.0;
        int py=tworx2*y;

        int p1=ry2-rx2*ry+(0.25)*rx2; //Initial value of decision parameter


        while(px<py)
        {


            points.append({convertCoord(x_centre + x, y_centre + y), currentcol});
            points.append({convertCoord(x_centre - x, y_centre + y), currentcol});
            points.append({convertCoord(x_centre - x, y_centre - y), currentcol});
            points.append({convertCoord(x_centre + x, y_centre - y), currentcol});

            x++;
            px+=twory2;

            if(p1>=0)
            {
                y--;
                py-=tworx2;
                p1=p1+ry2+px-py;

            }
            else
            {
                p1=p1+ry2+px;
            }
        }

        //For second region
        p1=ry2*((double)x+0.5)*((double)x+0.5)+rx2*(y-1)*(y-1)-rx2*ry2; //Initial value of decision paramemter


        while(y>=0)
        {

            points.append({convertCoord(x_centre + x, y_centre + y), currentcol});
            points.append({convertCoord(x_centre - x, y_centre + y), currentcol});
            points.append({convertCoord(x_centre - x, y_centre - y), currentcol});
            points.append({convertCoord(x_centre + x, y_centre - y), currentcol});

            y--;
            py-=tworx2;
            if(p1<=0)
            {
                x++;
                px+=twory2;
                p1=p1+rx2-py+px;

            }
            else
            {
                p1=p1+rx2-py;
            }

        }
    auto time2 = std::chrono::high_resolution_clock::now();
    elapsedellipse = (time2 - time1).count();
        modified = true;
        ellipse = false;

    }
    if(modified){

        QPair<QPoint, QColor> p;
        foreach (p   , points ){
            paint.setBrush(p.second);
            int x = p.first.x();
            int y = p.first.y();
            QPoint newp((x/size)*size, (y/size)*size);
            paint.drawRect(newp.x(), newp.y(), size,  size);
            if(delay == true){
               // sleep(1);
            }
        }
        delay = false;
    }


}
/*void frame_widget::flood_fill_until(int x1, int y1, QColor q1){


}*/


void frame_widget::setBoundaryColour(){
    boundary_fill_colour = currentcol;
}

void frame_widget::clearPolygon()
{
    polygon.clear();
    sortededges.clear();
}

void frame_widget::scanLineFill()
{
    for(int i = 0 ; i < sortededges.size() ; i++){
        for(int j = 0 ; j < sortededges.size() - 1 ; j++){
            if(sortededges[j].p1.y() > sortededges[j + 1].p2.y())
            {
                Edge temp = sortededges[i];
                sortededges[i] = sortededges[i + 1];
                sortededges[i + 1] = temp;
            }
        }
    }//sort the edges according to y in ascending order

    int scanlineend = sortededges[0].p2.y();
    for(int i = 1 ; i < sortededges.size() ; i++){
        if(scanlineend < sortededges[i].p2.y()){
            scanlineend = sortededges[i].p2.y();
        }
    }//find the largest y coordinate

    int scanline = sortededges[0].p1.y();

    vector<int> renderlist;

    for(; scanline <= scanlineend ; scanline ++){
        renderlist.clear();
        for(int i = 0 ; i < sortededges.size() ; i++){
            if(scanline == sortededges[i].p1.y())//intersects smaller vertice
            {
              if(scanline == sortededges[i].p2.y()){
                  sortededges[i].deactivate();
                  renderlist.push_back(round(sortededges[i].currX));
              }
              else{
                  sortededges[i].activate();
              }
            }

            if(scanline == sortededges[i].p2.y())//intersects the bigger vertice
            {
                sortededges[i].deactivate();
                renderlist.push_back((round(sortededges[i].currX)));
            }

            if(scanline > sortededges[i].p1.y() && scanline < sortededges[i].p2.y()){
                sortededges[i].update();
                renderlist.push_back(round( sortededges[i].currX));
            }
        }

        int swaptmp;

        for (int i = 0; i < (int)renderlist.size(); i++)
                    for (int j = 0; j < (int)renderlist.size() - 1; j++)
                    {
                        if (renderlist[j] > renderlist[j + 1])
                        {
                            swaptmp = renderlist[j];
                            renderlist[j] = renderlist[j + 1];
                            renderlist[j + 1] = swaptmp;
                        }

                    }

        for(int i = 0 ; i < (int)renderlist.size() ; i+= 2){
            //point1 = QPoint(renderlist[i], scanline);
            //point2 = QPoint(renderlist[i + 1], scanline);
            //drawLineBA();
            //usleep(900000);
            drawDelayLine(renderlist[i], scanline, renderlist[i + 1], scanline);
        }
    }






}

void frame_widget::mousePressEvent(QMouseEvent *event)
{
    if(seednow){
        QPixmap qPix  = QWidget::grab();
        QImage image(qPix.toImage());
        QPoint pixelval = convertCoord(seed.x(), seed.y());
        QColor q = image.pixel(pixelval.x() + size - 1, pixelval.y() + size - 1);
        seed_colour = q;
        seed = convertPixel(event->pos());
        fill_colour = currentcol;
        emit sendSeed(seed.x(), seed.y());
        seednow = false;
        return;
    }
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
    repaint();

}
void frame_widget::drawLineBA(){

    line_BA = true;
    repaint();
    QPixmap qPix  = QWidget::grab();

    QImage image(qPix.toImage());

    QColor q = image.pixel(305, 305);
    qDebug() << q.name();
    //repaint();
}

void frame_widget::drawCircle()
{
   circle = true;
   update();
}

void frame_widget::changeRadius(int size)
{
    radius = size;
}

void frame_widget::setCircleDraw(int val)
{

    circleDrawMethod = val;
}

void frame_widget::drawEllipse()
{
    ellipse = true;
    update();
}

void frame_widget::setrx(int val)
{
    rx = val;
}

void frame_widget::setry(int val)
{
    ry = val;
}

void frame_widget::floodFill()
{
    startfloodFill();
    delay = true;
    modified = true;
    update();
}
void frame_widget::boundaryFill(){
    startboundaryFill();
    modified = true;
    update();

}

void frame_widget::startboundaryFill(){
    QPoint temp(seed.x(), seed.y());
    QPixmap qPix  = QWidget::grab();
    QImage image(qPix.toImage());
    QPoint pixelval = convertCoord(seed.x(), seed.y());
   if(pixelval.x() < 0 || pixelval.x() > width() || pixelval.x() < 0 || pixelval.y() > height())
    {
        return;
    }
    QColor q = image.pixel(pixelval.x() + size - 1, pixelval.y() + size - 1);

    if(q != boundary_fill_colour && q != fill_colour){
        points.append({pixelval, fill_colour});
        modified = true;
        usleep(90000);
        repaint();
        seed = QPoint(temp.x() + 1, temp.y());
        startboundaryFill();
        seed = QPoint(temp.x() - 1, temp.y());
        startboundaryFill();
        seed = QPoint(temp.x(), temp.y() - 1);
        startboundaryFill();
        seed = QPoint(temp.x(), temp.y() + 1);
        startboundaryFill();
   }

}

void frame_widget::addPointToPolygon()
{
    polygon.push_back(lastpoint);

}

void frame_widget::drawPolygon(){
    for(int i = 0 ; i < polygon.size() ; i++){
        point1 = convertPixel(polygon[i]);
        point2 = convertPixel(polygon[(i + 1 )% polygon.size()]);
        drawLineBA();
        if(i == (polygon.size() - 1))
        {
            //continue;
        }
        if(point1.y() < point2.y()){
            sortededges.push_back(Edge(point1, point2));
        }
        else{
            sortededges.push_back(Edge(point2, point1));
        }
    }
}

void frame_widget::startfloodFill(){
    QPoint temp(seed.x(), seed.y());
    QPixmap qPix  = QWidget::grab();
    QImage image(qPix.toImage());
    QPoint pixelval = convertCoord(seed.x(), seed.y());
    if(pixelval.x() < 0 && pixelval.x() > width() && pixelval.y() < 0 && pixelval.y() > height())
    {
        return;
    }
    QColor q = image.pixel(pixelval.x() + size - 1, pixelval.y() + size - 1);

    if(q != seed_colour){
        return;
    }
    points.append({pixelval, fill_colour});
    modified = true;
    usleep(90000);
    repaint();
    seed = QPoint(temp.x() + 1, temp.y());
    qDebug() << seed ;
    startfloodFill();
    seed = QPoint(temp.x() - 1, temp.y());
    qDebug() << seed ;
    startfloodFill();
    seed = QPoint(temp.x() , temp.y() + 1);
    qDebug() << seed ;
    startfloodFill();
    seed = QPoint(temp.x(), temp.y() - 1);
    qDebug() << seed ;
    startfloodFill();

}

void frame_widget::setSeedColour()
{
    seednow = true;
   //seed = convertPixel(lastpoint);
   //fill_colour = currentcol;
}

