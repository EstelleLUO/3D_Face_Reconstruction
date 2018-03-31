//
//  Reconstruction_to_3D.cpp
//  openCVTest
//
//  Created by Estelle on 09/03/2018.
//  Copyright © 2018 Estelle. All rights reserved.
//

#include "Reconstruction_to_3D.hpp"

int recons_3D(string path){
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
            if (out_image.at<Vec3b>(i,j)[0]!=0){
                depth.push_back(out_image.at<Vec3b>(i,j)[0]);
                depth.push_back(count);
                count=0;
            }
        }
    }
    //for (int i = 0; i<depth.size();i++){
      //  cout<<depth[i]<<endl;
    //}
    int mark =0;
    int step =1;
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            if (out_image.at<Vec3b>(i,j)[0]==0){
                if (mark!=0 || mark!=depth.size()-2){
                    //cout<< mark+2<<endl;
                    //cout<<depth.size()<<endl;
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
                step=0;
            }
        }
    }

    
    
   
    
    namedWindow("Display Window", WINDOW_AUTOSIZE);
    imshow("Display Window", out_image);
    imwrite("/Users/estelle/Documents/faceFitResult/2D_Transformation/new_depth_map.bmp", out_image);
    //waitKey(0);
    
    ofstream outfile("new_result.txt",ios::trunc);
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            outfile<<out_image.at<Vec3b>(i,j)[0];
            cout<<out_image.at<Vec3b>(i,j)[0];
        }
    }
    //outfile<<out_image;
    outfile.close();
    waitKey(0);
    return 0;
}
