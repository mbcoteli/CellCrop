#include "my_qlabel.h"

my_qlabel::my_qlabel(QWidget *parent) :
    QLabel(parent)
{

    rubberband = new QRubberBand(QRubberBand::Rectangle, this);
}

void my_qlabel::mousePressEvent(QMouseEvent *ev)
{
try{
    QPoint m_point= ev->pos();

    presspoint = m_point;
        //I want to have another function get the event position.
        //How would I achieve this? It's void!
        //Is there perhaps some way to set up a signal and slot with the position?
    if(this->queuenum==0)
        emit(Select_Rectangle(m_point));

        if (!rubberband)
            rubberband = new QRubberBand(QRubberBand::Rectangle, this);
        rubberband->setGeometry(QRect(presspoint, QSize()));
        rubberband->show();

    emit Mouse_Pressed(queuenum);
    }
    catch(const std::bad_alloc &)
    {}
}


void my_qlabel::mouseReleaseEvent(QMouseEvent *ev)
{
try{
   QPoint m_point= ev->pos();

   releasepoint = m_point;

   if(this->queuenum==0)
   emit(ManuelSelect_Rectangle(presspoint,releasepoint));

   rubberband->hide();



    }
    catch(const std::bad_alloc &)
    {}

}


void my_qlabel::mouseMoveEvent(QMouseEvent* event)
{
    try{
    QToolTip::showText(event->globalPos(),
                       //  In most scenarios you will have to change these for
                       //  the coordinate system you are working in.
                       QString::number( event->pos().x() ) + ", " +
                       QString::number( event->pos().y() ),
                       this, rect() );


    rubberband->setGeometry(QRect(presspoint, event->pos()).normalized());
    QWidget::mouseMoveEvent(event);  // Or whatever the base class is.
}
catch(const std::bad_alloc &)
{}
}
