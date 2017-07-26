#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <imagematrix.h>

#include <QPixmap>

using namespace cv;
using namespace std;
class ImageController
{
public:
    ImageController();
    QPixmap ReadnewImage(string filename);
    bool DeleteImage(int index);
    Mat ImageSegmentation(Mat image);
    QPixmap CropImage(QPoint m_pt);
    QPixmap ManuelCropImage(QPoint m_presspt,QPoint m_releasept);
    Mat current_img;
    Mat current_crop_img;
    int foundsegmentobjects;
    vector<Rect> rectobjects;
    int maxwidth,maxwith_wcell;
    float resizeratio,resizeratio_c;
    bool SaveImageToFile(string filename);
    String MakePrediction(Mat croppedimg);
  //  String AreaPrediction(QPoint m_presspt,QPoint m_releasept);
    //Ptr<dnn::Importer>  importer;

};

#endif // IMAGECONTROLLER_H
