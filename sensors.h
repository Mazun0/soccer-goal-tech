/* 
 * File:   sensors.h
 * Author: mazuno
 *
 * Created on December 5, 2024, 6:09 AM
 */

#ifndef SENSORS_H
#define	SENSORS_H

#ifdef	__cplusplus
extern "C" {
#endif

void sensorInit();
void sensTrigger(uint8_t pin);
uint16_t SensEcho(uint8_t pin);
uint16_t calculate_distance(uint16_t pulse_width);



#ifdef	__cplusplus
}
#endif

#endif	/* SENSORS_H */

