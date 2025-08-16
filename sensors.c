/*
 * File:   sensors.c
 * Author: mazuno
 *
 * Created on 09 December 2024, 08:55
 */


#include <avr/io.h>
#include <util/delay.h>

/**
 * initializing distances sensors
 */
void sensorInit(){
    
    PORTA.DIR &= ~PIN7_bm; // Echo 1
    PORTA.DIR |= PIN6_bm; // Trig 1
    
    PORTA.DIR &= ~PIN5_bm; // Echo 2
    PORTA.DIR |=  PIN4_bm; // Trig 2
    
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;
}


/**
 * Toggle Trigger pins
 * @param pin the Pin that is Trig
 */
void sensTrigger(uint8_t pin){
    PORTA.OUT |= pin;
      _delay_us(10); // delay in micro seconds
    PORTA.OUT  &= ~(pin); // 
}
/**
 * Senses Waves that was from the sound wave
 * 
 * @param pin, the Echo Pins
 * @return the palse width
 */
uint16_t SensEcho(uint8_t pin){
    uint16_t pulse = 0;
    // counts as high
    while(!(PORTA.IN & pin)){ // if haven't recived, pass
        ;
    }
     while (PORTA.IN & pin) { // if recived
        pulse++; // counts the pulse  
        _delay_us(1);  // gets every microseconds
    }
    return pulse; // gets the rate
}

/**
 * 
 * @param pulse_width to convert it to cm 
 * @return the distance in cm
 */
uint16_t calculate_distance(uint16_t pulse_width) {
    return pulse_width * 0.0343 / 2;
    // formula from the data sheet 
}


