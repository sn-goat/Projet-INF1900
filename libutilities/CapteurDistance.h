#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/crc16.h>
#include <UART.h>
#include <Del.h>
#include <Can.h>
#include <Roues.h>

class CapteurDistance{
public:
    CapteurDistance();
    ~CapteurDistance(){};

    int lectureVolt(int n);
    bool centre(int n);
    void trouverCentre(int n);

private:
    Can canObj;
    UART uartObj;
    Roues roues;

    bool ifReculer = false;
    bool ifAvancer = false;
    const uint8_t BITSHIFT = 2;
    const uint8_t VALEUR_CENTRE = 35;
};