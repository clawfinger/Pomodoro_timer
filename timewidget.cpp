#include "timewidget.h"

TimeWidget::TimeWidget(QWidget *parent) :
    QWidget(parent), m_parentWidget(parent)
{
    //this->setMaximumSize(450, 80);
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
}

void TimeWidget::paintEvent(QPaintEvent *event)  //painting time digits
{
    QPainter painter(this);
    QFont timeFont;

    timeFont.setPixelSize(80);
    timeFont.setBold(true);
    painter.setFont(timeFont);


    QFontMetrics textMetrics = painter.fontMetrics();
   m_remainingTime = m_mainTimer->remainingTime()/1000;
    if(m_remainingTime <= 0){
        int leftDrawPoint = (this->width()-textMetrics.width("00:00"))/2;
        painter.setPen(Qt::black);
        painter.drawText(leftDrawPoint,(this->height()-25), "00:00");
        }
    else
    {
        int remainingMins = m_remainingTime/60;
        int remainingSecs = m_remainingTime%60;

        QString timeString;

        //providing zero symbol in time string example "18:09"

        if(remainingSecs > 9)
        {
            timeString = QString(QString::number(remainingMins)+":"+QString::number(remainingSecs));
        }
        else if(remainingSecs < 10)
        {
            timeString = QString(QString::number(remainingMins)+":0"+QString::number(remainingSecs));
        }
        int leftDrawPoint = (this->width()-textMetrics.width(timeString))/2;
         painter.setPen(Qt::blue);
        painter.drawText(leftDrawPoint,(this->height()-25), timeString);
    }
}

QSize TimeWidget::sizeHint() const
{
    //return QSize(250, 90);
    return QSize(m_parentWidget->width()-30, 90);
}

void TimeWidget::getTimer(QTimer* timer)
{
    m_mainTimer = timer;
}
