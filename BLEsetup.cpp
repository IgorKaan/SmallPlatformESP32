#include <BLEsetup.h>
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *pCharacteristic;
float txValue;
int zx;
int zy;
void (*driveMotor1) (int, int);


void BLEsetup::initialize(void (*drive) (int, int))
{
  driveMotor1 = drive;
  //driveMotor1 = drive;
  BLEDevice::init("ESP32");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_INDICATE 
                                       );

  pCharacteristic->setCallbacks(new BLEsetup());

  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->start();
}


void BLEsetup::onWrite(BLECharacteristic *pCharacteristic)
{

std::string value = pCharacteristic->getValue();

        for (int i = 0; i < value.length(); i++)
        //Serial.print(value[i]);
        zx = atoi(value.c_str());
        Serial.print("X=");
        Serial.println(zx); 
        driveMotor1(zx,zx);     
}

/*}
      if (value1.length() > 0) {
        for (int i = 0; i < value1.length(); i++)
          Serial.print(value1[i]);
        r = atoi(value1.c_str());
        Serial.print("Y=");
        Serial.println(r);
}
}*/
/*void BLEsetup::onWritey(BLECharacteristic *pCharacteristic1)
{

std::string value1 = pCharacteristic1->getValue();

      if (value1.length() > 0) {
        for (int i = 0; i < value1.length(); i++)
          Serial.print(value1[i]);
        r = atoi(value1.c_str());
        Serial.print("Y=");
        Serial.println(r);
}
}
*/
void BLEsetup::convert()
{

}
