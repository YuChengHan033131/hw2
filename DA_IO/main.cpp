#include "function.h"
Serial pc( USBTX, USBRX );
InterruptIn s(SW3);
AnalogOut Aout(DAC0_OUT);
DigitalOut R(LED_RED),G(LED_GREEN);
BusOut D4_11 (D6, D7, D9, D10, D11, D5, D4, D8);
AnalogIn Ain(A0);
EventQueue queue(32*EVENTS_EVENT_SIZE);
Timer t;
Thread SEvent;
int freq;
int length;
int main(){
    R=true;
    G=false;
    t.start();
    double a=0,b=0;
    while(1){
        float volt=Ain;
        if(volt==0){
            if(a==0){
                a=t.read();
                wait(1./500);
                continue;
            }else if(b==0){
                b=t.read();
                break;
            }
        }
    }
    freq=(int)round(1./(b-a));
    int temp=freq;
    length=0;
    while(temp!=0){
        temp/=10;
        length++;
    }
    int sample=500;
    float *ADCdata=new float[sample];
    for (int i = 0; i < sample; i++){
        ADCdata[i] = Ain;
        wait(1./sample);
    }
    for (int i = 0; i < sample; i++){
        pc.printf("%1.3f\r\n", ADCdata[i]);
        //wait(0.1);
    }
    SEvent.start(callback(&queue,&EventQueue::dispatch_forever));
    s.fall(&SPressed);
    s.rise(&SReleased);
    while(1){
        //sine wave generation
        sineWave();
    } 
}
