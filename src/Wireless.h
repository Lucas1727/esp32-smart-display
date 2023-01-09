#ifndef WIRELESS_H
#define WIRELESS_H

#include <WiFi.h>
// #include <LittleFS.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

const char *ssid = "";
const char *password = "";

void initialiseWifiManager() {
  WiFiManager wifiManager;

  wifiManager.autoConnect("ESP32");
}

// Setup Async Wi-Fi Manager
void initialiseWifi() {
  Serial.println("Starting Wi-Fi Manager");
  Serial.printf("Connecting to %s ", ssid);

  uint32_t notConnectedCounter = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    notConnectedCounter++;
    if (notConnectedCounter > 20) {  // Reset board if not connected after 5s
      Serial.println("Resetting due to Wifi not connecting...");
      ESP.restart();
    }
  }

  Serial.println("Connected to Wi-Fi");
}

void initialiseServer() {
}

#endif  // WIRELESS_H