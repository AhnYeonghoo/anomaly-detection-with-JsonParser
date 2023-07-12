#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "include/json/json.h"

#pragma warning(disable: 4996)
#pragma comment(lib, "lib_json.lib")

using namespace std;
using namespace cv;

int main()
{
	Json::Value value; // Json 객체 저장할 변수
	Json::CharReaderBuilder reader; // Json 읽어들이는 변수
	ifstream is("./images/result/_IMG09R-B_raw.json", ifstream::binary); 
	JSONCPP_STRING errs;
	const auto bret = Json::parseFromStream(reader, is, &value, &errs);

	cv::Mat image = imread("./images/sample-09R/_IMG09R-B_raw.jpg", IMREAD_GRAYSCALE);
	if (image.empty()) std::cout << "Not found image" << std::endl;
	cv::Mat img_rectangle;
	image.copyTo(img_rectangle);
	std::cout << value["shapes"][0]["points"][0][0].asDouble() << std::endl;
	std::cout << value["shapes"][0]["points"][0][1].asDouble() << std::endl;
	std::cout << value["shapes"][0]["points"][1][0].asDouble() << std::endl;
	std::cout << value["shapes"][0]["points"][1][1].asDouble() << std::endl;

	double points_x[4][2] =
	{
		{
			value["shapes"][0]["points"][0][0].asDouble(),
			value["shapes"][0]["points"][0][1].asDouble(),
		},
		{
			value["shapes"][1]["points"][0][0].asDouble(),
			value["shapes"][1]["points"][0][1].asDouble(),
		},
		{
			value["shapes"][2]["points"][0][0].asDouble(),
			value["shapes"][2]["points"][0][1].asDouble(),
		},
		{
			value["shapes"][2]["points"][0][0].asDouble(),
			value["shapes"][2]["points"][0][1].asDouble(),
		},
	};

	double points_y[4][2] =
	{ 
		{
			value["shapes"][0]["points"][1][0].asDouble(),
			value["shapes"][0]["points"][1][1].asDouble(),
		},
		{
			value["shapes"][1]["points"][1][0].asDouble(),
			value["shapes"][1]["points"][1][1].asDouble(),
		},
		{
			value["shapes"][2]["points"][1][0].asDouble(),
			value["shapes"][2]["points"][1][1].asDouble(),
		},
		{
			value["shapes"][2]["points"][1][0].asDouble(),
			value["shapes"][2]["points"][1][1].asDouble(),
		},
	};

	double point_x[2] = {
		value["shapes"][0]["points"][0][0].asDouble(),
		value["shapes"][0]["points"][0][1].asDouble(),
	};

	double point_y[2] = {
		value["shapes"][0]["points"][1][0].asDouble(),
		value["shapes"][0]["points"][1][1].asDouble(),
	};
	
	double point_x2[2] = {
		value["shapes"][1]["points"][0][0].asDouble(),
		value["shapes"][1]["points"][0][1].asDouble(),
	};

	double point_y2[2] = {
		value["shapes"][1]["points"][1][0].asDouble(),
		value["shapes"][1]["points"][1][1].asDouble(),
	};

	double point_x3[2] = {
		value["shapes"][2]["points"][0][0].asDouble(),
		value["shapes"][2]["points"][0][1].asDouble(),
	};

	double point_y3[2] = {
		value["shapes"][2]["points"][1][0].asDouble(),
		value["shapes"][2]["points"][1][1].asDouble(),
	};

	double point_x4[2] = {
		value["shapes"][2]["points"][0][0].asDouble(),
		value["shapes"][2]["points"][0][1].asDouble(),
	};

	double point_y4[2] = {
		value["shapes"][2]["points"][1][0].asDouble(),
		value["shapes"][2]["points"][1][1].asDouble(),
	};
	

	// print points 
	for (size_t i = 0; i < value["shapes"].size(); i++)
	{
		std::cout << value["shapes"][0]["points"][0] << std::endl;
	}

	std::cout << value["shapes"][0]["label"].size() << std::endl;
	
	
	auto member = value.getMemberNames();
	for (string s : member)
	{
		std::cout << s << std::endl;
	}


	cv::cvtColor(img_rectangle, img_rectangle, COLOR_GRAY2BGR);

	cv::circle(img_rectangle, Point(point_x[0], point_x[1]),
		130, Scalar(255, 25, 100), 8);

	cv::circle(img_rectangle, Point(point_x2[0], point_x2[1]),
		130, Scalar(255, 25, 100), 8);

	cv::resize(img_rectangle, img_rectangle, Size(555, 555), 0.25, 0.25, INTER_AREA);

	std::cout << value.getMemberNames().at(5) << std::endl;
	
	for (int i = 0; i < 11; i++)
	{
		if (value["shapes"][i]["label"].toStyledString().find("-") != string::npos)
		{
			cv::circle(img_rectangle, Point(points_x[i][0], points_x[i][1]),
				130, Scalar(255, 0, 100), 8);

			std::cout << "바운딩 박스 그리기" << std::endl;
			cv::imshow("image_box", img_rectangle);
			cv::waitKey(0);
		}
		else
		{
			std::cout << "바운딩 박스 그리지 않기" << std::endl;
		}
	}
	
	

	return 0;
}