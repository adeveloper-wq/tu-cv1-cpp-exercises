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
//// https://stackoverflow.com/questions/31028448/filtering-an-image-in-frequency-domain
// 
//int main()
//{
//    int kernel_size = 15;
//    Point anchor = Point(-1, -1);
//    double delta = 0;
//    Mat kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size * kernel_size);
//
//    bool fourier = false;
//
//    Mat I = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//fruits.jpg", IMREAD_GRAYSCALE);
//    I.convertTo(I, CV_32F);
//    if (I.empty()) {
//        cout << "Error opening image" << endl;
//        return EXIT_FAILURE;
//    }
//    TickMeter tm;
//    tm.start();
//    if (fourier) {
//        Mat padded;                            //expand input image to optimal size
//        int m = getOptimalDFTSize(I.rows);
//        int n = getOptimalDFTSize(I.cols); // on the border add zero values
//        copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
//        Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
//        Mat complexI;
//        merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
//        dft(complexI, complexI/*, cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT*/);            // this way the result may fit in the source matrix
//        //copyMakeBorder(kernel, kernel, 232, 233, 248, 249, BORDER_REPLICATE);
//
//        Mat paddedKernel;                            //expand input image to optimal size
//        copyMakeBorder(kernel, paddedKernel, 0, m - kernel.rows, 0, n - kernel.cols, BORDER_CONSTANT, Scalar::all(0));
//        Mat planesKernel[] = { Mat_<float>(paddedKernel), Mat::zeros(paddedKernel.size(), CV_32F) };
//        Mat complexIKernel;
//        merge(planesKernel, 2, complexIKernel);         // Add to the expanded another plane with zeros
//        dft(complexIKernel, complexIKernel/*, cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT*/);            // this way the result may fit in the source matrix
//        //copyMakeBorder(kernel, kernel, 232, 233, 248, 249, BORDER_REPLICATE);
//        //dft(kernel, kernel);
//        Mat filtered;
//        //filter2D(complexI, filtered, -1, kernel, anchor, delta, BORDER_DEFAULT);
//        mulSpectrums(complexI, complexIKernel, filtered, 0, false);
//        //boxFilter(I, filtered, -1, Size(5, 5));
//        Mat inverse;
//        dft(filtered, inverse, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);
//        normalize(inverse, inverse, 0, 1, NORM_MINMAX);
//        // compute the magnitude and switch to logarithmic scale
//        // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
//        split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
//        magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
//        Mat magI = planes[0];
//        magI += Scalar::all(1);                    // switch to logarithmic scale
//        log(magI, magI);
//        // crop the spectrum, if it has an odd number of rows or columns
//        magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
//        // rearrange the quadrants of Fourier image  so that the origin is at the image center
//        int cx = magI.cols / 2;
//        int cy = magI.rows / 2;
//        Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
//        Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
//        Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
//        Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
//        Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
//        q0.copyTo(tmp);
//        q3.copyTo(q0);
//        tmp.copyTo(q3);
//        q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
//        q2.copyTo(q1);
//        tmp.copyTo(q2);
//        normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
//                                                // viewable image form (float between values 0 and 1).
//        normalize(I, I, 0, 1, NORM_MINMAX);
//        normalize(inverse, inverse, 0, 1, NORM_MINMAX);
//        tm.stop();
//        cout << "Total time: " << tm.getTimeSec() << endl;
//        imshow("Input Image", I);    // Show the result
//        imshow("filtered image", inverse);
//        imshow("spectrum magnitude", magI);
//        waitKey();
//        return EXIT_SUCCESS;
//    }
//    else {
//        normalize(I, I, 0, 1, NORM_MINMAX);
//        Mat filtered;
//        filter2D(I, filtered, -1, kernel, anchor, delta, BORDER_DEFAULT);
//        tm.stop();
//        cout << "Total time: " << tm.getTimeSec() << endl;
//        imshow("Input Image", I);    // Show the result
//        imshow("filtered image", filtered);
//        waitKey();
//        return EXIT_SUCCESS;
//    }
//    
//}