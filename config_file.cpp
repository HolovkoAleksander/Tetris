#include "config_file.h"
#include <QFile>
#include <QDebug>


config::config(QObject *parent) : QObject(parent)
{


   // open_Config (NUM_DEVICE);
}
void config::open_Config(struct configFile_t *configFile)
{
  /*  QFile file("config_fw.txt");
    bool bStatus = false;
    file.open(QIODevice::WriteOnly | QIODevice::ReadOnly | QIODevice::Text);
    if (file.size()>10){
        QString text(file.readAll());
        //MC---------------------------------------------------------------------------------------
        int Index=text.indexOf("MC FOLDER:",0);
        Index=text.indexOf(":",Index);
        config_type_MC.folder_STM=text.mid(Index+1,text.indexOf("\n",Index+1)-Index-1);

        Index=text.indexOf("MC DEV TYPE:",Index);
        Index=text.indexOf(":",Index);
        config_type_MC.udf_info.dev_type=text.midRef(Index+1,3).toInt();

        Index=text.indexOf("MC HW_VER:",Index);
        Index=text.indexOf(":",Index);
        config_type_MC.udf_info.hw_ver=text.midRef(Index+1,1).toInt();

        Index=text.indexOf("MC RF_BAND:",Index);
        Index=text.indexOf(":",Index);
        config_type_MC.udf_info.rf_band=text.midRef(Index+1,1).toInt();

        Index=text.indexOf("MC SW_VER:",Index);
        Index=text.indexOf(":",Index);
        config_type_MC.udf_info.sw_ver=text.midRef(Index+1,8).toLong(&bStatus,16);

        //MCO---------------------------------------------------------------------------------------
        Index=text.indexOf("MCO FOLDER_STM:",0);
        Index=text.indexOf(":",Index);
        config_type_MCO.folder_STM=text.mid(Index+1,text.indexOf("\n",Index+1)-Index-1);

        Index=text.indexOf("MCO FOLDER_OVB:",0);
        Index=text.indexOf(":",Index);
        config_type_MCO.folder_OVB=text.mid(Index+1,text.indexOf("\n",Index+1)-Index-1);

        Index=text.indexOf("MCO DEV TYPE:",Index);
        Index=text.indexOf(":",Index);
        config_type_MCO.udf_info.dev_type=text.midRef(Index+1,3).toInt();

        Index=text.indexOf("MCO HW_VER:",Index);
        Index=text.indexOf(":",Index);
        config_type_MCO.udf_info.hw_ver=text.midRef(Index+1,1).toInt();

        Index=text.indexOf("MCO RF_BAND:",Index);
        Index=text.indexOf(":",Index);
        config_type_MCO.udf_info.rf_band=text.midRef(Index+1,1).toInt();

        Index=text.indexOf("MCO SW_VER:",Index);
        Index=text.indexOf(":",Index);
        config_type_MCO.udf_info.sw_ver=text.midRef(Index+1,8).toLong(&bStatus,16);

        //Light Switch---------------------------------------------------------------------------------

        Index=text.indexOf("LS FOLDER:",0);
        Index=text.indexOf(":",Index);
        config_type_LightSwitch.folder_STM=text.mid(Index+1,text.indexOf("\n",Index+1)-Index-1);

        Index=text.indexOf("LS DEV TYPE:",Index);
        Index=text.indexOf(":",Index);
        config_type_LightSwitch.udf_info.dev_type=text.midRef(Index+1,3).toInt();

        Index=text.indexOf("LS HW_VER:",Index);
        Index=text.indexOf(":",Index);
        config_type_LightSwitch.udf_info.hw_ver=text.midRef(Index+1,1).toInt();

        Index=text.indexOf("LS RF_BAND:",Index);
        Index=text.indexOf(":",Index);
        config_type_LightSwitch.udf_info.rf_band=text.midRef(Index+1,1).toInt();

        Index=text.indexOf("LS SW_VER:",Index);
        Index=text.indexOf(":",Index);
        config_type_LightSwitch.udf_info.sw_ver=text.midRef(Index+1,8).toLong(&bStatus,16);*/
       /* qDebug() <<config_type_LightSwitch.folder_STM;
        qDebug() <<config_type_LightSwitch.udf_info.dev_type;
        qDebug() <<config_type_LightSwitch.udf_info.hw_ver;
        qDebug() <<config_type_LightSwitch.udf_info.rf_band;
        qDebug() <<config_type_LightSwitch.udf_info.sw_ver;*/
    /*}else{
        file.write(("MC FOLDER:"+config_type_MC.folder_STM+"\n"+
                    "MC DEV TYPE:"+QString::number(config_type_MC.udf_info.dev_type)+"\n"+
                    "MC HW_VER:"+QString::number(config_type_MC.udf_info.hw_ver)+"\n"+
                    "MC RF_BAND:"+QString::number(config_type_MC.udf_info.rf_band)+"\n"+
                    "MC SW_VER:"+QString::number(config_type_MC.udf_info.sw_ver,16)+"\n"+

                    "MCO FOLDER_STM:"+config_type_MCO.folder_STM+"\n"+
                    "MCO FOLDER_OVB:"+config_type_MCO.folder_OVB+"\n"+
                    "MCO DEV TYPE:"+QString::number(config_type_MCO.udf_info.dev_type)+"\n"+
                    "MCO HW_VER:"+QString::number(config_type_MCO.udf_info.hw_ver)+"\n"+
                    "MCO RF_BAND:"+QString::number(config_type_MCO.udf_info.rf_band)+"\n"+
                    "MCO SW_VER:"+QString::number(config_type_MCO.udf_info.sw_ver,16)+"\n"+

                    "LS FOLDER:"+config_type_LightSwitch.folder_STM+"\n"+
                    "LS DEV TYPE:"+QString::number(+config_type_LightSwitch.udf_info.dev_type)+"\n"+
                    "LS HW_VER:"+QString::number(config_type_LightSwitch.udf_info.hw_ver)+"\n"+
                    "LS RF_BAND:"+QString::number(config_type_LightSwitch.udf_info.rf_band)+"\n"+
                    "LS SW_VER:"+QString::number(config_type_LightSwitch.udf_info.sw_ver,16)+"\n"
                    ).toUtf8());

    }
    file.close();

    switch (device_type){
        case MC:
            emit sig_config_types (MC,config_type_MC);
            break;
        case MCO:
            emit sig_config_types (MCO,config_type_MCO);
            break;
        case LIGHT_SWITCH:
            emit sig_config_types (LIGHT_SWITCH,config_type_LightSwitch);
            break;
        case NUM_DEVICE:
            emit sig_config_types (MC,config_type_MC);
            emit sig_config_types (MCO,config_type_MCO);
            emit sig_config_types (LIGHT_SWITCH,config_type_LightSwitch);
            break;
        default:
            break;
    }*/
}

void config::save_Config(struct configFile_t configFile)
{
    //qDebug() << __FUNCTION__ << config_type_MC.folder_STM;



    QFile file("config_tetris.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(("Record:"+QString::number(configFile.record)+"\n"+
                "Points:"+QString::number(configFile.points)+"\n"+
                "Area:"
                ).toUtf8());
    for (uint16_t y=0; y<SIZE_AREA_Y; y++)
        for (uint16_t x=0;  x<SIZE_AREA_X; x++)
            file.write((","+QString::number(configFile.record)).toUtf8());
    file.close();
}


