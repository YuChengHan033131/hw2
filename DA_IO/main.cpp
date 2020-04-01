#include "mbed.h"
#include<cmath>
Serial pc( USBTX, USBRX );
//DigitalIn s(SW3);
AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);
BusOut D4_11 (D4,D5,D6,D7,D8,D9,D10,D11);
Timer t;
int main(){
    pc.printf("start\r\n");
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
    int freq=(int)round(1./(b-a));
    char sevD_code[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    int temp=freq,length=0;
    while(temp!=0){
        temp/=10;
        length++;
    }
    while(1){
        for(int i=0;i<length;i++){
            wait(0.5);
        }
        wait(3);
    }
}