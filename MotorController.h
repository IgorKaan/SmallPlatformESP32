#ifndef MotorController_h
#define MotorController_h
#include "Arduino.h"//стандартная библиотека  Arduino.h
#include <SPI.h>     //библиотека для работы с шиной SPI

class MotorController //создаем класс RadioJoystick
{

private:
	struct motor // создаем объект класса
	{
		// инициализируем  пины для управления двигателям
		uint8_t pin_forward;
		uint8_t pin_back;
		uint8_t pin_speed;
	};
	motor* MotorRight;
	motor* MotorLeft;
	// функция считывания сигналов c пинов Arduino
	void setPinsValuesMotorDriver (motor* motorStruct, bool up, bool down, short speed);

public:
//Задаем подключеные соответствующие контакты, для правого и левого двигателей, в очередности pinUpRight, pinDownRight, pinSpeedRight, pinUpLeft, pinDownLeft, pinSpeedLeft
	void setup(uint8_t pinEnableR, uint8_t pinForwardR, uint8_t pinBackR , uint8_t pinForwardL, uint8_t pinBackL, uint8_t pinEnableL);

	void rotation(motor* motorStruct, short v);
	// контроль вращения двигателем на основе данных с джойстика
	void controlByJoystick(short x1, short x2);
	// номер канала
	int channel;

	void setupMotorDriver(uint8_t channel, short frequency, uint8_t resolution);

};
#endif
