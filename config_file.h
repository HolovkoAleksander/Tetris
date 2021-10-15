#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <QObject>
#include "block.h"


class config:  public QObject
{
    Q_OBJECT
public:
    struct configFile_t{
       uint32_t record=0;
       uint32_t points=0;
       uint8_t area[SIZE_AREA_Y][SIZE_AREA_X]={{0},{0}};
    };

public:
    explicit config(QObject *parent = nullptr);
public slots:
    void open_Config (struct configFile_t *configFile);
    void save_Config (struct configFile_t configFile);
signals:
   // void sig_config_types (device_type_t device_type,config_types_t);



};

#endif // CONFIG_FILE_H
