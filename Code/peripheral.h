#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include <QDialog>
#include <QFileDialog>
#include "imagecontroller.h"
#include <QPixmap>


namespace Ui {
class Peripheral;
}

class Peripheral : public QDialog
{
    Q_OBJECT

public:
    explicit Peripheral(QWidget *parent = 0);
    ~Peripheral();
    ImageController * m_imagecontrol;
    int bigimg_h_diff;

private slots:
    void openfilehandle();
    void savecropimage();
    void Crop_Image(QPoint m_pt);  
    void ManuelSelect_Rectangle(QPoint m_presspt,QPoint m_releasept);
private:
    Ui::Peripheral *ui;
};

#endif // PERIPHERAL_H
