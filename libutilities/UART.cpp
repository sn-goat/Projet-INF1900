#include "UART.h"


void UART::initialisationUART ( void ) {

    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0A = 0;

    UCSR0B |= (1<<RXEN0) ;
    UCSR0B |= (1<<TXEN0) ;

    // Format des trames: 8 bits, 1 stop bits, sans parité
    //8-bit
    UCSR0C |= (1<<UCSZ00) ;
    UCSR0C |= (1<<UCSZ01) ;
    //1 stop bit (already at default)

    //parity(already at def)


}

// Du USART vers le PC
void UART::transmissionUART ( uint8_t donnee ) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0))) ;
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

uint8_t UART::receiveUART( void )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}

UART::UART(): can_(Can()) {
    initialisationUART();
}

void UART::printUART(uint8_t donnee){
    char buffer[5];
    sprintf(buffer, "%d", donnee);

    printUART(buffer);
}
void UART::printUART(char* donnee){
    uint16_t i = 0;
    while (donnee[i] != '\0'){
        transmissionUART(donnee[i++]);
    }
}
void UART::printUART(const char* donnee){
    uint16_t i = 0;
    while (donnee[i] != '\0'){
        transmissionUART(donnee[i++]);
    }
}

void UART::printCan(){
    uint8_t valeur = can_.lecture(0) >> BITSHIFT_;
    transmissionUART (valeur);
}
