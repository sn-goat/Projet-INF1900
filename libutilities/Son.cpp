#include "Son.h"

Son::Son(){
    DDRD |= (1 << PD6) | (1 << PD7);
}

void Son::delay(uint32_t timeDelay){
    bool zeroTimeDelay = !timeDelay;
    if(zeroTimeDelay){
        _delay_ms(0);
    }
    else{
        for(uint32_t i = 0; i < timeDelay; i++){
            _delay_ms(1);
        }
    }
}

void Son::jouerNote(uint16_t note, uint16_t duree){
    
    OCR2A = ((F_CPU)/(2*PRESCALER*frequence[note-DEBUT]))-1;
    TCCR2A |= (1 << WGM21) | (1 << COM2A0);
    TCCR2B |= (1 << CS22) | (1 << CS21) |(1 << CS20);

    delay(duree);
}
void Son:: jouerSoulja(){
     for (int i=0; i< 5; i++){
         jouerNote(notes[i], durees[i]);
     }
 }
void Son::arreter(){
    TCCR2B = 0;
    OCR2A = 0;
    TCCR2A = 0;
    TCCR2B = 0;

}