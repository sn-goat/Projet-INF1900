#include <CapteurDistance.h>
#include <InfraRouge.h>
#include <Dessin.h>
#include <Son.h>
#include <Del.h>
#include <Bouton.h>
#include <Makerline.h>

struct Robot1{   
    Robot1();

    CapteurDistance capteurDistance;
    InfraRouge infraRouge;
    Dessin dessin;
    Son son;
    Del del;
    Bouton bouton;


    void decompresserDonnees(uint8_t tableauDonnees[6]);

    void jouerSonAigu();
    void clignoterDel();

    Ligne arrLignes[6];
    uint8_t tableauDonnees[6];




};

enum class State{START, ATTENTE, RECEPTION, ENVOI_RS232};

const uint8_t MASK = 1<< PD2;

const uint8_t NOTE_AIGU = 80;
const uint8_t NOTE_GRAVE = 45;
const uint16_t DELAY_NOTE_GRAVE = 1000;
const uint8_t DELAY_NOTE = 50;

const uint8_t DELAY_DEL = 100;
const uint8_t ITTERATIONS_DEL = 15;

const uint8_t ITTERATIONS_SON_AIGU = 3;

const uint8_t ITTERATIONS_DECOMPRESSER_DONNEES = 6;