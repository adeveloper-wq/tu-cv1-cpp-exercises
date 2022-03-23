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
//Mat fourier(Mat I) {
//    Mat padded;                            //expand input image to optimal size
//    int m = getOptimalDFTSize(I.rows);
//    int n = getOptimalDFTSize(I.cols); // on the border add zero values
//    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
//    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
//    Mat complexI;
//    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
//    dft(complexI, complexI/*, cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT*/);            // this way the result may fit in the source matrix
//    return complexI;
//}
//
//void Rearrange(cv::Mat& src, cv::Mat& dst)
//{
//    int cx = src.cols / 2;
//    int cy = src.rows / 2;
//    cv::Mat tmp;
//    tmp.create(src.size(), src.type());
//    src(cv::Rect(0, 0, cx, cy)).copyTo(tmp(cv::Rect(cx, cy, cx, cy)));
//    src(cv::Rect(cx, cy, cx, cy)).copyTo(tmp(cv::Rect(0, 0, cx, cy)));
//    src(cv::Rect(cx, 0, cx, cy)).copyTo(tmp(cv::Rect(0, cy, cx, cy)));
//    src(cv::Rect(0, cy, cx, cy)).copyTo(tmp(cv::Rect(cx, 0, cx, cy)));
//    dst = tmp;
//}
//
//int main()
//{
//    Mat AE = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//AE.png", IMREAD_GRAYSCALE);
//    Mat E = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//E.png", IMREAD_GRAYSCALE);
//    Mat A = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//A.png", IMREAD_GRAYSCALE);
//
//    //Mat fourierAE = fourier(AE);
//    //Mat fourierA = fourier(A);
//    //Mat fourierE = fourier(E);
//    
//    int width = cv::getOptimalDFTSize(std::max(AE.cols, AE.cols));
//    int height = cv::getOptimalDFTSize(std::max(AE.rows, AE.rows));
//    cv::Mat fft1;
//    cv::Mat fft2;
//
//    cv::copyMakeBorder(AE, fft1, 0, height - AE.rows, 0, width - AE.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
//    cv::copyMakeBorder(A, fft2, 0, height - AE.rows, 0, width - AE.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
//
//    fft1.convertTo(fft1, CV_32F);
//    fft2.convertTo(fft2, CV_32F);
//
//    cv::dft(fft1, fft1, 0, AE.rows);
//    cv::dft(fft2, fft2, 0, E.rows);
//
//    cv::mulSpectrums(fft1, fft2, fft1, 0, true);
//    // here cv::DFT_SCALE divide `width*height` 1 times
//    cv::idft(fft1, fft1, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
//    Rearrange(fft1, fft1);
//     
//    imshow("Input Image AE", AE);
//    imshow("Input Image A", A);
//    fft1 = (abs(fft1) / (10000000));
//    double min, max;
//    Point min_loc, max_loc;
//    minMaxLoc(fft1, &min, &max, &min_loc, &max_loc);
//    circle(fft1, max_loc, 30, Scalar(255));
//    imshow("inverse fourier", fft1);
//    waitKey();
//    return EXIT_SUCCESS;
//}