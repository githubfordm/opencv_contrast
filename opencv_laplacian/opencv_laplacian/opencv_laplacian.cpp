// opencv_laplacian.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	double total = 0;

	// laplacian masks
	double laplacian[3][3] = { { 0, -1, 0 },{ -1, 4, -1 },{ 0, -1, 0 } };

	// Put your image file here
	string imageName("../data/lena.png");
	if (argc > 1) {
		imageName = argv[1];
	}

	Mat image;
	image = imread(imageName.c_str(), IMREAD_GRAYSCALE); // Read the file


	Mat middleImage;
	middleImage = image.clone();
	Mat finalImage;
	finalImage = image.clone();

	// Derivative filtering
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			total = 0;
			for (int a = -1; a < 2; a++) {
				for (int b = -1; b < 2; b++) {
					// Get the bounded value
					if ((y + a >= 0) && (x + b >= 0) && (y + a < image.rows) && (x + b < image.cols)) {
						total += image.at<uchar>(y + a, x + b) * laplacian[a + 1][b + 1];
					}
				}
			}
			// calculate the value
			middleImage.at<uchar>(y, x) = saturate_cast<uchar>(total);
			finalImage.at<uchar>(y, x) = saturate_cast<uchar>(image.at<uchar>(y, x) + middleImage.at<uchar>(y, x));
		}
	}

	if (image.empty()) {	// Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", 1); // Create a window for display

	namedWindow("Middle window", 1); // Create the other window for the middle changed image
	namedWindow("Final window", 1); // Create the other window for the final changed image

	imshow("Display window", image);	// Show our image inside it

	imshow("Middle window", middleImage); // Show the middle changed image
	imshow("Final window", finalImage); // Show the final changed image(original + middle)

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}


