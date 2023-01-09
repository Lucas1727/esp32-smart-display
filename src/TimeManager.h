#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <Arduino.h>
#include <time.h>
#include <sntp.h>

const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";

char displayTime[22] = "";

const int daylightOffset_sec = 0;

const long gmtOffset_sec = 0;

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t) {
  Serial.println("Got time adjustment from NTP!");
}

void getTime() {

  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }

  strftime(displayTime, sizeof(displayTime), "%A %b %d %H:%M", &timeinfo);

  Serial.println(displayTime);
}

void initialiseTime() {
  sntp_set_time_sync_notification_cb(timeavailable);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
}

#endif  // TIMEMANAGER_H