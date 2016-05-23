#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
using namespace cv;
/// Global variables
Mat src, src_gray;
Mat dst, detected_edges;
int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";
/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
	//

  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, 30, 30*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result

  dst = Scalar::all(0);
  src.copyTo( dst, detected_edges);
 // imshow( window_name, dst );
  imwrite("Gray_Image.jpg", dst);
  cv::Mat img = cv::imread("gray1.jpg", 0);
  int x1;
  Point p = Point(658,270);
  double res=0,res1=0,res2=0,res3=0,z1=0,z2=0;
  int yy=257;
  for (int x = 0; x<img.cols; x++)
  {
	  for (int y = 0; y < img.rows; y++)
	  {
		  x1 = 0.99*x-385;
		  if (y==x1 || y == (x1 - 1) || y == (x1 + 1)){
			  if (img.at<uchar>(y, x) > 50 && x > 658){
				  //res = -1.096282465*pow(10, -4)*(y - yy)*y + 7.184203076*pow(10, -2)*(y - yy) - 6.56835185;
				 // res =(-1.381355524)*pow(10,-4)*(y-yy)*y + (8.434790931)*pow(10,-2)*(y-yy) - (5.870058903);
				  res2 = -9.539914*pow(10, -5)*(y - yy)*y + 0.06958931131*(y - yy) - 4.650445573;
				 //res = 1.096282465*pow(10, -4)*(y - yy)*y - 7.184203076*pow(10, -2)*(y - yy) + 12.56835185;
				  z2 = res2 - res3;
				  res3 = res2;
				   if (z2 > 1 && x > 663){
					  printf("Parking spot detected at pixel Z2 (%d , %d)\n", x, y);
				  }
				  yy = y;		
				 //line(img,p, Point(x, y), Scalar(255, 0, 0),2,2);
						//	  p = Point(x, y);

			  }
		  }
	  }
  	}
  res2 = -9.539914*pow(10, -5)*(720 - yy)*(720-yy) + 0.06958931131*(720 - yy) - 4.650445573;
  z2 = res2 - res3;

  if (z2 > 1){
	  printf("Parking spot detected at pixel (%d , %d)\n", 1116, 720);
	  p = Point(0, 0);
  }
	  yy = 0;
		  
  imshow(window_name, img);
  
  }


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  src = imread( "1.png");

  if( !src.data )
  { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
 // createTrackbar( "Min Threshold:", window_name, 50, 50, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
  }