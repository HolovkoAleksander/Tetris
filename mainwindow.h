#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
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
#define TOP 20
#define LEFT 20
#define WIDHT 300
#define HEIGHT 500
#define SIZE 20
#define SIZE_AREA_X ((HEIGHT-LEFT)/SIZE)
#define SIZE_AREA_Y ((WIDHT-TOP)/SIZE)

#define T_COLOR Qt::red
#define Q_COLOR Qt::green
#define I_COLOR Qt::darkBlue
#define Z_COLOR Qt::blue
#define S_COLOR Qt::magenta
#define J_COLOR Qt::yellow
#define L_COLOR Qt::darkGray

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void slotTimerAlarm ();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void currentBlock(QPainter *qp);

    void drawPointBW(QPainter *qp,int x, int y, uint8_t Color);
    void Square(QPainter *qp,int x, int y, Qt::GlobalColor Color);
    void T (QPainter *qp,int x, int y, angle_t rotate);
    void Q (QPainter *qp,int x, int y);
    void I (QPainter *qp,int x, int y, angle_t rotate);
    void Z (QPainter *qp,int x, int y, angle_t rotate);
    void S (QPainter *qp,int x, int y, angle_t rotate);
    void J (QPainter *qp,int x, int y, angle_t rotate);
    void L (QPainter *qp,int x, int y, angle_t rotate);

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void keyPressEvent( QKeyEvent * event);
private:
    Ui::MainWindow *ui;
    state_t key_state=RELASE;
    uint8_t angle=ANGLE_0;
    bool count=false;
    uint16_t current_X=0;
    uint16_t current_Y=0;
    Qt::GlobalColor Area[SIZE_AREA_Y][SIZE_AREA_X]={{Qt::white},{Qt::white}};
};
#endif // MAINWINDOW_H
