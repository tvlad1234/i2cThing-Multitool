#include "main.h"

#include "imu.h"
#include "environmental.h"

#include "ui.h"

int main(void)
{
    thingInit();

    initIMU();
    initEnvironmental();

    listSensors();

    while (1)
    {
        ui();
    }
}