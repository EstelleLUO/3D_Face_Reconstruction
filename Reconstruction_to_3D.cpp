//
//  Reconstruction_to_3D.cpp
//  openCVTest
//
//  Created by Estelle on 09/03/2018.
//  Copyright © 2018 Estelle. All rights reserved.
//

#include "Reconstruction_to_3D.hpp"

int recons_3D(){
    Mat image = imread("/Users/estelle/Documents/faceFitResult/2D_Transformation/depth_map.bmp");
    
    
    ofstream outfile("result.txt",ios::trunc);
    outfile<<image;
    outfile.close();
    return 0;
}
