This is my POC for a motorized Faceplate for my iron man Helmet.
It uses 2 synchronized MG90 servos in orderto get enough torque to move the faceplate.

Key features:
- Servo Movement by button press
- Audio (mp3) output via dfrobot player mini
- Servopower is switched on and off via ULN2003 Chip to save power and stop noise on servos
- Possibility to connect to the Esp32 via Bluetooth or Wifi to get the different parts of the suit working with each other

Used MCU in my case (i had it lying around...)
https://docs.m5stack.com/#/en/core/atom_matrix

Wiring schematic is in the /schematic/ subfolder of the project

Pinout:
RGB Led	G27
Btn	G39
IR	G12
SCL	G21
SDA	G25

```
                        PCB VIEW
                        ┌───┬───┬───┬───┬───┬───┬───┐
                        │   │   │   │   │   │   │3v3│
                        ├───┼───┼───┼───┼───┼───┼───┤
Servo1 powerswitch      │G21│   │   │   │   │   │G22│ -- Servo1 movement
                        ├───┼───┼───┼───┼───┼───┼───┤
Servo2 powerswitch      │G25│   │   │   │   │   │G19│ -- Servo2 movement
                        ├───┼───┼───┼───┼───┼───┼───┤
                        │5v5│   │   │   │   │   │G23│ --  Serial1 TX
                        ├───┼───┼───┼───┼───┼───┼───┤
                        │ G │   │   │   │   │   │G33│ --  Serial1 RX
                        └───┴───┴───┴───┴───┴───┴───┘

                                ┌───┬───┬───┬───┐
                                │G32│G26│5v5│ G │ GROVE PORT
                                └───┴───┴───┴───┘
```
to get Hardwareserial on the G23 and G33 pins for the DFplayer Mini you have to modify HardwareSerial.cpp in the Arduinolibrary
C:\Users\myUser\.platformio\packages\framework-arduinoespressif32\cores\esp32\HardwareSerial.cpp
