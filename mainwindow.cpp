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
    for (int y=0;y<SIZE_AREA_Y;y++ ) {
        for (int x=0;x< SIZE_AREA_X;x++) {
            Area[y][x]=Qt::white;
        }
    }

    ui->widget->setStyleSheet("* { background-color: rgb(255,255,255,50) }");

}
void MainWindow::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    QPainter qp(this);

    for (int y=0;y<SIZE_AREA_Y;y++ ) {
        for (int x=0;x< SIZE_AREA_X;x++) {
            Square_without_margin(&qp,x,y, Area[y][x]);
            if (Area[y][x]!=Qt::white)Square_margin(&qp,x,y);
        }
    }
    currentBlock(&qp);
}

void MainWindow::currentBlock(QPainter *qp) {
    qp->drawRect(TOP, LEFT, WIDHT, HEIGHT);
    //qp->setPen(QPen (Qt::red, 5, Qt::SolidLine));
    bool state=false;
    if(count){
        count=false;
        current_Y++;
    }
    if (key_state!=RELASE){
        switch (key_state){


        case DOWN_st:
           if (current_Y<SIZE_AREA_Y) current_Y++;
           break;
        default:
            break;
        }

    }
    state=J(qp, &current_Y,key_state);
    if (state){
      current_X= SIZE_AREA_X/2;
      current_Y=0;
    }
    key_state=RELASE;
    update();
}



void MainWindow::drawPointBW(QPainter *qp,int x, int y, uint8_t Color){
     QPen pen(Qt::black, 1, Qt::SolidLine);
     pen.setColor(((Color)<<16) | ((Color)<<8) | (Color));
     qp->setPen(pen);
     qp->drawPoint(x,y);
}





bool MainWindow::T(QPainter *qp,int x, int y, state_t key_state)
{
    qDebug() << key_state;
    static angle_t rotate=ANGLE_0;
    if (key_state!=RELASE){
        if (key_state==ENTER_st){
            switch(rotate){
                case ANGLE_0:  rotate=ANGLE_90;break;
                case ANGLE_90:  rotate=ANGLE_180;break;
                case ANGLE_180:  rotate=ANGLE_270;break;
                case ANGLE_270:  rotate=ANGLE_0;break;
            }

        }
    }

    if (x<1) x=1;
    else if (x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2 ;
    if (y>(SIZE_AREA_Y-1)) y=(SIZE_AREA_Y-1);
    else if (y<1) y=1;
    switch (rotate){
        case ANGLE_0:
            Square(qp,x-1,y, T_COLOR);
            Square(qp,x  ,y, T_COLOR);      //  0
            Square(qp,x+1,y, T_COLOR);      // 000
            Square(qp,x  ,y-1,T_COLOR);
            break;
        case ANGLE_90:
            Square(qp,x-1,y,T_COLOR);       // 0
            Square(qp,x-1,y-1,T_COLOR);         //00
            Square(qp,x-1,y-2,T_COLOR);       // 0
            Square(qp,x,y-1,T_COLOR);
            break;
        case ANGLE_180:
            Square(qp,x-1,y-2,T_COLOR);
            Square(qp,x,y-2,T_COLOR);         //
            Square(qp,x+1,y-2,T_COLOR);       //000
            Square(qp,x,y-1,T_COLOR);       // 0
            break;
        case ANGLE_270:
            Square(qp,x+1,y,T_COLOR);
            Square(qp,x+1,y-1,T_COLOR);       // 0
            Square(qp,x+1,y-2,T_COLOR);     //00
            Square(qp,x,y-1,T_COLOR);         // 0
            break;

    }
}

bool MainWindow::Q(QPainter *qp, int y, state_t key_state)
{
    static int x=SIZE_AREA_X/2;
    bool state=false;
    if (y==0) x=SIZE_AREA_X/2;
    switch (key_state) {
        case LEFT_st:
            if(x)
               if ((Area[y][x-1]==Qt::white)&&(Area[y-1][x-1]==Qt::white)) x--;
            break;
        case RIGHT_st:
            if(x<(SIZE_AREA_X-2))
               if ((Area[y][x+2]==Qt::white)&&(Area[y-1][x+2]==Qt::white)) x++;
            break;
        default:
            break;
    }
    if (y>(SIZE_AREA_Y-1)) y=(SIZE_AREA_Y-1);
    else if (y<1) y=1;
    Square(qp,x+1,y-1,Q_COLOR);
    Square(qp,x+1,y,Q_COLOR);       // 0
    Square(qp,x,y-1,Q_COLOR);     //00
    Square(qp,x,y,Q_COLOR);         // 0
    state |= checkArea (x+1,y);
    state |= checkArea (x,y);
    if (y==(SIZE_AREA_Y-1)) state=true;
    if (state){
        Area[y][x]=Q_COLOR;
        Area[y-1][x]=Q_COLOR;
        Area[y-1][x+1]=Q_COLOR;
        Area[y][x+1]=Q_COLOR;
        x=SIZE_AREA_X/2;
        return true;
    }
    return false;
}

bool MainWindow::I(QPainter *qp, int y, state_t key_state)
{
    static int x=SIZE_AREA_X/2;
    static angle_t rotate=ANGLE_0;
    bool state=false;


    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:  rotate=ANGLE_180;break;
            case ANGLE_180:  rotate=ANGLE_0;break;
        default:
            break;
        }
        case LEFT_st:
            if (rotate==ANGLE_0){
                if(x>1){
                    if (Area[y][x-2]==Qt::white) x--;
                }
            }else{
                if(x){
                    if ((Area[y][x-1]==Qt::white)&&(Area[y-1][x-1]==Qt::white)&&
                        (Area[y-2][x-1]==Qt::white)&&(Area[y+1][x-1]==Qt::white)) x--;
                }
            }
            break;
        case RIGHT_st:
            if (rotate==ANGLE_0){
                if(x<(SIZE_AREA_X-3))
                   if (Area[y][x+3]==Qt::white) x++;
            }else{
                if(x<(SIZE_AREA_X-1))
                    if ((Area[y][x+1]==Qt::white)&&(Area[y-1][x+1]==Qt::white)&&
                        (Area[y-2][x+1]==Qt::white)&&(Area[y+1][x+1]==Qt::white)) x++;
            }
            break;
        default:
            break;
    }
    switch (rotate){
        case ANGLE_0:
            if (y>(SIZE_AREA_Y)) y=(SIZE_AREA_Y);
            Square(qp,x+2,y,I_COLOR);
            Square(qp,x+1,y,I_COLOR);       // 0
            Square(qp,x,y,I_COLOR);     //00
            Square(qp,x-1,y,I_COLOR);
            state |= checkArea (x+2,y);
            state |= checkArea (x+1,y);
            state |= checkArea (x,y);
            state |= checkArea (x-1,y);
            if (state){
                Area[y][x+2]=I_COLOR;
                Area[y][x+1]=I_COLOR;
                Area[y][x]=I_COLOR;
                Area[y][x-1]=I_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_180:
            if (y>(SIZE_AREA_Y-2)) y=(SIZE_AREA_Y-2);
            else if (y<2) y=2;
            Square(qp,x,y-2,I_COLOR);
            Square(qp,x,y-1,I_COLOR);       // 0
            Square(qp,x,y,I_COLOR);     //00
            Square(qp,x,y+1,I_COLOR);
            state |= checkArea (x,y+1);
            if (state){
                Area[y-2][x]=I_COLOR;
                Area[y-1][x]=I_COLOR;
                Area[y][x]=I_COLOR;
                Area[y+1][x]=I_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
        break;
        default:
        break;
    }
    return false;
}
bool MainWindow::Z(QPainter *qp, int y, state_t key_state)
{
    static int x=SIZE_AREA_X/2;
    static angle_t rotate=ANGLE_0;
    bool state=false;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:  rotate=ANGLE_180;break;
            case ANGLE_180:  rotate=ANGLE_0;break;
        default:
            break;
        }
        break;
    case LEFT_st:
        if (rotate==ANGLE_0){
            if(x>2){
                if ((Area[y][x-2]==Qt::white)&&(Area[y-1][x-1]==Qt::white)) x--;
            }
        }else{
            if(x>1){
                if ((Area[y][x-2]==Qt::white)&&(Area[y-1][x-2]==Qt::white)&&
                    (Area[y+1][x-1]==Qt::white)) x--;
            }
        }
        break;
    case RIGHT_st:
        if (rotate==ANGLE_0){
            if(x<(SIZE_AREA_X-2))
               if ((Area[y-1][x+1]==Qt::white)&&(Area[y-1][x+2]==Qt::white)) x++;
        }else{
            if(x<(SIZE_AREA_X-1))
                if ((Area[y][x+2]==Qt::white)&&(Area[y+1][x+2]==Qt::white)&&
                    (Area[y-1][x+1]==Qt::white)) x++;
        }
        break;
    default:
        break;
    }

    switch (rotate){
        case ANGLE_0:
            if (y>(SIZE_AREA_Y-1)) y=(SIZE_AREA_Y-1);
            else if (y<2) y=2;
            Square(qp,x-1,y,Z_COLOR);
            Square(qp,x,y,Z_COLOR);       // 0
            Square(qp,x,y-1,Z_COLOR);     //00
            Square(qp,x+1,y-1,Z_COLOR);
            state |= checkArea (x-1,y);
            state |= checkArea (x,y);
            state |= checkArea (x,y-1);
            state |= checkArea (x+1,y-1);
            if (state){
                Area[y][x-1]=Z_COLOR;
                Area[y][x]=Z_COLOR;
                Area[y-1][x]=Z_COLOR;
                Area[y-1][x+1]=Z_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_180:
            if (y>(SIZE_AREA_Y-1)) y=(SIZE_AREA_Y-1);
            else if (y<2) y++;
            Square(qp,x,y,Z_COLOR);
            Square(qp,x,y+1,Z_COLOR);       // 0
            Square(qp,x-1,y,Z_COLOR);     //00
            Square(qp,x-1,y-1,Z_COLOR);
            state |= checkArea (x-1,y);
            state |= checkArea (x,y);
            state |= checkArea (x,y+1);
            state |= checkArea (x-1,y-1);
            if (state){
                Area[y][x-1]=Z_COLOR;
                Area[y][x]=Z_COLOR;
                Area[y+1][x]=Z_COLOR;
                Area[y-1][x-1]=Z_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        default:
        break;
    }
    return false;
}
bool MainWindow::S(QPainter *qp,int y, state_t key_state)
{
    static int x=SIZE_AREA_X/2;
    static angle_t rotate=ANGLE_0;
    bool state=false;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:  rotate=ANGLE_180;break;
            case ANGLE_180:  rotate=ANGLE_0;break;
        default:
            break;
        }
        break;
    case LEFT_st:
        if (rotate==ANGLE_0){
            if(x>2){
                if ((Area[y-1][x-2]==Qt::white)&&(Area[y][x-1]==Qt::white)) x--;
            }
        }else{
            if(x>1){
                if ((Area[y][x-2]==Qt::white)&&(Area[y+1][x-2]==Qt::white)&&
                    (Area[y-1][x-1]==Qt::white)) x--;
            }
        }
        break;
    case RIGHT_st:
        if (rotate==ANGLE_0){
            if(x<(SIZE_AREA_X-2))
               if ((Area[y-1][x+1]==Qt::white)&&(Area[y][x+2]==Qt::white)) x++;
        }else{
            if(x<(SIZE_AREA_X-1))
                if ((Area[y][x+1]==Qt::white)&&(Area[y-1][x+1]==Qt::white)&&
                    (Area[y-1][x+1]==Qt::white)) x++;
        }
        break;
    default:
        break;
    }

    switch (rotate){
        case ANGLE_0:
            if (y>(SIZE_AREA_Y-1)) y=(SIZE_AREA_Y-1);
            else if (y<2) y=2;
            Square(qp,x+1,y,S_COLOR);
            Square(qp,x,y,S_COLOR);       // 0
            Square(qp,x,y-1,S_COLOR);     //00
            Square(qp,x-1,y-1,S_COLOR);
            state |= checkArea (x-1,y-1);
            state |= checkArea (x,y);
            state |= checkArea (x,y-1);
            state |= checkArea (x+1,y);
            if (state){
                Area[y-1][x-1]=S_COLOR;
                Area[y][x]=S_COLOR;
                Area[y-1][x]=S_COLOR;
                Area[y][x+1]=S_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_180:
            if (y>(SIZE_AREA_Y-1)) y=(SIZE_AREA_Y-1);
            else if (y<2) y++;
            Square(qp,x-1,y,S_COLOR);
            Square(qp,x-1,y+1,S_COLOR);       // 0
            Square(qp,x,y,S_COLOR);     //00
            Square(qp,x,y-1,S_COLOR);
            state |= checkArea (x-1,y);
            state |= checkArea (x,y);
            state |= checkArea (x,y-1);
            state |= checkArea (x-1,y+1);
            if (state){
                Area[y][x-1]=S_COLOR;
                Area[y][x]=S_COLOR;
                Area[y+1][x-1]=S_COLOR;
                Area[y-1][x]=S_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        default:
        break;
    }
    return false;
}
bool MainWindow::J(QPainter *qp,uint16_t *y, state_t key_state)
{
    static int x=SIZE_AREA_X/2;
    static angle_t rotate=ANGLE_0;
    bool state=false;

    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:  rotate=ANGLE_90;break;
            case ANGLE_90:  rotate=ANGLE_180;break;
            case ANGLE_180:  rotate=ANGLE_270;break;
            case ANGLE_270:  rotate=ANGLE_0;break;
        }
        break;
    case LEFT_st:
        switch (rotate){
            case ANGLE_0:
                if(x>2)
                    if ((Area[*y-1][x-2]==Qt::white)&&(Area[*y][x-1]==Qt::white)) x--;
            break;
            case ANGLE_90:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y+1][x-2]==Qt::white)&&
                        (Area[*y-1][x-1]==Qt::white)) x--;
            break;
            case ANGLE_180:
                if(x>2)
                    if ((Area[*y-1][x-2]==Qt::white)&&(Area[*y][x-1]==Qt::white)) x--;
                break;
            case ANGLE_270:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y+1][x-2]==Qt::white)&&
                        (Area[*y-1][x-1]==Qt::white)) x--;
            break;
        }break;
    case RIGHT_st:
        switch (rotate){
            case ANGLE_0:
                if(x<(SIZE_AREA_X-2))
                   if ((Area[*y-1][x+1]==Qt::white)&&(Area[*y][x+2]==Qt::white)) x++;
                break;
            case ANGLE_90:
                if(x<(SIZE_AREA_X-1))
                    if ((Area[*y][x+1]==Qt::white)&&(Area[*y-1][x+1]==Qt::white)&&
                        (Area[*y-1][x+1]==Qt::white)) x++;
            break;
            case ANGLE_180:
                if(x<(SIZE_AREA_X-2))
                   if ((Area[*y-1][x+1]==Qt::white)&&(Area[*y][x+2]==Qt::white)) x++;
                break;
            case ANGLE_270:
                if(x<(SIZE_AREA_X-1))
                    if ((Area[*y][x+1]==Qt::white)&&(Area[*y-1][x+1]==Qt::white)&&
                        (Area[*y-1][x+1]==Qt::white)) x++;
            break;
        }
        break;
    default:
        break;
    }
    switch (rotate){
        case ANGLE_0:
            if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
            else if (*y<3) *y=3;
            Square(qp,x,*y-2, J_COLOR);
            Square(qp,x,*y-1, J_COLOR);      //  0
            Square(qp,x,*y, J_COLOR);      // 000
            Square(qp,x-1,*y,J_COLOR);
            state |= checkArea (x,*y-2);
            state |= checkArea (x,*y-1);
            state |= checkArea (x,*y);
            state |= checkArea (x-1,*y);
            if (state){
                Area[*y-2][x]=J_COLOR;
                Area[*y-1][x]=J_COLOR;
                Area[*y][x]=J_COLOR;
                Area[*y][x-1]=J_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_90:
        if (*y>(SIZE_AREA_Y)) *y=(SIZE_AREA_Y);
        else if (*y<1) y++;
            Square(qp,x-1,*y-1,J_COLOR);       // 0
            Square(qp,x,*y-1,J_COLOR);         //00
            Square(qp,x+1,*y-1,J_COLOR);       // 0
            Square(qp,x+1,*y,J_COLOR);
            state |= checkArea (x-1,*y-1);
            state |= checkArea (x,*y-1);
            state |= checkArea (x+1,*y-1);
            state |= checkArea (x+1,*y);
            if (state){
                Area[*y-1][x-1]=J_COLOR;
                Area[*y-1][x]=J_COLOR;
                Area[*y-1][x+1]=J_COLOR;
                Area[*y][x+1]=J_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_180:
        if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
        else if (*y<3) *y=3;
            Square(qp,x-1,*y, J_COLOR);
            Square(qp,x-1,*y-1, J_COLOR);      //  0
            Square(qp,x-1,*y-2, J_COLOR);      // 000
            Square(qp,x,*y-2,J_COLOR);
            state |= checkArea (x-1,*y);
            state |= checkArea (x-1,*y-1);
            state |= checkArea (x-1,*y-2);
            state |= checkArea (x,*y-2);
            if (state){
                Area[*y][x-1]=J_COLOR;
                Area[*y-1][x-1]=J_COLOR;
                Area[*y-2][x-1]=J_COLOR;
                Area[*y-2][x]=J_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_270:
            if (*y>(SIZE_AREA_Y)) *y=(SIZE_AREA_Y);
            else if (*y<1) y++;
            Square(qp,x+1,*y,J_COLOR);       // 0
            Square(qp,x,*y,J_COLOR);         //00
            Square(qp,x-1,*y-1,J_COLOR);       // 0
            Square(qp,x-1,*y,J_COLOR);
            state |= checkArea (x+1,*y);
            state |= checkArea (x,*y);
            state |= checkArea (x-1,*y-1);
            state |= checkArea (x-1,*y);
            if (state){
                Area[*y][x+1]=J_COLOR;
                Area[*y][x]=J_COLOR;
                Area[*y-1][x-1]=J_COLOR;
                Area[*y][x-1]=J_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
    }
    return false;
}
bool MainWindow::L(QPainter *qp,int x, int y, state_t key_state)
{
    static angle_t rotate=ANGLE_0;
    if (key_state!=RELASE){
        if (key_state==ENTER_st){
            switch(rotate){
                case ANGLE_0:  rotate=ANGLE_90;break;
                case ANGLE_90:  rotate=ANGLE_180;break;
                case ANGLE_180:  rotate=ANGLE_270;break;
                case ANGLE_270:  rotate=ANGLE_0;break;
            }
        }
    }

    if (x<1) x=1;
    else if (x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2 ;
    if (y>(SIZE_AREA_Y-1)) y=(SIZE_AREA_Y-1);
    else if (y<1) y=1;
    switch (rotate){
        case ANGLE_0:
            Square(qp,x-1,y-2, L_COLOR);
            Square(qp,x-1,y-1, L_COLOR);      //  0
            Square(qp,x-1,y, L_COLOR);      // 000
            Square(qp,x,y,L_COLOR);
            break;
        case ANGLE_90:
            Square(qp,x+1,y,L_COLOR);       // 0
            Square(qp,x+1,y-1,L_COLOR);       // 0
            Square(qp,x,y,L_COLOR);         //00
            Square(qp,x-1,y,L_COLOR);
            break;
        case ANGLE_180:
            Square(qp,x,y, L_COLOR);
            Square(qp,x,y-1, L_COLOR);      //  0
            Square(qp,x,y-2, L_COLOR);      // 000
            Square(qp,x-1,y-2,L_COLOR);
            break;
        case ANGLE_270:
            Square(qp,x-1,y-1,L_COLOR);       // 0
            Square(qp,x,y-1,L_COLOR);         //00
            Square(qp,x+1,y-1,L_COLOR);       // 0
            Square(qp,x-1,y,L_COLOR);
            break;
    }
}

bool MainWindow::checkArea(int x, int y)
{
    if (Area[y+1][x]!=Qt::white) return true;

    return false;
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
            key_state=LEFT_st;
            break;
        case Qt::Key_Right:
            key_state=RIGHT_st;
            break;
        case Qt::Key_Down:
            key_state=DOWN_st;
            break;
        case Qt::Key_Space:
            key_state=ENTER_st;
            break;
    }
    update();
}
void MainWindow::slotTimerAlarm()
{
    count=true;
    update();
}
