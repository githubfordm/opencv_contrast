// opencv_chromakey.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	int val_cb[256] = { 0, };
	int val_cr[256] = { 0, };
		

	// Put your image file here
	string imageName("../data/doggy.jpg");
	string backImageName("../data/lava.jpg");
	if (argc > 1) {
		imageName = argv[1];
	}

	Mat image;
	image = imread(imageName.c_str(), 1); // Read the file
	Mat newImage = image.clone(); // for chroma key
	Mat backImage = imread(backImageName.c_str(), 1);
	Mat chromaImage = image.clone();

	if (image.empty()) {	// Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cvtColor(image, newImage, CV_BGR2YCrCb);  // color transformation from open library

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			/* Get the values of cr & cb */
			int cr = saturate_cast<uchar>(newImage.at<Vec3b>(y, x)[1]);
			int cb = saturate_cast<uchar>(newImage.at<Vec3b>(y, x)[2]);

			val_cr[cr]++;
			val_cb[cb]++;
		}
	}

	int cr_key = -1;
	int cb_key = -1;

	for (int i = 0; i < 256; i++) {
		if (val_cr[i] > cr_key) {
			cr_key = i;
		}

		if (val_cb[i] > cb_key) {
			cb_key = i;
		}
	}


	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			/* Get the values of cr & cb */
			int cr = saturate_cast<uchar>(newImage.at<Vec3b>(y, x)[1]);
			int cb = saturate_cast<uchar>(newImage.at<Vec3b>(y, x)[2]);

			int dist_cr = cr_key - cr;
			int dist_cb = cb_key - cb;
			int dis = sqrt(pow(dist_cr, 2) + pow(dist_cb, 2));  // Get the distance
			float a = 0;

			//printf("%d ", dis);  // Print the value of distance for measuring thresholds 
			int inner = 28;
			int outer = 30;

			if (dis < inner) {
				a = 1; // if distance is within an inner threshold 
			}
			else if (dis >= inner && dis <= outer) {
				a = (dis - inner) / (outer - inner); // if distance is between inner and outer threashold
			}
			else {
				a = 0; // if distance is above an outer threshold 
			}

			/* Get the output image */
			chromaImage.at<Vec3b>(y, x) = (1 - a) * backImage.at<Vec3b>(y, x) + a * image.at<Vec3b>(y, x);
		}
	}
	
	bool chorm = imwrite("../data/chroma_key.bmp", chromaImage); // Save chroma key image

	namedWindow("Display window", 1); // Create a window for display
	namedWindow("Background window", 1); // background display
	namedWindow("Chroma window", 1); // chroma key display

	imshow("Display window", image);	// Show our image inside it
	imshow("Background window", backImage); // show the background image
	imshow("Chroma window", chromaImage); // show the chroma key image

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

