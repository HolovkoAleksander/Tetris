#include "block.h"

block::block(QObject *parent) : QObject(parent)
{

}




bool block::T(QPainter *qp,uint16_t *y, state_t key_state, angle_t rotate_s)
{
    static uint16_t x=SIZE_AREA_X/2;
    static angle_t rotate;
    if (*y==0) rotate=rotate_s;
    bool state=false;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:
                rotate=ANGLE_90;
                break;
            case ANGLE_90:
                if ((Area[*y-2][x-1]==Qt::white)&&(Area[*y-1][x+1]==Qt::white))
                rotate=ANGLE_180;
                if(x>(SIZE_AREA_X-1)) x=SIZE_AREA_X-1;
                break;
            case ANGLE_180:
                rotate=ANGLE_270;
                break;
            case ANGLE_270:
                if ((Area[*y][x-1]==Qt::white)&&(Area[*y][x+1]==Qt::white))
                rotate=ANGLE_0;
                if(x>(SIZE_AREA_X-1)) x=SIZE_AREA_X-1;
                break;
        }
        break;
    case LEFT_st:
        switch (rotate){
            case ANGLE_0:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-1]==Qt::white)) x--;
            break;
            case ANGLE_90:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)&&(Area[*y-2][x-2]==Qt::white)) x--;
            break;
            case ANGLE_180:
                if(x>1)
                    if ((Area[*y-2][x-2]==Qt::white)&&(Area[*y-1][x-1]==Qt::white)) x--;
                break;
            case ANGLE_270:
                    if (x)
                        if ((Area[*y-1][x-1]==Qt::white)&&(Area[*y][x]==Qt::white)&&(Area[*y-2][x]==Qt::white)) x--;

            break;
        }break;
    case RIGHT_st:
        switch (rotate){
            case ANGLE_0:
                if(x<(SIZE_AREA_X-2))
                   if ((Area[*y][x+2]==Qt::white)&&(Area[*y-1][x+1]==Qt::white)) x++;
                break;
            case ANGLE_90:
                if(x<(SIZE_AREA_X-1))
                    if ((Area[*y][x]==Qt::white)&&(Area[*y-1][x]==Qt::white)&&(Area[*y-2][x]==Qt::white)) x++;
            break;
            case ANGLE_180:
                if(x<(SIZE_AREA_X-2))
                   if ((Area[*y-2][x+2]==Qt::white)&&(Area[*y-1][x+1]==Qt::white)) x++;
                break;
            case ANGLE_270:
                if(x<(SIZE_AREA_X-2))
                    if ((Area[*y-1][x+1]==Qt::white)&&(Area[*y][x+2]==Qt::white)&&(Area[*y-2][x+2]==Qt::white))x++;
            break;
        }
        break;
    default:
        break;
    }



    switch (rotate){
        case ANGLE_0:
            if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
            else if (*y<1) *y=1;
            Square(qp,x-1,*y, T_COLOR);
            Square(qp,x  ,*y, T_COLOR);      //  0
            Square(qp,x+1,*y, T_COLOR);      // 000
            Square(qp,x  ,*y-1,T_COLOR);
            state |= checkArea (x-1,*y);
            state |= checkArea (x,*y);
            state |= checkArea (x+1,*y);
            state |= checkArea (x,*y-1);
            if (state){
                Area[*y][x-1]=T_COLOR;
                Area[*y][x]=T_COLOR;
                Area[*y][x+1]=T_COLOR;
                Area[*y-1][x]=T_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_90:
            if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
            else if (*y<2) *y=2;
            Square(qp,x-1,*y,T_COLOR);       // 0
            Square(qp,x-1,*y-1,T_COLOR);         //00
            Square(qp,x-1,*y-2,T_COLOR);       // 0
            Square(qp,x,*y-1,T_COLOR);
            state |= checkArea (x-1,*y);
            state |= checkArea (x-1,*y-1);
            state |= checkArea (x-1,*y-2);
            state |= checkArea (x,*y-1);
            if (state){
                Area[*y][x-1]=T_COLOR;
                Area[*y-1][x-1]=T_COLOR;
                Area[*y-2][x-1]=T_COLOR;
                Area[*y-1][x]=T_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_180:
            if (*y>(SIZE_AREA_Y)) *y=(SIZE_AREA_Y);
            else if (*y<2) *y=2;
            Square(qp,x-1,*y-2,T_COLOR);
            Square(qp,x,*y-2,T_COLOR);         //
            Square(qp,x+1,*y-2,T_COLOR);       //000
            Square(qp,x,*y-1,T_COLOR);       // 0
            state |= checkArea (x-1,*y-2);
            state |= checkArea (x,*y-2);
            state |= checkArea (x+1,*y-2);
            state |= checkArea (x,*y-1);
            if (state){
                Area[*y-2][x-1]=T_COLOR;
                Area[*y-2][x]=T_COLOR;
                Area[*y-2][x+1]=T_COLOR;
                Area[*y-1][x]=T_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_270:
            if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
            else if (*y<2) *y=2;
            Square(qp,x+1,*y,T_COLOR);
            Square(qp,x+1,*y-1,T_COLOR);       // 0
            Square(qp,x+1,*y-2,T_COLOR);     //00
            Square(qp,x,*y-1,T_COLOR);         // 0
            state |= checkArea (x+1,*y);
            state |= checkArea (x+1,*y-1);
            state |= checkArea (x+1,*y-2);
            state |= checkArea (x,*y-1);
            if (state){
                Area[*y][x+1]=T_COLOR;
                Area[*y-1][x+1]=T_COLOR;
                Area[*y-2][x+1]=T_COLOR;
                Area[*y-1][x]=T_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
    }
    return false;
}

bool block::Q(QPainter *qp, uint16_t *y, state_t key_state)
{
    static uint16_t x=SIZE_AREA_X/2;
    bool state=false;
    if (*y==0) x=SIZE_AREA_X/2;
    switch (key_state) {
        case LEFT_st:
            if(x)
               if ((Area[*y][x-1]==Qt::white)&&(Area[*y-1][x-1]==Qt::white)) x--;
            break;
        case RIGHT_st:
            if(x<(SIZE_AREA_X-2))
               if ((Area[*y][x+2]==Qt::white)&&(Area[*y-1][x+2]==Qt::white)) x++;
            break;
        default:
            break;
    }
    if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
    else if (*y<1) *y=1;
    Square(qp,x+1,*y-1,Q_COLOR);
    Square(qp,x+1,*y,Q_COLOR);       // 0
    Square(qp,x,*y-1,Q_COLOR);     //00
    Square(qp,x,*y,Q_COLOR);         // 0
    state |= checkArea (x+1,*y);
    state |= checkArea (x,*y);
    if (*y==(SIZE_AREA_Y-1)) state=true;
    if (state){
        Area[*y][x]=Q_COLOR;
        Area[*y-1][x]=Q_COLOR;
        Area[*y-1][x+1]=Q_COLOR;
        Area[*y][x+1]=Q_COLOR;
        x=SIZE_AREA_X/2;
        return true;
    }
    return false;
}

bool block::I(QPainter *qp, uint16_t *y, state_t key_state, angle_t rotate_s)
{
    static uint16_t x=SIZE_AREA_X/2;
    static angle_t rotate;
    if (*y==0) rotate=rotate_s;
    bool state=false;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:
                rotate=ANGLE_180;
                break;
            case ANGLE_180:
                if ((Area[*y][x-1]==Qt::white)&&(Area[*y][x]==Qt::white)&&
                    (Area[*y][x+1]==Qt::white)&&(Area[*y][x+2]==Qt::white))
                    rotate=ANGLE_0;
                break;
            default:
                break;
        }break;
        case LEFT_st:
            if (rotate==ANGLE_0){
                if(x>1){
                    if (Area[*y][x-2]==Qt::white) x--;
                }
            }else{
                if(x){
                    if ((Area[*y][x-1]==Qt::white)&&(Area[*y-1][x-1]==Qt::white)&&
                        (Area[*y-2][x-1]==Qt::white)&&(Area[*y+1][x-1]==Qt::white)) x--;
                }
            }
            break;
        case RIGHT_st:
            if (rotate==ANGLE_0){
                if(x<(SIZE_AREA_X-3))
                   if (Area[*y][x+3]==Qt::white) x++;
            }else{
                if(x<(SIZE_AREA_X-1))
                    if ((Area[*y][x+1]==Qt::white)&&(Area[*y-1][x+1]==Qt::white)&&
                        (Area[*y-2][x+1]==Qt::white)&&(Area[*y+1][x+1]==Qt::white)) x++;
            }
            break;
        default:
            break;
    }
    switch (rotate){
        case ANGLE_0:
            if (*y>(SIZE_AREA_Y)) *y=(SIZE_AREA_Y);
            Square(qp,x+2,*y,I_COLOR);
            Square(qp,x+1,*y,I_COLOR);       // 0
            Square(qp,x,*y,I_COLOR);     //00
            Square(qp,x-1,*y,I_COLOR);
            state |= checkArea (x+2,*y);
            state |= checkArea (x+1,*y);
            state |= checkArea (x,*y);
            state |= checkArea (x-1,*y);
            if (state){
                Area[*y][x+2]=I_COLOR;
                Area[*y][x+1]=I_COLOR;
                Area[*y][x]=I_COLOR;
                Area[*y][x-1]=I_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_180:
            if (*y>(SIZE_AREA_Y-2)) *y=(SIZE_AREA_Y-2);
            else if (*y<2) *y=2;
            Square(qp,x,*y-2,I_COLOR);
            Square(qp,x,*y-1,I_COLOR);       // 0
            Square(qp,x,*y,I_COLOR);     //00
            Square(qp,x,*y+1,I_COLOR);
            state |= checkArea (x,*y+1);
            if (state){
                Area[*y-2][x]=I_COLOR;
                Area[*y-1][x]=I_COLOR;
                Area[*y][x]=I_COLOR;
                Area[*y+1][x]=I_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
        break;
        default:
        break;
    }
    return false;
}
bool block::Z(QPainter *qp, uint16_t *y, state_t key_state, angle_t rotate_s)
{
    static uint16_t x=SIZE_AREA_X/2;
    static angle_t rotate;
    if (*y==0) rotate=rotate_s;
    bool state=false;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:  rotate=ANGLE_180;break;
            case ANGLE_180:
                if ((Area[*y][x-1]!=Qt::white)&&(Area[*y-1][x+1]!=Qt::white))
                rotate=ANGLE_0;
                break;
        default:
            break;
        }
        break;
    case LEFT_st:
        if (rotate==ANGLE_0){
            if(x>2){
                if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-1]==Qt::white)) x--;
            }
        }else{
            if(x>1){
                if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)&&
                    (Area[*y+1][x-1]==Qt::white)) x--;
            }
        }
        break;
    case RIGHT_st:
        if (rotate==ANGLE_0){
            if(x<(SIZE_AREA_X-2))
               if ((Area[*y-1][x+1]==Qt::white)&&(Area[*y-1][x+2]==Qt::white)) x++;
        }else{
            if(x<(SIZE_AREA_X-1))
                if ((Area[*y][x+2]==Qt::white)&&(Area[*y+1][x+2]==Qt::white)&&
                    (Area[*y-1][x+1]==Qt::white)) x++;
        }
        break;
    default:
        break;
    }

    switch (rotate){
        case ANGLE_0:
            if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
            else if (*y<1) *y=1;
            Square(qp,x-1,*y,Z_COLOR);
            Square(qp,x,*y,Z_COLOR);       // 0
            Square(qp,x,*y-1,Z_COLOR);     //00
            Square(qp,x+1,*y-1,Z_COLOR);
            state |= checkArea (x-1,*y);
            state |= checkArea (x,*y);
            state |= checkArea (x,*y-1);
            state |= checkArea (x+1,*y-1);
            if (state){
                Area[*y][x-1]=Z_COLOR;
                Area[*y][x]=Z_COLOR;
                Area[*y-1][x]=Z_COLOR;
                Area[*y-1][x+1]=Z_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_180:
            if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
            else if (*y<1) *y=1;
            Square(qp,x,*y,Z_COLOR);
            Square(qp,x,*y+1,Z_COLOR);       // 0
            Square(qp,x-1,*y,Z_COLOR);     //00
            Square(qp,x-1,*y-1,Z_COLOR);
            state |= checkArea (x-1,*y);
            state |= checkArea (x,*y);
            state |= checkArea (x,*y+1);
            state |= checkArea (x-1,*y-1);
            if (state){
                Area[*y][x-1]=Z_COLOR;
                Area[*y][x]=Z_COLOR;
                Area[*y+1][x]=Z_COLOR;
                Area[*y-1][x-1]=Z_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        default:
        break;
    }
    return false;
}
bool block::S(QPainter *qp,uint16_t *y, state_t key_state, angle_t rotate_s)
{
    static uint16_t x=SIZE_AREA_X/2;
    static angle_t rotate;
    if (*y==0) rotate=rotate_s;
    bool state=false;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:  rotate=ANGLE_180;break;
            case ANGLE_180:
                if ((Area[*y-1][x-1]==Qt::white)&&(Area[*y][x+1]==Qt::white))
                rotate=ANGLE_0;
                break;
        default:
            break;
        }
        break;
    case LEFT_st:
        if (rotate==ANGLE_0){
            if(x>2){
                if ((Area[*y-1][x-2]==Qt::white)&&(Area[*y][x-1]==Qt::white)) x--;
            }
        }else{
            if(x>1){
                if ((Area[*y][x-2]==Qt::white)&&(Area[*y+1][x-2]==Qt::white)&&
                    (Area[*y-1][x-1]==Qt::white)) x--;
            }
        }
        break;
    case RIGHT_st:
        if (rotate==ANGLE_0){
            if(x<(SIZE_AREA_X-2))
               if ((Area[*y-1][x+1]==Qt::white)&&(Area[*y][x+2]==Qt::white)) x++;
        }else{
            if(x<(SIZE_AREA_X-1))
                if ((Area[*y][x+1]==Qt::white)&&(Area[*y-1][x+1]==Qt::white)&&
                    (Area[*y-1][x+1]==Qt::white)) x++;
        }
        break;
    default:
        break;
    }

    switch (rotate){
        case ANGLE_0:
            if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
            else if (*y<1) *y=1;
            Square(qp,x+1,*y,S_COLOR);
            Square(qp,x,*y,S_COLOR);       // 0
            Square(qp,x,*y-1,S_COLOR);     //00
            Square(qp,x-1,*y-1,S_COLOR);
            state |= checkArea (x-1,*y-1);
            state |= checkArea (x,*y);
            state |= checkArea (x,*y-1);
            state |= checkArea (x+1,*y);
            if (state){
                Area[*y-1][x-1]=S_COLOR;
                Area[*y][x]=S_COLOR;
                Area[*y-1][x]=S_COLOR;
                Area[*y][x+1]=S_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        case ANGLE_180:
            if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
            else if (*y<1) *y=1;
            Square(qp,x-1,*y,S_COLOR);
            Square(qp,x-1,*y+1,S_COLOR);       // 0
            Square(qp,x,*y,S_COLOR);     //00
            Square(qp,x,*y-1,S_COLOR);
            state |= checkArea (x-1,*y);
            state |= checkArea (x,*y);
            state |= checkArea (x,*y-1);
            state |= checkArea (x-1,*y+1);
            if (state){
                Area[*y][x-1]=S_COLOR;
                Area[*y][x]=S_COLOR;
                Area[*y+1][x-1]=S_COLOR;
                Area[*y-1][x]=S_COLOR;
                x=SIZE_AREA_X/2;
                return true;
            }
            break;
        default:
        break;
    }
    return false;
}
bool block::J(QPainter *qp,uint16_t *y, state_t key_state, angle_t rotate_s)
{
    static uint16_t x=SIZE_AREA_X/2;
    static angle_t rotate;
    if (*y==0) rotate=rotate_s;
    bool state=false;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:
                if ((Area[*y-1][x-1]==Qt::white)&&(Area[*y][x+1]==Qt::white)&&(Area[*y-1][x+1]==Qt::white))
                rotate=ANGLE_90;
                if(x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2;

                break;
            case ANGLE_90:
                rotate=ANGLE_180;
                break;
            case ANGLE_180:
                if ((Area[*y-1][x-1]==Qt::white)&&(Area[*y][x-1]==Qt::white)&&(Area[*y][x+1]==Qt::white))
                rotate=ANGLE_270;
                if(x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2;
                break;
            case ANGLE_270:
                rotate=ANGLE_0;
                break;
        }
        break;
    case LEFT_st:
        switch (rotate){
            case ANGLE_0:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-1]==Qt::white)&&(Area[*y-2][x-1]==Qt::white)) x--;
            break;
            case ANGLE_90:
                if(x>1)
                    if ((Area[*y][x]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)) x--;
            break;
            case ANGLE_180:
                if(x>1)
                    if ((Area[*y-1][x-2]==Qt::white)&&(Area[*y][x-2]==Qt::white)&&(Area[*y-2][x-1]==Qt::white)) x--;
                break;
            case ANGLE_270:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)) x--;
            break;
        }break;
    case RIGHT_st:
        switch (rotate){
            case ANGLE_0:
                if(x<(SIZE_AREA_X-1))
                   if ((Area[*y-1][x+1]==Qt::white)&&(Area[*y-2][x+1]==Qt::white)&&(Area[*y][x+1]==Qt::white)) x++;
                break;
            case ANGLE_90:
                if(x<(SIZE_AREA_X-2))
                    if ((Area[*y][x+2]==Qt::white)&&(Area[*y-1][x+2]==Qt::white)) x++;
            break;
            case ANGLE_180:
                if(x<(SIZE_AREA_X-1))
                   if ((Area[*y-2][x+1]==Qt::white)&&(Area[*y-1][x]==Qt::white)&&(Area[*y][x]==Qt::white)) x++;
                break;
            case ANGLE_270:
                if(x<(SIZE_AREA_X-2))
                    if ((Area[*y][x+2]==Qt::white)&&(Area[*y-1][x]==Qt::white)) x++;
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
                rotate=ANGLE_0;
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
                rotate=ANGLE_0;
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
                rotate=ANGLE_0;
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
                rotate=ANGLE_0;
                return true;
            }
            break;
    }
    return false;
}
bool block::L(QPainter *qp,uint16_t *y, state_t key_state, angle_t rotate_s)
{
    static uint16_t x=SIZE_AREA_X/2;
    static angle_t rotate;
    if (*y==0) rotate=rotate_s;
    bool state=false;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:
                if ((Area[*y][x-1]==Qt::white)&&(Area[*y][x+1]==Qt::white)&&(Area[*y-1][x+1]==Qt::white))
                rotate=ANGLE_90;
                if(x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2;
                break;
            case ANGLE_90:
                rotate=ANGLE_180;
                break;
            case ANGLE_180:
                if ((Area[*y-1][x+1]==Qt::white)&&(Area[*y][x-1]==Qt::white)&&(Area[*y-1][x-1]==Qt::white))
                rotate=ANGLE_270;
                if(x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2;
                break;
            case ANGLE_270:
                rotate=ANGLE_0;
                break;
        }
        break;
    case LEFT_st:
        switch (rotate){
            case ANGLE_0:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)&&(Area[*y-2][x-2]==Qt::white)) x--;
            break;
            case ANGLE_90:
                if(x>1)
                    if ((Area[*y-1][x]==Qt::white)&&(Area[*y][x-2]==Qt::white)) x--;
            break;
            case ANGLE_180:
                if(x>1)
                    if ((Area[*y-2][x-2]==Qt::white)&&(Area[*y][x-1]==Qt::white)&&(Area[*y-1][x-1]==Qt::white)) x--;
                break;
            case ANGLE_270:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)) x--;
            break;
        }break;
    case RIGHT_st:
        switch (rotate){
            case ANGLE_0:
                if(x<(SIZE_AREA_X-1))
                   if ((Area[*y-1][x]==Qt::white)&&(Area[*y-2][x]==Qt::white)&&(Area[*y][x+1]==Qt::white)) x++;
                break;
            case ANGLE_90:
                if(x<(SIZE_AREA_X-2))
                    if ((Area[*y][x+2]==Qt::white)&&(Area[*y-1][x+2]==Qt::white)) x++;
            break;
            case ANGLE_180:
                if(x<(SIZE_AREA_X-1))
                   if ((Area[*y-2][x]==Qt::white)&&(Area[*y-1][x+1]==Qt::white)&&(Area[*y][x+1]==Qt::white)) x++;
                break;
            case ANGLE_270:
                if(x<(SIZE_AREA_X-2))
                    if ((Area[*y-1][x+2]==Qt::white)&&(Area[*y][x]==Qt::white)) x++;
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
            Square(qp,x-1,*y-2, L_COLOR);
            Square(qp,x-1,*y-1, L_COLOR);      //  0
            Square(qp,x-1,*y, L_COLOR);      // 000
            Square(qp,x,*y,L_COLOR);
            state |= checkArea (x-1,*y-2);
            state |= checkArea (x-1,*y-1);
            state |= checkArea (x-1,*y);
            state |= checkArea (x,*y);
            if (state){
                Area[*y][x]=L_COLOR;
                Area[*y][x-1]=L_COLOR;
                Area[*y-1][x-1]=L_COLOR;
                Area[*y-2][x-1]=L_COLOR;
                x=SIZE_AREA_X/2;
                rotate=ANGLE_0;
                return true;
            }
            break;
        case ANGLE_90:
        if (*y>(SIZE_AREA_Y)) *y=(SIZE_AREA_Y);
        else if (*y<1) y++;
            Square(qp,x+1,*y,L_COLOR);       // 0
            Square(qp,x+1,*y-1,L_COLOR);       // 0
            Square(qp,x,*y,L_COLOR);         //00
            Square(qp,x-1,*y,L_COLOR);
            state |= checkArea (x+1,*y);
            state |= checkArea (x+1,*y-1);
            state |= checkArea (x,*y);
            state |= checkArea (x-1,*y);
            if (state){
                Area[*y][x+1]=L_COLOR;
                Area[*y-1][x+1]=L_COLOR;
                Area[*y][x]=L_COLOR;
                Area[*y][x-1]=L_COLOR;
                x=SIZE_AREA_X/2;
                rotate=ANGLE_0;
                return true;
            }
            break;
        case ANGLE_180:
        if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
        else if (*y<3) *y=3;
            Square(qp,x,*y, L_COLOR);
            Square(qp,x,*y-1, L_COLOR);      //  0
            Square(qp,x,*y-2, L_COLOR);      // 000
            Square(qp,x-1,*y-2,L_COLOR);
            state |= checkArea (x,*y);
            state |= checkArea (x,*y-1);
            state |= checkArea (x,*y-2);
            state |= checkArea (x-1,*y-2);
            if (state){
                Area[*y][x]=L_COLOR;
                Area[*y-1][x]=L_COLOR;
                Area[*y-2][x]=L_COLOR;
                Area[*y-2][x-1]=L_COLOR;
                x=SIZE_AREA_X/2;
                rotate=ANGLE_0;
                return true;
            }
            break;
        case ANGLE_270:
            if (*y>(SIZE_AREA_Y)) *y=(SIZE_AREA_Y);
            else if (*y<1) y++;
            Square(qp,x-1,*y-1,L_COLOR);       // 0
            Square(qp,x,*y-1,L_COLOR);         //00
            Square(qp,x+1,*y-1,L_COLOR);       // 0
            Square(qp,x-1,*y,L_COLOR);
            state |= checkArea (x-1,*y-1);
            state |= checkArea (x,*y-1);
            state |= checkArea (x+1,*y-1);
            state |= checkArea (x-1,*y);
            if (state){
                Area[*y-1][x-1]=L_COLOR;
                Area[*y-1][x]=L_COLOR;
                Area[*y-1][x+1]=L_COLOR;
                Area[*y][x-1]=L_COLOR;
                x=SIZE_AREA_X/2;
                rotate=ANGLE_0;
                return true;
            }
            break;
    }
    return false;
}

bool block::checkArea(int x, int y)
{
    if (Area[y+1][x]!=Qt::white) return true;

    return false;
}

void block::Square(QPainter *qp, int x, int y, Qt::GlobalColor Color)
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


//*******************************************************************************************/
void block::nextT(QPainter *qp, angle_t rotate_s)
{
    uint16_t x=10,y=2;
    switch (rotate_s){
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

void block::nextQ(QPainter *qp)
{
    uint16_t x=0,y=0;
    Square(qp,x+1,y-1,Q_COLOR);
    Square(qp,x+1,y,Q_COLOR);       // 0
    Square(qp,x,y-1,Q_COLOR);     //00
    Square(qp,x,y,Q_COLOR);         // 0
}

void block::nextI(QPainter *qp, angle_t rotate_s)
{
    uint16_t x=10,y=2;
    switch (rotate_s){
        case ANGLE_0:
            Square(qp,x+2,y,I_COLOR);
            Square(qp,x+1,y,I_COLOR);       // 0
            Square(qp,x,y,I_COLOR);     //00
            Square(qp,x-1,y,I_COLOR);
            break;
        case ANGLE_180:
            Square(qp,x,y-2,I_COLOR);
            Square(qp,x,y-1,I_COLOR);       // 0
            Square(qp,x,y,I_COLOR);     //00
            Square(qp,x,y+1,I_COLOR);
        break;
        default:
        break;
    }
}
void block::nextZ(QPainter *qp,angle_t rotate_s)
{
    uint16_t x=10,y=2;
    switch (rotate_s){
        case ANGLE_0:
            Square(qp,x-1,y,Z_COLOR);
            Square(qp,x,y,Z_COLOR);       // 0
            Square(qp,x,y-1,Z_COLOR);     //00
            Square(qp,x+1,y-1,Z_COLOR);
            break;
        case ANGLE_180:
            Square(qp,x,y,Z_COLOR);
            Square(qp,x,y+1,Z_COLOR);       // 0
            Square(qp,x-1,y,Z_COLOR);     //00
            Square(qp,x-1,y-1,Z_COLOR);
            break;
        default:
        break;
    }
}
void block::nextS(QPainter *qp, angle_t rotate_s)
{
    uint16_t x=10,y=2;
    switch (rotate_s){
        case ANGLE_0:
            Square(qp,x+1,y,S_COLOR);
            Square(qp,x,y,S_COLOR);       // 0
            Square(qp,x,y-1,S_COLOR);     //00
            Square(qp,x-1,y-1,S_COLOR);
            break;
        case ANGLE_180:
            Square(qp,x-1,y,S_COLOR);
            Square(qp,x-1,y+1,S_COLOR);       // 0
            Square(qp,x,y,S_COLOR);     //00
            Square(qp,x,y-1,S_COLOR);
            break;
        default:
        break;
    }
}
void block::nextJ(QPainter *qp,angle_t rotate_s)
{
    uint16_t x=10,y=2;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:
                if ((Area[*y-1][x-1]==Qt::white)&&(Area[*y][x+1]==Qt::white)&&(Area[*y-1][x+1]==Qt::white))
                rotate=ANGLE_90;
                if(x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2;

                break;
            case ANGLE_90:
                rotate=ANGLE_180;
                break;
            case ANGLE_180:
                if ((Area[*y-1][x-1]==Qt::white)&&(Area[*y][x-1]==Qt::white)&&(Area[*y][x+1]==Qt::white))
                rotate=ANGLE_270;
                if(x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2;
                break;
            case ANGLE_270:
                rotate=ANGLE_0;
                break;
        }
        break;
    case LEFT_st:
        switch (rotate){
            case ANGLE_0:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-1]==Qt::white)&&(Area[*y-2][x-1]==Qt::white)) x--;
            break;
            case ANGLE_90:
                if(x>1)
                    if ((Area[*y][x]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)) x--;
            break;
            case ANGLE_180:
                if(x>1)
                    if ((Area[*y-1][x-2]==Qt::white)&&(Area[*y][x-2]==Qt::white)&&(Area[*y-2][x-1]==Qt::white)) x--;
                break;
            case ANGLE_270:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)) x--;
            break;
        }break;
    case RIGHT_st:
        switch (rotate){
            case ANGLE_0:
                if(x<(SIZE_AREA_X-1))
                   if ((Area[*y-1][x+1]==Qt::white)&&(Area[*y-2][x+1]==Qt::white)&&(Area[*y][x+1]==Qt::white)) x++;
                break;
            case ANGLE_90:
                if(x<(SIZE_AREA_X-2))
                    if ((Area[*y][x+2]==Qt::white)&&(Area[*y-1][x+2]==Qt::white)) x++;
            break;
            case ANGLE_180:
                if(x<(SIZE_AREA_X-1))
                   if ((Area[*y-2][x+1]==Qt::white)&&(Area[*y-1][x]==Qt::white)&&(Area[*y][x]==Qt::white)) x++;
                break;
            case ANGLE_270:
                if(x<(SIZE_AREA_X-2))
                    if ((Area[*y][x+2]==Qt::white)&&(Area[*y-1][x]==Qt::white)) x++;
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
                rotate=ANGLE_0;
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
                rotate=ANGLE_0;
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
                rotate=ANGLE_0;
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
                rotate=ANGLE_0;
                return true;
            }
            break;
    }
    return false;
}
bool block::L(QPainter *qp,uint16_t *y, state_t key_state, angle_t rotate_s)
{
    static uint16_t x=SIZE_AREA_X/2;
    static angle_t rotate;
    if (*y==0) rotate=rotate_s;
    bool state=false;
    switch (key_state)
    {
    case ENTER_st:
        switch(rotate){
            case ANGLE_0:
                if ((Area[*y][x-1]==Qt::white)&&(Area[*y][x+1]==Qt::white)&&(Area[*y-1][x+1]==Qt::white))
                rotate=ANGLE_90;
                if(x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2;
                break;
            case ANGLE_90:
                rotate=ANGLE_180;
                break;
            case ANGLE_180:
                if ((Area[*y-1][x+1]==Qt::white)&&(Area[*y][x-1]==Qt::white)&&(Area[*y-1][x-1]==Qt::white))
                rotate=ANGLE_270;
                if(x>(SIZE_AREA_X-2)) x=SIZE_AREA_X-2;
                break;
            case ANGLE_270:
                rotate=ANGLE_0;
                break;
        }
        break;
    case LEFT_st:
        switch (rotate){
            case ANGLE_0:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)&&(Area[*y-2][x-2]==Qt::white)) x--;
            break;
            case ANGLE_90:
                if(x>1)
                    if ((Area[*y-1][x]==Qt::white)&&(Area[*y][x-2]==Qt::white)) x--;
            break;
            case ANGLE_180:
                if(x>1)
                    if ((Area[*y-2][x-2]==Qt::white)&&(Area[*y][x-1]==Qt::white)&&(Area[*y-1][x-1]==Qt::white)) x--;
                break;
            case ANGLE_270:
                if(x>1)
                    if ((Area[*y][x-2]==Qt::white)&&(Area[*y-1][x-2]==Qt::white)) x--;
            break;
        }break;
    case RIGHT_st:
        switch (rotate){
            case ANGLE_0:
                if(x<(SIZE_AREA_X-1))
                   if ((Area[*y-1][x]==Qt::white)&&(Area[*y-2][x]==Qt::white)&&(Area[*y][x+1]==Qt::white)) x++;
                break;
            case ANGLE_90:
                if(x<(SIZE_AREA_X-2))
                    if ((Area[*y][x+2]==Qt::white)&&(Area[*y-1][x+2]==Qt::white)) x++;
            break;
            case ANGLE_180:
                if(x<(SIZE_AREA_X-1))
                   if ((Area[*y-2][x]==Qt::white)&&(Area[*y-1][x+1]==Qt::white)&&(Area[*y][x+1]==Qt::white)) x++;
                break;
            case ANGLE_270:
                if(x<(SIZE_AREA_X-2))
                    if ((Area[*y-1][x+2]==Qt::white)&&(Area[*y][x]==Qt::white)) x++;
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
            Square(qp,x-1,*y-2, L_COLOR);
            Square(qp,x-1,*y-1, L_COLOR);      //  0
            Square(qp,x-1,*y, L_COLOR);      // 000
            Square(qp,x,*y,L_COLOR);
            state |= checkArea (x-1,*y-2);
            state |= checkArea (x-1,*y-1);
            state |= checkArea (x-1,*y);
            state |= checkArea (x,*y);
            if (state){
                Area[*y][x]=L_COLOR;
                Area[*y][x-1]=L_COLOR;
                Area[*y-1][x-1]=L_COLOR;
                Area[*y-2][x-1]=L_COLOR;
                x=SIZE_AREA_X/2;
                rotate=ANGLE_0;
                return true;
            }
            break;
        case ANGLE_90:
        if (*y>(SIZE_AREA_Y)) *y=(SIZE_AREA_Y);
        else if (*y<1) y++;
            Square(qp,x+1,*y,L_COLOR);       // 0
            Square(qp,x+1,*y-1,L_COLOR);       // 0
            Square(qp,x,*y,L_COLOR);         //00
            Square(qp,x-1,*y,L_COLOR);
            state |= checkArea (x+1,*y);
            state |= checkArea (x+1,*y-1);
            state |= checkArea (x,*y);
            state |= checkArea (x-1,*y);
            if (state){
                Area[*y][x+1]=L_COLOR;
                Area[*y-1][x+1]=L_COLOR;
                Area[*y][x]=L_COLOR;
                Area[*y][x-1]=L_COLOR;
                x=SIZE_AREA_X/2;
                rotate=ANGLE_0;
                return true;
            }
            break;
        case ANGLE_180:
        if (*y>(SIZE_AREA_Y-1)) *y=(SIZE_AREA_Y-1);
        else if (*y<3) *y=3;
            Square(qp,x,*y, L_COLOR);
            Square(qp,x,*y-1, L_COLOR);      //  0
            Square(qp,x,*y-2, L_COLOR);      // 000
            Square(qp,x-1,*y-2,L_COLOR);
            state |= checkArea (x,*y);
            state |= checkArea (x,*y-1);
            state |= checkArea (x,*y-2);
            state |= checkArea (x-1,*y-2);
            if (state){
                Area[*y][x]=L_COLOR;
                Area[*y-1][x]=L_COLOR;
                Area[*y-2][x]=L_COLOR;
                Area[*y-2][x-1]=L_COLOR;
                x=SIZE_AREA_X/2;
                rotate=ANGLE_0;
                return true;
            }
            break;
        case ANGLE_270:
            if (*y>(SIZE_AREA_Y)) *y=(SIZE_AREA_Y);
            else if (*y<1) y++;
            Square(qp,x-1,*y-1,L_COLOR);       // 0
            Square(qp,x,*y-1,L_COLOR);         //00
            Square(qp,x+1,*y-1,L_COLOR);       // 0
            Square(qp,x-1,*y,L_COLOR);
            state |= checkArea (x-1,*y-1);
            state |= checkArea (x,*y-1);
            state |= checkArea (x+1,*y-1);
            state |= checkArea (x-1,*y);
            if (state){
                Area[*y-1][x-1]=L_COLOR;
                Area[*y-1][x]=L_COLOR;
                Area[*y-1][x+1]=L_COLOR;
                Area[*y][x-1]=L_COLOR;
                x=SIZE_AREA_X/2;
                rotate=ANGLE_0;
                return true;
            }
            break;
    }
    return false;
}
