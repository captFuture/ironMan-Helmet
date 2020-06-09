#include <Arduino.h>
#include <Servo.h>
#include "variables.h"
#include "M5Atom.h"
#include "DFRobotDFPlayerMini.h"

Servo servo1;
Servo servo2;
uint8_t DisBuff[2 + 5 * 5 * 3];
DFRobotDFPlayerMini jarvisSound;

void setup() {
    Serial1.begin(9600);
    M5.begin(true, true, true);
    delay(10);

    Serial.println(); Serial.println("Connecting hinge...");

    servo1.attach(SERVO1PIN);
    servo2.attach(SERVO2PIN);
    pinMode(SERVO1POWERPIN, OUTPUT);
    pinMode(SERVO2POWERPIN, OUTPUT);
    servo1.writeMicroseconds(SERVO1Current);
    servo1.writeMicroseconds(SERVO2Current);

    Serial.println("--- Starting system ---");
    Serial.println("Helmet Closed");
    setBuff(0x00, 0x00, 0x40);
    M5.dis.displaybuff(DisBuff);
    changeEyes(0);
    if(!debug){
        if (!jarvisSound.begin(Serial1)) { 
            Serial.println(F("Unable to begin:"));
            Serial.println(F("1.Please recheck the connection!"));
            Serial.println(F("2.Please insert the SD card!"));
            while(true){
            delay(0); 
            }
        }
        Serial.println(F("Soundsystem online."));
        
        jarvisSound.volume(30);  //Set volume value. From 0 to 30
        jarvisSound.play(4);  //Play mp3 004
        delay(3000);
        jarvisSound.play(2);  //Play mp3 002
    }else{
        Serial.println(F("Soundsystem deactivated for debugging."));
    }
}

void loop() {
    if (M5.Btn.wasPressed())
    {
        if(opened){
            Serial.println("Helmet Currently open");
            changeEyes(0);
            closeHelmet();
            changeEyes(1);
            if(!debug){playSound(5);}
            opened = false;
            Serial.println("Helmet now Closed");
        }else if(!opened){
            Serial.println("Helmet currently Closed");
            changeEyes(1);
            openHelmet();
            changeEyes(0);
            if(!debug){playSound(6);}
            Serial.println("Helmet now Opened");
            opened = true;
        }else{}
    }

    if (M5.Btn.pressedFor(2000)){
        debug = !debug;
        Serial.print("Debug: "); Serial.println(debug);
        delay(2000);
    }
    delay(50);
    M5.update();
}

void openHelmet(){
    Serial.println("Opening Helmet");
    digitalWrite(SERVO1POWERPIN, HIGH);
    digitalWrite(SERVO2POWERPIN, HIGH);
    ledNum = 0;
    for(int i = maxLoop; i >= 0; i--){
        pos1 = i;
        pos2 = pos1;
        pos1 = map(pos1, 0, maxLoop, smin1, smax1);
        pos2 = map(pos2, 0, maxLoop, smax2, smin2);
        ledNum = map(i, 0, maxLoop , 0, 24);
        if(debug){
            Serial.print(pos1);  Serial.print(" | "); 
            Serial.print(pos1); Serial.print(" | "); 
            Serial.print(pos2); Serial.print(" | ");
            Serial.print(ledNum); Serial.println("");
        }
        servo1.writeMicroseconds(pos1);
        servo2.writeMicroseconds(pos2);
        M5.dis.drawpix(ledNum, 0x00f000);
        M5.update();
    }
    digitalWrite(SERVO1POWERPIN, LOW);
    digitalWrite(SERVO2POWERPIN, LOW);
}

void closeHelmet(){
    Serial.println("Closing Helmet");
    digitalWrite(SERVO1POWERPIN, HIGH);
    digitalWrite(SERVO2POWERPIN, HIGH);
    ledNum = 0;
    for(int i = 0; i <= maxLoop; i++){
        pos1 = i;
        pos2 = pos1;
        pos1 = map(pos1, 0, maxLoop, smin1, smax1);
        pos2 = map(pos2, 0, maxLoop, smax2, smin2);
        ledNum = map(i, 0, maxLoop , 0, 24);
        if(debug){
            Serial.print(pos1);  Serial.print(" | "); 
            Serial.print(pos1); Serial.print(" | "); 
            Serial.print(pos2); Serial.print(" | ");
            Serial.print(ledNum); Serial.println("");
        }
        servo1.writeMicroseconds(pos1);
        servo2.writeMicroseconds(pos2);
        M5.dis.drawpix(ledNum, 0xf00000);
        M5.update();
    }
    digitalWrite(SERVO1POWERPIN, LOW);
    digitalWrite(SERVO2POWERPIN, LOW);
}

void playSound(int soundnumber){
    jarvisSound.play(soundnumber);
}

void changeEyes(int eyepattern){

}

void setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
    DisBuff[0] = 0x05;
    DisBuff[1] = 0x05;
    for (int i = 0; i < 25; i++)
    {
        DisBuff[2 + i * 3 + 0] = Rdata;
        DisBuff[2 + i * 3 + 1] = Gdata;
        DisBuff[2 + i * 3 + 2] = Bdata;
    }
}