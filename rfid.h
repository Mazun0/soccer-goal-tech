/* 
 * File:   rfid.h
 * Author: mazuno
 *
 * Created on 08 December 2024, 17:24
 */

#ifndef RFID_H
#define	RFID_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
#define SAMPLES_PER_BIT 16    // taken from LAB 7 
#define USART_BAUD_VALUE(BAUD_RATE) (uint16_t) ((F_CPU << 6) / (((float) SAMPLES_PER_BIT) * (BAUD_RATE)) + 0.5)

void USART_init();
void USART_Enable();
void USART_Disable();



#ifdef	__cplusplus
}
#endif

#endif	/* RFID_H */

