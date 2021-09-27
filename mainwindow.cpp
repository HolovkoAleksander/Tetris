#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>




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
        currentBlock(&qp);
    }
}

void MainWindow::currentBlock(QPainter *qp) {
    qp->drawRect(TOP, LEFT, WIDHT, HEIGHT);
    //qp->setPen(QPen (Qt::red, 5, Qt::SolidLine));
    current_Y++;
    if (key_state!=RELASE){
        switch (key_state){
         case ENTER_st:
            if(angle) angle--;
            else angle=ANGLE_270;
            break;
        case RIGHT_st:
           if(current_X<SIZE_AREA_X) current_X++;
           break;
        case LEFT_st:
           if(current_X) current_X--;
           break;
        case DOWN_st:
           current_Y=SIZE_AREA_Y;
           break;
        default:
            break;
        }
        key_state=RELASE;
    }
    T(qp,current_X, current_Y,(angle_t)angle);


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
    switch (event->key()){

        case Qt::Key_Left:
            key_state=LEFT_st;
            break;
        case Qt::Key_Right:
            key_state=RIGHT_st;
            break;
        case Qt::Key_Down:
            key_state=DOWN_st;
            break;
        case Qt::Key_Enter:
            key_state=ENTER_st;
            break;
    }

    if( event->key() == Qt::Key_Left )
    {
        // do your stuff here
    }
}
void MainWindow::T(QPainter *qp,int x, int y, angle_t rotate)
{
    if (x<1) x=1;
    else if (x>(SIZE_AREA_X-1)) x=SIZE_AREA_X-1;
    if (y>(SIZE_AREA_Y-1)) y=(SIZE_AREA_Y-1);
    switch (rotate){
        case ANGLE_0:
            Square(qp,x-1,y,T_COLOR);
            Square(qp,x,y,T_COLOR);
            Square(qp,x+1,y,T_COLOR);
            Square(qp,x,y-1,T_COLOR);
            break;
        case ANGLE_90:
            Square(qp,x-1,y+1,T_COLOR);
            Square(qp,x-1,y,T_COLOR);
            Square(qp,x-1,y-1,T_COLOR);
            Square(qp,x,y,T_COLOR);
            break;
        case ANGLE_180:
            Square(qp,x-1,y,T_COLOR);
            Square(qp,x,y,T_COLOR);
            Square(qp,x+1,y,T_COLOR);
            Square(qp,x,y+1,T_COLOR);
            break;
        case ANGLE_270:
            Square(qp,x+1,y+1,T_COLOR);
            Square(qp,x+1,y,T_COLOR);
            Square(qp,x+1,y-1,T_COLOR);
            Square(qp,x,y,T_COLOR);
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

