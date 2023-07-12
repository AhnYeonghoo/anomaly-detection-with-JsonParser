#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "include/json/json.h"

#pragma warning(disable: 4996)
#pragma comment(lib, "lib_json.lib")


int main()
{
	std::string path = "C:\\images\\sample-09R\\*.jpg";
	std::vector<std::string> str;
	int index = 0;
	cv::glob(path, str, false);
	std::cout << "로드 개수:  " << str.size() << std::endl;

	Json::Value value; // Json 객체 저장할 변수
	Json::CharReaderBuilder reader; // Json 읽어들이는 변수
	std::ifstream is("./images/result/_IMG09R-B_raw.json", std::ifstream::binary); 
	JSONCPP_STRING errs;
	const auto bret = Json::parseFromStream(reader, is, &value, &errs);

	cv::Mat image = cv::imread("./images/sample-09R/_IMG09R-B_raw.jpg", cv::IMREAD_GRAYSCALE);
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

	// print points 
	for (size_t i = 0; i < value["shapes"].size(); i++)
	{
		std::cout << value["shapes"][0]["points"][0] << std::endl;
	}

	std::cout << value["shapes"][0]["label"].size() << std::endl;
	
	
	auto member = value.getMemberNames();
	for (std::string s : member)
	{
		std::cout << s << std::endl;
	}


	cv::cvtColor(img_rectangle, img_rectangle, cv::COLOR_GRAY2BGR);

	/*cv::circle(img_rectangle, cv::Point(point_x[0], point_x[1]),
		130, cv::Scalar(255, 25, 100), 8);

	cv::circle(img_rectangle, cv::Point(point_x2[0], point_x2[1]),
		130, cv::Scalar(255, 25, 100), 8);*/

	std::vector<cv::Point> objectLocations;
	for (int i = 0; i < 11; i++)
	{
		if (value["shapes"][i]["label"].toStyledString().find("-") != std::string::npos)
		{
			objectLocations.push_back(cv::Point( points_x[i][0], points_x[i][1]));
		}
	}

	std::cout << value.getMemberNames().at(5) << std::endl;

	for (const auto& location : objectLocations)
	{
		cv::circle(img_rectangle, cv::Point(location), 130, cv::Scalar(255, 25, 100), 8);
	}


	cv::resize(img_rectangle, img_rectangle, cv::Size(555, 555), 0.25, 0.25, cv::INTER_AREA);
	cv::imshow("image_box", img_rectangle);
	cv::waitKey(0);
	
	

	return 0;
}