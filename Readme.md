https://docs.m5stack.com/#/en/core/atom_matrix

Pinout:
RGB Led	G27
Btn	G39
IR	G12
SCL	G21
SDA	G25

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

to get Hardwareserial on the G23 and G33 pins for the DFplayer Mini you have to modify HardwareSerial.cpp in the Arduinolibrary
C:\Users\myUser\.platformio\packages\framework-arduinoespressif32\cores\esp32\HardwareSerial.cpp