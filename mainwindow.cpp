#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>

int Button=40;
int Top=60;
int Left=45;
int Right=60;
int Height;
int Width;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


ui->widget->setStyleSheet("* { background-color: rgb(255,255,255,50) }");

}
void MainWindow::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    QPainter qp(this);
    drawIMG(&qp);
}

void MainWindow::drawIMG(QPainter *qp) {

    qp->setPen(QPen (Qt::red, 5, Qt::SolidLine));





    Height = Button-Top;
    Width  = Right-Left;
    qp->fillRect(Left, Top, Width, Height,Qt::red );
    qp->setPen(QPen (Qt::black, 1, Qt::SolidLine));
    qp->drawRect(Left, Top, Width, Height);

    update();
}

void MainWindow::drawPointBW(QPainter *qp,int x, int y, uint8_t Color){
     QPen pen(Qt::black, 1, Qt::SolidLine);
     pen.setColor(((Color)<<16) | ((Color)<<8) | (Color));
     qp->setPen(pen);
     qp->drawPoint(x,y);
}


void MainWindow::keyPressEvent( QKeyEvent *event)
{
    qDebug() << event->key() ;
    if( event->key() == Qt::Key_A )
    {
        // do your stuff here
    }
}
void MainWindow::T(int x, int y, angle_t rotate)
{
    switch (rotate){
        case ANGLE_0:
        break;
        case ANGLE_90:
        break;
        case ANGLE_180:
        break;
        case ANGLE_270:
        break;
    }
}

void MainWindow::Q(int x, int y)
{

}

void MainWindow::I(int x, int y, angle_t rotate)
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
void MainWindow::Z(int x, int y, angle_t rotate)
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
void MainWindow::S(int x, int y, angle_t rotate)
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
void MainWindow::J(int x, int y, angle_t rotate)
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
void MainWindow::L(int x, int y, angle_t rotate)
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

