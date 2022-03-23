//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//#include <math.h>
//
//using namespace cv;
//using namespace std;
//
//Mat image, image_gray, filtered_image;
//
//
//int main(int argc, char** argv)
//{
//
//    char* filename = argc == 3 ? argv[1] : (char*)"d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//fruits.jpg";
//    image = imread(filename, 1);
//    cvtColor(image, image_gray, COLOR_BGR2GRAY);
//    filtered_image = image_gray.clone();
//
//    double Gx[3][3] = {
//        {1.0, 0.0, -1.0} ,
//        {2.0, 0.0, -2.0} ,
//        {1.0, 0.0, -1.0}
//    };
//
//    double Gy[3][3] = {
//        {1.0, 2.0, 1.0} ,
//        {0.0, 0.0, 0.0} ,
//        {-1.0, -2.0, -1.0}
//    };
//    //for (int i = 0; i < image_gray.rows-2; i++)
//    //{
//    //    for (int j = 0; j < image_gray.cols-2; j++) {
//    //        double G_x = (image_gray.at<uchar>(i, j)) - (image_gray.at<uchar>(i + 2, j)) +
//    //            (2 * (double)image_gray.at<uchar>(i, j + 1)) - (2 * (double)image_gray.at<uchar>(i + 2, j + 1)) +
//    //            (image_gray.at<uchar>(i, j + 2)) - (image_gray.at<uchar>(i + 2, j + 2));
//    //        
//    //        double G_y = (Gx[0][0] * image_gray.at<uchar>(i, j)) + (Gx[0][1] * image_gray.at<uchar>(i + 1, j)) + (Gx[0][2] * image_gray.at<uchar>(i + 2, j)) +
//    //            (Gx[1][0] * image_gray.at<uchar>(i, j + 1)) + (Gx[1][1] * image_gray.at<uchar>(i + 1, j + 1)) + (Gx[1][2] * image_gray.at<uchar>(i + 2, j + 1)) +
//    //            (Gx[2][0] * image_gray.at<uchar>(i, j + 2)) + (Gx[2][1] * image_gray.at<uchar>(i + 1, j + 2)) + (Gx[2][2] * image_gray.at<uchar>(i + 2, j + 2));
//
//    //        if (G_x < 0) {
//    //            G_x = G_x * -1;
//    //        }
//
//    //        if (G_y < 0) {
//    //            G_y = G_y * -1;
//    //        }
//
//    //        int G = (int)G_x;
//    //        
//    //        filtered_image.at<uchar>(i, j) = G;
//    //    }
//    //}
//
//    for (int i = 0; i < image_gray.rows; i++)
//    {
//        for (int j = 0; j < image_gray.cols - 2; j++) {
//            double G_x = image_gray.at<uchar>(i, j + 2) - image_gray.at<uchar>(i, j);
//            if (G_x < 0) {
//                G_x = G_x * -1;
//            }
//            int G = (int)G_x;
//            filtered_image.at<uchar>(i, j) = G;
//        }
//    }
//
//    /*for (int i = 0; i < filtered_image.cols; i++)
//    {
//        for (int j = 0; j < filtered_image.rows - 2; j++) {
//            double G_x = (double)filtered_image.at<uchar>(j, i) + filtered_image.at<uchar>(j + 1, i) + filtered_image.at<uchar>(j + 1, i) + filtered_image.at<uchar>(j + 2, i);
//            if (G_x < 0) {
//                G_x = G_x * -1;
//            }
//            int G = (int)G_x;
//            filtered_image.at<uchar>(j, i) = G;
//        }
//    }*/
//
//    for (int i = 0; i < filtered_image.cols; i++)
//    {
//        for (int j = 0; j < filtered_image.rows - 2; j++) {
//            double G_x = (double)filtered_image.at<uchar>(j, i) + filtered_image.at<uchar>(j + 1, i);
//            if (G_x < 0) {
//                G_x = G_x * -1;
//            }
//            int G = (int)G_x;
//            filtered_image.at<uchar>(j, i) = G;
//        }
//    }
//
//    for (int i = 0; i < filtered_image.cols; i++)
//    {
//        for (int j = 0; j < filtered_image.rows - 2; j++) {
//            double G_x = (double)filtered_image.at<uchar>(j, i) + filtered_image.at<uchar>(j + 1, i);
//            if (G_x < 0) {
//                G_x = G_x * -1;
//            }
//            int G = (int)G_x;
//            filtered_image.at<uchar>(j, i) = G;
//        }
//    }
//
//    namedWindow("NormalImage");
//    namedWindow("FilterImage");
//    imshow("NormalImage", image);
//    imshow("FilterImage", filtered_image);
//    waitKey();
//
//    return 0;
//}
