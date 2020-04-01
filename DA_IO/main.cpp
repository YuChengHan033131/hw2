#include "mbed.h"
#include<cmath>
Serial pc( USBTX, USBRX );
DigitalIn s(SW3);
AnalogOut Aout(DAC0_OUT);
DigitalOut R(LED_RED),G(LED_GREEN);
AnalogIn Ain(A0);
BusOut D4_11 (D6, D7, D9, D10, D11, D5, D4, D8);
Timer t;
int power_10(int n){
    int temp=1;
    for(int i=0;i<n;i++){
        temp*=10;
    }
    return temp;
}

int main(){
    pc.printf("start\r\n");
    R=true;
    G=true;
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
        if(s==1){
            G=true;
            R=false;
            for(int i=length-1;i>=0;i--){
                D4_11=sevD_code[(freq/power_10(i))%10];
                wait(0.5);
                D4_11=0x00;
                wait(0.1);
            }
        }else{
            R=true;
            G=false;
        }
        
        D4_11=0x00;
        wait(3);
    }
}