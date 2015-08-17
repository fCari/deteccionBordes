#include <cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
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
bool buscarPts(Point v, Point tmp){
    for(int y=-1;y<=1;y++){
        for(int x=-1;x<=1;x++){
            cout<<"1 ---------"<<v<<" , "<<Point(tmp.x+x,tmp.y+y)<<endl;
            if((v==Point(tmp.x+x,tmp.y+y))){
                 cout<<"2 ---------"<<v<<" , "<<Point(tmp.x+x,tmp.y+y)<<endl;
                if(x==y&&x==0){
                    cout<<" ---------"<<endl;
                    getchar();
                    return true;
                    
                }
            }
        }
    }    
    return false;
}
int main() {
    /*
    std::vector<std::list<Point>> vect;
    vect.resize(100);

    
    vect[0].push_back(Point(3,4)); // ← !
    vect[0].push_back(Point(5,6));
    list<Point>::iterator it;
    for (it = vect[0].begin(); it != vect[0].end(); it++)
    std::cout << (*it)<< " , "<<endl;
    
   // cout<<vect[0].pop_back();
    cout<<"----fin------";
    */
    Mat img=imread("/home/fredy/imagenes/img/binary.jpg",0);
    Mat res=Mat::zeros(img.rows,img.cols, CV_8UC1);
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
    int px2=5555;
    vector<list<Point> > pts;
   
    int v=0;
    for(int y=2;y<img.rows-2;y++){
        for(int x=2;x<img.cols-2;x++){
            int px1=2*img.at<uchar>(y,x)-img.at<uchar>(y,x+1)-img.at<uchar>(y+1,x);
            if(px1>umbral){
                px1=umbral;                
            }
            if(px1==0){
                px2=2*img.at<uchar>(y,x)-img.at<uchar>(y,x-1)-img.at<uchar>(y-1,x);
                if(px2>umbral){
                       px2=umbral;
                }                
            }            
            if((px1==0&&px2!=0)||(px1!=0&&px2==0))
                res.at<uchar>(y,x)=umbral;
            //else if((px1==0&&px2==255)||(px1==255&&px2==0))
            //    res.at<uchar>(y,x)=255;
            else
                res.at<uchar>(y,x)=0;//mejor con px1 en vez de 0
            //----------------------GUARDAR EN VECTOR-----------------------------------
            int cont=0;
            cout<<"tamño de los puntoss:"<<pts.size()<<endl;
            if(pts.size()!=0){
                cout<<" ::: "<<v<<endl;
                for(int h=0;h<=v;h++){
                   // cout<<"  ::::::::::::: "<<pts[v].front()<<",.-"<<buscarPts(pts[v].front(),Point(4,5))<<endl;
                    //getchar();
                    cout<<" ::: "<<pts[v].back()<<" , "<<Point2d(x,y)<<" , "<<buscarPts(pts[v].back(),Point2d(x,y));
                    getchar();
                        if(buscarPts(pts[v].back(),Point2d(x,y))){
                           pts[v].push_back(Point2d(x,y));
                           cout<<" 1 ";
                        }else if(buscarPts(pts[v].front(),Point2d(x,y))){
                           pts[v].push_front(Point2d(x,y));
                           cout<<" 2 ";
                        }else{
                           cont++;  
                           cout<<" 3 ";
                        }
                        
                }
                if(cont==v+1){
                    cout<<" 4 ";
                    v++;
                    pts[v].push_back(Point(x,y));
                } 
            }else{
               pts.resize(100);
                pts[v].push_back(Point(x,y));
                cout<<" coorde:::"<<x<<" , "<<y<<endl;
                //pts[v].push_back(Point(x,y+1));
                //pts[v].push_back(Point(x,y+2));
                //list<Point>::iterator it;
                /*for (it = pts[0].begin(); it != pts[0].end(); it++)
                     cout << (*it)<< " , "<<endl;*/
                
            }       
        }
    }
    /*cout<<v<<endl;
    getchar();
    for(int h=0;h<=v;h++){
             list<Point>::iterator it;
                for (it = pts[h].begin(); it != pts[h].end(); it++)
                     cout << (*it)<< " , ";
             cout<<endl;
    }*/
    //namedWindow( "imagenes",CV_WINDOW_KEEPRATIO);
   // imshow("imagenes",res);
    waitKey(0);
    
    return 0;
}

