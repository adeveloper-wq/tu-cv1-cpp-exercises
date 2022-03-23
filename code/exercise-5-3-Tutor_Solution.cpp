//// Computer Vision, winter 2021, TU Dresden, Holger Heidrich
//// opencv DFT example modified to
//// find rotated text lines
////-------------------------------------------
//#include "opencv2/core/core.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
////-----------------------------------------------
//// Rearrange the quadrants of Fourier image so that the origin is at the image center
//void ShiftDFT(InputArray _Im)
//{
//   Mat Im = _Im.getMat();
//
//   int cx = Im.cols / 2;
//   int cy = Im.rows / 2;
//
//   Mat q0(Im, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
//   Mat q1(Im, Rect(cx, 0, cx, cy));  // Top-Right
//   Mat q2(Im, Rect(0, cy, cx, cy));  // Bottom-Left
//   Mat q3(Im, Rect(cx, cy, cx, cy)); // Bottom-Right
//
//   Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
//   q0.copyTo(tmp);
//   q3.copyTo(q0);
//   tmp.copyTo(q3);
//
//   q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
//   q2.copyTo(q1);
//   tmp.copyTo(q2);
//}
////---------------------
//// normalize and show an image - helper function
//void debugShow(const String& filename, InputArray img, bool bwrite = false)
//{
//   Mat tmp = img.getMat();
//   Mat Im8u;
//   cv::normalize(tmp, Im8u, 0, 255, NORM_MINMAX);
//   Im8u.convertTo(Im8u, CV_8UC1);
//   cv::imshow("debug: " + filename, Im8u);    // Show the result
//   if (bwrite) cv::imwrite(filename, Im8u);
//}
//
////-----------------------------
//int main(int argc, char ** argv)
//{
//   const char* filename = argc >= 2 ? argv[1] : "d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//txt.png";
//
//   Mat I = imread(filename, IMREAD_GRAYSCALE);
//   if (I.empty())
//      return -1;
//
//   double smin = 0, smax = 0;
//   Point minLoc; Point maxLoc;
//
//   Mat realInput;
//   I.convertTo(realInput, CV_64F, 1.0, 0.0);
//   // put the image in a larger zero image to have better frequency resolution
//   Size largerSize = I.size()*4; // Size(std::max(A.cols, B.cols), std::max(A.rows, B.rows));
//   
//   Size dftSize;
//   // calculate the size of DFT transform
//   dftSize.width = getOptimalDFTSize(largerSize.width);
//   dftSize.height = getOptimalDFTSize(largerSize.height);
//
//   // allocate temporary buffers and initialize them with 0's
//   Mat tempI(dftSize, realInput.type(), Scalar::all(0));
//   Mat roiI = tempI(Rect(0, 0, I.cols, I.rows)); 
//   realInput.copyTo(roiI);
//
//   Mat spectC;
//   Mat planes[] = { tempI, Mat::zeros(tempI.size(), CV_64F) };
//
//   // now transform the padded A & B in-place;
//   // use "nonzeroRows" hint for faster processing
//   dft(tempI, spectC, DFT_COMPLEX_OUTPUT);
//   split(spectC, planes);
//   magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
//   // Find the max in the power spectrum that is next to the zero-order
//
//   Mat padded;                            //expand input image to optimal size
//
//   Mat magI = planes[0];
//   //pow(magI, 2.0, magI);
//   minMaxLoc(planes[0], &smin, &smax);
//
//   // magI += 1.0;                    // switch to logarithmic scale
//   //log(magI, magI);
//
//   // rearrange the quadrants of Fourier image  so that the origin is at the image center
//   ShiftDFT(magI);
//
//   debugShow("magI.png", magI,true);
//
//   int cx = magI.cols / 2;
//   int cy = magI.rows / 2;
//
//   Point MaxPoint1, MaxPoint2, MaxPoint3, MaxPoint4;
//   
//   circle(magI, Point(cx, cy), 12, 0.0, FILLED);    // cancel out the zero diffraction order (= the middle) of the spectrum
//   minMaxLoc(magI, &smin, &smax, &minLoc, &maxLoc);     // Find first diffraction order of text lines
//   MaxPoint1 = maxLoc;
//   circle(magI, maxLoc, 3, 0.0, FILLED);
//   minMaxLoc(magI, &smin, &smax, &minLoc, &maxLoc); // Find first diffraction order (negative of MaxPoint1) of text lines
//   MaxPoint2 = maxLoc;
//   
//   Mat Mask = Mat::zeros(magI.size(), CV_8U);    // mask to limit search for 6th diffraction order of text lines
//
//   // look for far away points to increase angle accuracy
//   circle(Mask, Point(cx, cy) + (MaxPoint1 - Point(cx, cy)) * 6, 10, 1, FILLED); // draw mask to find 6th diffraction order of text lines
//   minMaxLoc(magI, &smin, &smax, &minLoc, &maxLoc, Mask);    // Find 6th diffraction order of text lines
//   MaxPoint3 = maxLoc;
//   Mask = 0;
//   circle(Mask, Point(cx, cy) + (MaxPoint2 - Point(cx, cy)) * 6, 10, 1, FILLED);
//   minMaxLoc(magI, &smin, &smax, &minLoc, &maxLoc, Mask);    // Find 6th diffraction order (negative of MaxPoint3) of text lines
//   MaxPoint4 = maxLoc;
//
//   Mask = Mat::zeros(magI.size(), CV_64F);      // mask for CV_64F
//   Mask.at<double>(MaxPoint1) = 1.0;
//   Mask.at<double>(MaxPoint2) = 1.0;            
//   imshow("Mask", Mask);
//   //  rearrange the quadrants to match the spectrum
//   ShiftDFT(Mask);
//
//   Mat MaskPlanes[] = {Mask, Mask}; 
//   Mat complexMask;
//   merge(MaskPlanes, 2, complexMask);
//   Mat lineSpec = spectC.mul(complexMask);  // take the text line wave out of the spectrum (including its phase),!not complex multiplication!
//   // do inverse dft
//   Mat lineWaves;
//   dft(lineSpec, lineWaves, DFT_INVERSE + DFT_SCALE + DFT_REAL_OUTPUT);
//   normalize(lineWaves, lineWaves, 0, 255, NORM_MINMAX);
//   debugShow("lineWaves0.png", lineWaves, true);
//
//   // for left and right border: get Rotation angle from MaxPoints in Spectrum
//   double dy = MaxPoint4.y - MaxPoint3.y;
//   double dx = MaxPoint4.x - MaxPoint3.x;
//   
//   // aspect ratio correction for angle (because frequency is measured in waves per width and height):
//   dy *= double(lineSpec.cols) / double (lineSpec.rows);
//
//   double rotAngle = atan2(dx, dy)*180.0 / CV_PI; // y-axis inverted in images
//   Mat RotMat = getRotationMatrix2D(Point(I.cols, I.rows), -rotAngle, 1.0);
//
//   // put the txt image in an empty image and rotate
//   Mat RotImg = Mat::zeros(I.size() * 2, CV_64F);
//   RotImg = 255.0;
//
//   Mat RotZone(RotImg, Rect(I.cols / 2, I.rows / 2, I.cols, I.rows));
//   realInput.copyTo(RotZone);
//   debugShow("RotImg.png", RotImg, true);
//   Mat RotatedImg;
//   warpAffine(RotImg, RotatedImg, RotMat, RotImg.size());   // rotate text to get lines horizontal
//   debugShow("RotatedImg.png", RotatedImg, true);
//   Mat ResultImg;
//   RotatedImg(Rect(I.cols / 2, I.rows / 2, I.cols, I.rows)).copyTo(ResultImg);  // crop result
//   //realInput.copyTo(roiI);
//   debugShow("ResultImg.png", ResultImg, true);
//   
//   // get the left and right border of the text by parallel projection (optional)
//   Mat ColumnSums = Mat::zeros(1, ResultImg.cols, CV_64F);
//   for (int j = 0; j < ResultImg.rows; j++)
//   {
//      for (int i = 0; i < ResultImg.cols; i++)
//      {
//         ColumnSums.at<double>(0, i) += ResultImg.at<double>(j, i);
//      }
//   }
//   int leftBorder = 0, rightBorder = 0;
//   for (int i = 1; i < ColumnSums.cols / 4; i++)
//   {
//      double grad = ColumnSums.at<double>(0, i - 1) - ColumnSums.at<double>(0, i + 1);
//      if (grad > 2000.0)
//      {
//         leftBorder = i;
//         break;
//      }
//   }
//   for (int i = ColumnSums.cols-2; i > ColumnSums.cols *3 / 4; i--)
//   {
//      double grad = ColumnSums.at<double>(0, i + 1) - ColumnSums.at<double>(0, i - 1);
//      if (grad > 2000.0)
//      {
//         rightBorder = i;
//         break;
//      }
//   }
//   
//   // could do this for the border of the txt lines, but let us use the wave image instead
//   Mat TxtLinesBinary(lineWaves, Rect(0,0, I.cols, I.rows));
//
//   // rotate the lines
//   RotImg = 255.0;
//   RotZone = RotImg(Rect(I.cols / 2, I.rows / 2, I.cols, I.rows));
//   TxtLinesBinary.copyTo(RotZone);
//   debugShow("ResIm.png", ResultImg, true);
//   debugShow("linesinwithe.png", RotImg, true);
//   warpAffine(RotImg, RotatedImg, RotMat, RotImg.size());
//   debugShow("RotatedLines.png", RotatedImg, true);
//   // crop out the (back-)rotated lines 
//   TxtLinesBinary = RotatedImg(Rect(I.cols / 2, I.rows / 2, I.cols, I.rows));
//   // fill the borders
//   TxtLinesBinary(Rect(0, 0, leftBorder, TxtLinesBinary.rows)) = 255.0;
//   TxtLinesBinary(Rect(rightBorder, 0, TxtLinesBinary.cols-rightBorder, TxtLinesBinary.rows)) = 255.0;
//   debugShow("TxtLinesWaves.png", TxtLinesBinary, true);
//
//   TxtLinesBinary = TxtLinesBinary > 210.0;  // Thres the wave image - let txt be large than space between lines
//   debugShow("TxtLinesBinary.png", TxtLinesBinary, true);
//
//   // get and draw the contours around the txt lines:
//   vector<vector<Point> > contours;
//   vector<Vec4i> hierarchy;
//   vector<vector<Point> > contours0;
//   findContours(TxtLinesBinary, contours0, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//   contours.resize(contours0.size());
//   for (size_t k = 0; k < contours0.size(); k++)
//      approxPolyDP(Mat(contours0[k]), contours[k], 3, true);   // remove noise -> get straight lines
//   Mat txtLinesContour = Mat::zeros(TxtLinesBinary.size(), CV_8UC3);
//   txtLinesContour = CV_RGB(255, 255, 255);  // make it a white image
//
//   for (size_t k = 0; k < contours.size(); k++)
//   {
//      if (contours[k].size() < 7)
//         drawContours(txtLinesContour, contours, k, Scalar(0, 0, 255), 1, LINE_AA, hierarchy, -1); // BGR
//   }
//   debugShow("txtLinesContour.png", txtLinesContour, true);
//   Mat ResultRGB = Mat::zeros(ResultImg.size(), CV_8UC3);
//   
//   ResultImg.convertTo(ResultRGB, CV_8UC1);
//   cvtColor(ResultRGB, ResultRGB, COLOR_GRAY2BGR);
//   ResultRGB = ResultRGB & txtLinesContour;
//
//   debugShow("ResultRGB.png", ResultRGB, true);
//
//   normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with double values into a
//   // viewable image form (double between values 0 and 1).
//
//   imshow("Input Image", I);    // Show the result
//   imshow("spectrum magnitude", magI);
// 
//   waitKey();
//
//   return 0;
//}