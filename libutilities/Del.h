#pragma once

#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>

class Del{
public:
    Del(volatile uint8_t* portx,volatile uint8_t* ddrX, uint8_t pinM, uint8_t pinP);

    void allumerRouge();
    void allumerVert();
    void allumerAmbre();
    void eteindre();
    ~Del() = default;

private:
    volatile uint8_t* _portx;
    uint8_t _pinM;
    uint8_t _pinP;
    static constexpr uint8_t DELAI_AMBRE_ROUGE = 5;
    static constexpr uint8_t DELAI_AMBER_VERT = 5;



};
