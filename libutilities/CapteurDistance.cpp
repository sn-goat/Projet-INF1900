#include "CapteurDistance.h"

CapteurDistance::CapteurDistance() : canObj(Can()), uartObj(UART()), roues(Roues(1,0.85)){}


int CapteurDistance::lectureVolt(int n){
    uint16_t volt;
    uint16_t total = 0;
    uint8_t val;
    for(int i = 0 ; i < n ; i++){
        volt = canObj.lecture(PA0);
        volt = volt >> BITSHIFT;
        total += volt;
     }
    val = total/n;
    uartObj.transmissionUART(val);
    return val;
}

bool CapteurDistance::centre(int n){
    int volt = lectureVolt(n);
    return (volt==35); 
}

void CapteurDistance::trouverCentre(int n){
    int volt;
    while(!centre(n)){
        volt = lectureVolt(n);
        if(volt > VALEUR_CENTRE){
            roues.reculer();
            ifReculer = true;
            roues.accelerer(150); 
        }
        else{
            roues.avancer();
            ifAvancer = true;
            roues.accelerer(150);
        }
    }
    roues.arreter();

    if(ifReculer){
        roues.avancer();
        roues.accelerer(120);
        _delay_ms(1500);
    }
    
    if(ifAvancer){
        roues.reculer();
        roues.accelerer(130);
        _delay_ms(1000);
    }

    roues.reculer();
    while(lectureVolt(n) > 22){
        roues.ajustementPWM(130, 1);
    }

    roues.arreter();
    
}