#include "Roues.h"


Roues::Roues(){
    //PMW avec Minuterie1
    //Les signaux sortent des ports PD4 et PD5
    ajustementRoueDroite = 1;
    ajustementRoueGauche = 1;

    TCCR0A |= (1 << WGM00) | (1 << COM0A1)  | (1 << COM0B1);
    TCCR0B |= (1 << CS01);

    DDRB |= (1 << PB3) | (1 << PB4);
    DDRB |= (1 << PD2) | (1 << PD5);

    vitesseRoueDroite_ = VITESSE_MIN;
    vitesseRoueGauche_ = VITESSE_MIN;
}

Roues::Roues(double ajustementRoueDroite1, double ajustementRoueGauche1) : Roues() {
    //PMW avec Minuterie1
    //Les signaux sortent des ports PD4 et PD5
    ajustementRoueDroite = ajustementRoueDroite1;
    ajustementRoueGauche = ajustementRoueGauche1;

}

Roues::~Roues(){
    TCCR0A = 0;
    TCCR0B = 0;
    OCR0A = 0;
    OCR0B = 0;

}

void Roues::delay(uint32_t timeDelay){
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

void Roues::ajustementPWM(uint32_t pwmValueA, uint32_t pwmValueB){
    OCR0A = pwmValueA * ajustementRoueDroite;
    OCR0B = pwmValueB * ajustementRoueGauche;

}

void Roues::accelerer(uint32_t vitesse){
    //VITESSE_MAX = 255
    
    
    vitesseRoueDroite_ = ( vitesse  <= VITESSE_MAX) ? vitesse : VITESSE_MAX;
    vitesseRoueGauche_ = ( vitesse  <= VITESSE_MAX) ? vitesse : VITESSE_MAX;

    ajustementPWM(vitesseRoueDroite_, vitesseRoueGauche_);
}

void Roues::decelerer(uint32_t vitesse){
    //VITESSE_MIN = 0

    vitesseRoueDroite_ = (vitesse >= VITESSE_MIN) ? vitesse : VITESSE_MIN;
    vitesseRoueGauche_ = (vitesse >= VITESSE_MIN) ? vitesse : VITESSE_MIN;

    ajustementPWM(vitesseRoueDroite_, vitesseRoueGauche_);
}

void Roues::avancer(){
    PORTB &= ~(1 << PB5) & ~(1 << PB2);

}

void Roues::reculer(){
    PORTB |= (1 << PB5) | (1 << PB2);
}

void Roues::tournerDroite(){
     //90 degree

    arreter();
    delay(DELAY_ROTATION);
    ajustementPWM(VITESSE_MIN, VITESSE_ROTATION);
    delay(TEMPS_ROTATION_90);
    arreter();
    delay(DELAY_ROTATION);
    ajustementPWM(vitesseRoueDroite_, vitesseRoueGauche_);

}

void Roues::tournerGauche(){
    //90 degree

    arreter();
    delay(DELAY_ROTATION);
    ajustementPWM(VITESSE_ROTATION, VITESSE_MIN);
    delay(TEMPS_ROTATION_90);
    arreter();
    delay(DELAY_ROTATION);
    ajustementPWM(vitesseRoueDroite_, vitesseRoueGauche_);


}
    void Roues::tournerGaucheFort(){
    arreter();
    delay(DELAY_ROTATION);
    ajustementPWM(VITESSE_ROTATION, VITESSE_MIN);
    delay(TEMPS_ROTATION_FORT);
    arreter();
    delay(DELAY_ROTATION);
    ajustementPWM(vitesseRoueDroite_, vitesseRoueGauche_);

    }

void Roues::arreter(){
    vitesseRoueDroite_ = VITESSE_MIN;
    vitesseRoueGauche_ = VITESSE_MIN;

    ajustementPWM(vitesseRoueDroite_, vitesseRoueGauche_);
}