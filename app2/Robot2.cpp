#include <Robot2.h>


Robot2::Robot2() : infraRouge(InfraRouge()), dessin(Dessin()), makerline(Makerline()),
                    son(Son()), del(Del(&PORTC, &DDRC, PC2, PC3)), bouton(Bouton()) 
{
    DDRC &= READING_OUTPUT_PORTC;
}

bool Robot2::isBoutonClicked(){
    const uint8_t DELAY_CENT_MS = 100;

    if(PINC & (1 << PC0)){
        _delay_ms(DELAY_CENT_MS);
        if(PINC & (1 << PC0)){
            return true;
        }
        return false;
    }
    return false;
}

void Robot2::jouerSonAigu(){
    for(uint8_t i = 0; i < ITTERATIONS_SON_AIGU; ++i){
        son.jouerNote(NOTE_AIGU, DELAY_NOTE);
        son.arreter();
        _delay_ms(DELAY_NOTE);

    }
}

void Robot2::clignoterDel(){
    for(uint8_t i = 0; i < ITTERATIONS_DEL; ++i ) {
        del.allumerVert();
        _delay_ms(DELAY_DEL);
        del.eteindre();
        _delay_ms(DELAY_DEL);
    }
}

void Robot2::compresserDonnees(Ligne arrLignes[6]){
    for(uint8_t i = 0; i < ITTERATIONS_COMPRESSER_DONNEES; ++i){
        tableauDonnees[i] = (arrLignes[i].number << 4) | (arrLignes[i].corner << 2) | arrLignes[i].size;
    }
}