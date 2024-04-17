#pragma once
# define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

enum class Mode{ CTC, PWM };

class Minuterie1{
public:
    const uint8_t PRESCALER_256 = (1<<CS12);

    void partirMinuterie ( uint16_t duree);

    //Mode::CTC ou Mode::PWM
    Minuterie1(Mode mode);

    void stopMinuterie();

private:
    Mode mode_; 
};