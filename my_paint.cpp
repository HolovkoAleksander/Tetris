#include "my_paint.h"
#include <QPainter>

#include <QDebug>
#include <QDesktopWidget>
#include <QDateTime>
#include <QApplication>
#include <QString>


uint64_t time_st=0;
#define TIME_DELAY_ms       1000
int Button=40;
int Top=60;
int Left=5;
int Right=20;
int Height;
int Width;

my_paint::my_paint(QWidget *parent)
    :QWidget(parent,Qt::Window | Qt::FramelessWindowHint)
{

    setAttribute(Qt::WA_ShowWithoutActivating);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowTitle("my_paint");
    //show();



}
my_paint::~my_paint()
{

}
void my_paint::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    QPainter qp(this);
    drawIMG(&qp);
}

void my_paint::drawIMG(QPainter *qp) {

    qp->setPen(QPen (Qt::red, 5, Qt::SolidLine));



    Button++;

    Height = Button-Top;
    Width  = Right-Left;
    qp->drawRect(Left, Top, Width, Height);


    update();






}

void my_paint::drawPointBW(QPainter *qp,int x, int y, uint8_t Color){
     QPen pen(Qt::black, 1, Qt::SolidLine);
     pen.setColor(((Color)<<16) | ((Color)<<8) | (Color));
     qp->setPen(pen);
     qp->drawPoint(x,y);
}




