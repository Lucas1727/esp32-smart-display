#ifndef MATRIX_H
#define MATRIX_H

#include <GPxMatrix.h> //https://github.com/3tawi/GPxMatrix.git

#define OE 15
#define CLK 2
#define LAT 4
#define A 12
#define B 14
#define C 27
#define D 26
#define E 25

// RGB pins for     (R1, G1, B1, R2, G2, B2)
uint8_t rgbpins[] = {18, 21, 23, 5, 19, 22};

GPxMatrix matrix(A, B, C, D, E, CLK, LAT, OE, false, 128, rgbpins);

int hue = 0,           // Colour hue on LED for text (text range 0-7)
    colourRed = 100,   // Colour value on LED for red on text (text range 0-255)
    colourGreen = 100, // Colour value on LED for green on text (text range 0-255)
    colourBlue = 100;  // Colour value on LED for blue on text (text range 0-255)

void matrixReset()
{
  // matrix.swapBuffers(false); // Update display
  matrix.fillScreen(0); // Clear background
  matrix.setCursor(0, 0);
}

void matrixStart()
{
  matrix.begin();

  matrixReset();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(1);

  matrix.setTextColor(matrix.Color888(colourBlue, colourGreen, colourRed));
}

void matrixBoot()
{
  matrixReset();
  matrix.print("Booting");

  for (int i = 0; i < 5; i++)
  {
    delay(500);
    matrix.print(".");
  }
}

void matrixTextColour(char chars[], int blue, int green, int red)
{
  matrix.setTextColor(matrix.Color888(blue, green, red));
  matrix.println(chars);
  Serial.println(chars);
}

void matrixText(char chars[])
{
  matrix.println(chars);
  Serial.println(chars);
}

// Gets the local time from pool.ntp.org and prints it on LED matrix
void printLocalTimeLED()
{

  char displayTime[21] = "";

  struct tm timeinfo;

  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }

  strftime(displayTime, sizeof(displayTime), "%A %b %d  %H:%M", &timeinfo);

  matrixReset();

  matrix.println(displayTime);
  Serial.println(displayTime);
}

#endif // MATRIX_H