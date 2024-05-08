## Note from the owner of this repository

Hello! It's Clarence, one of the developers of the CG2271 project. 
This repository contains **(SOME)** code that we used in the working laboratories (from which some of the robot drivers are used in the project),
as well as the final project code that was used in the test run. 

This project would not have been possible without my amazing groupmates:
- Claribel Ho [See Claribel's GitHub profile!](https://github.com/claribelho)
- Daryl Tay [See Daryl's GitHub profile!](https://github.com/daryltay415)
- Eugene Chan [See Eugene's GitHub profile!](https://github.com/EugeneChanJiajun)
- Yeo Zhi Shen [See Zhi Shen's GitHub profile!](https://github.com/yeozhishen)

# Project introduction and specifications

This project is a graded component (40%) of the module CG2271, Real-time Operating Systems, taken in AY23/24 Semester 2 under Dr. Ravi Suppiah. 
The aim of the project was to design a RTOS-based robotic car that will be controlled through an Android App. The robotic car must be able to fulfil the following features:
1. Establish a WiFi/BT connection with the Android App OR Alternative Controller
2. Receive commands from the Control Device and execute the correct response
3. Move the car in multiple directions.
4. Control the various LED’s according to the car’s status
5. Play different sounds/tunes according to the cars status.

The project was done in groups of 4-5 members, with no additional budget given, so we had to work with what was given. Here is a list of components that were provided by the teaching team:
- DRV8833 Dual Motor Driver Carrier 
- Robot Smart Car Chassis Kit 
- Red LED 5mm 
- Green LED 5mm 
- Prototyping Breadboards 
- Jumper Wire Bundle (40 pcs) 
- Battery Holder AA x 6 
- Piezo Buzzer 
- 9V Battery Connector 
- 220 ohms Resistors 
- Duracell Batteries (Pack of 12) 
- GP 9V Batteries 
- Push Button Switch 
- 1-Way Connector Strip 
- 2-Way Connector Strip 
- FRDM KL25Z Board 
- LED Strip 
- ESP32

The project allowed us to learn more about working in an RTOS-enabled environment, working with multiple threads (on a single cored processor in this case) and how to prevent race conditions using OS constructs to protect critical sections of our code (like Mutexes and Semaphores). It was a step-up in difficulty from what I'd done previously in introduction courses like EPP1 (CG1111A) and EPP2 (CG2111A) where we worked with Arduinos and RPi. 


