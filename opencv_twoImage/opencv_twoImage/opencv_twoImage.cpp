// opencv_twoImage.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <iostream>
#include <string>

#include<cv.h>
#include<highgui.h>


using namespace cv;

using namespace std;

double alpha = 0.5;
double beta;
double input;

int main(int argc, char** argv)
{
	// Put your image file here
	string imageName("../data/happyDog.jpg");
	string otherImName("../data/happyCat.jpg");

	if (argc > 1) {
		imageName = argv[1];
	}

	Mat image;
	image = imread(imageName.c_str(), IMREAD_COLOR); // Read the file
	Mat otherImage;
	otherImage = imread(otherImName.c_str(), IMREAD_COLOR);

	Mat blend;

	// Resize the file
	cv::resize(image, blend, cv::Size(otherImage.cols, otherImage.rows), 0, 0, CV_INTER_NN);

	std::cout << "Enter the alpha value [0-1]: "; std::cin >> alpha;

	beta = 1.0 - alpha;

	// combine the pixels by given size
	for (int y = 0; y < blend.rows; y++) {
		for (int x = 0; x < blend.cols; x++) {
			for (int c = 0; c < 3; c++) {
				blend.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * (blend.at<Vec3b>(y, x)[c])) +
					saturate_cast<uchar>(beta *(otherImage.at<Vec3b>(y, x)[c]));
			}
		}
	}


	if (image.empty() || otherImage.empty()) {	// Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", 1); // Create a window for display

	imshow("Display window", blend);	// Show our image inside it

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

