//sine wave generation
#include "function.h"

int power_10(int n){
    int temp=1;
    for(int i=0;i<n;i++){
        temp*=10;
    }
    return temp;
}

float ampl=0.5,offset=0.5;
void sineWave(){
    Aout=offset+ampl*sin(2*3.14159*freq*t.read());
}

char sevD_code[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
void showFreq(){
    for(int i=length-1;i>=0;i--){
        D4_11=sevD_code[(freq/power_10(i))%10];
        wait(0.5);
        D4_11=0x00;
        wait(0.1);
    }
        D4_11=0x00;
        wait(1);
}

int id;
void SPressed(){
    G=true;
    R=false;
    id=queue.call_every(3000,showFreq);
}

void SReleased(){
    R=true;
    G=false;
    queue.cancel(id);
}
