#include "main.h"
#include "imu.h"
#include "sensorTypes.h"

#include "mpu6050.h"
#include "adxl345.h"

extern uint8_t numSensors;

uint8_t accelType = NO_SENSOR;
uint8_t gyroType = NO_SENSOR;

void initIMU()
{
    if (mpuBegin(thingPort()))
    {
        accelType = ACCEL_MPU;
        gyroType = GYRO_MPU;
        numSensors += 2; // accel + gyro
        return;
    }

    if (adxlBegin(thingPort()))
    {
        accelType = ACCEL_ADXL;
        numSensors++; // just accel
        return;
    }
}

void readAccel(float *gx, float *gy, float *gz)
{
    switch (accelType)
    {
    case ACCEL_MPU:
        readMPUAccel(gx, gy, gz);
        break;

    case ACCEL_ADXL:
        readADXLAccel(gx, gy, gz);
        break;

    default:
        break;
    }
}

void readGyro(float *gx, float *gy, float *gz)
{
    switch (gyroType)
    {
    case GYRO_MPU:
        readMPUGyro(gx, gy, gz);
        break;

    default:
        break;
    }
}