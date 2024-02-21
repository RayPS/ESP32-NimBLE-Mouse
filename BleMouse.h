#ifndef ESP32_BLE_MOUSE_H
#define ESP32_BLE_MOUSE_H
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)

#include "NimBLEHIDDevice.h"
#include "NimBLECharacteristic.h"

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_BACK 8
#define MOUSE_FORWARD 16
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE) # For compatibility with the Mouse library

class BleMouse : protected NimBLEServerCallbacks {
private:
  uint8_t _buttons;
  NimBLEHIDDevice* hid;
  NimBLECharacteristic* inputMouse;
  void buttons(uint8_t b);
  void rawAction(uint8_t msg[], char msgSize);
  void onConnect(NimBLEServer* pServer);
  void onDisconnect(NimBLEServer* pServer);
public:
  BleMouse(std::string deviceName = "ESP32-Mouse", std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
  void begin(void);
  void end(void);
  void click(uint8_t b = MOUSE_LEFT);
  void move(signed char x, signed char y, signed char wheel = 0, signed char hWheel = 0);
  void press(uint8_t b = MOUSE_LEFT);   // press LEFT by default
  void release(uint8_t b = MOUSE_LEFT); // release LEFT by default
  bool isPressed(uint8_t b = MOUSE_LEFT); // check LEFT by default
  bool isConnected(void);
  void setBatteryLevel(uint8_t level);
  uint8_t batteryLevel;
  std::string deviceManufacturer;
  std::string deviceName;
  bool connected = false;
};



#endif // CONFIG_BT_ENABLED
#endif // ESP32_BLE_MOUSE_H
