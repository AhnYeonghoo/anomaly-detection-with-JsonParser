#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int mainCode2_4()
{
	Mat image = Mat(400, 600, CV_8UC3, Scalar(0, 0, 0));
	
	line(image, Point(100, 100), Point(300, 300), Scalar(0, 0, 255), 7);
	rectangle(image, Point(250, 30), Point(450, 200), Scalar(0, 255, 0), 5);
	circle(image, Point(100, 300), 60, Scalar(255, 0, 0), 3);
	ellipse(image, Point(300, 300), Point(100, 100), 45, 130, 270, Scalar(255, 255, 255), 5);

	imshow("image", image);
	waitKey(0);
	return 0;
}