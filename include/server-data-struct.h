#ifndef SERVER_DATA_STRUCT_H
#define SERVER_DATA_STRUCT_H

#include <qglobal.h>

#pragma pack(push, 1)

struct server_data_t
{
    quint64 count;           ///< Счетчик сообщений 8
    float   railway_coord;   ///< Текущая координата (м) 12
    float   velocity;        ///< Скорость (м/с) 16
    float   time;            ///< Модельное время 20
    float   deltaTime;       ///< Интервал между отправками 24
    int     dir;             ///< Направление изменения координаты 28
    quint32 railway_num;     ///< Номер участка 32
    bool    spot_light_low;  ///< Прожектор тускло 33
    bool    spot_light_high; ///< Прожектор ярко 34

    server_data_t()
        : count(0)
        , railway_coord(0.0)
        , velocity(0.0)
        , time(0.0)
        , deltaTime(0.0)
        , dir(0)
        , railway_num(0)
        , spot_light_low(false)
        , spot_light_high(false)
    {

    }
};

#pragma pack(pop)

#endif // SERVER_DATA_STRUCT_H
