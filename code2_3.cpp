#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int mainCode2_3()
{
	Mat src = imread("./images/sample-10/_IMG10-A_raw.jpg", IMREAD_COLOR);
	if (src.empty())
	{
		cout << "image not found" << endl;
	}

	Mat gray, edge, output;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	resize(gray, gray, Size(555, 555), 0.25, 0.25, INTER_AREA);
	flip(gray, gray, 1);
	imshow("gray", gray);
	waitKey(0);
	return 0;
}