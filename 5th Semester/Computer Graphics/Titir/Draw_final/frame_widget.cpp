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

void frame_widget::drawDelayLine(int x1, int y1, int x2, int y2, int delay)
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
                    //usleep(90000);
                    usleep(delay);
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
                   //usleep(90000);
                    usleep(delay);
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

vector<vector<int>> frame_widget::matMult3_3(vector<vector<int> > x, vector<vector<int> > y)
{
    vector<vector<int>> ans(x.size());
    for(int i = 0 ; i < x.size() ; i++){
        for(int j = 0 ; j < y[i].size() ; j++){
            int sum = 0;
            for(int k = 0 ; k < x[i].size() ; k++){
                sum += x[i][k] * y[k][j];
            }
            ans[i][j] = sum;
        }
    }
    return ans;

}

void frame_widget::translate(int tx, int ty)
{
    vector<vector<int>> mat(3);
    mat[0] = {1, 0, tx * size};
    mat[1] = {0, 1, ty * size};
    mat[2] = {0, 0, 1};

    for(int i = 0 ; i < polygon.size() ; i++){

        vector<int> c = {polygon[i].x(), polygon[i].y(), 1};
        vector<int> newc = matMult3_1(mat, c);

        polygon[i].setX(newc[0]);
        polygon[i].setY(newc[1]);

        points.append({polygon[i], currentcol});

        //points.append({temp, currentcol});

    }
    modified = true;
    drawPolygon();
    repaint();
}

void frame_widget::scale(int sx, int sy)
{
    vector<vector<int>> mat = {{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}};

    for(int i = 0 ; i < polygon.size() ; i++){
        vector<int> c = {pivot.x() - polygon[i].x(), pivot.y() - polygon[i].y(), 1};
        vector<int> newc = matMult3_1(mat, c);
        polygon[i].setX(pivot.x() - newc[0]);
        polygon[i].setY(pivot.y() - newc[1]);
        points.append({polygon[i], currentcol});
    }
    modified = true;
    drawPolygon();
    repaint();
}

void frame_widget::rotate(int angle, int piv_x, int piv_y)
{
   double dang = (double)((angle * 3.14)/180.0);
   double sinang = sin(dang);
   double cosang = cos(dang);

   vector<vector<double>> mat = {{cosang, -sinang, 0}, {sinang, cosang, 0}, {0, 0, 1}};

   for(int i = 0 ; i < polygon.size() ; i++){
       vector<double> c = {piv_x - (double)polygon[i].x(), piv_y - (double)polygon[i].y(), 1.0};
       vector<double> newc = matMult3_1D(mat, c);

       polygon[i].setX( -(int)newc[0] + piv_x);
       polygon[i].setY( -(int)newc[1] + piv_y);

       points.append({polygon[i], currentcol});

   }
   modified = true;
   drawPolygon();
   repaint();

}

void frame_widget::clipLine(int x1, int y1, int x2, int y2, int xmin, int xmax, int ymin, int ymax, bool flag)
{
    double t1 = 0.0, t2 = 1.0;
    int dx = x2 - x1;
    int dy = y2 - y1;

    int i;
    double t;

    double p[4];
    double q[4];

    p[0] = -dx;
    q[0] = x1 - xmin;

    p[1] = dx;
    q[1] = xmax - x1;

    p[2] = -dy;
    q[2] = y1 - ymin;

    p[3] = dy;
    q[3] = ymax - y1;

    for(i = 0 ; i < 4 ; i++){
        if(p[i]==0 && q[i]<0)//line is parallel and outside
        {
                    if(flag)
                        drawDelayLine(x1, y1, x2, y2, 0);
                    in = false;
                    return ;
        }
                if(p[i]<0.0)
                {
                   t=q[i]/p[i];
                    if(t>t1)
                        {
                          t1=t;
                        }
                }
                if(p[i]>0.0)
                {
                    t=q[i]/p[i];
                    if(t<t2)
                        {t2=t;}
                }

    }
    if(t1<t2)
        {
            double xt1, yt1, xt2, yt2;
             xt1=x1+t1*(x2-x1);
             yt1=y1+t1*(y2-y1);
             xt2=x1+t2*(x2-x1);
             yt2=y1+t2*(y2-y1);
                srand(time(0));
                if(flag){
             QColor temp = currentcol;
             drawDelayLine(x1, y1, xt1, yt1, 0);
             currentcol = QColor(rand()%255, rand()%255, rand()%255);
             drawDelayLine(xt1, yt1, xt2, yt2, 0);
             currentcol = temp;
             drawDelayLine(xt2, yt2, x2, y2, 0);
                }
             endp1 = QPoint(xt1, yt1);
             endp2 = QPoint(xt2, yt2);
                in = true;;
             update();
    }
    else{
        if(flag)
            drawDelayLine(x1, y1, x2, y2, 0);
        in = false;;
        return;
    }
}

void frame_widget::drawPolygonCoord(QVector<QPoint> poly, QColor q)
{
    QColor temp = currentcol;
    currentcol = q;
   for(int i = 0 ; i < poly.size() ; i++){
       point1 = poly[i];
       point2 = poly[(i + 1)%poly.size()];

       points.push_back({convertCoord(point1.x(), point1.y()), q});
        points.push_back({convertCoord(point2.x(), point2.y()), q});


       drawLineBA();
   }
   modified = true;
   currentcol = temp;
}

void frame_widget::clipPolygon()
{
   QVector<QPoint> cPolygon;

   int len = polygon.size();
   for(int i = 0 ; i < polygon.size() ; i++){
       point1 = convertPixel(polygon[i]);
       point2 = convertPixel(polygon[(i + 1)%len]);

       clip(true);
       if(in){
           if(cPolygon.size() == 0){
               cPolygon.append(endp1);

           }
           else if(cPolygon[cPolygon.size() - 1] != endp1){
               cPolygon.append(endp1);
           }

           cPolygon.append(endp2);

       }
   }

  //polygon = cPolygon;
  //drawPolygon();
   //currentcol = Qt::white;
   drawPolygonCoord(cPolygon, QColor(rand()%255, rand()%255, rand()%255));
  repaint();
}



void frame_widget::reflect()
{
    QPoint p1 = cPoint1; //convertCoord(point1.x(), point1.y());
    QPoint p2 = cPoint2; //convertCoord(point2.x(), point2.y());
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();

    double a = -dy;
    double b = dx;
    double c = (p2.x()*p1.y() - p1.x() * p2.y())/(p2.x() - p1.x()); //p1.x() * dy - p1.y() * dx;
     double m = dy/dx;

    for(int i = 0 ; i < polygon.size() ; i++){

        double d = (polygon[i].x() + (polygon[i].y() - c) * m)/(1 + m * m);
        polygon[i].setX(2 * d - polygon[i].x());
        polygon[i].setY(2 * d * m - polygon[i].y() + 2 * c);

        points.append({polygon[i], currentcol});

    }
    modified = true;
    drawPolygon();
    repaint();
}

void frame_widget::clip(bool flag)
{
   int xmin = min(pmax1.x(), pmax2.x());
   int xmax  = max(pmax1.x(), pmax2.x());

   int ymin = min(pmax2.y(), pmax1.y());
   int ymax = max(pmax1.y(), pmax2.y());



   clipLine(point1.x(), point1.y(), point2.x(), point2.y(), xmin, xmax, ymin, ymax, flag);

}



vector<int> frame_widget::matMult3_1(vector<vector<int> > mat, vector<int> coords)
{
        if(mat[0].size() == coords.size()){
            vector<int> ans(mat.size());
            for(int i = 0 ; i < (int)mat.size() ; i++){
                int sum = 0;
                for(int j = 0 ; j < (int)mat[i].size() ; j++){
                    sum += mat[i][j] * coords[j];
                }
                ans[i] = sum;
            }
            return ans;
        }
        else{
            vector<int> f(1);
            return f;
        }
}

vector<double> frame_widget::matMult3_1D(vector<vector<double> > mat, vector<double> coords)
{
          vector<double> ans(mat.size());
            for(int i = 0 ; i < (int)mat.size() ; i++){
                int sum = 0;
                for(int j = 0 ; j < (int)mat[i].size() ; j++){
                    sum += mat[i][j] * coords[j];
                }
                ans[i] = sum;
            }
            return ans;

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
    pivot = convertCoord(0, 0);
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
            if(sortededges[j].p1.y() > sortededges[j + 1].p1.y())
            {
                Edge temp = sortededges[j];
                sortededges[j] = sortededges[j + 1];
                sortededges[j + 1] = temp;
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
            drawDelayLine(renderlist[i], scanline, renderlist[i + 1], scanline, 90000);
        }
    }


    QColor temp = currentcol;
    currentcol = polygoncolour;
    //polygoncolour = currentcol;
    //currentcol = temp;
    for(int i = 0 ; i < polygon.size(); i++){
        points.append({polygon[i], currentcol});
    }
    drawPolygon();
    currentcol = temp;



}

void frame_widget::settx(int x)
{
    tx = x;

}

void frame_widget::setty(int y)
{
    ty = y;

}

void frame_widget::setAngle(int ang)
{
    angle = ang;

}

void frame_widget::ontranslate()
{
    translate(tx, ty);

}

void frame_widget::setPivotPoint()
{
    pivot = lastpoint;


}

void frame_widget::onscale()
{
    scale(tx, ty);

}

void frame_widget::onrotate()
{
    rotate(angle, pivot.x(), pivot.y());

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
    cPoint1 = lastpoint;
    return (point1);

}

QPoint frame_widget::setPoint2()
{
    point2 = convertPixel(lastpoint);
    cPoint2 = lastpoint;
    return point2;

}

void frame_widget::setBoundaryPoint1()
{
    pmax1 = convertPixel(lastpoint);

}

void frame_widget::setBoundaryPoint2()
{
    pmax2 = convertPixel(lastpoint);
    int xmax = max(pmax1.x(), pmax2.x());
    int xmin = min(pmax1.x(), pmax2.x());

    int ymax = max(pmax1.y(), pmax2.y());
    int ymin = min(pmax1.y(), pmax2.y());

    QPoint temp1 = point1;
    QPoint temp2 = point2;



    point1 = QPoint(xmax, ymin);
    points.append({convertCoord(point1.x(), point1.y()), currentcol});
    point2 = QPoint(xmax, ymax);
    points.append({convertCoord(point2.x(), point2.y()), currentcol});
    drawLineBA();

    point2 = QPoint(xmin, ymin);
    points.append({convertCoord(point2.x(), point2.y()), currentcol});
    drawLineBA();

    point1 = QPoint(xmin, ymax);
    points.append({convertCoord(point1.x(), point1.y()), currentcol});
    drawLineBA();

    point2 = QPoint(xmax, ymax);
    points.append({convertCoord(point2.x(), point2.y()), currentcol});
    drawLineBA();

    point1 = temp1;
    point2 = temp2;

   modified = true;

    repaint();

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
    polygoncolour = currentcol;
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

