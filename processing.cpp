#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int mainProcessing()
{
	char buf[256];
	Mat image;
	Mat gray_image;
	Mat image_threshold;
	String image_path("./images/sample-10/*.jpg");
	vector<String> str;
	
	// �̹��� ������ ���� ����
	int index = 0;
	
	glob(image_path, str, false); // �������� �̹��� �ҷ����� �Լ�
	cout << "�ҷ��� �̹����� ����: " << str.size() << endl;

	if (str.size() == 0)
	{
		cout << "�̹����� �������� �ʽ��ϴ�\n";
	}
	vector<Mat> images;
	Vec3b color;
	for (int i = 0; i < str.size(); i++)
	{
		image = imread(str[i], IMREAD_GRAYSCALE);
		resize(image, image, Size(555, 555), 0.25, 0.25, INTER_AREA); // ũ�� ���
		images.push_back(image);
	}
	
	Vec3b color0 = images.at(0).at<Vec3b>(Point(100, 100));
	Vec3b color1 = images.at(1).at<Vec3b>(Point(100, 100));
	Vec3b color2 = images.at(2).at<Vec3b>(Point(100, 100));

	for (int i = 0; i < 3; i++)
	{
		cout << int(color.val[i]) << " ";
	}
	cout << endl;
	
	
	

	for (int i = 0; i < images.size(); i++)
	{
		resize(images.at(i), images.at(i), Size(555, 555), 0.25, 0.25, INTER_AREA);
		imshow("image",images.at(i));
		waitKey(0);
	}

	
	return 0;
}