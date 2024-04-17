#include <Makerline.h>
#include <InfraRouge.h>
#include <Dessin.h>
#include <Son.h>
#include <Del.h>
#include <Bouton.h>

struct Robot2{   
    Robot2();

    Makerline makerline;
    InfraRouge infraRouge;
    Dessin dessin;
    Son son;
    Del del;
    Bouton bouton;

    bool isBoutonClicked();

    void compresserDonnees(Ligne arrLignes[6]);

    void jouerSonAigu();
    void clignoterDel();

    uint8_t tableauDonnees[6];




};

enum class State{START, ATTENTE, ENVOI_IR, ENVOI_RS232};

const uint8_t MASK = 1<< PD2;

const uint8_t NOTE_AIGU = 80;
const uint8_t DELAY_NOTE = 50;

const uint16_t DELAY_ATTENTE = 2000;

const uint8_t DELAY_DEL = 100;
const uint8_t ITTERATIONS_DEL = 15;

const uint8_t READING_OUTPUT_PORTC = ~(1 << PC0);

const uint8_t ITTERATIONS_SON_AIGU = 3;

const uint8_t ITTERATIONS_COMPRESSER_DONNEES = 6;