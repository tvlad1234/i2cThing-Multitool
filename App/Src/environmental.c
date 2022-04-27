#include "main.h"
#include "environmental.h"
#include "sensorTypes.h"

#include "bmp085.h"
#include "htu21df.h"

extern uint8_t numSensors;

uint8_t tempType = NO_SENSOR;
uint8_t presType = NO_SENSOR;
uint8_t humType = NO_SENSOR;

void initEnvironmental()
{
    if (bmpBegin(BMP085_STANDARD, thingPort()))
    {
        if (!tempType)
        {
            tempType = TEMP_BMP085;
            numSensors++;
        }

        if (!presType)
        {
            presType = PRES_BMP085;
            numSensors++;
        }
    }

    if (htuBegin(thingPort()))
    {
        if (!tempType)
        {
            tempType = TEMP_HTU21DF;
            numSensors++;
        }
        if (!humType)
        {
            humType = HUM_HTU21DF;
            numSensors++;
        }
    }
}

void readTemp(float *t)
{
    switch (tempType)
    {
    case TEMP_BMP085:
        *t = readBMPTemperature();
        break;

    case TEMP_HTU21DF:
        *t = readHTUTemperature();
        break;

    default:
        break;
    }
}

void readPres(uint32_t *p)
{
    switch (presType)
    {
    case PRES_BMP085:
        *p = readBMPPressure();
        break;

    default:
        break;
    }
}

void readHum(float *h)
{
    switch (humType)
    {
    case HUM_HTU21DF:
        *h = readHTUHumidity();
        break;

    default:
        break;
    }
}
