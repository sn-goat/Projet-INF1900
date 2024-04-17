#include "Minuterie1.h"

void Minuterie1::partirMinuterie ( uint16_t duree) {
    cli();
        
    stopMinuterie();

    TCNT1 = 0 ;
    OCR1A = duree;
    switch(mode_){
        case Mode::CTC:
            TCCR1A = 0;

            TCCR1B |= (1 << WGM12) | PRESCALER_256 ; 
        break;

        case Mode::PWM:
            TCCR1A |= (1 << WGM10);
            TCCR1B |= PRESCALER_256;
        break;
    }
    TCCR1C = 0;

    TIMSK1 |= (1<<OCIE1A) ;
    sei();
}

Minuterie1::Minuterie1(Mode mode){
    mode_ = mode;
}

void Minuterie1::stopMinuterie(){
    TCCR1A = 0; 
    TCCR1B = 0;
    TCCR1C = 0;
}