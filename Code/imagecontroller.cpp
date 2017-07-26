#include "imagecontroller.h"

#include <stdio.h>
#include <fstream>

using namespace cv;

ImageController::ImageController()
{
        maxwidth = 960;
        maxwith_wcell =100;

        String modelTxt = "celltype.prototxt";
        String modelBin = "celltype.caffemodel";


  /*      try                                     //Try to import Caffe GoogleNet model
        {

            importer = dnn::createCaffeImporter(modelTxt, modelBin);

        }
        catch (const cv::Exception &err)        //Importer can throw errors, we will catch them
        {
            std::cerr << err.msg << std::endl;
        }
        if (!importer)
        {
            std::cerr << "Can't load network by using the following files: " << std::endl;
            std::cerr << "prototxt:   " << modelTxt << std::endl;
            std::cerr << "caffemodel: " << modelBin << std::endl;
            std::cerr << "bvlc_googlenet.caffemodel can be downloaded here:" << std::endl;
            std::cerr << "http://dl.caffe.berkeleyvision.org/bvlc_googlenet.caffemodel" << std::endl;
            exit(-1);
        }


        cv::dnn::initModule();*/


}

QPixmap ImageController::ReadnewImage(string filename)
{
    Mat operateimg= imread(filename);
    Mat segmentedcells= ImageSegmentation(operateimg);
   //QImage img((uchar*)mat.data, mat.cols, mat.rows, QImage::Format_RGB32);



    QPixmap m_img = QPixmap::fromImage(QImage(segmentedcells.data, segmentedcells.cols,segmentedcells.rows, segmentedcells.step,QImage::Format_RGB888));



    return m_img;
}
bool ImageController::DeleteImage(int index)
{

    return true;
}

/* Find best class for the blob (i. e. class with maximal probability) */
/*void getMaxClass(dnn::Blob &probBlob, int *classId, double *classProb)
{
    Mat probMat = probBlob.matRefConst().reshape(1, 1); //reshape the blob to 1x1000 matrix
    imshow("aaa",probMat);
    Point classNumber;
    minMaxLoc(probMat, NULL, classProb, NULL, &classNumber);
    *classId = classNumber.x;
}
std::vector<String> readClassNames(const char *filename = "celltypes.txt")
{
    std::vector<String> classNames;
    std::ifstream fp(filename);
    if (!fp.is_open())
    {
        std::cerr << "File with classes labels not found: " << filename << std::endl;
        exit(-1);
    }
    std::string name;
    while (!fp.eof())
    {
        std::getline(fp, name);
        if (name.length())
            classNames.push_back( name.substr(name.find(' ')+1) );
    }
    fp.close();
    return classNames;
}

String ImageController::MakePrediction(Mat img)
{

       dnn::Net net;
       importer->populateNet(net);


       if (img.empty())
       {
           std::cerr << "Can't read image from the file: " << std::endl;
           exit(-1);
       }
       resize(img, img, Size(100, 100));       //GoogLeNet accepts only 224x224 RGB-images
       //Mat binphoto = imread("D:\PeripheralBloodSmear\DeepLearning\Image\mean.binaryproto",img.type());

       cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

       dnn::Blob inputBlob = dnn::Blob(img);  //Convert Mat to dnn::Blob image batch
       net.setBlob(".data", inputBlob);        //set the network input
       net.forward();                          //compute output
       dnn::Blob prob = net.getBlob("prob");   //gather output of "prob" layer
       int classId;
       double classProb;
       getMaxClass(prob, &classId, &classProb);//find the best class
       std::vector<String> classNames = readClassNames();

       return  classNames.at(classId);



}
*/
Mat ImageController::ImageSegmentation(Mat image)
{

    Mat gray_dest;
    Mat dist_trans;
    Mat sure_fg;
    Mat resized_obj;
        Mat dist_8u;
        RNG rng(12345);


    cvtColor(image,gray_dest,COLOR_BGR2GRAY);

    threshold(gray_dest,gray_dest,0,255,THRESH_BINARY_INV+THRESH_OTSU);






    int morph_size = 2;
    Mat element = getStructuringElement( MORPH_RECT, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

    morphologyEx( gray_dest, gray_dest, MORPH_OPEN, element, Point(-1,-1), 1 );

    dilate(gray_dest,element,3);



    erode(gray_dest,element,3);







    gray_dest.convertTo(dist_8u, CV_8U);



    // Find total markers
    vector<vector<Point> > contours;
    findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1);

    // Create the marker image for the watershed algorithm
        Mat markers = Mat::zeros(gray_dest.size(), CV_32SC1);
        // Draw the foreground markers
        for (int i = 0; i < contours.size(); i++)
        {
            Scalar color = Scalar( rng.uniform(0, 255));
            drawContours(markers, contours, i, color, 1);
        }
       // imshow("aaa",markers);
        // Draw the background marker
        circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);





        // Perform the watershed algorithm
           watershed(image, markers);
           Mat mark = Mat::zeros(markers.size(), CV_8UC1);
           markers.convertTo(mark, CV_8UC1);
           bitwise_not(mark, mark);
          // imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
                                         // image looks like at that point
           // Generate random colors

           /// Approximate contours to polygons + get bounding rects and circles
             vector<vector<Point> > contours_poly( contours.size() );
             vector<Rect> boundRect( contours.size() );
             vector<Point2f>center( contours.size() );
             vector<float>radius( contours.size() );

             for( int i = 0; i < contours.size(); i++ )
                { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
                  boundRect[i] = boundingRect( Mat(contours_poly[i]) );
                  minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
                }

            current_img = image.clone();
             /// Draw polygonal contour + bonding rects + circles

             for( int i = 0; i< contours.size(); i++ )
                {
                  Scalar color = Scalar( 0, 0, 0 );
                  //drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
            if(boundRect[i].area() < 100 || boundRect[i].area() > 50)
                  rectangle( image, boundRect[i].tl(), boundRect[i].br(), color, 0.5, 8, 0 );
                }

            foundsegmentobjects = contours.size();
            rectobjects = boundRect;
            resizeratio = (float)maxwidth / (float)image.cols;

            resize(image,resized_obj,Size(maxwidth,(int)(resizeratio * (float)image.rows)));
            cvtColor(resized_obj, resized_obj, CV_BGR2RGB);
            return resized_obj;
           // Visualize the final image
           //imshow("Final Result", image);
}

QPixmap ImageController::CropImage(QPoint m_pt)
{
    Rect m_rct;
    float pt_x = (float)m_pt.x() /resizeratio;
    float pt_y = (float)m_pt.y() /resizeratio;
    for( int i = 0; i< foundsegmentobjects; i++ )
       {
         m_rct = rectobjects[i];
         if(m_rct.contains(Point(pt_x,pt_y)))
             break;
       }
    Mat segmentedcells= current_img(m_rct);

    current_crop_img = segmentedcells.clone();
   //QImage img((uchar*)mat.data, mat.cols, mat.rows, QImage::Format_RGB32);
    resizeratio_c = (float)maxwith_wcell / (float)segmentedcells.cols;

    resize(segmentedcells,segmentedcells,Size(maxwith_wcell,(int)(resizeratio_c * (float)segmentedcells.rows)));

    QPixmap m_img = QPixmap::fromImage(QImage(segmentedcells.data, segmentedcells.cols, segmentedcells.rows, segmentedcells.step,QImage::Format_RGB888));


    return m_img;


}


QPixmap ImageController::ManuelCropImage(QPoint m_presspt,QPoint m_releasept)
{
    Rect m_rct;

    m_rct.x = (int)((float)m_presspt.x() /resizeratio);
    m_rct.y = (int)((float)m_presspt.y() /resizeratio);

    int r_pt_x = (int)((float)m_releasept.x() /resizeratio);
    int r_pt_y = (int)((float)m_releasept.y() /resizeratio);

    m_rct.width = r_pt_x - m_rct.x;
    m_rct.height = r_pt_y -m_rct.y;


    Mat segmentedcells= current_img(m_rct);

    current_crop_img = segmentedcells.clone();
   //QImage img((uchar*)mat.data, mat.cols, mat.rows, QImage::Format_RGB32);
    resizeratio_c = (float)maxwith_wcell / (float)segmentedcells.cols;

    resize(segmentedcells,segmentedcells,Size(maxwith_wcell,(int)(resizeratio_c * (float)segmentedcells.rows)));



    QPixmap m_img = QPixmap::fromImage(QImage(segmentedcells.data, segmentedcells.cols, segmentedcells.rows, segmentedcells.step,QImage::Format_RGB888));


    return m_img;


}

/*
String ImageController::AreaPrediction(QPoint m_presspt,QPoint m_releasept)
{
    Rect m_rct;

    m_rct.x = (int)((float)m_presspt.x() /resizeratio);
    m_rct.y = (int)((float)m_presspt.y() /resizeratio);

    int r_pt_x = (int)((float)m_releasept.x() /resizeratio);
    int r_pt_y = (int)((float)m_releasept.y() /resizeratio);

    m_rct.width = r_pt_x - m_rct.x;
    m_rct.height = r_pt_y -m_rct.y;


    Mat segmentedcells= current_img(m_rct);

    current_crop_img = segmentedcells.clone();

   //QImage img((uchar*)mat.data, mat.cols, mat.rows, QImage::Format_RGB32);
    //resizeratio_c = (float)maxwith_wcell / (float)segmentedcells.cols;

    //resize(segmentedcells,segmentedcells,Size(maxwith_wcell,(int)(resizeratio_c * (float)segmentedcells.rows)));


    return MakePrediction(current_crop_img);


}
*/




bool ImageController::SaveImageToFile(string filename)
{

    imwrite(filename,current_crop_img);

    return true;

}

