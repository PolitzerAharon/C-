#include "utilities/mpl_writer.hpp"
#include "utilities/point_reader.hpp"
#include "utilities/timer.hpp"
#include "utilities/random_points.hpp"
#include "Geometry.hpp"
#include "Quadtree.hpp"

using namespace std;



int main(int argc, char* argv[]){

  sf::Timer timer;

  string s = "testData/swelakes.csv";
  // string s = "testData/swe.csv";

  // auto Test_Data = sf::readCsvPoints<Point>(s); 

  int numberOfRandomPoints = 2000000;
  sf::RandomPointGenerator<Point> generator;  
  generator.addNormalPoints(numberOfRandomPoints);
  vector<Point> Test_Data = generator.takePoints();
  cout << "\n\nNumber of Random Points: " << numberOfRandomPoints;


  Rectangle rootNode = Find_Minimal_Covering_Rectangle(Test_Data);
  int bucketCapacity = 100000;
  cout << "\n\nBucketCapacity: " << bucketCapacity;

  timer.start();
  QuadTree qt = QuadTree(Test_Data, bucketCapacity, rootNode);
  cout << "\n\nConstructing Quadtree ";
  timer.stop();






  // // Example Query Test Rectangle
  double testBlx = rootNode.bottomLeft.x + 4e5;
  double testBly = rootNode.bottomLeft.y + 10.5e5;
  double testTrx = testBlx + 1.2*1e5;
  double testTry = testBly + 0.8*1e5;

  Point testBottomLeft = Point(testBlx, testBly);
  Point testTopRight = Point(testTrx, testTry);
  Rectangle Query_Test_Rectangle = Rectangle(testBottomLeft, testTopRight);




  timer.start();
  vector<Point> points_from_query = qt.query(Query_Test_Rectangle, Test_Data);
  cout << "\n\nQuery with Query() ";
  timer.stop();


    timer.start();
  vector<Point> points_from_brute_force = cut_points(Query_Test_Rectangle, Test_Data);
  cout << "\n\nQuery with Brute force ";
  timer.stop();



  auto Query_Writer = sf::MplWriter<Point, Rectangle>("Query_Plot.py");
  int queryPointCount = points_from_query.size();
  int totalPointCount = Test_Data.size();
  double percentage = (double) queryPointCount/totalPointCount;
  cout << "\n\n\nPercantage of queried points vs. total points:  " << percentage << "\n\n\n";

  // Plot Queried Rectangle and Points on top of overall data set
  Query_Writer << Test_Data;
  Query_Writer << rootNode;

  Query_Writer << points_from_query;
  Query_Writer << Query_Test_Rectangle;

  return 1;
}