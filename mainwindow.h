#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "block.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class block;
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

    void Square_without_margin(QPainter *qp,int x, int y, Qt::GlobalColor Color);
    void Square_margin(QPainter *qp,int x, int y);




protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void keyPressEvent( QKeyEvent * event);
private:
    block *block=new class block(this);
    Ui::MainWindow *ui;
    block::state_t key_state=block::RELASE;
    bool count=false;
    uint16_t current_X=0;
    uint16_t current_Y=0;


};
#endif // MAINWINDOW_H
