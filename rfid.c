/*
 * File:   rfid.c
 * Author: mazuno
 *
 * Created on 07 December 2024, 20:10
 */

#define F_CPU 3333333
#include <avr/io.h>
#define SAMPLES_PER_BIT 16    // taken from LAB 7 
#define USART_BAUD_VALUE(BAUD_RATE) (uint16_t) ((F_CPU << 6) / (((float) SAMPLES_PER_BIT) * (BAUD_RATE)) + 0.5)
#define BUF_SIZE 128


/**
 * Initalizing USART for RFID Scanner
 */
void USART_init(){
    PORTA.DIR &= ~PIN1_bm;
    PORTA.DIR |= PIN0_bm;
    USART1.BAUD = (uint16_t)USART_BAUD_VALUE(9600); 
    USART1.DBGCTRL = USART_DBGRUN_bm;
    USART1.CTRLC |= (USART_CMODE_ASYNCHRONOUS_gc|USART_PMODE_DISABLED_gc|USART_SBMODE_1BIT_gc|USART_CHSIZE_8BIT_gc);  
}

/**
 * To enable for RFID Scanner
 */
void USART_Enable(){
      USART1.CTRLB |=  (USART_TXEN_bm| USART_RXEN_bm | USART_RXMODE_NORMAL_gc);
}


/**
 * To disable the RFID Scanner
 */
void USART_Disable(){
    
   USART1.CTRLB &=  ~(USART_TXEN_bm| USART_RXEN_bm | USART_RXMODE_NORMAL_gc);

}


