#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "block.h"
#include "config_file.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class block;
class config;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void slotTimerAlarm ();
    void on_pushButton_5_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void currentBlock(QPainter *qp);

    void drawPointBW(QPainter *qp,int x, int y, uint8_t Color);

    void Square_without_margin(QPainter *qp,int x, int y, Qt::GlobalColor Color);
    void Square_margin(QPainter *qp,int x, int y);
    void Check_line (void);




protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void keyPressEvent( QKeyEvent * event);
private:
    block *block=new class block(this);
    config *config =new class config(this);
    config::configFile_t configFile;
    Ui::MainWindow *ui;
    QTimer *timer;
    block::state_t key_state=block::RELASE;
    bool count=false;
    uint16_t current_X=0;
    uint16_t current_Y=0;
    uint32_t points=0;
    uint8_t Speed=0;
    uint32_t Record=0;


};
#endif // MAINWINDOW_H
