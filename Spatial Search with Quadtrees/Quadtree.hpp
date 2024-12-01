

Rectangle Find_Minimal_Covering_Rectangle(const vector<Point>& points){

  double mostDown = points.front().y;
  double mostLeft = points.front().x;

  double mostUp = mostDown;
  double mostRight = mostLeft;

  double x,y;
  for(Point p: points){
    x = p.x;
    y = p.y;
    if(y < mostDown){ mostDown = y;}
    else if(y> mostUp){ mostUp = y;}
    if(x < mostLeft){ mostLeft = x;}
    else if(x> mostRight){ mostRight = x;}
  }
  Point rootBottomLeft = Point(mostLeft,mostDown);
  Point rootTopRight = Point(mostRight,mostUp);

  return Rectangle(rootBottomLeft, rootTopRight);
}



bool is_in_Rectangle(Point& p,Rectangle& r){
  bool answer = ( (r.left <= p.x) && (r.bottom <= p.y) && (r.right >= p.x) && (r.top >= p.y) );
  return answer;
}

int Count_Points_in_Rectangle(Rectangle R, vector<Point> pointCloud){
  int count = 0;
  for(Point p : pointCloud){
     count += is_in_Rectangle(p,R);
   }
  return count;
}


vector<Point> cut_points(Rectangle& smallerRectangle, vector<Point> largerPointCloud){
  for(auto p = largerPointCloud.begin(); p!= largerPointCloud.end(); ){
    if(!is_in_Rectangle(*p,smallerRectangle)){
      largerPointCloud.erase(p);
    }else{
      ++p;
    }
  }
  return largerPointCloud;
}


bool infringes(Rectangle& intruder, Rectangle& defender){
  bool answer = ( (intruder.right >= defender.left) && (intruder.left <= defender.right) && (intruder.top >= defender.bottom) && (intruder.bottom <= defender.top)  );
  return answer;
}


auto Quadtree_Writer = sf::MplWriter<Point, Rectangle>("Quadtree_Plot.py");


void printPointVector(vector<Point> points){
  for(Point p : points){
    p.print();
  }
}


class QuadTree{
  public:

    int bucketCapacity;

    bool leaf = 0;

    vector<Point> innerPoints;

    Rectangle root;

    vector<QuadTree> children;

    Point midpoint;


    // Default constructor
    QuadTree() : bucketCapacity(0), leaf(false), root(Rectangle()), midpoint(Point()) {}

    // Constructor
    QuadTree(const vector<Point>& points,const int bc, const Rectangle& rootRectangle){



      bucketCapacity = bc;
      innerPoints = points;
      root = rootRectangle;

      midpoint = root.midPoint;

      Rectangle r1 = Rectangle(root.midPointLeft, root.midPointUpper);
      Rectangle r2 = Rectangle(root.midPoint, root.topRight);
      Rectangle r3 = Rectangle(root.midPointLower, root.midPointRight);
      Rectangle r4 = Rectangle(root.bottomLeft, root.midPoint);

      if(points.size() > bc){ //Else, declare as leaf

        //Instantiate children
        vector<Point> pointsChild1 = cut_points(r1, points);
        vector<Point> pointsChild2 = cut_points(r2, points);
        vector<Point> pointsChild3 = cut_points(r3, points);
        vector<Point> pointsChild4 = cut_points(r4, points);

        children = vector<QuadTree>(4);
        children[0] = QuadTree(pointsChild1, bc, r1);
        children[1] = QuadTree(pointsChild2, bc, r2);
        children[2] = QuadTree(pointsChild3, bc, r3);
        children[3] = QuadTree(pointsChild4, bc, r4);

      }else{
        leaf = 1;
        // Print points only if its a leaf
        Quadtree_Writer << points;
        Quadtree_Writer << rootRectangle;
      }
    }

    // Copy Constructor
    QuadTree(const QuadTree& qt) {
       bucketCapacity = qt.bucketCapacity;
       innerPoints = qt.innerPoints;
       root = qt.root;
       midpoint = qt.midpoint;
       leaf = qt.leaf;

       if (!qt.leaf) {
          children = vector<QuadTree>(qt.children.size());
          for (size_t i = 0; i < qt.children.size(); i++) {
             children[i] = QuadTree(qt.children[i]);
          }
       }
    }

    // Destructor
    ~QuadTree(){
    }

    vector<Point> query(Rectangle& r, vector<Point>& data){
        if(!leaf){
        vector<Point> containingPoints;
            for(int child = 0; child<4; child++){
            if(infringes(r, children[child].root ) ){

                vector<Point> collection2 = children[child].query(r, data);
                containingPoints.insert(containingPoints.end(), collection2.begin(), collection2.end() );
            }
            }
        return containingPoints;
        }else{
            return cut_points(r, innerPoints);
        }
    }
};