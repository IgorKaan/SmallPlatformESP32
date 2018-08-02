#include "MotorController.h"     //библиотека для управления двигателями
#include "Arduino.h"            //стандартная библиотека  Arduino.h
#include <SPI.h>                //библиотека для работы с шиной SPI
#include "esp32-hal-ledc.h"     //библиотека ШИМ

//Задаем подключеные соответствующие контакты, для правого и левого двигателей, в очередности pinUpRight, pinDownRight, pinSpeedRight, pinUpLeft, pinDownLeft, pinSpeedLeft
void MotorController::setup(uint8_t pinEnableR, uint8_t pinForwardR, uint8_t pinBackR , uint8_t pinForwardL, uint8_t pinBackL, uint8_t pinEnableL)
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
void MotorController::setupMotorDriver(uint8_t channel, short frequency, uint8_t resolution)
{
	ledcSetup(channel,frequency,resolution);
	ledcAttachPin(MotorRight->pin_speed,channel);
    ledcAttachPin(MotorLeft->pin_speed,channel);
}

// функция считывания сигналов c пинов Arduino
void  MotorController::setPinsValuesMotorDriver (motor* motorStruct, bool up, bool down, short speed)
{
    digitalWrite(motorStruct->pin_forward, up);
	digitalWrite(motorStruct->pin_back, down);
	ledcWrite(channel, speed);
}
// эта функция обеспечит вращение двигателей в двух направлениях на установленной скорости
void MotorController::rotation(motor* motorStruct, short v)
{
	if (v>100) v = 100;
	if (v<-100) v = -100;
	if (v>0) {
		setPinsValuesMotorDriver(motorStruct, HIGH, LOW, v*2.55); //настройки запуска двигателя в одну сторону
	}
	else if (v<0) {
		setPinsValuesMotorDriver(motorStruct, LOW, HIGH, (-v)*2.55);//настройки запуска двигателя в обратную  сторону
	}
	else {
		setPinsValuesMotorDriver(motorStruct, LOW, LOW, 0); //двигатель отключен
	}
}
// контроль вращения двигателем на основе данных с джойстика
void MotorController::controlByJoystick(short x1, short x2)
{
	rotation(MotorRight, x2 - x1);
	rotation(MotorLeft, x2 + x1);
}
