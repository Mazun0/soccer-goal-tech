#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <avr/interrupt.h>

#include "lights.h"
#include "display.h"
#include "sensors.h"
#include "rfid.h"


#define F_CPU 3333333


uint8_t search_count = 0;
uint8_t goal = 0;    
uint16_t dist1;
uint16_t dist2;

/**
 * Initalizing Timer/Count A
 * 
 */
void TCA0_init(void){
    TCA0.SINGLE.INTCTRL = (TCA_SINGLE_OVF_bm);
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
    TCA0.SINGLE.PER = 41667;  // Base  0.1 seconds
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV8_gc;       
//                                     /* start timer */  
}

/*
 ISR Interrupt for Overflow
 */
ISR(TCA0_OVF_vect){
    
     turnOnRedLigtht();
     if(search_count > 0){ // Search Mode
        if ((USART1.STATUS & USART_RXCIF_bm)){  // If Detected
            USART_Disable(); // disable RFID Scanner
            turnOffRedLight(); 
            turnOnGreenLigtht();
            USART1.STATUS &= ~USART_RXCIF_bm; // clear the flag for USART
            search_count = 0; // Cancel out Search 
            goal = 50; // Transition to Goal
        }
        search_count--; 
     
    } // If not found
     if(search_count == 0){
         USART_Disable();        
         turnOffRedLight();
         TCA0.SINGLE.INTFLAGS = (TCA_SINGLE_OVF_bm);
     }
     // Goal State
     if (goal > 0){
         goal --;
         
     }
     if(goal == 0){
         turnOffGreenLight();
         TCA0.SINGLE.INTFLAGS = (TCA_SINGLE_OVF_bm);
     }
       TCA0.SINGLE.INTFLAGS = (TCA_SINGLE_OVF_bm);
     
}

/**
 * To read both echos and use the global variables here
 */
void readBoth_echos(){
    sensTrigger(PIN6_bm); // calls trigger
    dist1 = SensEcho(PIN7_bm); // calls echo 
    // use the value of Echo to get a reading 
    dist1 = calculate_distance(dist1);
    _delay_ms(50); // small debouncing  
    sensTrigger(PIN4_bm);
    dist2 = SensEcho(PIN5_bm); 
    dist2 = calculate_distance(dist2);
}

int main(void) {
   
    lights_init();
    initTWI();
    USART_init();
    sensorInit();
    LCD_init();
    turnOnRedLigtht();
    print_Goal();
    _delay_ms(10000);
    turnOffRedLight();
    LCD_sendCommand(DISPLAY_CLEAR);  // Clear screen
    TCA0_init(); //  timer initialization
    dist1 = 11; // Initalized to 11 or else it assumes that the distance is 0 when 
    dist2 = 11; 
    sei();
    while (1) { 
        readBoth_echos();
           cursorMode(0); // goes to first row
           Display_Distance(1,dist1);
           _delay_ms(50); // Delay for Priting 
           cursorMode(1);// moves to second row
            Display_Distance(2,dist2);
           if(dist1 < 9 || dist2 < 9){ // if distance have changed
               search_count = 3; // Starts Search Mode
               USART_Enable(); // enable USART 
              TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
           }           
     }     
}
    