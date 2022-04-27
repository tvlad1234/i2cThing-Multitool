#include "main.h"
#include "ui.h"

#include "sensorTypes.h"
#include "imu.h"
#include "environmental.h"

#define MAX_PAGES 5
#define DPS_TO_RADS (0.017453293F)

uint8_t page = 1;
uint8_t numSensors = 0;

extern uint8_t accelType;
extern uint8_t gyroType;
extern uint8_t tempType;
extern uint8_t presType;
extern uint8_t humType;

void listSensors()
{

    if (numSensors == 0)
    {
        printf("No sensors found!\n");
        flushDisplay();
        Error_Handler();
    }

    char s[40] = "";

    if (accelType)
        strcat(s, "Acc ");
    if (gyroType)
        strcat(s, "Gyr ");
    if (tempType)
        strcat(s, "Tmp ");
    if (presType)
        strcat(s, "Atm ");
    if (humType)
        strcat(s, "Hum");

    printf("%s\n", s);
    flushDisplay();
    while (!readButton())
        ;
    HAL_Delay(200);
}

void printAccel()
{
    char sx[10], sy[10], sz[10];
    float x, y, z;
    readAccel(&x, &y, &z);

    clearDisplay();
    setCursor(0, 0);

    printFloat(x, 1, sx);
    printFloat(y, 1, sy);
    printFloat(z, 1, sz);
    printf("Accel in m/s^2\nX: %s Y: %s\nZ: %s\n", sx, sy, sz);

    flushDisplay();
    HAL_Delay(50);
}

void printGyro()
{
    char sx[10], sy[10], sz[10];
    float x, y, z;
    readGyro(&x, &y, &z);

    clearDisplay();
    setCursor(0, 0);

    printFloat(x * DPS_TO_RADS, 1, sx);
    printFloat(y * DPS_TO_RADS, 1, sy);
    printFloat(z * DPS_TO_RADS, 1, sz);
    printf("AngVel in rad/s\nX: %s Y: %s\nZ: %s\n", sx, sy, sz);

    flushDisplay();
    HAL_Delay(50);
}

void printTemp()
{
    char t[10];
    float temp;
    readTemp(&temp);

    clearDisplay();
    setCursor(0, 0);

    printFloat(temp, 2, t);
    printf("Temperature:\n%s C\n", t);
    flushDisplay();
    HAL_Delay(50);
}

void printPres()
{
    char p[10];
    uint32_t pres;
    readPres(&pres);

    clearDisplay();
    setCursor(0, 0);

    printFloat(pres / 100.0f, 2, p);
    printf("Atm. pressure:\n%s hPa\n", p);
    flushDisplay();
    HAL_Delay(50);
}

void printHum()
{
    char h[10];
    float hum;
    readHum(&hum);

    clearDisplay();
    setCursor(0, 0);

    printFloat(hum, 2, h);
    printf("Humidity:\n%s %% \n", h);
    flushDisplay();
    HAL_Delay(50);
}

void ui()
{
    switch (page)
    {
    case 1:
        if (accelType)
            printAccel();
        else
            page++;
        break;

    case 2:
        if (gyroType)
            printGyro();
        else
            page++;
        break;

    case 3:
        if (tempType)
            printTemp();
        else
            page++;
        break;

    case 4:
        if (presType)
            printPres();
        else
            page++;
        break;

    case 5:
        if (humType)
            printHum();
        else
            page++;
        break;

    default:
        page = 1;
        break;
    }

    if (readButton())
    {
        if (page == MAX_PAGES)
            page = 0;
        page++;
        HAL_Delay(200);
    }
}
