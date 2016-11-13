#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QString>
#include <QFont>

class TimeWidget : public QWidget
{
    Q_OBJECT
private:
    QWidget* m_parentWidget;
    QTimer* m_mainTimer;
    int m_remainingTime;
public:
    explicit TimeWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const;
public slots:
    //void updateTime();
    void getTimer(QTimer*);
};

#endif // TIMEWIDGET_H
