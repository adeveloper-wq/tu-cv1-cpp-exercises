//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//#include <math.h>
//
//using namespace cv;
//using namespace std;
//
//Mat image, image_gray;
//
//Mat output;
//
//Mat convertToChar(Mat mIn)
//{
//    Mat mOut(mIn.rows, mIn.cols, CV_8U);
//    double min_val, max_val;
//    minMaxLoc(mIn, &min_val, &max_val);
//    convertScaleAbs(mIn, mOut, 255.0 / (max_val - min_val), -255.0 * min_val / (max_val - min_val));
//    return mOut;
//}
//
//int main(int argc, char** argv)
//{
//    char* filename = argc == 3 ? argv[1] : (char*)"d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//paper.png";
//    image = imread(filename, 1);
//
//    cvtColor(image, image_gray, COLOR_BGR2GRAY);
//    image_gray.convertTo(image_gray, CV_32FC1);
//    GaussianBlur(image_gray, image_gray, Size(0, 0), 1.0);
//    Mat imx(image_gray);
//    Mat imy(image_gray);
//
//    image_gray.adjustROI(-1, -1, 0, -2);
//    imx.adjustROI(-1, -1, -2, 0);
//
//    Mat im_x = image_gray - imx;
//
//    image_gray.adjustROI(1, -1, -1, +1);
//    imy.adjustROI(-2, 0, -1, -1);
//
//    Mat im_y = image_gray - imy;
//
//    Mat imx2 = im_x.mul(im_x);
//    Mat imy2 = im_y.mul(im_y);
//    Mat imxy = im_x.mul(im_y);
//
//    GaussianBlur(imx2, imx2, Size(0, 0), 3.0);
//    GaussianBlur(imy2, imy2, Size(0, 0), 3.0);
//    GaussianBlur(imxy, imxy, Size(0, 0), 3.0);
//
//    Mat xx_yy = imx2 - imy2;
//    Mat sqrtMat;
//    sqrt(xx_yy.mul(xx_yy) + 4.0 * imxy.mul(imxy), sqrtMat);
//
//    output = Mat::zeros(image_gray.size(), CV_32FC1);
//
//    output.adjustROI(-1, -1, -1, -1);
//    output = imx2 + imy2 - sqrtMat;
//
//    float alpha = 0.06;
//    Mat HarrisMat = imy2.mul(imx2) - imxy.mul(imxy) - alpha * (imx2 + imy2).mul(imx2 + imy2);
//
//    namedWindow("NormalImage");
//    namedWindow("Smaller Eigenvalue");
//    namedWindow("Harris measure");
//    imshow("NormalImage", convertToChar(image_gray));
//    imshow("Smaller Eigenvalue", convertToChar(output));
//    imshow("Harris measure", convertToChar(HarrisMat));
//
//    waitKey();
//
//    return 0;
//}