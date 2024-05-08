<style>
    img {
        display: block; 
        margin-left: auto;
        margin-right: auto;
    }
</style>

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

# The finished product

This is what our final robot looks like: 

<img height=300 src="CG2271 Robot Image.jpg">

There was a video submission that required us to submit either:
- A 2-3 min YouTube submission at the end of the semester;
- 3 TikTok videos (>= 1min each) to be spread across the semester.

Naturally, we picked the YouTube submission. You can watch the video (horribly edited by yours truly, with my more-than subpar editing abilities) below: 

<a href="https://www.youtube.com/watch?v=wXjS5M0aDrQ"> 
    <img height=500 src="https://img.youtube.com/vi/wXjS5M0aDrQ/0.jpg"> 
</a>

# Final Remarks

This project was quite an enjoyable one. Many thanks to my groupmates for making this project bearable, as well as the teaching team for creating this module for us to learn and ~~suffer?~~ enjoy! 

If you are taking this module in the future and are reading this, do feel free to take some inspiration from our implementations (and possibly improve on it)! However, the teaching team has mentioned likely changes to be implemented in the following semesters (I heard there might be gesture-control, voice commands... 😙), so do take note. Also keep in mind of NUS' plagiarism policy! 😅