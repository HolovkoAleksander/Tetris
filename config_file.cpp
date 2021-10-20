#include "config_file.h"
#include <QFile>
#include <QDebug>


config::config(QObject *parent) : QObject(parent)
{


   // open_Config (NUM_DEVICE);
}
void config::open_Config(struct configFile_t *configFile)
{
   QFile file("config_tetris.txt");
    file.open(QIODevice::WriteOnly | QIODevice::ReadOnly | QIODevice::Text);
    if (file.size()>10){
        QString text(file.readAll());
        int Index=text.indexOf("Record:",0);
        Index=text.indexOf(":",Index);
        configFile->record=text.midRef(Index+1,6).toLong();

        Index=text.indexOf("Points:",Index);
        Index=text.indexOf(":",Index);
        configFile->points=text.midRef(Index+1,6).toLong();

        /*Index=text.indexOf("CurNumber:",Index);
        Index=text.indexOf(":",Index);
        configFile->curNumber=text.midRef(Index+1,2).toShort();

        Index=text.indexOf("NextNumber:",Index);
        Index=text.indexOf(":",Index);
        configFile->nextNumber=text.midRef(Index+1,2).toShort();*/

        Index=text.indexOf("Area:",Index);
        Index=text.indexOf(":",Index);
        Index++;
        for (uint16_t y=0; y<SIZE_AREA_Y; y++)
            for (uint16_t x=0;  x<SIZE_AREA_X; x++){
               configFile->area[y][x]=text.midRef(Index,1).toShort();
               Index++;
               //Index=text.indexOf(",",Index);
            }
    }
    file.close();


}

void config::save_Config(struct configFile_t *configFile)
{
    //qDebug() << __FUNCTION__ << config_type_MC.folder_STM;



    QFile file("config_tetris.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(("Record:"+QString::number(configFile->record).rightJustified(6,'0')+"\n"+
                "Points:"+QString::number(configFile->points).rightJustified(6,'0')+"\n"+
                "CurNumber:"+QString::number(configFile->curNumber).rightJustified(2,'0')+"\n"+
                "NextNumber:"+QString::number(configFile->nextNumber).rightJustified(2,'0')+"\n"+
                "Area:"
                ).toUtf8());
    for (uint16_t y=0; y<SIZE_AREA_Y; y++)
        for (uint16_t x=0;  x<SIZE_AREA_X; x++)
            file.write((QString::number(configFile->area[y][x])).toUtf8());
    file.close();
}


