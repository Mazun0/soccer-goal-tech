# Soccer Goal Line Technology

# Overview
A soccer goal line system where it’s equipped with ultrasonic distance sensors for goal posts and an RIFD scanner inside the goal while the ball inside is equipped with RFID chips. If the ball fully crosses as the RFID scanner reads the ball, it makes as a goal



## Features 
- Integrated in a model goal post where sensors read the ball’s position based on distance pointing post to post
- Activating the RFID if the sensors detect the ball. 
- Green light signals a goal if an RFID scanner reads the ball in Goal fully crossed the line from distance.

## Design / Archtecture

the Goal Line technology system uses the ATmega3208 microcontroller to read the ball’s sensors. When the ball has gone between the goal posts, the RFID activates with a short amount of time to look for the ball. The premise is to have the ball that is passed the line on the ball’s circumference. A 16x2 LCD display acts like a de bugger to measure out the distance between each goal poles where one Ultrasonic Sensor is higher and the other Sensor is lower to account for hight. A red light will signal for search mode, and the green light signals as goal.

## Software and Tools
- Language(s): C
- Tools: MPLABx IDE, Linux
- Hardware: ATmega3208 (AVR-BLE), Ultrasonic Distance Sensor (HC SR04), Grove 16x2 LCD, 2 x Breadboard, ID-12LA RFID reader, and 4x RFID Button 16mm,  2x 220 Ohms Resisters, A small foam soccer ball (about 19cm in circumference)



![Model of goal line system](docs/IMG_0371.jpg)


## Project Structure


/docs – Images and write-up
lights.c
lights.h
display.h
display.c
main.c
rfid.h
rfid.c
sensors.c
sensors.h


## Challenges

Trying to design a system for a sport that is well know for fast pace and physical especially down to a scale model represents a few challenges.

First was the timing as well bring the logic. Having the Ultrasonic Sensors wasn’t enough and could represent errors if the ball was read outside the goal. I worked around with it by adding the logic that starts the timer when the ball reached the line. As well to abide the rules of the sport and counting the positions for the chips inside, I have to account the distance of the RFID where it’s reachable accounting the rules where the ball needs to fully pass the line. 

Another challenge is the timing, where due to the nature of the sport, having a more forgiving time would make it too easy to read the ball but a much quicker time would not be too forgiving. 

For debugging, I settled to use an LCD display to read the distance between the goal post read by the distance sensors, as well having two lights where red represents the search activation and green for goal.


## Future Plans
-  redesign the goal post with more reliable sensors
- Create android application for signaling goal 
- Implement freeRTOS for consistency. (this was written in Bare Metal) 
- Improve accuracy of the ball’s position


## Author
Miguel Zapata
