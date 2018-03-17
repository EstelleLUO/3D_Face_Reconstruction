#ifndef Data_Analysis_hpp
#define Data_Analysis_hpp

#include <stdio.h>
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
#include "math.h"
#include <vector>
#include "Data_Analysis.hpp"

using namespace std;
vector<double> Depth_Grouping(string path);
//Mat Histogram::DepthGrouping(const cv::Mat &image, int minValue);

#endif /* Data_Analysis_hpp */
