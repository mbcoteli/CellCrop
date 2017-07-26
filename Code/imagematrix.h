#ifndef IMAGEMATRIX_H
#define IMAGEMATRIX_H

//#include <opencv2/dnn.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QVector>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;
class imagematrix
{
enum cellcategory{none,eritrosit,bazofil};
public:
    imagematrix();
    Mat bigimage;
    QVector<Mat> celllist;
    QVector<cellcategory> celltype;

};



#endif // IMAGEMATRIX_H
