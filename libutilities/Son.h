#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
class Son {
public:
    Son();
    void jouerNote(uint16_t note, uint16_t duree);
    void jouerSoulja();
    void arreter();
private:
    void delay(uint32_t timeDelay);

    const uint8_t DEBUT = 45;
    const uint16_t PRESCALER =1024;
    double frequence[37] ={
    110, 116.54, 123.47, 130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00,
    196.00, 207.65, 220, 233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63,
    349.23, 369.99, 392.00, 415.30, 440, 466.16, 493.88, 523.25, 554.37, 587.33,
    622.25, 659.26, 698.46, 739.99, 783.99, 830.61, 880
    };
    const uint16_t notes[5] = {64, 59, 60, 64, 59};
    const uint16_t durees[5] = {700, 700, 930, 700, 700};
    const uint8_t TAILLE_SOULJA = 5;

};