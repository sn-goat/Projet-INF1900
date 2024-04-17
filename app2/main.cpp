/*
Créé par: Sergile Nyouvop, Mervin Tounou, Matthew Hantar and Yani Haddad
Date de création: 02/04/2024
Groupe: 2
Projet app2
Description: Ce fichier C++ orchestre l'exécution des instructions à partir de la table des états.
             Le robot2 suit les lignes des circuits dans le sens horaire, mesure les segments de 
             ligne, puis les envoie au robot1 via une transmission infrarouge. Le robot2 peut 
             également envoyer une carte du circuit via RS232 vers un PC. À chaque état, le robot2 génère 
             différentes couleurs de lumière et des sons sur le microcontrôleur AVR.
Indentification des matériaux: Microcontrôleur AVR ATMega324PA; Les broches C2 et C3 sont connectées aux broches Free-DEL; 
                               La broche D2 est connectée au bonton int; Un condensateur, une résistance et un bouton-poussoir 
                               sont connectés avec quatre câbles sur le breadboard dont un sur C0 et C1, et un sur GRNB et VCCB; 
                               Une DEL infrarouge est connectée au breadboard avec une résistance, un câble, 
                               un câble connecté à D5 et un câble connecté à GRNC; Les broches B2, B3, B4 et B5 son connectées
                               aux pont en H; Les broches A0, A1, A2, A3, A4, GRNA et VCCA sont connecté au Makerline; Les broches
                               D6 et D7 sont connecté au son; Un câble USB relie l'ordinateur au microcontrôleur 
                               pour installer le programme;

                                            Table des états app2
+--------------+-----------------+------------+----------------+-------------------------+-------------------------+
| État Initial |    Entrée A     |  Entrée B  | Prochain État  |        Sortie A         |        Sortie B         |
+--------------+-----------------+------------+----------------+-------------------------+-------------------------+
| STATE        | Bonton Poussoir | Bonton INT | Prochain STATE | Sortie PORTC PC2 et PC3 | Sortie PORTD PD6 et PD7 |
+--------------+-----------------+------------+----------------+-------------------------+-------------------------+
| START        | X               | X          | ATTENTE        | PAS DE COULEUR          | SON                     |
| ATTENTE      | 0               | 0          | ATTENTE        | ROUGE                   | PAS DE SON              |
| ATTENTE      | 0               | 1          | ENVOI_IR       | ROUGE                   | PAS DE SON              |
| ATTENTE      | 1               | 0          | ENVOI_RS232    | ROUGE                   | PAS DE SON              |
| ATTENTE      | 1               | 1          | ATTENTE        | ROUGE                   | PAS DE SON              |
| ENVOI_IR     | X               | X          | ATTENTE        | PAS DE COULEUR          | SON                     |
| ENVOI_RS232  | X               | X          | ATTENTE        | VERT                    | PAS SON                 |
+--------------+-----------------+------------+----------------+-------------------------+-------------------------+

*/
#define F_CPU 8000000UL
#define ISR_NOBLOCK
#include <Robot2.h>

volatile uint8_t gBoutonPoussoir = 0;
const uint8_t gDELAY_30_MS = 30;
ISR (INT0_vect) {

    _delay_ms ( gDELAY_30_MS );
    if ( PIND & (MASK) ){
        gBoutonPoussoir = 1;   
    }
    else{
        gBoutonPoussoir = 0;
    }
}

int main(){
    Robot2 robot2 = Robot2();

    State STATE = State::START;
    while(true){
        switch(STATE){
            case State::START:
                robot2.son.jouerSoulja();
                robot2.son.arreter();
                robot2.makerline.faireCircuit();
                STATE = State::ATTENTE;

                break;
            case State::ATTENTE:
                robot2.del.allumerRouge();
        
                while(!gBoutonPoussoir && !robot2.isBoutonClicked()){
                    robot2.del.allumerRouge();
                }

                if(gBoutonPoussoir){
                    STATE = State::ENVOI_IR;
                }
                else if(!robot2.isBoutonClicked()){
                    STATE = State::ENVOI_RS232;
                }
                else if(gBoutonPoussoir && robot2.isBoutonClicked()){
                    STATE = State::ATTENTE;
                }

                break;

            case State::ENVOI_IR:
                robot2.del.eteindre();

                robot2.jouerSonAigu();

                _delay_ms(DELAY_ATTENTE);

                robot2.compresserDonnees(robot2.makerline.arrLignes);
                robot2.infraRouge.envoyerTableau(robot2.tableauDonnees);

                STATE = State::ATTENTE;

                break;   
            case State::ENVOI_RS232:
                robot2.del.eteindre();

                while(robot2.isBoutonClicked()){}

                if(!robot2.isBoutonClicked()){
                    //robot2.dessin..(robot2.makerline.arrLignes)...
                    robot2.dessin.dessiner(1, 1, robot2.makerline.arrLignes);
                    //TODO: Clignoter Del utilise des delay donc tout le robot va devenir frozen pendant
                    robot2.clignoterDel();
                }
                STATE = State::ATTENTE;

            break;


        }
    }
    
}