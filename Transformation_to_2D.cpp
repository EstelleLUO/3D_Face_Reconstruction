//
//  Transformation_to_2D.cpp
//  openCVTest
//
//  Created by Estelle on 08/03/2018.
//  Copyright © 2018 Estelle. All rights reserved.
//


/*
 * This cpp includes codes to transfrom 3D cloud map to 2D depthmap
 */
#include "Transformation_to_2D.hpp"

int trans_2D(string path){
    // Create a new image
    Mat image(360,720,CV_16UC1,Scalar(0));
    
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
    int i = 0;
    infile.open(path, ios::in);
    if (infile.fail()){
        cout << "error open!"<<endl;
    }
    depth_LUT = Depth_Grouping(path);
    while (!infile.eof()){
        infile >> x_string >> y_string >> z_string;
        double y = stod(x_string);
        double z = stod(y_string);
        double x = stod(z_string);
        // Divide the sphere into eight parts
        depth =sqrt(x*x+y*y+z*z);
        //int rows = image.rows;
        //int cols = image.cols;
        
        unsigned short int pixel = (unsigned short int)depth_LUT[i];
        
        if (x>0&&y>0&&z>=0){
            x_map = round(atan(y/x)*2/pi*180)+360;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        
        else if (x>0&&y==0&&z>=0)
        {
            x_map=360;
            y_map =round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        
        else if (x>0 && y<0&&z>=0){
            x_map = round(atan(x/(-y))*2/pi*180)+180;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
            
        }
        
        else if (x<0 && y>0&&z>=0){
            x_map = round(atan((-x)/y)*2/pi*180)+540;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        else if (x<0 && y==0&&z>=0){
            x_map = 540;
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
            
        else if(x<0 && y<0&&z>=0){
            x_map = round(atan(y/x)*2/pi*180);
            y_map = round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        
        else if (x>0&&y>0&&z<0){
            x_map = round(atan(y/x)*2/pi*180)+360;
            y_map = 360- round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        else if (x>0&&y==0&&z<0){
            x_map = 360;
            y_map = 360- round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }

        else if (x>0 && y<0&&z<0){
            x_map =round(atan(x/(-y))*2/pi*180)+180;
            y_map =360- round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        
        else if (x<0 && y>0&&z<0){
            x_map = round(atan((-x)/y)*2/pi*180)+540;
            y_map = 360- round(asin(sqrt(x*x+y*y)/depth)*2/pi*180);
        }
        else if (x<0 && y==0&&z<0){
            x_map = 540;
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
        image.at<ushort>(y_map,x_map) = pixel;
    
        i++;
    }
    
    // Save Image
    namedWindow("Display Window", WINDOW_AUTOSIZE);
    imshow("Display Window", image);
    imwrite("/Users/estelle/Documents/faceFitResult/2D_Transformation/depth_map.png", image);
    //waitKey(0);
    //destroyAllWindows();
    
    return 0;
}
