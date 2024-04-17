#pragma once

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

class Roues{
public:
    Roues();
    Roues(double ajustementRoueDroite1, double ajustementRoueGauche1);
    ~Roues();

    void tournerDroite();
    void tournerGauche();
    void tournerGaucheFort();
    void avancer();
    void reculer();
    void accelerer(uint32_t vitesse);
    void decelerer(uint32_t vitesse);
    void arreter();

    void ajustementPWM(uint32_t pwmValeurA, uint32_t pwmValeurB);

private:
    uint32_t vitesseRoueDroite_;
    uint32_t vitesseRoueGauche_;
    double ajustementRoueDroite;
    double ajustementRoueGauche;
    
    static constexpr uint32_t TEMPS_ROTATION_90 = 1900;
    static constexpr uint32_t TEMPS_ROTATION_FORT = 2650;
    static constexpr uint32_t DELAY_ROTATION = 750;
    static constexpr uint32_t VITESSE_MAX = 255;
    static constexpr uint32_t VITESSE_MIN = 0;
    static constexpr uint32_t VITESSE_ROTATION = 150;
    
    void delay(uint32_t timeDelay);
    


};