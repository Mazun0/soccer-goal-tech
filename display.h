/* 
 * File:   display..h
 * Author: mazuno
 *
 * Created on November 22, 2024, 9:55 AM
 */

#ifndef DISPLAY__H
#define	DISPLAY__H

//#include <arv/io.h>



#ifdef	__cplusplus
extern "C" {
#endif

    
    
//
#define DIPSLAY_ADDR 0x3E
#define DISPLAY_DATA 0x40 // 
#define COMMAND_MODE 0x00 // 
#define DISPLAY_CLEAR 0x01
#define DISPLAY_ON_CURSOR_OFF 0x0C // 
#define EIGHT_BIT_TWO_LINES 0x38
#define AUTO_INCREMENT 0x06
#define DDRAM_ADDR 0x80 
#define ROW_ONE 0x00
#define ROW_TWO 0x40

    
    
void initTWI(void);
void LCD_sendData(uint8_t data);
void Display_Distance(uint8_t sens,uint16_t distance);
void LCD_sendCommand(uint8_t cmd);
void LCD_init(void);
void LCD_writeString(char* str);
void print_Goal();
void cursorMode(uint8_t row);



    


#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY__H */

