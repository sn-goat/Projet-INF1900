/*
Créé par: Sergile Nyouvop, Mervin Tounou, Matthew Hantar and Yani Haddad
Date de création: 02/04/2024
Groupe: 2
Projet app1
Description: Ce fichier C++ orchestre l'exécution des instructions à partir de la table des états.
             Le robot1 doit s'orienter vers l'ouverture de la boite là où il est placé, recevoir les segments
             envoyés par le robot2 via transmission infrarouge et envoyer une carte du circuit avec les 
             segments ajoutés via RS232 vers un PC. À chaque état, le robot1 génère 
             différentes couleurs de lumière et des sons sur le microcontrôleur AVR.
Indentification des matériaux: Microcontrôleur AVR ATMega324PA; Les broches A2 et A3 sont connectées aux broches Free-DEL;  
                               Les broches B2, B3, B4 et B5 son connectées aux pont en H; La broche D2 est connectée au bonton int;
                               Les broches D6 et D7 sont connecté au son; Un câble USB relie l'ordinateur au microcontrôleur pour
                               installer le programme;Les broches A1, A2, A3, GDNA et VCCA sont connectées au capteur de distance; La broche
                               A7 est connectée au capteur infrafrouge sur le breadboard avec les broches GNDB  et VCCB;

                                            Table des états app1
+--------------+------------+-----------------+----------------+-------------------------+-------------------------+
| État Initial |  Entrée A  |    Entrée B     | Prochain État  |        Sortie A         |        Sortie B         |
+--------------+------------+-----------------+----------------+-------------------------+-------------------------+
| STATE        | Bonton INT | ERROR RECEPTION | Prochain STATE | Sortie PORTA PA1 et PA2 | Sortie PORTD PD6 et PD7 |
+--------------+------------+-----------------+----------------+-------------------------+-------------------------+
| START        | X          | X               | ATTENTE        | PAS DE COULEUR          | SON                     |
| ATTENTE      | 0          | X               | ATTENTE        | ROUGE                   | PAS DE SON              |
| ATTENTE      | 1          | X               | RECEPTION      | ROUGE                   | PAS DE SON              |
| RECEPTION    | X          | NON             | ENVOI_RS232    | PAS DE COULEUR          | PAS DE SON              |
| RECEPTION    | X          | OUI             | ATTENTE        | PAS DE COULEUR          | SON                     |
| ENVOI_RS232  | X          | X               | ATTENTE        | VERT                    | PAS SON                 |
+--------------+------------+-----------------+----------------+-------------------------+-------------------------+


*/
#define F_CPU 8000000UL
#define ISR_NOBLOCK
#include <Robot1.h>
#include <Dessin.h>

volatile uint8_t gBoutonPoussoir = 0;
const uint8_t gDELAY_30_MS = 30;
ISR (INT0_vect) {

    _delay_ms (gDELAY_30_MS);
    if ( PIND & (MASK) ){
        gBoutonPoussoir = 1;   
    }
    else{
        gBoutonPoussoir = 0;
    }
}

int main(){
    Dessin dessin;
    Robot1 robot1;
    State STATE = State::START;


    while(true){
        switch(STATE){
            case State::START:
                //robot1.son.jouer....();
                //robot1.son.arreter();

                robot1.capteurDistance.trouverCentre(200);
                STATE = State::ATTENTE;
                break;

            case State::ATTENTE:
                robot1.del.allumerRouge();

                while(!gBoutonPoussoir){
                    robot1.del.allumerRouge();
                }
                if(gBoutonPoussoir){
                        STATE = State::RECEPTION;
                    }

                robot1.jouerSonAigu();
                robot1.son.arreter();
                break;

            case State::RECEPTION:
            {
                robot1.del.eteindre();

                robot1.infraRouge.recevoirTableau(robot1.tableauDonnees);
                
                bool ERROR = (robot1.tableauDonnees[0] == 0) || (robot1.tableauDonnees[1] == 0) || (robot1.tableauDonnees[2] == 0) || (robot1.tableauDonnees[3] == 0);
                if(ERROR){
                    robot1.son.jouerNote(NOTE_GRAVE, DELAY_NOTE_GRAVE);
                    robot1.son.arreter();
                    
                    STATE = State::ATTENTE;
                } else {
                    STATE = State::ENVOI_RS232;
                }

                robot1.decompresserDonnees(robot1.tableauDonnees);
                break;
            }
            case State::ENVOI_RS232:
                robot1.del.allumerVert();

                while(!gBoutonPoussoir){}

                if(gBoutonPoussoir){
                    
                        //robot1.dessin..(robot.arrLignes).
                        dessin.dessiner(1, 1, robot1.arrLignes);
                        //TODO: Clignoter Del utilise des delay donc tout le robot va devenir frozen pendant
                        robot1.clignoterDel();
                    }
                    
                STATE = State::ATTENTE;
                break;
        }
    }
    
}