#include "Makerline.h"



Makerline::Makerline():roues(Roues(1,0.99)){
    DDRA = 0x00;
   
    
}

void Makerline::rotation(uint8_t vitesseDroite, uint8_t vitesseGauche){
    _delay_ms(800);
    if(PINA & S5){
        roues.ajustementPWM(vitesseDroite,vitesseGauche);
        _delay_ms(500);

    }
     while(!(PINA & S5)){
            roues.ajustementPWM(vitesseDroite, vitesseGauche);
        }
        roues.arreter();
        _delay_ms(1000);

}


void Makerline::rotation2(uint8_t vitesseDroite, uint8_t vitesseGauche){
    _delay_ms(800);
    if(PINA & S2){
        roues.ajustementPWM(vitesseDroite,vitesseGauche);
        _delay_ms(500);

    }
     while(!(PINA & S2)){
            roues.ajustementPWM(vitesseDroite, vitesseGauche);
        }
        roues.arreter();
        _delay_ms(1000);

}

void Makerline::reculer(){
    roues.reculer();
        roues.accelerer(vitesse);
        switch (PINA & 0b00011111)
        {
            case S3:
                roues.reculer();
                roues.accelerer(vitesse);
                break;
                    
            case S4_S5:
            case S3_S4:
                 roues.ajustementPWM(vitesse+5,vitesse);                        
                 break;
                    
            case S4:
                roues.ajustementPWM(vitesse+10,vitesse);
                break;

            case S1:
            case S2:
            case S1_S2:               
                roues.ajustementPWM(vitesse+5,vitesse);

            case S2_S3:        
                roues.ajustementPWM(vitesse,vitesse+5);
                break;

            case S1_S2_S3_S4_S5:
                roues.arreter();
                allPinsOn = true;
                break;

            case NO_CAPTOR:
                roues.avancer();
                break;

        }
}

void Makerline::faireCircuit(){
    while(!premierTurn){
        switch (PINA & 0b00011111)
        {
        case S3:
            roues.avancer();
            roues.accelerer(vitesse);
            break;
        case S4_S5:
        case S3_S4:
            roues.ajustementPWM(vitesse-35,vitesse+55);
            
            
            break;
        case S4:
        roues.ajustementPWM(vitesse,vitesse+65);
        break;

        case S1:
        case S1_S2:

            roues.ajustementPWM(vitesse+35,vitesse);
        
        case S2_S3:
            
            roues.ajustementPWM(vitesse+25,vitesse);
        
            break;
        case S2_S3_S4_S5:
        case S2_S4_S5:
        case S3_S5:
        case S3_S4_S5:

            roues.ajustementPWM(vitesse,vitesse);
            _delay_ms(650);
            roues.arreter();
            rotation(1, vitesse);

            roues.arreter();

            premierTurn = true;
            break;
        
        
        }
    }
    // return les vitesse avec les focntions et le mettre apres tourner 
    while(true){
        
        
        while(!recul && !fin){
            switch (PINA & 0b00011111){
            case S3:
                roues.avancer();
                roues.accelerer(vitesse);
                //segment();
                break;
            case S4_S5:
            case S3_S4:
                roues.ajustementPWM(vitesse-35,vitesse+55);
                //segment();
                
                break;
            case S5:
                roues.ajustementPWM(vitesse,vitesse+85);
                break;
            case S4:
                roues.ajustementPWM(vitesse,vitesse+65);
                //segment();
            break;

            case S1:
            case S1_S2:

                roues.ajustementPWM(vitesse+35,vitesse);
                //segment();
            case S2:
            case S2_S3:
                
                roues.ajustementPWM(vitesse+15,vitesse);
                //segment();
            
                break;
            //Quand il trouve un segment
            case S1_S2_S3_S4_S5:
            case S2_S3_S4_S5:
            case S2_S4_S5:
            case S3_S5:
            case S3_S4_S5:

                roues.arreter();
                _delay_ms(400);
                
                roues.avancer();
                roues.accelerer(vitesse);
                _delay_ms(500);
   
                roues.arreter();
                _delay_ms(500);
                
                //Corner 
                if(!(PINA & S1_S2_S3_S4_S5)){

                    roues.avancer();
                    roues.accelerer(vitesse);
                    _delay_ms(300);

                    rotation(1, vitesse);
                    roues.arreter();
                    cornerNumber++;       
                    break;
                }
                roues.reculer();
                _delay_ms(500);
                roues.arreter();

                //Ajuste pour aller sur la ligne
                roues.ajustementPWM(vitesse-5,vitesse);
                roues.reculer();
                _delay_ms(1500);
                
                roues.arreter();
                _delay_ms(100);
                
                //Ajustement aller sur la ligne
                roues.ajustementPWM(vitesse, vitesse-5);
                roues.avancer();
                roues.accelerer(vitesse);
                _delay_ms(2800);
                

                //pour tourner sur la ligne

                roues.arreter();
                _delay_ms(800);
                if(!(PINA & S1_S2_S3_S4_S5)){
                    rotation2(1,vitesse);
                }
                roues.reculer();
                rotation(vitesse,1);
                roues.avancer();

                //Check la longeur du segment
                roues.avancer();
                roues.accelerer(vitesse);
                _delay_ms(500);
                

                
                break;
            case S1_S2_S3:
           
                roues.arreter();
                _delay_ms(400);
                
                roues.avancer();
                roues.accelerer(vitesse);
                _delay_ms(950);
                roues.arreter();
   
                // roues.arreter();
                // _delay_ms(500);

                // roues.reculer();
                // _delay_ms(500);
                // roues.arreter();

                // //Ajuste pour aller sur la ligne
                // roues.ajustementPWM(vitesse-5,vitesse);
                // roues.reculer();
                // _delay_ms(1500);
                
                // roues.arreter();
                // _delay_ms(100);
                
                // //Ajustement aller sur la ligne
                // roues.ajustementPWM(vitesse, vitesse);
                // roues.avancer();
                // roues.accelerer(vitesse);
                // _delay_ms(2000);
 
                // //pour tourner sur la ligne
                // roues.arreter();
                // roues.reculer();
                // roues.avancer();
                //rotation2(vitesse,1);
                roues.tournerGauche();
                while(!(PINA & S1_S2_S3_S4_S5)){
                    roues.reculer();
                    roues.accelerer(vitesse);
                }
                roues.arreter();
                // roues.avancer();
                // rotation(vitesse,1);
                //roues.tournerGauche();
                fin = true;
                break;

            case NO_CAPTOR:
                roues.arreter();
                _delay_ms(300);
                roues.reculer();
                roues.accelerer(vitesse);
                _delay_ms(850);

                //Technique de ryan le roux mais inversed
                while(!allPinsOn){
                    if (!(PINA & S1_S2_S3_S4_S5)){
                        allPinsOn = true;
                    }
                    reculer();
                    _delay_ms(200);
                    roues.arreter();
                    _delay_ms(100);
                    numberOfStops++;
                    if (!(PINA & S1_S2_S3_S4_S5)){
                        allPinsOn = true;
                    }

                }

                //A AJUSTER, cest pas encore tres bien tester
                //size 1 = petit
                //size 2 = moyen
                //size 3 = grand
                if(numberOfStops < 9){
                    size = 1;
                }
                else if(numberOfStops <= 14){
                    size = 2;
                }
                else{
                    size = 3;
                }
                //number, corner, size, position dans le        
                Ligne ligne{lineNumber, cornerNumber, size};
                arrLignes[indexArrLigne] = ligne;
                size = 0;
                numberOfStops = 0;
                lineNumber++;
                indexArrLigne++;
                allPinsOn = false;
                recul = true;
                break;



                //((PINA & (1 << S1) )&& (PINA & (1 << S2)) && (PINA & (1 << S3)) && (PINA & (1 << S4)) && (PINA & (1 << S5))
                //(PINA & (1 << S1) )&& (PINA & (1 << S2)) && (PINA & (1 << S3)) && (PINA & (1 << S4)) && (PINA & (1 << S5))
            // case (S1_S2_S3_S4_S5):
            //     del.allumerRouge();
            //     roues.arreter();
            //     _delay_ms(1000);
            //     // roues.ajustementPWM(vitesse,vitesse);
            //     // _delay_ms(500);
            //     // roues.tournerDroite();
            //     break;
            }
        }
        
        if (recul == true){
            roues.arreter();
            _delay_ms(400);

            roues.avancer();
            roues.accelerer(vitesse);
            _delay_ms(1500);

            roues.arreter();
            roues.avancer();
            roues.tournerGaucheFort();
            //_delay_ms(400);
            rotation(1,vitesse);
            recul = false;
        }
        if (fin==true ){
            roues.avancer();
            roues.accelerer(vitesse);
            _delay_ms(725);
            roues.arreter();
            break;

        }

    }
   

}