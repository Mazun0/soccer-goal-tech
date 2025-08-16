/*
 * File:   display.c
 * Author: mazuno
 *
 * Created on 08 December 2024, 21:34
 */
#include <string.h>

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"



/**
 * initializing TWI For display
 */

void initTWI(void) {
    // Enable pull-ups for SDA and SCL pins (PORTA pins 2 and 3)
    PORTA.DIR  |= PIN2_bm; 
    PORTA.DIR  |= PIN3_bm;
    PORTA.OUT |= (PIN2_bm | PIN3_bm); 
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm;
    // Set PA2 and PA3 high (output high)
 
    TWI0.MBAUD = 10;

    // Set TWI to idle state and clear status flags
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;

    // Enable TWI peripheral and run in debug mode
    TWI0.DBGCTRL = TWI_DBGRUN_bm;
    TWI0.MCTRLA |= TWI_ENABLE_bm;  // Enable TWI peripheral
}    


/**
 * Displaying Distance
 * @param sens the Sensor that is used with
 * @param distance the distance that is used
 */
void Display_Distance(uint8_t sens,uint16_t distance) {
    char buffer[16]; /// have a string ready
    snprintf(buffer, sizeof(buffer), "Dist %d: %d ",sens,distance);
    LCD_writeString(buffer); 
}

/**
 * Initalizing Display with commands
 */
void LCD_init(void) {
    _delay_ms(50);  //
    LCD_sendCommand(DISPLAY_CLEAR);  // Clear screen
    _delay_ms(5);           // small delay 
    LCD_sendCommand(DISPLAY_ON_CURSOR_OFF); // to turn on display
    LCD_sendCommand(EIGHT_BIT_TWO_LINES);  // Set setting 8 bit two lines
    LCD_sendCommand(AUTO_INCREMENT);  // setting auto-Increment
    
    

}

/**
 * Sending data to display 
 * @param data: the unit that it is using 
 */
void LCD_sendData(uint8_t data) {
    TWI0.MADDR = (DIPSLAY_ADDR << 1);  // Set write operation (0x3E)
    while (!(TWI0.MSTATUS & TWI_WIF_bm));  
    TWI0.MDATA = DISPLAY_DATA;  // setting to Data mode
    while (!(TWI0.MSTATUS & TWI_WIF_bm));  
    TWI0.MDATA = data;  
    while (!(TWI0.MSTATUS & TWI_WIF_bm));  
    TWI0.MCTRLB = TWI_MCMD_STOP_gc;  
    _delay_ms(5);  
}

/**
 * To send data from a array of char
 * @param str an array of chars
 */
void LCD_writeString( char* str) {
    while (*str != '\0') { 
        _delay_ms(5);  
        LCD_sendData((uint8_t)*str); // sends char to data  
        str++; // moves to next pointer
    }
}

/**
 * to Print goal for goal mode
 */
void print_Goal(){
    LCD_sendCommand(DISPLAY_CLEAR);   
    LCD_writeString("GOAL");
}

/**
 * To print Search for Search mode
 */
void print_search(){
    LCD_sendCommand(DISPLAY_CLEAR);  
    LCD_writeString("SEARCH");
}

/**
 * for sending commands to the Display
 * 
 * @param cmd, the Commands
 */
void LCD_sendCommand(uint8_t cmd) {
   
    TWI0.MADDR = (DIPSLAY_ADDR << 1);  // Set address 
    while (!(TWI0.MSTATUS & TWI_WIF_bm));  
    TWI0.MDATA = COMMAND_MODE; // Set to command
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
    // Sends command
    TWI0.MDATA = cmd;
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
    TWI0.MCTRLB = TWI_MCMD_STOP_gc;
    _delay_ms(5);

}


/**
 * For setting the row 
 * 
 * @param row
 */
void cursorMode(uint8_t row){
    // Not How I've expected to use cursor
    // I can simply switch to a lower cursor
    uint8_t addr = 0;
    if (row == 0){
        addr = ROW_ONE ; // set the address to the first row
    }
    else if(row == 1){
        addr = ROW_TWO; // Address of second row
    }
    LCD_sendCommand(DDRAM_ADDR | addr); // setting DDRAM + the address
    // Since there is auto increment I assume there 
    // is no need to make col parameter
}
