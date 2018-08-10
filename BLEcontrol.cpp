#include <BLEcontrol.h>
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *pCharacteristic;
BLECharacteristic *pCharacteristic1;
void (*BLEDataProcessing) (std::string);


void BLEcontrol::initialize(void parseBLEData(std::string valueFromJoystick))
{
  BLEDataProcessing = parseBLEData;
  BLEDevice::init("MyESP");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_INDICATE 
                                       );

  pCharacteristic->setCallbacks(new BLEcontrol());

  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->start();
}


void BLEcontrol::onWrite(BLECharacteristic *pCharacteristic)
{
  std::string valueFromJoystick = pCharacteristic->getValue();
  BLEDataProcessing(valueFromJoystick);
}



