// opencv_derivative.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
#include<math.h>


using namespace cv;

using namespace std;

int main(int argc, char** argv)
{
	double x_total = 0;
	double y_total = 0;

	// sobel masks
	double x_sobel[3][3] = { { 1, 0, -1 }, { 2, 0, -2 }, { 1, 0, -1 } };
	double y_sobel[3][3] = { { 1, 2, 1 },{ 0, 0, 0 },{ -1, -2, -1 } };

	// Put your image file here
	string imageName("../data/lena.png");
	if (argc > 1) {
		imageName = argv[1];
	}

	Mat image;
	image = imread(imageName.c_str(), IMREAD_GRAYSCALE); // Read the file


	Mat newImage;
	newImage = image.clone();

	// Derivative filtering
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			x_total = 0;
			y_total = 0;
			for (int a = -1; a < 2 ; a++) {
				for (int b = -1; b < 2; b++) {
					// Get the bounded value
					if ((y + a >= 0) && (x + b >= 0) && (y + a < image.rows) && (x + b < image.cols)) {
						x_total += image.at<uchar>(y + a, x + b) * (x_sobel[a + 1][b + 1]);
						y_total += image.at<uchar>(y + a, x + b) * (y_sobel[a + 1][b + 1]);
					}
				}
			}
			// calculate the value
			newImage.at<uchar>(y, x) = sqrt((x_total*x_total)+(y_total*y_total));
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


