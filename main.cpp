#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
using namespace cv;

#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "math.h"
#define w 400
#include "Data_Analysis.hpp"

using namespace std;
/*
void drawDepthmap(double x_map,double y_map, double depth){
    char depthmap_window[]="Drawing of Depthmap";
    Mat depthmap_image = Mat::zeros(w,w,CV_8UC3);
    
    
    
}
*/
int main() {
    // Create a new image
    Mat image(360,720,CV_8UC3,Scalar(0,0,0));
    
    string x_string;
    string y_string;
    string z_string;
    ifstream infile;
    const double pi = atan(1)*4;
    vector<double> depth_LUT;
    vector<double> depth_grouping;
    
    double x_map;
    double y_map;
    double depth;
    Vec3b pixel;
    int i = 0;
    infile.open("statue_head.txt", ios::in);
    if (infile.fail()){
        cout << "error open!"<<endl;
    }
    depth_LUT = Depth_Grouping();
    while (!infile.eof()){
        infile >> x_string >> y_string >> z_string;
        //string stream(x_string);
        //string stream(y_string);
        //string stream(z_string);
        double y = stod(x_string);
        double z = stod(y_string);
        double x = stod(z_string);
        // Divide the sphere into eight parts
        depth =sqrt(x*x+y*y+z*z);
        
        
        pixel[0] = depth_LUT[i];
        pixel[1] = depth_LUT[i];
        pixel[2] = depth_LUT[i];
        
        
        if (x>0&&y>=0&&z>=0){
            x_map = round(atan(y/x)*2/pi*180)+360;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
            /*
            pixel[0] = 255;
            pixel[1] = 0;
            pixel[2] = 0;
             */
        }
        
        /*
        if (y>=0&&z>=0){
            x_map = round(atan(y/x)*2/pi*180)+360;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        else if (y<0 && z>=0){
            x_map = 360 - round(atan((-y)/x)*2/pi*180);
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
         */
        
        else if (x>0 && y<0&&z>=0){
            x_map = round(atan(x/(-y))*2/pi*180)+180;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
            /*
            pixel[0] = 0;
            pixel[1] = 255;
            pixel[2] = 0;
             */
        }
        
        else if (x<0 && y>=0&&z>=0){
            x_map = round(atan((-x)/y)*2/pi*180)+540;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        else if(x<0 && y<0&&z>=0){
            x_map = round(atan(y/x)*2/pi*180);
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        
        /*
        else if (y>=0&&z<0){
            x_map = round(atan(y/x)*360/pi)+360;
            y_map = 180 - round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        
        else{
            x_map = 360 - round(atan((-y)/x)*360/pi);
            y_map = 180 - round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
         */
        
        else if (x>0&&y>=0&&z<0){
            x_map = round(atan(y/x)*2/pi*180)+360;
            y_map = 360- round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        else if (x>0 && y<0&&z<0){
            x_map =round(atan(x/(-y))*2/pi*180)+180;
            y_map =360- round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
         
        else if (x<0 && y>=0&&z<0){
            x_map = round(atan((-x)/y)*2/pi*180)+540;
            y_map = 360- round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        else if (x<0 && y<0&&z<0){
            x_map = round(atan(y/x)*2/pi*180);
            y_map = 360- round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
         
        else if (x==0 && y>=0&&z>=0){
            x_map = 540;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        else if (x==0&&y<0&&z>=0){
            x_map = 180;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        else if (x==0 && y>=0&&z<0){
            x_map = 540;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180)+180;
        }
        else{
            x_map = 180;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180)+180;
        }
        
        //cout << x_map<<"      x_map"<<endl;
        //cout << y_map << "        y_map"<<endl;
        image.at<Vec3b>(y_map,x_map) = pixel;
        i++;
    }
    /*
    for (int i = 0;i<image.rows;i++){
        for (int j =0;j<image.cols;j++){
            if (i == 0 || j==0){
                Vec3b pixel;
                pixel[0] = 255;
                pixel[1] = 255;
                pixel[2] = 0;
                image.at<Vec3b>(i,j) = pixel;
            }
        }
    }
     */
    // Save Image
    //imwrite("./Depth Map", image);
    namedWindow("Display Window", WINDOW_AUTOSIZE);
    imshow("Display Window", image);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
