#include "Del.h"

Del::Del(volatile uint8_t* portx,volatile uint8_t* ddrX,  uint8_t pinM, uint8_t pinP) : 
                                                    _portx(portx),
                                                    _pinM(pinM),
                                                    _pinP(pinP) 
{
    *ddrX |= (1 << _pinP); 
    *ddrX |= (1 << _pinM);
}


void Del::allumerRouge(){
    *_portx |= (1 << _pinM);
    *_portx &= ~(1 << _pinP);
}

void Del::allumerVert(){
    *_portx |= (1 << _pinP);
    *_portx &= ~(1 << _pinM);
}

void Del::allumerAmbre(){
    allumerVert();
    _delay_ms(DELAI_AMBRE_ROUGE);
    allumerRouge();
    _delay_ms(DELAI_AMBRE_ROUGE);
}

void Del::eteindre(){
    *_portx &= ~(1 << _pinP) & ~(1 << _pinM);
}
