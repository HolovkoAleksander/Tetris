#ifndef MY_PAINT_H
#define MY_PAINT_H

#include <QWidget>
class QPaintEvent;

class my_paint :public QWidget
{
    Q_OBJECT
public:
    my_paint(QWidget *parent = nullptr);
    ~my_paint();

    void drawIMG(QPainter *qp);
    void drawPointBW(QPainter *qp,int x, int y, uint8_t Color);



protected:
    virtual void paintEvent(QPaintEvent *e);
private:

};

#endif // MY_PAINT_H
