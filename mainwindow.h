#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
typedef enum{
    ANGLE_0=0,
    ANGLE_90,
    ANGLE_180,
    ANGLE_270
}angle_t;

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
    void drawIMG(QPainter *qp);

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
};
#endif // MAINWINDOW_H
