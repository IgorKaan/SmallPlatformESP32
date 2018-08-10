#include <Arduino.h>
#include <MotorController.h>
#include <SPI.h>
#include "esp32-hal-ledc.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEcontrol.h>

#define PIN_ENABLE_R 13
#define PIN_FORWARD_R 12
#define PIN_BACK_R 14
#define PIN_FORWARD_L 27
#define PIN_BACK_L 26
#define PIN_ENABLE_L 25

short x, y, x1, x2;
uint8_t channel = 0;
short frequency = 30000;
uint8_t resolution = 8;
std::string valueFromJoystick;
std::string valuex;
std::string valuey;
short xCoord;
short yCoord;
uint8_t splitindex;
BLEcontrol Esp32;
MotorController DriveCar;
void driveMotor(short, short);
void parseBLEData(std::string valueFromJoystick);

void setup()
{
    Serial.begin(115200);
    DriveCar.setup(PIN_ENABLE_R,PIN_FORWARD_R,PIN_BACK_R,PIN_FORWARD_L,PIN_BACK_L,PIN_ENABLE_L);
    DriveCar.setupMotorDriver(channel,frequency,resolution);
    Esp32.initialize(parseBLEData);
}

void parseBLEData(std::string valueFromJoystick)
{
    splitindex = valueFromJoystick.find("/");
    valuex = valueFromJoystick.substr(0,splitindex);
    valuey = valueFromJoystick.substr(splitindex+1);
    xCoord = atoi(valuex.c_str());
    yCoord = atoi(valuey.c_str());
    driveMotor(xCoord, yCoord);
}
void driveMotor(short x1,short x2)
{
    x = map(x1, 0, 4095, -100, 100);
    y = map(x2, 0, 4095, -100, 100);
    DriveCar.controlByJoystick(x,y);
}   

void loop()
{
}
