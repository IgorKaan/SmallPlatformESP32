#ifndef BLEsetup_h
#define BLEsetup_h
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>


class BLEsetup: public BLECharacteristicCallbacks 
{
    public:
    int zx;
    int zy;
    int r;
    int i;
    void onWrite(BLECharacteristic *pCharacteristic); 
    //void onWrite(BLECharacteristic *pCharacteristic1);
    void initialize(void (*drive) (int, int));
    void convert();
};

#endif
