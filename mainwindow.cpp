#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>
#include "block.h"

 QRandomGenerator *randomGenerat;
 uint8_t NextBlock;
 uint8_t CurBlock;
    uint32_t newTimer=1000;
    uint32_t prevTimer=1000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,timer(new QTimer())
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(newTimer); // И запустим таймер
    for (int y=0;y<SIZE_AREA_Y;y++ ) {
        for (int x=0;x< SIZE_AREA_X;x++) {
            block->Area[y][x]=Qt::white;
        }
    }
    config->open_Config(&configFile);
    Record=configFile.record;
    /*for (int x=1;x< SIZE_AREA_X;x++) {
        block->Area[SIZE_AREA_Y-1][x]=I_COLOR;
    }
    for (int x=1;x< SIZE_AREA_X;x++) {
        block->Area[SIZE_AREA_Y-2][x]=I_COLOR;
    }
    for (int x=1;x< SIZE_AREA_X;x++) {
        block->Area[SIZE_AREA_Y-3][x]=I_COLOR;
    }
    for (int x=1;x< SIZE_AREA_X;x++) {
        block->Area[SIZE_AREA_Y-4][x]=I_COLOR;
    }*/
    randomGenerat =  QRandomGenerator::global();
    ui->widget->setStyleSheet("* { background-color: rgb(255,255,255,50) }");
    NextBlock=randomGenerat->generate()%18;
    CurBlock=NextBlock;
    QFont font = ui->label->font();
    font.setPointSize(14);
    font.setBold(true);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);
    ui->label_6->setText("Record");
    ui->label_7->setText(QString::number(Record));
    ui->label_4->setText("Speed");
    ui->label_5->setText(QString::number(Speed));
    ui->label->setFont(font);
    ui->label_2->setText(QString::number(0));
    ui->label->setGeometry(NEXT_LEFT,NEXT_TOP-55,100,20);
    ui->label_2->setGeometry(NEXT_LEFT,NEXT_TOP+NEXT_HEIGHT+60,100,20);
    ui->label_3->setGeometry(NEXT_LEFT,NEXT_TOP+NEXT_HEIGHT+30,100,20);
    ui->label_4->setGeometry(NEXT_LEFT,NEXT_TOP+NEXT_HEIGHT+90,100,20);
    ui->label_5->setGeometry(NEXT_LEFT,NEXT_TOP+NEXT_HEIGHT+120,100,20);
    ui->label_6->setGeometry(NEXT_LEFT,20,100,20);
    ui->label_7->setGeometry(NEXT_LEFT,50,100,20);

}
void MainWindow::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    QPainter qp(this);
    Check_line();
    ui->label_2->setText(QString::number(points));
     ui->label_5->setText(QString::number(Speed));
    for (int y=0;y<SIZE_AREA_Y;y++ ) {
        for (int x=0;x< SIZE_AREA_X;x++) {
            Square_without_margin(&qp,x,y, block->Area[y][x]);
            if (block->Area[y][x]!=Qt::white){
                Square_margin(&qp,x,y);
                if (y==0) endGame=true;
            }
        }

    }
    if (endGame){
        qDebug() << "endGame";
        QLabel *labelEndGame = new QLabel(this);
        labelEndGame->setGeometry(LEFT+WIDHT+100,TOP+HEIGHT-50,100,20);
        labelEndGame->setText("END GAME");
        timer->stop();
        return;
    }
    currentBlock(&qp);
    if (points>Record) Record=points;
    ui->label_7->setText(QString::number(Record));
    if (points<10000){
        newTimer=1000;
        Speed=0;
    }else if (points<20000){
        newTimer=900;
        Speed=1;
    }else if (points<30000){
        Speed=2;
        newTimer=800;
    }else if (points<40000){
        Speed=3;
        newTimer=700;
    }else if (points<50000){
        Speed=4;
        newTimer=600;
    }else if (points<60000){
        Speed=5;
        newTimer=500;
    }else if (points<70000){
        Speed=6;
        newTimer=400;
    }else if (points<80000){
        Speed=7;
        newTimer=300;
    }else if (points<90000){
        Speed=8;
        newTimer=200;
    }else{
        Speed=9;
        newTimer=100;
    }
    if (newTimer!=prevTimer){
        prevTimer=newTimer;
        timer->start(newTimer);
    }
}

void MainWindow::currentBlock(QPainter *qp) {
    qp->drawRect(LEFT,TOP, WIDHT, HEIGHT);

    //qp->drawRect(NEXT_LEFT, NEXT_TOP, NEXT_WIGHT, NEXT_HEIGHT);
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

    }//CurBlock
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
    }//NextBlock
    switch (NextBlock) {
        case 0:
            block->nextT(qp, block::ANGLE_0);
            break;
        case 1:
            block->nextT(qp,block::ANGLE_90);
            break;
        case 2:
            block->nextT(qp,block::ANGLE_180);
            break;
        case 3:
            block->nextT(qp,block::ANGLE_270);
            break;
        case 4:
            block->nextQ(qp);
            break;
        case 5:
            block->nextI(qp, block::ANGLE_0);
            break;
        case 6:
            block->nextI(qp, block::ANGLE_180);
            break;
        case 7:
            block->nextZ(qp, block::ANGLE_0);
            break;
        case 8:
            block->nextZ(qp, block::ANGLE_180);
            break;
        case 9:
            block->nextS(qp, block::ANGLE_0);
            break;
        case 10:
            block->nextS(qp, block::ANGLE_180);
            break;
        case 11:
            block->nextJ(qp, block::ANGLE_0);
            break;
        case 12:
            block->nextJ(qp, block::ANGLE_90);
            break;
        case 13:
            block->nextJ(qp, block::ANGLE_180);
            break;
        case 14:
            block->nextJ(qp, block::ANGLE_270);
            break;
        case 15:
            block->nextL(qp, block::ANGLE_0);
            break;
        case 16:
            block->nextL(qp, block::ANGLE_90);
            break;
        case 17:
            block->nextL(qp, block::ANGLE_180);
            break;
        case 18:
            block->nextL(qp, block::ANGLE_270);
            break;
        default:
            break;
    }
    if (state){
      current_X= SIZE_AREA_X/2;
      current_Y=0;
      CurBlock=NextBlock;
      NextBlock=randomGenerat->generate()%18;
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
    int Top=TOP+y*SIZE;
    int Button=Top+SIZE;
    int Left=LEFT+x*SIZE;
    int Right=Left+SIZE;
    int Height;
    int Width;
    Height = Button-Top;
    Width  = Right-Left;
    qp->fillRect(Left+1, Top+1, Width-1, Height-1,Color );
}

void MainWindow::Square_margin(QPainter *qp, int x, int y)
{
    int Top=TOP+y*SIZE;
    int Button=Top+SIZE;
    int Left=LEFT+x*SIZE;
    int Right=Left+SIZE;
    int Height;
    int Width;
    Height = Button-Top;
    Width  = Right-Left;
    qp->setPen(QPen (Qt::black, 1, Qt::SolidLine));
    qp->drawRect(Left, Top, Width, Height);
}

void MainWindow::Check_line()
{
    bool line=true;
    uint8_t numLine=0;
    uint16_t eraseLine[4]={0,0,0,0};
    for (int y=(SIZE_AREA_Y-1);y!=0;y-- ) {
        line=true;
        for (int x=0;x< SIZE_AREA_X;x++) {
           if (block->Area[y][x]==Qt::white){
               line=false;
           }
        }
        if (line){
            eraseLine[numLine]=y;
            numLine++;

        }
    }
    if (numLine){
        qDebug() <<eraseLine[0] <<eraseLine[1] <<eraseLine[2] <<eraseLine[3];
       for (uint8_t i=0;i<4 ;i++ ) {
            if (eraseLine[i]){
                for (int st_Y=eraseLine[i]+i;st_Y!=1;st_Y--) {
                        for (int x=0;x< SIZE_AREA_X;x++) {
                           block->Area[st_Y][x]=block->Area[st_Y-1][x];
                        }
                 }
            }
        }
    }

   /* for (int st_Y=y;st_Y!=1;st_Y--) {
        for (int x=0;x< SIZE_AREA_X;x++) {
           block->Area[st_Y][x]=block->Area[st_Y-1][x];
        }
    }
    y=(SIZE_AREA_Y-1);*/
    //if (numLine) qDebug() << eraseLine[0] <<eraseLine[1] << eraseLine[2]  << eraseLine[3];
    switch (numLine){
    case 1: points+=100; break;
    case 2: points+=400; break;
    case 3: points+=800; break;
    case 4: points+=1600;break;
    default:
        break;
    }
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

void MainWindow::on_pushButton_5_clicked()
{
    configFile.points=points;
    configFile.record=Record;
    configFile.curNumber=CurBlock;
     configFile.nextNumber=NextBlock;
    for (int y=(SIZE_AREA_Y-1);y!=0;y-- ) {
        for (int x=0;x< SIZE_AREA_X;x++) {

            switch (block->Area[y][x]){
                case T_COLOR:configFile.area[y][x]=1; break;
                case Q_COLOR:configFile.area[y][x]=2; break;
                case I_COLOR:configFile.area[y][x]=3; break;
                case Z_COLOR:configFile.area[y][x]=4; break;
                case S_COLOR:configFile.area[y][x]=5; break;
                case J_COLOR:configFile.area[y][x]=6; break;
                case L_COLOR:configFile.area[y][x]=7; break;
            default:
                configFile.area[y][x]=0;
                break;

            }
        }

    }
   // memcpy((void *)&configFile.area,(void *)&block->Area,(SIZE_AREA_X*SIZE_AREA_Y));
    config->save_Config(&configFile);
}

void MainWindow::on_pushButton_6_clicked()
{
   config->open_Config(&configFile);
   points=configFile.points;
   Record=configFile.record;
   CurBlock=configFile.curNumber;
   NextBlock=configFile.nextNumber;
   for (int y=(SIZE_AREA_Y-1);y!=0;y-- ) {
       for (int x=0;x< SIZE_AREA_X;x++) {

           switch (configFile.area[y][x]){
               case 1:block->Area[y][x]=T_COLOR; break;
               case 2:block->Area[y][x]=Q_COLOR; break;
               case 3:block->Area[y][x]=I_COLOR; break;
               case 4:block->Area[y][x]=Z_COLOR; break;
               case 5:block->Area[y][x]=S_COLOR; break;
               case 6:block->Area[y][x]=J_COLOR; break;
               case 7:block->Area[y][x]=L_COLOR; break;
           default:
               block->Area[y][x]=NULL_COLOR;
               break;

           }
       }

   }
}


void MainWindow::on_pushButton_7_clicked()
{
    for (int y=0;y<SIZE_AREA_Y;y++ ) {
        for (int x=0;x< SIZE_AREA_X;x++) {
            block->Area[y][x]=Qt::white;
        }
    }
    NextBlock=randomGenerat->generate()%18;
    CurBlock=NextBlock;
    NextBlock=randomGenerat->generate()%18;
    timer->start(newTimer);
    endGame=false;
}

