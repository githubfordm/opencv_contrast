// opencv_histogram.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

int main(int argc, char** argv)
{
	// Put your image file here
	string imageName("../data/fruit.jpg");
	
	if (argc > 1) {
		imageName = argv[1];
	}

	Mat image;
	image = imread(imageName.c_str(), IMREAD_COLOR); // Read the file

	Mat newImage; // Image for histogram equalization
	newImage = Mat::zeros(image.size(), image.type());

	cvtColor(image, image, CV_BGR2GRAY); // Change image to grayscale

	equalizeHist(image, newImage); // Do histogram equalization


	// Histogram calculation
	Mat in_hist, out_hist;
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;

	calcHist(&image, 1, 0, Mat(), in_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&newImage, 1, 0, Mat(), out_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw a histogram
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	Mat histNewImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	normalize(image, image, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(newImage, newImage, 0, histNewImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++) {
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(in_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(in_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}

	for (int i = 1; i < histSize; i++) {
		line(histNewImage, Point(bin_w*(i - 1), hist_h - cvRound(out_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(out_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}

	namedWindow("Display window", 1); // Create a window for display
	namedWindow("Histogram equalization window", 1);
	
	namedWindow("calcHistDemo", WINDOW_AUTOSIZE); // Create a window for display histogram
	namedWindow("calcHistNewDemo", WINDOW_AUTOSIZE);

	imshow("Display window", image);	// Show our image inside it
	imshow("Histogram eqaulization window", newImage);

	imshow("calcHistDemo", histImage); // Show the histogram
	imshow("calcHistNewDemo", histNewImage);

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

