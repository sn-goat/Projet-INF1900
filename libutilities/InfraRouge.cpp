#include "InfraRouge.h"


InfraRouge::InfraRouge() {
    cli();

    DDRA &= ~(1 << PIN_RECEPTEUR);
    DDRD |= (1 << PIN_ENVOYEUR);

    TCCR1A |= (1 << WGM11) | (1 << WGM10); 
    TCCR1A |= (1 << COM1A0) | (1 << COM1B0);

    TCCR1B |=(1 << CS10);
    TCCR1B |= (1 << WGM12) | (1 << WGM13); 

    OCR1A = 0;
    

    sei(); 


}
void InfraRouge::commencerPWM() {
    OCR1A = PWM_38_kHZ;
}
void InfraRouge::arreterPWM() {
    OCR1A = PWM_0_kHZ;
}

InfraRouge::~InfraRouge() {
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 0;
}

void InfraRouge::envoyerImpulsionDebut(){
    commencerPWM();
    _delay_us(DELAY_SIRC_START);
    arreterPWM();
    _delay_us(DELAY_LARGEUR_IMPLUSION_PWM);
}

void InfraRouge::creationImpulsion( bool bit ){
     if ( bit ) {
        commencerPWM();
        _delay_us(DELAY_SIRC_ONE);
    } else  {
        commencerPWM();
        _delay_us(DELAY_SIRC_ZERO);
    }

    arreterPWM();
    _delay_us(DELAY_LARGEUR_IMPLUSION_PWM);
}

void InfraRouge::envoyerCrc( uint8_t crc ){
     envoyerCommande(crc);

}

void InfraRouge::envoyerCommande(uint8_t commande){
    uint8_t longeurCharacter = 0x08;
    uint8_t bit_charactere;

     for (uint8_t positionBit = 0x00; positionBit < longeurCharacter; ++positionBit ) {
        bit_charactere = commande & (1 << positionBit);
        creationImpulsion(bit_charactere);
    }

}



void InfraRouge::envoyer( uint8_t commande ) {
    uint8_t crc = 0;
    crc = _crc_ibutton_update(crc, commande);

    envoyerImpulsionDebut();
    envoyerCommande(commande);
    envoyerImpulsionDebut();
    envoyerCrc(crc);
    envoyerImpulsionDebut();
}

void InfraRouge::envoyerDonne(uint8_t donne){
    _delay_ms(1000);
    for(uint8_t i = 0; i < ITERATION_ENVOYER_DONEE; ++i){
        envoyer(donne);
    }
}

void InfraRouge::envoyerTableau(uint8_t tableau[6]){
    for(uint8_t i = 0; i < ITERATION_ENVOYER_TABLEAU; ++i){
        envoyerDonne(tableau[i]);
    }

}


bool InfraRouge::signalRecuEleve(){
    return !(PINA & (1 << PIN_RECEPTEUR));
}

uint8_t InfraRouge::mesurelongeurSignal(){
    uint8_t longeur = 0;

    while(signalRecuEleve()) {
        _delay_us(100);
        ++longeur;
    }

    return longeur;
}

bool InfraRouge::signalDansSpectre(uint8_t valeur, uint8_t valeurTheorique){
    return valeur >= valeurTheorique - INCERTITUDE && valeur <= valeurTheorique + INCERTITUDE; 
}

uint8_t InfraRouge::recevoirCommande(){
    uint8_t commmande = 0;
    uint8_t longeurSignal = 0;
    uint8_t longeurCommande = 0;

    if (signalRecuEleve()){
        while(!signalDansSpectre(longeurSignal, 24)){
            longeurSignal = mesurelongeurSignal();
            while(!signalRecuEleve()){
            }
        }
        do{
            longeurSignal = mesurelongeurSignal();

            if(signalDansSpectre(longeurSignal, 6)){
                commmande &= ~(1 << longeurCommande);
            }
            else if(signalDansSpectre(longeurSignal, 12)){
                commmande |= (1 << longeurCommande);                
            }
            while(!signalRecuEleve()){
            }
            longeurCommande++;
        }while(!signalDansSpectre(longeurSignal, 24));      
    }

    return commmande;

    
}

uint16_t InfraRouge::recevoir(){ 
    uint16_t result = 0;

    result = recevoirCommande();
    result = result << 8;
    result|= recevoirCommande();

    return result;

}

void InfraRouge::recevoirTableau(uint8_t tableau[6]){
    uint16_t data;
    char charactere = '\0';
    uint8_t crc = 0;
    for(uint8_t i = 0; i < ITERATION_RECEVOIR_TABLEAU; ++i){
        while(true){
            data = recevoir();
            charactere = data & 0xFF;
            crc = (data >> 8) & 0xFF ;
            uint8_t valeur[] = { charactere, crc};


            if ((checkCrc(valeur) == 0) && (charactere != 0)){
                tableau[i] = charactere;
                 break;
             }

        }
    }
}

uint8_t InfraRouge::checkCrc( uint8_t valeursRecues[]){
    uint8_t crc = 0, i;
    uint8_t taille = sizeof(valeursRecues) / sizeof(valeursRecues[0]);

    for (i = 0; i < taille; i++)
        crc = _crc_ibutton_update(crc, valeursRecues[i]);
    return crc;
} 


