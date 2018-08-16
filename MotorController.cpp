#include "MotorController.h"     //библиотека для управления двигателями
#include "Arduino.h"            //стандартная библиотека  Arduino.h
#include <SPI.h>                //библиотека для работы с шиной SPI
#include "esp32-hal-ledc.h"     //библиотека ШИМ

//Задаем подключеные соответствующие контакты, для правого и левого двигателей, в очередности pinUpRight, pinDownRight, pinSpeedRight, pinUpLeft, pinDownLeft, pinSpeedLeft
void MotorController::setup(uint8_t pinEnableR, uint8_t pinForwardR, uint8_t pinBackR , uint8_t pinForwardL, uint8_t pinBackL, uint8_t pinEnableL, uint8_t channel_Right, uint8_t channel_Left)
{
	MotorRight = new motor();
	MotorLeft = new motor();
// инициализируем все пины для управления двигателями
	MotorRight->pin_forward = pinForwardR;
	MotorRight->pin_back = pinBackR;
	MotorRight->pin_speed = pinEnableR;
	MotorLeft->pin_forward = pinForwardL;
	MotorLeft->pin_back = pinBackL;
	MotorLeft->pin_speed = pinEnableL;

// обозначаем порты как выходы
	pinMode(MotorRight->pin_forward, OUTPUT);
	pinMode(MotorRight->pin_back, OUTPUT);
	pinMode(MotorRight->pin_speed, OUTPUT);
	pinMode(MotorLeft->pin_forward, OUTPUT);
	pinMode(MotorLeft->pin_back, OUTPUT);
	pinMode(MotorLeft->pin_speed, OUTPUT);



}
// функция задает номер канала, частоту, разрешение
void MotorController::setupMotorDriver(uint8_t channel_Right, uint8_t channel_Left, short frequency, uint8_t resolution)
{
	MotorRight->channel = channel_Right;
	MotorLeft->channel = channel_Left;

	ledcSetup(channel_Right,frequency,resolution);
	ledcSetup(channel_Left,frequency,resolution);
	ledcAttachPin(MotorRight->pin_speed, channel_Right);
    ledcAttachPin(MotorLeft->pin_speed, channel_Left);
}

// функция считывания сигналов c пинов Arduino
void  MotorController::setPinsValuesMotorDriver (motor* motorStruct, bool up, bool down, short speed)
{
    digitalWrite(motorStruct->pin_forward, up);
	digitalWrite(motorStruct->pin_back, down);
	ledcWrite(motorStruct->channel, speed);
}
// эта функция обеспечит вращение двигателей в двух направлениях на установленной скорости
void MotorController::rotation(motor* motorStruct, short Speed, short Side)
{
	//if (v>100) v = 100;
	//if (v<-100) v = -100;
	if (Side>0) {
		setPinsValuesMotorDriver(motorStruct, HIGH, LOW, Speed); //настройки запуска двигателя в одну сторону
	}
	else if (Side<0) {
		setPinsValuesMotorDriver(motorStruct, LOW, HIGH, -(Speed));//настройки запуска двигателя в обратную  сторону
	}
	else {
		setPinsValuesMotorDriver(motorStruct, LOW, LOW, 0); //двигатель отключен
	}
}
// контроль вращения двигателем на основе данных с джойстика
void MotorController::controlByJoystick(short xCoord, short yCoord, float reduceSpeed)
{
	if ((xCoord > -400 && xCoord < 400) && yCoord > 400) {

	    rotation(MotorLeft, -yCoord, -yCoord);
		rotation(MotorRight, yCoord/reduceSpeed, yCoord);
		Serial.println("Moving forward");

	}
	
	else if (xCoord > 400 && yCoord >=0) {
		rotation(MotorLeft, 0, 0);
		rotation(MotorRight, yCoord, yCoord);
		Serial.println("Moving forward left");
		Serial.println(yCoord/reduceSpeed);
		Serial.println(yCoord);
	}

	else if (xCoord < -400 && yCoord >=0) {
	    rotation(MotorLeft, -yCoord, -yCoord);
		rotation(MotorRight, 0, 0);
		Serial.println("Moving forward right");
	}

	else if ((xCoord > -400 && xCoord < 400) && yCoord < -400) {
	    rotation(MotorLeft, -yCoord, -yCoord);
		rotation(MotorRight, yCoord, yCoord);
		Serial.println("Moving back");
	}
	else if (xCoord > 400 && yCoord <= 0) {
		rotation(MotorLeft, 0, 0);
		rotation(MotorRight, yCoord, yCoord);
		Serial.println("Moving back left");
	}
	else if (xCoord < -400 && yCoord <= 0) {
	    rotation(MotorLeft, -yCoord, -yCoord);
		rotation(MotorRight, 0, 0);
		Serial.println("Moving back right");
	}
	else {
		rotation(MotorLeft, 0, 0);
		rotation(MotorRight, 0, 0);
	}
}
