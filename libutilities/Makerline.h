#pragma once
#define F_CPU 8000000UL
#define ISR_NOBLOCK
#include <Son.h>
#include <Del.h>
#include <Can.h>
#include <Roues.h>
#include <Dessin.h>



class Makerline{
public:

    Makerline();
    void faireCircuit();

    Ligne arrLignes[6]; 
    

private:   
    void rotation(uint8_t vitesseDroite, uint8_t vitesseGauche);
    void rotation2(uint8_t vitesseDroite, uint8_t vitesseGauche);
    void reculer();

    int vitesse = 155;

    bool premierTurn = false;
    bool turn = true;
    bool recul = false;
    bool isCorner = false;
    bool fin = false;
    bool allPinsOn = false;
    bool fin_fin = false;

    uint8_t cornerNumber = 0;
    uint8_t numberOfStops = 0;
    uint8_t lineNumber = 0;
    uint8_t size = 0;
    uint8_t indexArrLigne = 0;
    Roues roues;


};
const uint8_t S3 = 0x04;
//tourner a droite
const uint8_t S3_S4 = 0x0C;
//
//
//tourner a gauche
const uint8_t NO_CAPTOR = 0x00;
const uint8_t S1 = 0x01;
const uint8_t S2 = 0x02;
const uint8_t S4 = 0x08;
const uint8_t S5 = 0x10;
const uint8_t S2_S3 = 0x06;
const uint8_t S1_S2_S3 = 0x07;
const uint8_t S2_S4_S5= 0x1A;
const uint8_t S1_S2 = 0x03;
const uint8_t S3_S4_S5 = 0x1C;
const uint8_t S3_S5 = 0x14;
const uint8_t S2_S3_S4_S5 = 0x1E;
const uint8_t S1_S2_S3_S4_S5 = 0x1F;
const uint8_t S4_S5 = 0x18;
const uint8_t S1_S5 = 0x11;
const uint8_t S1_S3 = 0x05;
