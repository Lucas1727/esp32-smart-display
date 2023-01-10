#include <Arduino.h>

// #include "MQTT.h"
#include "TimeManager.h"
#include "Matrix.h"
#include "Wireless.h"
#include "Bitmaps.h"
// #include "Functions.h"

void connectMessage()
{
  matrix.setTextColor(matrix.Color888(150, 0, 0));
  matrix.println("ESP32 Smart Display");
  matrix.setTextColor(matrix.Color888(100, 100, 100));
  matrix.println("Connect to");

  matrixTextColour(ipAddress, 0, 0, 150);

  matrix.setTextColor(matrix.Color888(100, 100, 100));
  matrix.println("to access the webpage");
  matrix.setTextColor(matrix.Color888(0, 255, 255));

  matrix.drawBitmap(0, 33, weatherSunBitmap, 8, 8, matrix.Color888(0, 255, 255));
}

void printTime()
{
  getTime();
  matrixText(displayTime);
}

void setup()
{
  Serial.begin(115200);

  initialiseTime();
  initialiseWifiManager();
  initialiseServer();

  matrixStart();
  matrixBoot();

  matrixReset();

  connectMessage();

  getTime();
}

void loop()
{
  delay(1000);
}