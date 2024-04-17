#pragma once
#define F_CPU 8000000UL
#include <avr/io.h> 
#include <stdio.h>
#include <string.h>
#include "Can.h"

class UART{
public:
    void initialisationUART ( void );
    
    // Du USART vers le PC
    void transmissionUART ( uint8_t donnee );
    unsigned char receiveUART ( void );

    //fonctions pour le debug 
    void printUART(uint8_t donnee);
    void printUART(char* donnee);
    void printUART(const char* donnee);
    void printCan();


    //Constructeur call le init 
    UART();
private:
    Can can_;
    const uint8_t BITSHIFT_ = 2;
};