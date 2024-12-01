#include <iostream>


using namespace std;

class Point{
public:
  double x;
  double y;

  Point(){
    x = 0;
    y = 0;
  }

  Point(double xCoord, double yCoord){
    x=xCoord;
    y=yCoord;
  }

  ~Point(){
  }


  void print(){
    cout << "\n\n\nx: " << x << "  y: " << y;
  }
};



class Rectangle{
public:
  Point bottomLeft;
  Point topRight;
  Point midPoint;
  Point midPointLower;
  Point midPointUpper;

  Point midPointLeft;
  Point midPointRight;

  double bottom;
  double top;
  double left;
  double right;

  double midx;
  double midy;

  Rectangle(Point& bl, Point& tr){
    bottomLeft=bl;
    topRight=tr;
    bottom = bl.y;
    top = tr.y;
    left = bl.x;
    right = tr.x;
    midx = (left + right)/2;
    midy = (bottom + top)/2;
    midPoint = Point(midx, midy);

    midPointLower = Point(midx, bottom);
    midPointUpper = Point(midx, top);

    midPointLeft = Point(left, midy);
    midPointRight = Point(right, midy);
  }

  Rectangle(const Rectangle& r){
    bottomLeft=r.bottomLeft;
    topRight=r.topRight;
    bottom = r.bottomLeft.y;
    top = r.topRight.y;
    left = r.bottomLeft.x;
    right = r.topRight.x;
    midx = (left + right)/2;
    midy = (bottom + top)/2;
    midPoint = Point(midx, midy);

    midPointLower = Point(midx, bottom);
    midPointUpper = Point(midx, top);

    midPointLeft = Point(left, midy);
    midPointRight = Point(right, midy);
  }

  Rectangle(){
    bottomLeft = Point(0,0);
    topRight = bottomLeft;
    bottom = 0;
    top = 0;
    left = 0;
    right = 0;
    midx = 0;
    midy = 0;
    midPoint = Point(midx, midy);

    midPointLower = Point(midx, bottom);
    midPointUpper = Point(midx, top);

    midPointLeft = Point(left, midy);
    midPointRight = Point(right, midy);
  }

  ~Rectangle(){
  }

  void print(){
    cout << "\n\n\n\n\n\nbottomLeft: "; bottomLeft.print(); cout << "  \n\n\ntopRight: "; topRight.print(); cout << "\n\n\n";
  }
};