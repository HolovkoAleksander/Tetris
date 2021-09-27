#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

#define TOP 20
#define LEFT 20
#define WIDHT 300
#define HEIGHT 500
#define SIZE 20
#define SIZE_AREA_X ((HEIGHT-LEFT)/SIZE)
#define SIZE_AREA_Y ((WIDHT-TOP)/SIZE)
bool count=false;
uint16_t current_X=0;
uint16_t current_Y=0;
Qt::GlobalColor Area[SIZE_AREA_Y][SIZE_AREA_X]={Qt::white};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer= new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000); // И запустим таймер


ui->widget->setStyleSheet("* { background-color: rgb(255,255,255,50) }");

}
void MainWindow::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    QPainter qp(this);
    if(count){
        count=false;
        drawIMG(&qp);
    }
}

void MainWindow::drawIMG(QPainter *qp) {
    qp->drawRect(TOP, LEFT, WIDHT, HEIGHT);
    //qp->setPen(QPen (Qt::red, 5, Qt::SolidLine));
    current_Y++;

    T(qp,10, current_Y,ANGLE_0);



}

void MainWindow::slotTimerAlarm()
{
    count=true;
    update();
}

void MainWindow::drawPointBW(QPainter *qp,int x, int y, uint8_t Color){
     QPen pen(Qt::black, 1, Qt::SolidLine);
     pen.setColor(((Color)<<16) | ((Color)<<8) | (Color));
     qp->setPen(pen);
     qp->drawPoint(x,y);
}

void MainWindow::Square(QPainter *qp, int x, int y, Qt::GlobalColor Color)
{
    int Top=TOP+y*10;
    int Button=Top+10;
    int Left=LEFT+x*10;
    int Right=Left+10;
    int Height;
    int Width;
    Height = Button-Top;
    Width  = Right-Left;
    qp->fillRect(Left, Top, Width, Height,Color );
    qp->setPen(QPen (Qt::black, 1, Qt::SolidLine));
    qp->drawRect(Left, Top, Width, Height);
}


void MainWindow::keyPressEvent( QKeyEvent *event)
{
    qDebug() << event->key() ;
    if( event->key() == Qt::Key_A )
    {
        // do your stuff here
    }
}
void MainWindow::T(QPainter *qp,int x, int y, angle_t rotate)
{
    switch (rotate){
        case ANGLE_0:
        Square(qp,x-1,y,T_COLOR);
        Square(qp,x,y,T_COLOR);
        Square(qp,x+1,y,T_COLOR);
        Square(qp,x,y-1,T_COLOR);
        break;
        case ANGLE_90:
        break;
        case ANGLE_180:
        break;
        case ANGLE_270:
        break;

    }
}

void MainWindow::Q(QPainter *qp,int x, int y)
{

}

void MainWindow::I(QPainter *qp,int x, int y, angle_t rotate)
{
    switch (rotate){
        case ANGLE_0:
        break;
        case ANGLE_180:
        break;
        default:
        break;
    }
}
void MainWindow::Z(QPainter *qp,int x, int y, angle_t rotate)
{
    switch (rotate){
        case ANGLE_0:
        break;
        case ANGLE_180:
        break;
        default:
        break;
    }
}
void MainWindow::S(QPainter *qp,int x, int y, angle_t rotate)
{
    switch (rotate){
        case ANGLE_0:
        break;
        case ANGLE_180:
        break;
        default:
        break;
    }
}
void MainWindow::J(QPainter *qp,int x, int y, angle_t rotate)
{

        switch (rotate){
            case ANGLE_0:
            break;
            case ANGLE_180:
            break;
            default:
            break;
        }
}
void MainWindow::L(QPainter *qp,int x, int y, angle_t rotate)
{

        switch (rotate){
            case ANGLE_0:
            break;
            case ANGLE_180:
            break;
            default:
            break;
        }
}
MainWindow::~MainWindow()
{
    delete ui;
}

