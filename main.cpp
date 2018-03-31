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
#include "Transformation_to_2D.hpp"
#include "image_info.hpp"

using namespace std;
/*
void drawDepthmap(double x_map,double y_map, double depth){
    char depthmap_window[]="Drawing of Depthmap";
    Mat depthmap_image = Mat::zeros(w,w,CV_8UC3);
    
    
    
}
*/
int main() {
    string path = "/Users/estelle/Documents/faceFitResult/2D_Transformation/position.txt";
    string out_path ="/Users/estelle/Documents/faceFitResult/2D_Transformation/depth_map.bmp";
   
    trans_2D(path);
    recons_3D(out_path);
    
    input_image();
    return 0;
}
