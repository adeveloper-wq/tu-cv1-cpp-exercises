// Holger Heidrich wt21
// Stereo Reconstruction with simple block matching
//#include "stdafx.h"

#ifdef _CH_
#pragma package <opencv>
#endif

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>

using namespace std;
using namespace cv;

#define MaxCost   100000.0
#define n_disp       16
#define BlockWidth   7

Mat cost[n_disp], imL, imR, imDisp;

int width, height;

char wndnameL[] = "LinkesBild";
char wndnameR[] = "RechtesBild";
char wndnameDisp[] = "DispBild";
char wndnameresR[] = "resRBild";
//-------------------------------------------------------------------
// helper function that produces visible images from out of 0..255 range images 
Mat Debugimg(Mat img, const String& filename = "")
{
    Mat gray_img(Size(img.rows, img.cols), CV_8U);
    double min_val, max_val;
    Point min_loc, max_loc;
    minMaxLoc(img, &min_val, &max_val, &min_loc, &max_loc);
    convertScaleAbs(img, gray_img, 255.0 / (max_val - min_val), -255.0 * min_val / (max_val - min_val));
    if (filename.empty()) imwrite("debug.png", gray_img);
    else                  imwrite(filename, gray_img);
    return gray_img;
}

//-------------------------------------------------------------------
int main(int argc, char** argv)
{

    // the image to load
    char* filename_l = argc == 3 ? argv[1] : (char*)"d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//visStudiotemp//ConsoleApplication1//tsukuba_L.png";
    char* filename_r = argc == 3 ? argv[2] : (char*)"d://Daten//Dokumente//Studium//2021-10-Computer-Vision-1//Exercise-1//visStudiotemp//ConsoleApplication1//tsukuba_R.png";

    Mat imFL, imFR, grey, imGT;
    int x, y, d, step;
    float* pCorrCost[n_disp];
    int mindisp;

    imFL = imread(filename_l, 1);
    if (imFL.empty())
    {
        std::cout << "couldn't load left image" << std::endl;
        return -1;
    }

    imFR = imread(filename_r, 1);
    if (imFR.empty())
    {
        std::cout << "couldn't load right image" << std::endl;
        return -1;
    }

    width = imFL.cols;
    height = imFL.rows;

    if ((width != imFR.cols) || (height != imFR.rows)) {
        std::cout << "Different image sizes - terminated!" << std::endl;
        return -1;
    }

    imFL.convertTo(imL, CV_32F);
    imFR.convertTo(imR, CV_32F);
    imDisp = Mat::zeros(imFL.size(), CV_8UC1);

    //// -> calc Matching costs, store a cost image for each Disparity
    clock_t start, finish;
    double  duration;
    start = clock();

    Mat iR, iL, idiff, iCost;
    for (d = 0; d < n_disp; d++)
    {
        cost[d].create(imFL.size(), CV_32FC1);
        cost[d] = MaxCost;
        // calc difference images 
        iR = imR(Rect(0, 0, width - d, height));
        iL = imL(Rect(d, 0, width - d, height));
        idiff = iR - iL;

        idiff = idiff.mul(idiff);

        iCost = cost[d](Rect(d, 0, width - d, height));

        Mat channels[3];
        split(idiff, channels);
        iCost = channels[0] + channels[1] + channels[2];
        blur(iCost, iCost, Size(BlockWidth, BlockWidth));
        //Debugimg(cost[d], "cost_" + to_string(d) + ".png");
    }

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "costs took: " << duration << "s." << std::endl;
    //// <- calc Matching costs, store a cost image for each Disparity

       // chose disparity with least cost:
    start = clock();
    step = cost[0].step;

    for (y = BlockWidth / 2; y < height - BlockWidth / 2; y++)
    {  // determine optimal disparity for each pixel in the row
        float mincost = 1.0e8;
        uchar* pimDisp = (uchar*)(imDisp.data + y * imDisp.step);

        for (d = 0; d < n_disp; d++)
        {
            //pCorrCost[d] = (float*)(cost[d].data + y * cost[d].step); //
            pCorrCost[d] = cost[d].ptr<float>(y);

            // pCorrCost[d]+=BlockWidth/2; 
        }
        for (x = 0; x < width - n_disp - (BlockWidth / 2); x++)
        {
            mincost = *pCorrCost[0];
            mindisp = 0;
            pCorrCost[0]++;                     // advance one pixel (next x) in cost image of disparity 0

            for (d = 1; d < n_disp; d++)
            {
                if (mincost > *pCorrCost[d])
                {
                    mincost = *pCorrCost[d];
                    mindisp = d;
                }
                pCorrCost[d]++;                  // advance one pixel (next x) in cost image of disparity d
            }
            *pimDisp++ = mindisp * 16; // make the disps visible
        }  // for (x=1; x<width; x++)
    }

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "best match select took: " << duration << "s." << std::endl;
    imwrite("imDisp.png", imDisp);
    medianBlur(imDisp, imDisp, 25);
    imwrite("imDispMedian.png", imDisp);
    ////// -> compare with ground truth: 
    //imGT = imread("images/tsukubatruedisp.jpg", 0);
    //if (imGT.empty())
    //{
    //    std::cout << "couldn't load gound truth image" << std::endl;
    //    return -1;
    //}

    // remove border (not filled in ground truth)
    //Mat GTmask = imGT > 0;
    //imDisp = imDisp & GTmask;
    //imwrite("GTmask.png", GTmask);
    imwrite("imDispMased.png", imDisp);

    //int PixCount = countNonZero(imGT);
    //absdiff(imGT, imDisp, imGT);
    //imwrite("Diff.png", imGT);
    //imGT = imGT > 18;  // allow disparity diff of 1 (grey level 16 in the image)
    //int DiffPixCount = countNonZero(imGT);
    //std::cout << "wrong pixels - DiffPix: " << (float)DiffPixCount * 100.0 / (float)(PixCount) << "%" << std::endl;
    ////// <- compare with ground truth 

    imwrite("Disp.png", imDisp);

    // Create a window
    namedWindow(wndnameL, 1);
    namedWindow(wndnameR, 1);
    namedWindow(wndnameDisp, 1);

    // Show the images
    imshow(wndnameL, imFL);
    imshow(wndnameR, imFR);
    imshow(wndnameDisp, imDisp);

    // Wait for a key stroke
    waitKey(0);
    return 0;
}
