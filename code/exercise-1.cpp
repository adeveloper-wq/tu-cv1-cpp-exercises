//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//#include <algorithm>
//
//using namespace cv;
//using namespace std;
//
//Mat greyImg1;
//Mat greyImg2;
//
//
//int main(int argc, char* argv[])
//{
//	Mat img1 = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//1.jpg", 1);
//	Mat img2 = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//2.jpg", 1);
//
//	//Mat img1 = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Excercise-1//Unbenannt.png", 1);
//	//Mat img2 = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Excercise-1//white.png", 1);
//	// EQUAL BRIGHTNESS:
//	
//	cvtColor(img1, greyImg1, COLOR_BGR2GRAY);
//	cvtColor(img2, greyImg2, COLOR_BGR2GRAY);
//
//	Scalar mean1, mean2, stddev1, stddev2;
//
//	meanStdDev(greyImg1, mean1, stddev1);
//	meanStdDev(greyImg2, mean2, stddev2);
//
//	cout << "Mean 1: " << mean1 << "\nMean 2: " << mean2 << "\nstdDev1: " << stddev1 << "\nstdDev2: " << stddev2 << "\n";
// 
//	double a = 1.0, b = 0.0, a1;
//
//	a = sqrt(stddev1.val[0] / stddev2.val[0]);
//	a1 = 1.0 / a;
//	b = 0.5 * (mean1.val[0] * a1 - mean2.val[0] * a);
//
//	cout << "--------------AFTER-TRANSFORM---------------\n";
//
//	img1.convertTo(img1, CV_8U, a1, -b);
//	img2.convertTo(img2, CV_8U, a, b);
//
//	cvtColor(img1, greyImg1, COLOR_BGR2GRAY);
//	cvtColor(img2, greyImg2, COLOR_BGR2GRAY);
//
//	meanStdDev(greyImg1, mean1, stddev1);
//	meanStdDev(greyImg2, mean2, stddev2);
//
//	cout << "Mean 1: " << mean1 << "\nMean 2: " << mean2 << "\nstdDev1: " << stddev1 << "\nstdDev2: " << stddev2 << "\n";
//
//	int from_to[] = { 0,2 };
//	mixChannels(&img1, 1, &img2, 1, from_to, 1);
//
//	resize(img1, img1, Size(img1.cols / 4, img1.rows / 4));
//	resize(img2, img2, Size(img2.cols / 4, img2.rows / 4));
//
//	imshow("1", img1);
//	imshow("2", img2);
//	waitKey();
//	return 0;
//
////d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Excercise-1//1.jpg
////d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Excercise-1//2.jpg
//}