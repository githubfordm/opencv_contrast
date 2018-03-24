// opencv_sample.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

#include<cv.h>
#include<highgui.h>


using namespace cv;

using namespace std;

double alpha;
int beta;

int main(int argc, char** argv)
{
	// Put your image file here
	string imageName("../data/happyDog.jpg");
	if (argc > 1) {
		imageName = argv[1];
	}

	Mat image;
	image = imread(imageName.c_str(), IMREAD_COLOR); // Read the file

	Mat newImage;
	newImage = Mat::zeros(image.size(), image.type());

	std::cout << "Enter the alpha value [1.0-3.0]: "; std::cin >> alpha;
	std::cout << "Enter the beta value [0-100]: "; std::cin >> beta;

	// Manipulate the contrast of image
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (int c = 0; c < 3; c++) {
				newImage.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	if (image.empty()) {	// Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", 1); // Create a window for display
	namedWindow("New window", 1); // Create the other window for the changed image

	imshow("Display window", image);	// Show our image inside it
	imshow("New window", newImage); // Show the changed image

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

