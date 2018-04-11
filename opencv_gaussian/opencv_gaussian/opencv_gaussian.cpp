// opencv_gaussian.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	int n = 0;
	double s = 0;  // signal
	double total = 0;
	double gaussian = 0;

	// Put your image file here
	string imageName("../data/happyDog.jpg");
	if (argc > 1) {
		imageName = argv[1];
	}

	Mat image;
	image = imread(imageName.c_str(), IMREAD_GRAYSCALE); // Read the file


	Mat newImage;
	newImage = image.clone();


	while ((n % 2 != 1) || (n > 9)) {
		std::cout << "Enter the value : "; std::cin >> n;

		if ((n % 2 == 0) || (n > 9))
			printf("Please input the odd number from 1 to 9.\n");
	}

	std::cout << "Enter the sigma : "; std::cin >> s;

	// Gaussian Smoothing filters
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			total = 0;
			for (int a = -(n / 2); a < n / 2 + 1; a++) {
				for (int b = -(n / 2); b < n / 2 + 1; b++) {
					// Get the bounded value
					if ((y + a >= 0) && (x + b >= 0) && (y + a < image.rows) && (x + b < image.cols)) {
						gaussian = exp((-(pow(a, 2) + pow(b, 2))) / (2 * s * s)) / (2 * 3.14 * s * s);
						total += image.at<uchar>(y + a, x + b) * gaussian;
					}
				}
			}
			newImage.at<uchar>(y, x) = total;
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

