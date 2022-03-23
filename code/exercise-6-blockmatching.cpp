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
//Mat image_L, image_R, image_L_gray, image_R_gray;
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
//    image_L = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//visStudiotemp//ConsoleApplication1//tsukuba_L.png", 1);
//    image_R = imread("d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//visStudiotemp//ConsoleApplication1//tsukuba_R.png", 1);
//
//    cvtColor(image_L, image_L_gray, COLOR_BGR2GRAY);
//    cvtColor(image_R, image_R_gray, COLOR_BGR2GRAY);
//    Mat output_image;
//    image_L_gray.copyTo(output_image);
//    image_L_gray.convertTo(image_L_gray, CV_32FC1);
//    image_R_gray.convertTo(image_R_gray, CV_32FC1);
//
//  
//    // Point middle = Point(image_L_gray.cols / 2, image_L_gray.rows / 2);
//
//    // circle(image_L_gray, middle, 20, Scalar(500), -1);
//
//    // cout << middle << endl;
//
//    Mat diff;
//
//    //image_L_gray(Range(middle.x -3, middle.x + 3), Range(middle.y - 3, middle.y + 3)).copyTo(block_L);
//
//    for (int row = 3; row < image_L_gray.rows - 3 ; row++) {
//        for (int col_L = 3; col_L < image_L_gray.cols - 3; col_L++) {
//            Mat block_L;
//            image_L_gray(Range(row - 3, row + 3), Range(col_L - 3, col_L + 3)).copyTo(block_L);
//            vector<int> sad;
//            for (int col_R = (col_L - 15 > 3 ? col_L - 15 : 3); col_R < (col_L + 15 < image_L_gray.cols - 3 ? col_L + 15 : image_L_gray.cols - 3); col_R++) {
//                Mat block_R;
//                image_R_gray(Range(row - 3, row + 3), Range(col_R - 3, col_R + 3)).copyTo(block_R);
//                absdiff(block_L, block_R, diff);
//                sad.push_back(sum(diff)[0]);
//            }
//            int smallest = NULL;
//            for (const int i : sad) {
//                if (smallest == NULL || smallest > i)
//                    smallest = i;
//            }       
//            output_image.ptr<int>(row)[col_L] = smallest;
//        }
//        //subtract(block_L, block_R, diff);
//    }
//
//    imshow("NormalLeftImage", convertToChar(image_L_gray));
//    imshow("NormalRightImage", convertToChar(image_R_gray));
//    imshow("Dif", output_image);
//
//    waitKey();
//
//    return 0;
//}