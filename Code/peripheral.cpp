#include "peripheral.h"
#include "ui_peripheral.h"

Peripheral::Peripheral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peripheral)
{
    ui->setupUi(this);

    connect(ui->openfile_button,SIGNAL(clicked()),this,SLOT(openfilehandle()));
    connect(ui->save_celltypes_button,SIGNAL(clicked()),this,SLOT(savecropimage()));

    connect(ui->image_label,SIGNAL(Select_Rectangle(QPoint)),this,SLOT(Crop_Image(QPoint)));ui->image_label->queuenum =0;
    connect(ui->image_label,SIGNAL(ManuelSelect_Rectangle(QPoint,QPoint)),this,SLOT(ManuelSelect_Rectangle(QPoint,QPoint)));ui->image_label->queuenum =0;

    m_imagecontrol = new ImageController();

       for(int k=0;k <4;k++)
       {
        QListWidgetItem * item = new QListWidgetItem();
        if(k==0)
        {
            item->setText( "None");
            item->setIcon(QIcon("../icon/None.png"));
            item->setSizeHint(QSize(item->sizeHint().width(), 30));
        }
        else if(k==1)
        {
            item->setText( "Eritrosit");
           item->setIcon(QIcon("../icon/eritrosit.png"));
           item->setSizeHint(QSize(item->sizeHint().width(), 30));
        }
        else if(k==2)
        {
            item->setText( "2Eritrosit");
            item->setIcon(QIcon("../icon/2eritrosit.png"));
            item->setSizeHint(QSize(item->sizeHint().width(), 30));
        }
        else if(k==3)
        {
            item->setText( "Bazofil");
            item->setIcon(QIcon("../icon/Bazofil.png"));
            item->setSizeHint(QSize(item->sizeHint().width(), 30));
        }
        ui->celllist_widget->addItem(item);
        }



}

Peripheral::~Peripheral()
{
    delete ui;
}

void Peripheral::openfilehandle()
{


QString fileName = QFileDialog::getOpenFileName(this,tr("Select Wav File"),"D:\\Lifatek_Technical\\OYPC\\images",tr("Image files (*.jpg)"));

if(!fileName.isEmpty())
{
std::string image_location = fileName.toLocal8Bit().constData();

QPixmap m_img = m_imagecontrol->ReadnewImage(image_location);

bigimg_h_diff = ui->image_label->height() - m_img.height();

ui->image_label->setPixmap(m_img);
}

}

void Peripheral::savecropimage()
{
    QString s = ui->celllist_widget->currentItem()->text();
    int randomValue = qrand();
    int randomValue_2 = qrand();
    QString filename = "../Image/" + s + "_"+QString::number(randomValue)+ QString::number(randomValue_2) +".png"; // CORRECT

    std::string utf8_text = filename.toUtf8().constData();

   m_imagecontrol->SaveImageToFile(utf8_text);


}

void Peripheral::Crop_Image(QPoint m_pt)
{
    if(ui->selection_type->isChecked())
    {
    QPoint m_crop = m_pt;

    m_crop.setY(m_pt.y()-bigimg_h_diff/2);

    QPixmap m_img = m_imagecontrol->CropImage(m_crop);

    ui->cell_label->setPixmap(m_img);
}

}


void Peripheral::ManuelSelect_Rectangle(QPoint m_presspt,QPoint m_releasept)
{

    ui->Result_value->setText(QDir::currentPath());
    if(ui->selection_type->isChecked())
    {
        QPoint m_crop_press = m_presspt;
        QPoint m_crop_release = m_releasept;

        if(m_crop_release.x() -m_crop_press.x() < 10 )
            return;

        m_crop_press.setY(m_presspt.y()-bigimg_h_diff/2);
        m_crop_release.setY(m_releasept.y()-bigimg_h_diff/2);

        QPixmap m_img = m_imagecontrol->ManuelCropImage(m_crop_press,m_crop_release);

        ui->cell_label->setPixmap(m_img);

      //  String result = m_imagecontrol->AreaPrediction(m_crop_press,m_crop_release);

      //  ui->Result_value->setText(QString::fromStdString(result));


    }




}
