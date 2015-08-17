#include <cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/flann/flann.hpp>
#include <opencv2/legacy/legacy.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
using namespace std;
using namespace cv;
int BLACK=0;
int WHITE=255;

int main(int argc, char** argv) {
    Mat img=imread("/home/system/imagenes/img/binary.jpg",0);
    
    for(int i=0;i<img.rows;i++){
        for(int j=0;j<img.cols;j++){
            if(img.at<uchar>(i,j)<100){
            img.at<uchar>(i,j)=0;
            }else{
            img.at<uchar>(i,j)=255;
            }
        }
    }
    imshow("imagenes22",img);

    int umbral=255;
    
    
    for(int y=1;y<img.rows-1;y++){
        for(int x=1;x<img.cols-1;x++){
            int px=2*img.at<uchar>(y,x)-img.at<uchar>(y,x+1)-img.at<uchar>(y+1,x);
            int c=0;
            if(px>umbral){
                px=umbral;
                c++;
            }
            img.at<uchar>(y,x)=px;
            if(c==0){
                  px=2*img.at<uchar>(img.rows-y,img.cols-x)-img.at<uchar>(img.rows-y,img.cols-x-1)-img.at<uchar>(img.rows-y-1,img.cols-x);
                 if(px>umbral){
                        img.at<uchar>(img.rows-y,img.cols-x)=umbral;
                 }
                 }
            img.at<uchar>(img.rows-y,img.cols-x)=px;
        }
    }
    imshow("imagenes",img);
    waitKey(0);
    return 0;
}

