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

  matrix.setTextColor(matrix.Color888(0, 0, 150));
  matrix.println(ipAddress);

  matrix.setTextColor(matrix.Color888(100, 100, 100));
  matrix.println("to access the webpage");
  matrix.setTextColor(matrix.Color888(0, 255, 255));
}

void drawSmile()
{
  matrix.drawBitmap(48, 32, circleFillBitmap, 32, 32, matrix.Color888(colourBlue, colourGreen, colourRed));
  matrix.drawCircleHelper(64, 48, 16, 1, matrix.Color888(100, 100, 100)); // Top Left
  matrix.drawCircleHelper(63, 48, 16, 2, matrix.Color888(100, 100, 100)); // Top Right
  matrix.drawCircleHelper(63, 47, 16, 4, matrix.Color888(100, 100, 100)); // Bottom Right
  matrix.drawCircleHelper(64, 47, 16, 8, matrix.Color888(100, 100, 100)); // Bottom Left
  matrix.drawBitmap(48, 32, smileBitmap, 32, 32, matrix.Color888(0, 0, 0));
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

  getTime();

  matrixReset();
  connectMessage();
}

void loop()
{
  matrixColour(0, 50, 50);
  drawSmile();
  delay(1000);
  matrixColour(0, 50, 0);
  drawSmile();
  delay(1000);
  matrixColour(50, 0, 0);
  drawSmile();
  delay(1000);
  matrixColour(0, 0, 50);
  drawSmile();
  delay(1000);
}