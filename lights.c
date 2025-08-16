/*
 * File:   lights.c
 * Author: mazuno
 *
 * Created on 07 December 2024, 17:49
 */

#include "lights.h"
#include <avr/io.h>

/**
 * to initalize pins for LED lights
 */
void lights_init(){
   PORTD.DIR |= PIN6_bm; // Red Light
   PORTD.DIR |= PIN1_bm; // Green Lgiht
}

/**
 * To turn on Red light
 */
void turnOnRedLigtht(){
    PORTD.OUT |= PIN6_bm;
}
/**
 * To turn off Red Light
 */
void turnOffRedLight(){
    PORTD.OUT &= ~(PIN6_bm);
}

/**
 * To Turn on Green light
 */
void turnOnGreenLigtht(){
    PORTD.OUT |= PIN1_bm;
}
/**
 * To turn off Green light
 */
void turnOffGreenLight(){
    PORTD.OUT &= ~(PIN1_bm);
}