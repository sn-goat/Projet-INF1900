#include <Robot1.h>

Robot1::Robot1() : capteurDistance(CapteurDistance()), dessin(Dessin()),
                    son(Son()), del(Del(&PORTA, &DDRA, PA2, PA3)), bouton(Bouton()) 
{}


void Robot1::jouerSonAigu(){
    for(uint8_t i = 0; i < ITTERATIONS_SON_AIGU; ++i){
        son.jouerNote(NOTE_AIGU, DELAY_NOTE);
        son.arreter();
        _delay_ms(DELAY_NOTE);
    }
}

void Robot1::clignoterDel(){
    for(uint8_t i = 0; i < ITTERATIONS_DEL; ++i ) {
        del.allumerVert();
        _delay_ms(DELAY_DEL);
        del.eteindre();
        _delay_ms(DELAY_DEL);
    }
}

void Robot1::decompresserDonnees(uint8_t tableauDonnees[6]){
    for(uint8_t i = 0; i < ITTERATIONS_DECOMPRESSER_DONNEES; ++i){
        arrLignes[i].number = (tableauDonnees[i]  & 0x70) >> 4; arrLignes[i].corner = (tableauDonnees[i] & 0x0C) >> 2; 
        arrLignes[i].size = tableauDonnees[i] & 0x03;
    }
}