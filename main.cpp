#include <Arduino.h>
#include <MotorController.h>
#include <SPI.h>
#include "esp32-hal-ledc.h"

#define PIN_ENABLE_R 13
#define PIN_FORWARD_R 12
#define PIN_BACK_R 14
#define PIN_FORWARD_L 27
#define PIN_BACK_L 26
#define PIN_ENABLE_L 25

MotorController DriveCar;
short x, y, x1, x2;

uint8_t channel = 0;
short frequency = 30000;
uint8_t resolution = 8;


void setup()
{
    DriveCar.setup(PIN_ENABLE_R,PIN_FORWARD_R,PIN_BACK_R,PIN_FORWARD_L,PIN_BACK_L,PIN_ENABLE_L);
    DriveCar.setupMotorDriver(channel,frequency,resolution);
    Serial.begin(115200);
}

void loop()
{
    x1 = map(x, 0, 4095, -100, 100);
    x2 = map(y, 0, 4095, -100, 100);
    DriveCar.controlByJoystick(0,1000);
}