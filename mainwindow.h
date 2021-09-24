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
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void drawIMG(QPainter *qp);
    void drawPointBW(QPainter *qp,int x, int y, uint8_t Color);
    void T (int x, int y, angle_t rotate);
    void Q (int x, int y);
    void I (int x, int y, angle_t rotate);
    void Z (int x, int y, angle_t rotate);
    void S (int x, int y, angle_t rotate);
    void J (int x, int y, angle_t rotate);
    void L (int x, int y, angle_t rotate);

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void keyPressEvent( QKeyEvent * event);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
