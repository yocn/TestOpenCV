//
//  main.cpp
//  TestOpenCV
//
//  Created by 赵英坤 on 2018/8/7.
//  Copyright © 2018年 赵英坤. All rights reserved.
//

#include <iostream>
#include "opencv2\opencv.hpp"
#include "cxcore.hpp"
#include "opencv2\highgui\highgui.hpp"

using namespace cv;
using namespace std;

int edgeThresh = 1;

// 声明 原始图片，灰度图片，和 canny边缘图片
Mat image, cedge;
Mat gray, edge;

void onTrackbar(int, void*)
{
    //blur 灰度图片
    blur(gray, edge, Size(3,3));
    
    // Canny 边缘检测
    Canny(gray,edge, edgeThresh, edgeThresh*3, 3);
    
    //全部设为0
    cedge = Scalar::all(0);
    
    //拷贝边缘的象素点
    image.copyTo(cedge, edge);
    
    imshow("Edge map", edge);
    
}

int main(int argc, char** argv)
{
    
    
    // 载入图片
    image = imread(argv[1], 1);
    
    // 判断载入图片是否成功
    if(image.empty())
    {
        printf("miss the image file: %d \n", argv[1]);
        return -1;
    }
    
    // 生成灰度图片，因为只有灰度图片才能生成边缘图片
    cedge.create(image.size(), image.type());
    cvtColor(image,gray, CV_BGR2GRAY);
    
    //新建一个窗口
    namedWindow("Edge map", 1);
    
    // 生成一个进度条来控制边缘检测
    createTrackbar("Canny Threshold", "Edge map", &edgeThresh, 100, onTrackbar);
    
    //初始化图像
    onTrackbar(0,0);
    
    waitKey(0);
    
    return 0;
}
