#include <Arduino.h>
#include <BLEjoystick.h>
#include "BLEDevice.h"

//std::string ServiceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
//std::string CharacteristicUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");

uint8_t JoystickxPin = 34;
uint8_t JoystickyPin = 35;

BLEjoystick Joystick;

void setup() {

	//Joystick.SetupUUID(ServiceUUID,CharacteristicUUID);
	Joystick.BLEjoystickSetup();

} 
void loop() {

	Joystick.GetDataFromJoystick(JoystickxPin, JoystickyPin);

} 