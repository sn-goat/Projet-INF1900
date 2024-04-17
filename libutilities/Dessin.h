#pragma once
#define F_CPU 8000000UL
#define ISR_NOBLOCK
#include <UART.h>
#include <util/delay.h>

//number, corner, size dans le struct
struct Ligne{
    uint8_t number;
    uint8_t corner;
    uint8_t size;
};

enum Length {
    SMALL = 1,
    MEDIUM = 2,
    BIG = 3,
};

class Dessin
{
public:
    Dessin();
    void print(char phrase[], uint8_t nbIteration);
    void dessiner(uint8_t n, uint8_t r, Ligne Lignes[6]);
    UART uart;
    uint8_t nSegs = 6;

};