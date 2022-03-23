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
//// taken from https://docs.opencv.org/4.x/d8/d01/tutorial_discrete_fourier_transform.html
//Mat powerSpectrum(Mat I, int rows, int cols) {
//    Mat padded;                            //expand input image to optimal size
//    int m = getOptimalDFTSize(rows);
//    int n = getOptimalDFTSize(cols); // on the border add zero values
//    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
//    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
//    Mat complexI;
//    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
//    dft(complexI, complexI);            // this way the result may fit in the source matrix
//    // compute the magnitude and switch to logarithmic scale
//    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
//    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
//    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
//    Mat magI = planes[0];
//    magI += Scalar::all(1);                    // switch to logarithmic scale
//    log(magI, magI);
//    // crop the spectrum, if it has an odd number of rows or columns
//    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
//    // rearrange the quadrants of Fourier image  so that the origin is at the image center
//    int cx = magI.cols / 2;
//    int cy = magI.rows / 2;
//    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
//    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
//    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
//    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
//    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
//    q0.copyTo(tmp);
//    q3.copyTo(q0);
//    tmp.copyTo(q3);
//    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
//    q2.copyTo(q1);
//    tmp.copyTo(q2);
//    normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
//                                            // viewable image form (float between values 0 and 1).
//    return magI;
//}
//
//int main()
//{
//    Mat I = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//txt.png", IMREAD_GRAYSCALE);
//
//    if (I.empty()) {
//        cout << "Error opening image" << endl;
//        return EXIT_FAILURE;
//    }
//
//    Mat magI = powerSpectrum(I, I.rows * 4, I.cols *4);
//   
//    imshow("Input Image", I);    // Show the result
//
//    Mat magIShow = magI.clone();
//
//    // decrease region of interest to find the max dots we are looking for
//    rectangle(magI, Point(0, 0), Point(4*magI.cols/10, magI.rows), Scalar(0), -1);
//    rectangle(magI, Point(magI.cols - (4 * magI.cols / 10), 0), Point(magI.cols, magI.rows), Scalar(0), -1);
//
//
//    double min, max;
//    Point min_loc, max_loc;
//    int radius = 30;
//    vector<Point> points;
//
//    // find brightest dots
//    for (int i = 0; i < 12; i++) {
//        circle(magI, Point(magI.cols / 2, magI.rows / 2), radius, Scalar(0), -1);
//        cout << max_loc << "MAX POINT" << endl;
//        points.push_back(max_loc);
//        minMaxLoc(magI, &min, &max, &min_loc, &max_loc);
//        circle(magIShow, max_loc, 20, Scalar(255));
//        radius += 30;
//    }
//
//    // display found dots
//    Mat pointsDrawn =  Mat::zeros(magI.rows, magI.cols, CV_8U);;
//    for (const Point& point : points) {
//        circle(pointsDrawn, point, 1, Scalar(255), -1);
//    }
//    imshow("spectrum magnitude", magIShow);
//    imshow("points", pointsDrawn);
//
//    // get spectrum of the dots image (to get the waves)
//    imshow("points fourier", powerSpectrum(pointsDrawn, pointsDrawn.rows, pointsDrawn.cols));
//    waitKey();
//    return EXIT_SUCCESS;
//}