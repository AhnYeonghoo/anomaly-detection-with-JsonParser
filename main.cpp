#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "include/json/json.h"

#pragma warning(disable: 4996)
#pragma comment(lib, "lib_json.lib")


void loadFolderImages(std::string path)
{
	std::vector<std::string> str;
	cv::glob(path, str, false);
	
	std::cout << "로드 개수: " << str.size() << std::endl;
}

Json::Value loadJson(std::string path)
{
	Json::Value value;
	Json::CharReaderBuilder reader;
	std::ifstream is(path, std::ifstream::binary);
	
	JSONCPP_STRING err;
	const auto bret = Json::parseFromStream(reader, is, &value, &err);

	return value;
}

cv::Mat loadImage(std::string path, int color_or_gray = cv::IMREAD_GRAYSCALE)
{
	cv::Mat image = cv::imread(path, color_or_gray);

	if (image.empty())
	{
		std::cout << "Not found image" << std::endl;
	}
	return image;
}

int main()
{
	std::string path = "C:\\images\\sample-09R\\*.jpg";
	loadFolderImages(path);
	
	int index = 0;

	const auto value = loadJson("./images/result/_IMG09R-B_raw.json");
	cv::Mat image = loadImage("./images/sample-09R/_IMG09R-B_raw.jpg", cv::IMREAD_GRAYSCALE);

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