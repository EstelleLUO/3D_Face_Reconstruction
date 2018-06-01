//
//  Reconstruction_to_3D.cpp
//  openCVTest
//
//  Created by Estelle on 09/03/2018.
//  Copyright © 2018 Estelle. All rights reserved.
//

#include "Reconstruction_to_3D.hpp"
#include "image_info.hpp"
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
#include "Data_Analysis.hpp"
#include "Reconstruction_to_3D.hpp"
#include <stdio.h>
#include <vector>
using namespace std;

/*
 * This file can read data from 2D depth map and then output a txt file
 * with data of each pixels in it
 */
int recons_3D(string path){
    // Recons_3D read into depth_map.bmp and carries out image processing on it
    // Then it outputs an new_depth_map which is new result_image
    Mat image = imread(path);
   
    Mat out_image;
    out_image = image.clone();
    
    
    int rows = out_image.rows;
    int cols = out_image.cols;
    
    vector<int> depth;
    int count=0;
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            count++;
            double current =(double)out_image.at<Vec3b>(i,j)[0];
            if (current!=0){
                depth.push_back(current);
                depth.push_back(count);
                count=0;
            }
        }
    }

    int mark =0;
    int step =1;
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            double current =(double)out_image.at<Vec3b>(i,j)[0];
            if (current==0){
                if (mark!=0 || mark!=depth.size()-1){
                    out_image.at<Vec3b>(i,j)[0]=((depth[mark+2])-depth[mark])/(depth[mark+1])*step+depth[mark];
                    out_image.at<Vec3b>(i,j)[1]=((depth[mark+2])-depth[mark])/(depth[mark+1])*step+depth[mark];
                    out_image.at<Vec3b>(i,j)[2]=((depth[mark+2])-depth[mark])/(depth[mark+1])*step+depth[mark];
                    step++;
                }
                else{
                    out_image.at<Vec3b>(i,j)[0]=0;
                    out_image.at<Vec3b>(i,j)[1]=0;
                    out_image.at<Vec3b>(i,j)[2]=0;
                    step++;
                }
            }
            else{
                mark=mark+2;
                step=1;
            }
        }
    }
    
    
    namedWindow("Display Window", WINDOW_AUTOSIZE);
    imshow("Display Window", out_image);
    imwrite("/Users/estelle/Documents/faceFitResult/2D_Transformation/new_depth_map.bmp", out_image);
    //waitKey(0);

    trans_3D("/Users/estelle/Documents/faceFitResult/2D_Transformation/new_depth_map.bmp");
    return 0;
}

void trans_3D(string path){
    // Get min and Max for further transformation
    
    Mat image = imread(path);
    int rows = image.rows;
    int cols = image.cols;
    
    const double pi = atan(1)*4;
    double x_map;
    double y_map;
    //unsigned char depth;
    double depth;
    double x_3d;
    double y_3d;
    double z_3d; // These three coordinates are in Mashlabs form, which is different from normal norm.
    
    vector<double> depth_grouping;
    string x_string;
    string y_string;
    string z_string;

    ifstream infile;
    string original_path = "/Users/estelle/Documents/faceFitResult/2D_Transformation/result.txt";
    infile.open(original_path, ios::in);
    while (!infile.eof()){
        infile >> x_string >> y_string >> z_string;
        string stream(x_string);
        double y = stod(x_string);
        double z = stod(y_string);
        double x = stod(z_string);
        
        double depth =sqrt(x*x+y*y+z*z);
        depth_grouping.push_back(depth);
    }
    
    vector<double>::iterator max = max_element(begin(depth_grouping), end(depth_grouping));
    vector<double>::iterator min = min_element(begin(depth_grouping), end(depth_grouping));
    
    double max_double = *max;
    double min_double = *min;
    cout << max_double<<"original max"<<endl;
    cout << min_double<<"original min"<<endl;
    ofstream outfile("/Users/estelle/Documents/faceFitResult/2D_Transformation/new_result.txt",ios::trunc);
    
    for (int i=cols/2;i<(3*cols/4);i++)
        //x>0 y>0 z>0
    // Why i = 360 cannot work?
    //for (int i = 361;i<540;i++)
    {
        x_map = i;
        for (int j = 0;j<(rows/2);j++)
        {
            y_map = j;
            depth = (double)image.at<Vec3b>(y_map,x_map)[0];
            if (depth == 0) continue;
            //new_depth = (double) depth;
            //cout << new_depth<<endl;
            depth = depth*(max_double - min_double)/255+min_double;
            y_3d = depth*cos(y_map*pi/(2*180));
            x_3d = depth*sin(y_map*pi/360)*sin((x_map-360)*pi/360);
            z_3d = depth*sin(y_map*pi/360)*cos((x_map-360)*pi/360);
            //if (x_3d!=0) cout << x_3d<<y_3d<<z_3d;
            outfile << x_3d <<" " << y_3d <<" "<< z_3d <<endl;
            
        }
        for (int j=rows/2;j<rows;j++)
        {
            y_map=j;
            depth = (double)image.at<Vec3b>(y_map,x_map)[0];
            if (depth == 0) continue;
            depth = depth*(max_double - min_double)/255+min_double;
            y_3d = - depth*cos((360-y_map)*pi/360);
            x_3d = depth*sin((360-y_map)*pi/360)*sin((x_map-360)*pi/360);
            z_3d = depth*sin((360-y_map)*pi/360)*cos((x_map-360)*pi/360);
            //if (x_3d!=0) cout << x_3d<<y_3d<<z_3d;
            outfile << x_3d <<" " << y_3d <<" "<< z_3d <<endl;
        }
    }
    
    for (int i=3*cols/4;i<cols;i++)
    //for (int i = 540;i<=720;i++)
    {
        x_map = i;
        for (int j = 0;j<(rows/2);j++)
        {
            y_map = j;
            depth = (double)image.at<Vec3b>(y_map,x_map)[0];
            if (depth == 0) continue;
            depth = depth*(max_double - min_double)/255+min_double;
            y_3d = depth*cos(y_map*pi/360);
            z_3d = - depth*sin(y_map*pi/360)*sin((x_map-540)*pi/360);
            x_3d = depth*sin(y_map*pi/360)*cos((x_map-540)*pi/360);
            //if (x_3d!=0) cout << x_3d<<y_3d<<z_3d;
            outfile << x_3d <<" " << y_3d <<" "<< z_3d <<endl;
            
        }
        for (int j=rows/2;j<rows;j++)
        {
            y_map=j;
            depth = (double)image.at<Vec3b>(y_map,x_map)[0];
            if (depth == 0) continue;
            depth = depth*(max_double - min_double)/255+min_double;
            y_3d = - depth*cos((360-y_map)*pi/360);
            z_3d = - depth*sin((360-y_map)*pi/360)*sin((x_map-540)*pi/360);
            x_3d = depth*sin((360-y_map)*pi/360)*cos((x_map-540)*pi/360);
            //if (x_3d!=0) cout << x_3d<<y_3d<<z_3d;
            outfile << x_3d <<" " << y_3d <<" "<< z_3d <<endl;
        }
    }
    
    for (int i=0;i<(cols/4);i++)
    //for (int i = 0;i<180;i++)
    {
        x_map = i;
        for (int j = 0;j<(rows/2);j++)
        {
            y_map = j;
            depth = (double)image.at<Vec3b>(y_map,x_map)[0];
            if (depth == 0) continue;
            depth = depth*(max_double - min_double)/255+min_double;
            y_3d = depth*cos((y_map)*pi/360);
            x_3d = - depth*sin((y_map)*pi/360)*sin(x_map*pi/360);
            z_3d = - depth*sin((y_map)*pi/360)*cos(x_map*pi/360);
            //if (x_3d!=0) cout << x_3d<<y_3d<<z_3d;
            outfile << x_3d <<" " << y_3d <<" "<< z_3d <<endl;
            
        }
        for (int j=rows/2;j<rows;j++)
        {
            y_map=j;
            depth = (double)image.at<Vec3b>(y_map,x_map)[0];
            if (depth == 0) continue;
            depth = depth*(max_double - min_double)/255+min_double;
            y_3d = - depth*cos((360-y_map)*pi/360);
            x_3d = - depth*sin((360-y_map)*pi/360)*sin(x_map*pi/360);
            z_3d = - depth*sin((360-y_map)*pi/360)*cos(x_map*pi/360);
            //if (x_3d!=0) cout << x_3d<<y_3d<<z_3d;
            outfile << x_3d <<" " << y_3d <<" "<< z_3d <<endl;
        }
    }
    
    for (int i=cols/4;i<(cols/2);i++)
    //for (int i = 180;i<360;i++)
    {
        x_map = i;
        for (int j = 0;j<(rows/2);j++)
        {
            y_map = j;
            depth = (double)image.at<Vec3b>(y_map,x_map)[0];
            if (depth == 0) continue;
            depth = depth*(max_double - min_double)/255+min_double;
            y_3d = depth*cos(y_map*pi/360);
            z_3d = depth*sin(y_map*pi/360)*sin((x_map-180)*pi/360);
            x_3d = - depth*sin(y_map*pi/360)*cos((x_map-180)*pi/360);
            outfile << x_3d <<" " << y_3d <<" "<< z_3d <<endl;
            
        }
        for (int j=rows/2;j<rows;j++)
        {
            y_map=j;
            depth = (double)image.at<Vec3b>(y_map,x_map)[0];
            if (depth == 0) continue;
            depth = depth*(max_double - min_double)/255+min_double;
            y_3d = -depth*cos((360-y_map)*pi/360);
            z_3d = depth*sin((360-y_map)*pi/360)*sin((x_map-180)*pi/360);
            x_3d = - depth*sin((360-y_map)*pi/360)*cos((x_map-180)*pi/360);
            //if (x_3d!=0) cout << x_3d<<y_3d<<z_3d;
            outfile << x_3d <<" " << y_3d <<" "<< z_3d <<endl;
        }
    }
    return;
}


