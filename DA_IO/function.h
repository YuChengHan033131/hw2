#ifndef FUNCTION_H
#define FUNCTION_H
#include "mbed.h"
#include<cmath>
extern AnalogOut Aout;
extern BusOut D4_11;
extern InterruptIn s;
extern Serial pc;
extern Timer t;
extern int freq;
extern int length;
extern DigitalOut R,G;
extern EventQueue queue;
int power_10(int n);
void sineWave();
void showFreq();
void SPressed();
void SReleased();
#endif