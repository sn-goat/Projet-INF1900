#pragma once
#define F_CPU 8000000UL
#define F_IR 38000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/crc16.h>
#include <Minuterie1.h>

class InfraRouge {
public:
    InfraRouge();
    ~InfraRouge();

    void envoyerTableau(uint8_t tableau[6]);
    void recevoirTableau(uint8_t tableau[6]);

    void lectureIncorrecte();

private:
    void envoyer ( uint8_t commande );

    uint16_t recevoir();

    void envoyerImpulsionDebut();
    void commencerPWM();
    void arreterPWM();



    uint8_t mesurelongeurSignal();
    bool signalDansSpectre(uint8_t valeur, uint8_t valeurTheorique);


    uint8_t checkCrc(uint8_t valeursRecues[]);
    bool signalRecuEleve();

    void creationImpulsion( bool bit );
    
    void envoyerCrc(uint8_t crc);
    void envoyerCommande(uint8_t commande);
    void envoyerDonne(uint8_t commande );
    
    uint8_t recevoirCommande();


};

const uint8_t PWM_38_kHZ = (F_CPU / (2 * F_IR)) - 1;
const uint8_t PWM_0_kHZ = 0;

const uint16_t DELAY_SIRC_ONE = 1200;
const uint16_t DELAY_SIRC_ZERO = 600;
const uint16_t DELAY_SIRC_START = 2400;
const uint16_t DELAY_LARGEUR_IMPLUSION_PWM = 600;

const uint8_t PIN_RECEPTEUR = PA7;  
const uint8_t PIN_ENVOYEUR = PD5;

const uint16_t DELAY_INCORRECT = 1000;

const uint8_t ITERATION_ENVOYER_DONEE = 5;

const uint8_t ITERATION_ENVOYER_TABLEAU = 6;

const uint8_t ITERATION_RECEVOIR_TABLEAU = 6;



const uint8_t INCERTITUDE = 3;
