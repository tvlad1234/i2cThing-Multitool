#ifndef IMU_H
#define IMU_H

#include "main.h"

void initIMU();
void readAccel(float *gx, float *gy, float *gz);
void readGyro(float *gx, float *gy, float *gz);

#endif