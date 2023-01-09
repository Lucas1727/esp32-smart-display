#include <Arduino.h>

// #include "MQTT.h"
#include "TimeManager.h"
#include "Matrix.h"
#include "Wireless.h"
// #include "Functions.h"

void setup()
{
  Serial.begin(115200);

  initialiseTime();
  // initialiseWifi();
  initialiseWifiManager();

  matrixStart();
  matrixBoot();

  getTime();

  // initialiseServer();
}

void loop()
{
  getTime();
  printText(displayTime);
  delay(5000);
}