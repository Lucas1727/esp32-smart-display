#ifndef WIRELESS_H
#define WIRELESS_H

#include <WiFi.h>
// #include <LittleFS.h>
#include <WiFiManager.h>       // https://github.com/tzapu/WiFiManager
#include <ESPAsyncWebServer.h> //https://github.com/me-no-dev/ESPAsyncWebServer
#include <SPIFFS.h>            //https://github.com/me-no-dev/ESPAsyncWebServer

const char *ssid = "";
const char *password = "";

char ipAddress[16] = "xxx.xxx.xxx.xxx";

AsyncWebServer server(80);

void initialiseWifiManager()
{
  WiFiManager wifiManager;

  wifiManager.setConfigPortalTimeout(180);
  wifiManager.autoConnect("ESP32");
}

// Setup Async Wi-Fi Manager
void initialiseWifi()
{
  Serial.println("Starting Wi-Fi Manager");
  Serial.printf("Connecting to %s ", ssid);

  uint32_t notConnectedCounter = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    notConnectedCounter++;
    if (notConnectedCounter > 20)
    { // Reset board if not connected after 5s
      Serial.println("Resetting due to Wifi not connecting...");
      ESP.restart();
    }
  }

  Serial.println("Connected to Wi-Fi");
}

// Replaces placeholder with IP Address
String processor(const String &var)
{
  // Serial.println(var);
  if (var == "IPADDRESS")
  {
    return ipAddress;
  }
  return String();
}

void initialiseServer()
{
  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  File file = SPIFFS.open("/index.html");

  if (file)
  {
    Serial.println("Successfully opened files");
  }
  else
  {
    Serial.println("Failed to open files");
  }

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", String(), false, processor); });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/style.css", "text/css"); });

  // Route to load main.js file
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/main.js", "text/javascript"); });

  WiFi.localIP().toString().toCharArray(ipAddress, 16);

  // Start server
  server.begin();
}

#endif // WIRELESS_H