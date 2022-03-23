//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgcodecs/imgcodecs.hpp"
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
//    char* filename = argc == 3 ? argv[1] : (char*)"d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//paper3.jpg";
//    image = imread(filename, 1);
//
//    cv::resize(image, image, cv::Size(), 0.2, 0.2);
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
//    double smin = 0, smax = 0;
//    Point minLoc; Point maxLoc;
//    vector<Point2f> pts_src;
//    vector<Point2f> pts_dst;
//
//    minMaxLoc(HarrisMat, &smin, &smax, &minLoc, &maxLoc);
//    circle(HarrisMat, maxLoc, 20, Scalar(500), -1);
//    pts_src.push_back(maxLoc);
//
//    minMaxLoc(HarrisMat, &smin, &smax, &minLoc, &maxLoc);
//    circle(HarrisMat, maxLoc, 20, Scalar(500), -1);
//    pts_src.push_back(maxLoc);
//
//    minMaxLoc(HarrisMat, &smin, &smax, &minLoc, &maxLoc);
//    circle(HarrisMat, maxLoc, 20, Scalar(500), -1);
//    pts_src.push_back(maxLoc);
//
//    minMaxLoc(HarrisMat, &smin, &smax, &minLoc, &maxLoc);
//    circle(HarrisMat, maxLoc, 20, Scalar(500), -1);
//    pts_src.push_back(maxLoc);
//
//    Mat dest_img(image_gray.rows, image_gray.cols, image_gray.depth(), cv::Scalar(0));
//
//    Point temp;
//    int width = image_gray.cols / 1.5;
//
//    temp = Point(0, 0);
//    circle(dest_img, temp, 20, Scalar(500), -1);
//    pts_dst.push_back(temp);
//
//    temp = Point(width, 0);
//    circle(dest_img, temp, 20, Scalar(500), -1);
//    pts_dst.push_back(temp);
//
//    temp = Point(0, ((width) / 7) * 10);
//    circle(dest_img, temp, 20, Scalar(500), -1);
//    pts_dst.push_back(temp);
//
//    temp = Point(width, ((width) / 7) * 10);
//    circle(dest_img, temp, 20, Scalar(500), -1);
//    pts_dst.push_back(temp);
//
//    cout << pts_src << endl;
//
//    Point reorder_temp_3 = pts_src[0];
//    pts_src[0] = pts_src[2];
//    pts_src[2] = pts_src[3];
//    pts_src[3] = reorder_temp_3;
//
//    cout << pts_src << endl;
//    cout << pts_dst << endl;
//
//    // Calculate Homography
//    Mat homography = getPerspectiveTransform(pts_src, pts_dst);
//
//    // Warped image
//    Mat im_warped;
//
//    warpPerspective(image_gray, im_warped, homography, dest_img.size());
//
//    namedWindow("NormalImage");
//    namedWindow("Smaller Eigenvalue");
//    namedWindow("Harris measure");
//    imshow("WarpedImage", convertToChar(im_warped));
//    imshow("NormalImage", convertToChar(image_gray));
//    imshow("DestImage", convertToChar(dest_img));
//    imshow("Smaller Eigenvalue", convertToChar(output));
//    imshow("Harris measure", convertToChar(HarrisMat));
//
//    waitKey();
//
//    return 0;
//}