#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QPainter>
#define TOP 20
#define LEFT 20
#define WIDHT 400
#define HEIGHT 600

#define NEXT_LEFT (LEFT+WIDHT+20)
#define NEXT_TOP 150
#define NEXT_WIGHT  100
#define NEXT_HEIGHT 100


#define SIZE 20
#define SIZE_AREA_X ((WIDHT)/SIZE)
#define SIZE_AREA_Y ((HEIGHT)/SIZE)

#define T_COLOR Qt::red
#define Q_COLOR Qt::green
#define I_COLOR Qt::darkBlue
#define Z_COLOR Qt::blue
#define S_COLOR Qt::magenta
#define J_COLOR Qt::yellow
#define L_COLOR Qt::darkGray
#define NULL_COLOR Qt::white
class block : public QObject
{
    Q_OBJECT

public:
    typedef enum{
        ANGLE_0=0,
        ANGLE_90=1,
        ANGLE_180=2,
        ANGLE_270=3
    }angle_t;
    typedef enum{
        RELASE=0,
        LEFT_st,
        RIGHT_st,
        DOWN_st,
        ENTER_st
    }state_t;
public:
    explicit block(QObject *parent = nullptr);
    void Square(QPainter *qp,int x, int y, Qt::GlobalColor Color);
    bool T (QPainter *qp, uint16_t *y, state_t key_state, angle_t rotate_s);
    bool Q (QPainter *qp,uint16_t *y, state_t key_state);
    bool I (QPainter *qp,uint16_t *y, state_t key_state, angle_t rotate_s);
    bool Z (QPainter *qp,uint16_t *y, state_t key_state, angle_t rotate_s);
    bool S (QPainter *qp,uint16_t *y, state_t key_state, angle_t rotate_s);
    bool J (QPainter *qp,uint16_t *y, state_t key_state,  angle_t rotate_s);
    bool L (QPainter *qp,uint16_t *y,  state_t key_state, angle_t rotate_s);

    void endGame(QPainter *qp);

    void nextT (QPainter *qp,angle_t rotate_s);
    void nextQ (QPainter *qp);
    void nextI (QPainter *qp,angle_t rotate_s);
    void nextZ (QPainter *qp,angle_t rotate_s);
    void nextS (QPainter *qp,angle_t rotate_s);
    void nextJ (QPainter *qp,angle_t rotate_s);
    void nextL (QPainter *qp,angle_t rotate_s);
    bool checkArea(int x, int y);
signals:

public:
    Qt::GlobalColor Area[SIZE_AREA_Y][SIZE_AREA_X]={{Qt::white},{Qt::white}};

};

#endif // BLOCK_H
