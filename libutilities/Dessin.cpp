#define F_CPU 8000000UL
#include "Dessin.h"

Dessin::Dessin(){


}

void Dessin::print(char phrase[], uint8_t nbIteration)
{
    for (int i = 0; i < nbIteration; i++)
    {
        _delay_ms(100);
        uart.printUART(phrase);
    }
}




void Dessin::dessiner(uint8_t n, uint8_t r, Ligne lignes[6])
{

    char start[] = "";
    char nextLine[] = "\n";
    char text[] = "Produit par: Gear 5";

    char charStart[] = "┌";
    char line[] = "───────────";
    char charEnd[] = "┐\n";

    char bord[] = "│";
    char bordEnd[] = "│\n";
    char space[] = "           ";

    char lastLineBord[] = "└";
    char lastLineBord2[] = "┘";

    char boxe1[] = "┏";
    char boxeSpace[] = "      ";
    char boxeLine[] = "━━━━━";
    char boxeIn[] = "     ";
    char boxeEnd[] = "┓";
    char boxeBord[] = "┃";
    char boxeLastBord[] = "┗";
    char boxeLastEnd[] = "┛";
    char parcourLine[] = "══════";
    char parcourB[] = "║";
    char parcourSpace[] = "                                                ";
    char spaceParcourEnd[] = "     ";
    char space1[] = " ";
    char midJoin[] = "╣";
    print(start, 50);
    print(nextLine, 1);
    print(charStart, 1);
    print(line, 9);
    print(charEnd, 1);

    for (int i = 0; i < 2; i++)
    {
        print(bord, 1);
        print(space, 9);
        print(bordEnd, 1);
    }

    
    print(bord, 1);
    print(boxeSpace, 1);
    print(boxe1, 1);
    print(boxeLine, 5);
    print(boxeEnd, 1);
    print(space, 6);
    print(bordEnd, 1);

    for (int j = 0; j < 2; j++)
    {
        print(bord, 1);
        print(boxeSpace, 1);
        print(boxeBord, 1);
        print(boxeIn, 5);
        print(boxeBord, 1);
        print(space, 6);
        print(bordEnd, 1);
    }

    print(bord, 1);
    print(boxeSpace, 1);
    print(boxeBord, 1);
    print(boxeIn, 5);
    print(boxeBord, 1);
    print(space, 1);
    uint8_t compt = 0;

    char parcourBStart[] = "╔";
    char parcoursHaut[] = "═"; // ═══════════════════════════════════════════════

    char parcourBStart2[] = "╗";
   
  


    char topT[] = "╦"; // ╦
   
    char segBody[] = "|";

   
    char head[] = " ___ ";
    char midUpRob[] = "/   \\";
    char robBord[] = "|   |";
    char midRobot[] = "▓   ▓";
    char robotDown[] = "\\___/";

    int positions[] = {0, 0, 0, 0, 0, 0};
    int lengths[] = {0, 0, 0, 0, 0, 0};
    
    uint8_t top = 1;
    uint8_t bottom = 1;

    for(int i =0; i< 6; i++){
            if(lignes[i].corner == 0 ){
                top++;
            }
            else if(lignes[i].corner == 2){
                bottom++;
            }
    }

    for (int i = 0; i < nSegs; i++)
    {


        if (lignes[i].corner == 0)
        {                                                        
            positions[i] = (48*(i+1))/top; 
           
            switch(lignes[i].size){
                case Length::SMALL:
                    lengths[i] = 1;
                    break;
                case Length::MEDIUM:
                    lengths[i] = 2;
                    break;
                case Length::BIG:
                    lengths[i] = 3;
                    break;        
            }
        }
    }

    print(parcourBStart, 1); 
    for (int i = 0; i < 49; i++)
    {
        if (i != 1)
        {
            if (positions[0] == i-1 || positions[1] == i-1
             || positions[2] == i-1 || positions[3] == i-1 ||
              positions[4] == i-1 || positions[5] == i-1)
            {
                print(&topT[0], 1);
            }
            else
            {
                print(&parcoursHaut[0], 1);
            }
        
        }
        

    }
    
    print(parcourBStart2, 1);  
    print(spaceParcourEnd, 1);
    print(bordEnd, 1);         

 
    for (int l = 0; l < 5; l++)
    {
        char parcourSpaceCopy[] = "                                                ";
        for (int x = 0; x < 6; x++)
        {
            if (positions[x] != 0)
            {
                if (lengths[x] >= 0)
                {
                    parcourSpaceCopy[positions[x]] = segBody[0]; 
                    lengths[x]--;
                }
            }
        }
        if ((n % 3 == 0) && r == 1)
        {
            if (compt == 0)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(head, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 1)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(midUpRob, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 2)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(robBord, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 3)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(midRobot, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 4)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(robotDown, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }
            compt += 1;
        }

        else if ((n % 3 == 1) && r == 0)
        {
            if (compt == 0)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(head, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 1)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(midUpRob, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 2)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(midRobot, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 3)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(robBord, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 4)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(robotDown, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            } 
            compt += 1;
        }

        else
        {
             // robot1
            print(bord, 1);
            print(boxeSpace, 1);
            print(boxeBord, 1);
            print(boxeIn, 5);
            print(boxeBord, 1);
            print(space, 1);
        }
       
        print(parcourB, 1);
        print(parcourSpaceCopy, 1);
        print(parcourB, 1);

        
        print(spaceParcourEnd, 1);
        print(bordEnd, 1);
    }
    
    print(bord, 1);
    print(boxeSpace, 1);
    print(boxeBord, 1);
    print(boxeIn, 5);
    print(space1, 12);
    print(parcourB, 1);
    print(parcourSpace, 1);
    print(parcourB, 1);
    print(spaceParcourEnd, 1);
    print(bordEnd, 1);

  
    print(bord, 1);
    print(boxeSpace, 1);
    print(boxeBord, 1);
    print(boxeIn, 5);
    print(space1, 6);
    print(parcourLine, 1);
    print(midJoin, 1);
    print(parcourSpace, 1);
    print(parcourB, 1);
    print(spaceParcourEnd, 1);
    print(bordEnd, 1);

    print(bord, 1);
    print(boxeSpace, 1);
    print(boxeBord, 1);
    print(boxeIn, 5);
    print(space1, 12);
    print(parcourB, 1);
    print(parcourSpace, 1);
    print(parcourB, 1);
    print(spaceParcourEnd, 1);
    print(bordEnd, 1);
    compt = 0;
    
   
   
 
 
    
    char parcourBEnd[] = "╚";
    char parcourBEnd2[] = "╝";
   
    char parcoursBas[] = "═";

    

    
    
    char botT[] = "╩"; 


   

    
    for (int i = 0; i < nSegs; i++)
    {
        if (lignes[i].corner == 2)
        {                                                         
            positions[i] = (48*(i+1))/top -4;
            switch(lignes[i].size){
                case Length::SMALL:
                    lengths[i] = 1;
                    break;
                case Length::MEDIUM:
                    lengths[i] = 2;
                    break;
                case Length::BIG:
                    lengths[i] = 3;
                    break;        
            }
                                                       
        }
    }

   

    for (int z = 0; z < 5; z++)
    {
        char parcourSpaceCopy[] = "                                                ";
        for (int x = 0; x < 6; x++)
        {
            if (positions[x] != 0)
            {
                if (lengths[x] <= 0)
                {
                    parcourSpaceCopy[positions[x]] = segBody[0]; 
                }
                lengths[x]--;
            }
        }

        if ((n % 3 == 1) && r == 1)
        {
            if (compt == 0)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(head, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 1)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(midUpRob, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 2)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(midRobot, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 3)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(robBord, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            else if (compt == 4)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(robotDown, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }
            compt += 1;
        }

        else if ((n % 3 == 0) && r == 0)
        {
            if (compt == 0)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(head, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            if (compt == 1)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(midUpRob, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            if (compt == 2)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(robBord, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            if (compt == 3)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(midRobot, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }

            if (compt == 4)
            {
                print(bord, 1);
                print(boxeSpace, 1);
                print(boxeBord, 1);
                print(boxeIn, 2);
                print(robotDown, 1);
                print(boxeIn, 2);
                print(boxeBord, 1);
                print(space, 1);
            }
            compt += 1;
        }
        
        else {
            print(bord, 1);
            print(boxeSpace, 1);
            print(boxeBord, 1);
            print(boxeIn, 5);
            print(boxeBord, 1);
            print(space, 1);
        }

        print(parcourB, 1);
        print(parcourSpaceCopy, 1);
        print(parcourB, 1);
        print(spaceParcourEnd, 1);
        print(bordEnd, 1);
    }

    // fermetture parcours
    print(bord, 1);
    print(boxeSpace, 1);
    print(boxeBord, 1);
    print(boxeIn, 5);
    print(boxeBord, 1);
    print(space, 1);
    print(parcourBEnd, 1);
    for (int i = 0; i < 49; i++)
    {
        if (i != 1)
        {
            if (positions[0] == i-1 || positions[1] == i-1
             || positions[2] == i-1 || positions[3] == i-1 ||
              positions[4] == i-1 || positions[5] == i-1)
            {
                print(&botT[0], 1);
            }
            else
            {
                print(&parcoursBas[0], 1);
            }
        
        }
    }
    print(parcourBEnd2, 1);
    print(spaceParcourEnd, 1);
    print(bordEnd, 1);
    // boite
    for (int j = 0; j < 2; j++)
    {
        print(bord, 1);
        print(boxeSpace, 1);
        print(boxeBord, 1);
        print(boxeIn, 5);
        print(boxeBord, 1);
        print(space, 6);
        print(bordEnd, 1);
    }

    // fermetture boite
    print(bord, 1);
    print(boxeSpace, 1);
    print(boxeLastBord, 1);
    print(boxeLine, 5);
    print(boxeLastEnd, 1);
    print(space, 6);
    print(bordEnd, 1);

    for (int k = 0; k < 2; k++)
    {
        print(bord, 1);
        print(space, 9);
        print(bordEnd, 1);
    }

    print(lastLineBord, 1);
    print(line, 9);
    print(lastLineBord2, 1);
    print(nextLine, 1);
    print(text, 1);
}
