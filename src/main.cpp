#include <Arduino.h>
#include "Encoder.h"

Encoder encInput(3, 5, 10, 4);
#define PWMPin 9

float speed = 0;

const float step = 0.02;

void setupTimer1()
{
    //Set PWM frequency to about 25khz on pins 9,10 (timer 1 mode 10, no prescale, count to 320)
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << CS10) | (1 << WGM13);
    ICR1 = 320;
    OCR1A = 0;
    OCR1B = 0;
}

void setPWM9(float f)
{
    OCR1A = (uint16_t)(320 * f);
}

void setup() 
{
    pinMode(9, OUTPUT);
    setupTimer1();
}

void loop() 
{
    encInput.handle();
    if (encInput.up())
    {
      speed += step;
    }
    if (encInput.down())
    {
      speed -= step;
    }
    if (encInput.pressed())
    {
      speed = 0;
    }
    speed = constrain(speed, 0, 1);
    setPWM9(speed);
}

