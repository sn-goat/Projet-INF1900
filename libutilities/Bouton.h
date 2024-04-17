#pragma once

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


class Bouton{
public:
    Bouton();
    ~Bouton() = default;
private:    
    void initialisation();
};