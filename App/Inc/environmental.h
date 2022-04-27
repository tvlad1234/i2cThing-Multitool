#ifndef ENVIRONMENTAL_H
#define ENVIRONMENTAL_H

#include "main.h"

void initEnvironmental();
void readTemp(float *t);
void readPres(uint32_t *p);
void readHum(float *h);

#endif