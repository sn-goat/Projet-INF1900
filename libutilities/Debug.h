#pragma once
#define F_CPU 8000000UL
#include <avr/io.h> 
#include <avr/interrupt.h>
#include "Can.h"
#include  "UART.h"

UART uartt;
const uint8_t BITSHIFT = 2;
#ifdef DEBUG 
    #define DEBUG_PRINT(X); uartt.printUART(X)
    #define DEBUG_PRINT_CAN(); uartt.printCan()
#else

    #define DEBUG_PRINT(X) do {} while (0)
    #define DEBUG_PRINT_CAN() do {} while (0)

#endif
