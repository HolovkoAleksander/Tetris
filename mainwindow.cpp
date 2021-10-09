#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>
#include "block.h"

 QRandomGenerator *randomGenerat;
 uint8_t Next_Block;
 uint8_t CurBlock;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer= new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000); // И запустим таймер
    for (int y=0;y<SIZE_AREA_Y;y++ ) {
        for (int x=0;x< SIZE_AREA_X;x++) {
            block->Area[y][x]=Qt::white;
        }
    }
    randomGenerat =  QRandomGenerator::global();
    ui->widget->setStyleSheet("* { background-color: rgb(255,255,255,50) }");
    Next_Block=randomGenerat->generate()%18;
    CurBlock=Next_Block;

}
void MainWindow::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    QPainter qp(this);

    for (int y=0;y<SIZE_AREA_Y;y++ ) {
        for (int x=0;x< SIZE_AREA_X;x++) {
            Square_without_margin(&qp,x,y, block->Area[y][x]);
            if (block->Area[y][x]!=Qt::white)Square_margin(&qp,x,y);
        }
    }
    currentBlock(&qp);
}

void MainWindow::currentBlock(QPainter *qp) {
    qp->drawRect(LEFT,TOP, WIDHT, HEIGHT);

    qp->drawRect(NEXT_LEFT, NEXT_TOP, NEXT_WIGHT, NEXT_HEIGHT);
    //qp->setPen(QPen (Qt::red, 5, Qt::SolidLine));

    bool state=false;
    if(count){
        count=false;
        current_Y++;
    }
    if (key_state!=block::RELASE){
        switch (key_state){


        case block::DOWN_st:
           if (current_Y<SIZE_AREA_Y) current_Y++;
           break;
        default:
            break;
        }

    }
    switch (CurBlock) {
    case 0:
        state=block->T(qp, &current_Y,key_state,block::ANGLE_0);
        break;
    case 1:
        state=block->T(qp, &current_Y,key_state,block::ANGLE_90);
        break;
    case 2:
        state=block->T(qp, &current_Y,key_state,block::ANGLE_180);
        break;
    case 3:
        state=block->T(qp, &current_Y,key_state,block::ANGLE_270);
        break;
    case 4:
        state=block->Q(qp, &current_Y,key_state);
        break;
    case 5:
        state=block->I(qp, &current_Y,key_state,block::ANGLE_0);
        break;
    case 6:
        state=block->I(qp, &current_Y,key_state,block::ANGLE_180);
        break;
    case 7:
        state=block->Z(qp, &current_Y,key_state,block::ANGLE_0);
        break;
    case 8:
        state=block->Z(qp, &current_Y,key_state,block::ANGLE_180);
        break;
    case 9:
        state=block->S(qp, &current_Y,key_state,block::ANGLE_0);
        break;
    case 10:
        state=block->S(qp, &current_Y,key_state,block::ANGLE_180);
        break;
    case 11:
        state=block->J(qp, &current_Y,key_state,block::ANGLE_0);
        break;
    case 12:
        state=block->J(qp, &current_Y,key_state,block::ANGLE_90);
        break;
    case 13:
        state=block->J(qp, &current_Y,key_state,block::ANGLE_180);
        break;
    case 14:
        state=block->J(qp, &current_Y,key_state,block::ANGLE_270);
        break;
    case 15:
        state=block->L(qp, &current_Y,key_state,block::ANGLE_0);
        break;
    case 16:
        state=block->L(qp, &current_Y,key_state,block::ANGLE_90);
        break;
    case 17:
        state=block->L(qp, &current_Y,key_state,block::ANGLE_180);
        break;
    case 18:
        state=block->L(qp, &current_Y,key_state,block::ANGLE_270);
        break;
    default:
        break;
    }
    if (state){
      current_X= SIZE_AREA_X/2;
      current_Y=0;
      CurBlock=Next_Block;
      Next_Block=randomGenerat->generate()%18;
    }
    key_state=block::RELASE;
    update();
}



void MainWindow::drawPointBW(QPainter *qp,int x, int y, uint8_t Color){
     QPen pen(Qt::black, 1, Qt::SolidLine);
     pen.setColor(((Color)<<16) | ((Color)<<8) | (Color));
     qp->setPen(pen);
     qp->drawPoint(x,y);
}




void MainWindow::Square_without_margin(QPainter *qp, int x, int y, Qt::GlobalColor Color)
{
    int Top=TOP+y*10;
    int Button=Top+10;
    int Left=LEFT+x*10;
    int Right=Left+10;
    int Height;
    int Width;
    Height = Button-Top;
    Width  = Right-Left;
    qp->fillRect(Left+1, Top+1, Width-1, Height-1,Color );
}

void MainWindow::Square_margin(QPainter *qp, int x, int y)
{
    int Top=TOP+y*10;
    int Button=Top+10;
    int Left=LEFT+x*10;
    int Right=Left+10;
    int Height;
    int Width;
    Height = Button-Top;
    Width  = Right-Left;
    qp->setPen(QPen (Qt::black, 1, Qt::SolidLine));
    qp->drawRect(Left, Top, Width, Height);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent( QKeyEvent *event)
{
    switch (event->key()){
        case Qt::Key_Left:
            key_state=block::LEFT_st;
            break;
        case Qt::Key_Right:
            key_state=block::RIGHT_st;
            break;
        case Qt::Key_Down:
            key_state=block::DOWN_st;
            break;
        case Qt::Key_Space:
            key_state=block::ENTER_st;
            break;
    }
    update();
}
void MainWindow::slotTimerAlarm()
{
    count=true;
    update();
}
