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

std::string SERV_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
std::string CHAR_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
std::string valueFromJoystick;
std::string valuex;
std::string valuey;

short x, y, x1, x2;
short frequency = 30000;
short xCoord;
short yCoord;

uint8_t resolution = 11;
uint8_t splitindex;
uint8_t channel_R = 0;
uint8_t channel_L = 1;

float reduceSpeed = 1.4;

BLEcontrol Esp32;
MotorController DriveCar;
void driveMotor(short, short);
void parseBLEData(std::string valueFromJoystick);

void setup()
{
    Serial.begin(115200);
    DriveCar.setup(PIN_ENABLE_R,PIN_FORWARD_R,PIN_BACK_R,PIN_FORWARD_L,PIN_BACK_L,PIN_ENABLE_L, channel_R, channel_L);
    DriveCar.setupMotorDriver(channel_R, channel_L, frequency, resolution);
    Esp32.initialize(parseBLEData,SERV_UUID,CHAR_UUID);
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
    x = map(x1, 0, 4095, -2000, 2000);
    y = map(x2, 0, 4095, -2000, 2000);
    DriveCar.controlByJoystick(x,y,reduceSpeed);
    Serial.println(x);
    Serial.println(y);
}   

void loop()
{
}
