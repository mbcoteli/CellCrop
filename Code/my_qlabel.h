#ifndef MY_QLABEL_H
#define MY_QLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QToolTip>
#include <QRect>
#include <QRubberBand>

class my_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit my_qlabel(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *ev);

    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent* event);

    int queuenum;

    QPoint presspoint;
    QPoint releasepoint;

    QRubberBand *rubberband;


signals:

    void Mouse_Pressed(int number);

    void Select_Rectangle(QPoint m_point);

    void ManuelSelect_Rectangle(QPoint m_presspoint,QPoint m_releasepoint);

public slots:

};

#endif // MY_QLABEL_H
