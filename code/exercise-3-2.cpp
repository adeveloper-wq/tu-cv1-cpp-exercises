//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//#include <math.h>
//
//using namespace cv;
//using namespace std;
//
//Mat image, image_gray, integral_image_init, filtered_image;
//
//cv::Mat integralImage(const cv::Mat& img)
//{
//    CV_Assert(img.type() == CV_8UC1);
//
//    int nRows = img.rows;
//    int nCols = img.cols;
//
//    cv::Mat S = cv::Mat::zeros(nRows + 1, nCols + 1, CV_32SC1);
//
//    for (int i = 1; i <= nRows; ++i)
//    {
//        for (int j = 1; j <= nCols; ++j)
//        {
//            S.ptr<int>(i)[j] = S.ptr<int>(i)[j - 1] + S.ptr<int>(i - 1)[j] - S.ptr<int>(i - 1)[j - 1] + int(img.ptr<uchar>(i - 1)[j - 1]);
//        }
//    }
//    return S;
//}
//
//int main(int argc, char** argv)
//{
//
//    char* filename = argc == 3 ? argv[1] : (char*)"d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//fruits.jpg";
//    image = imread(filename, 1);
//    cvtColor(image, image_gray, COLOR_BGR2GRAY);
//    integral_image_init = image_gray;
//    filtered_image = image_gray.clone();
//
//    Mat integral_image = integralImage(image_gray);
//
//    for (int i = 0; i < image_gray.rows-5; i++) {
//        for (int j = 0; j < image_gray.cols-5; j++) {
//            double sum = - (double)integral_image.ptr<int>(i + 4)[j] + (double)integral_image.ptr<int>(i)[j] + (double)integral_image.ptr<int>(i + 4)[j + 4] - (double)integral_image.ptr<int>(i)[j + 4];
//            
//            int box = (int)(sum / 4);
//
//            //cout << box << "\n";
//                        
//            filtered_image.at<uchar>(i, j) = box;
//        }
//    }
//
//    namedWindow("NormalImage");
//    namedWindow("FilterImage");
//    imshow("NormalImage", image_gray);
//    imshow("FilterImage", filtered_image);
//    waitKey();
//
//    return 0;
//}