//#include <Arduino.h>
//#include "SoftwareSerial.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <ArduinoJson.h>

#define STATION_ID "1111"

#define WIFI_SSID "******"
#define WIFI_PASSWORD "******"

// Communication Protocol Commands
#define DOCK_LOCK 11
#define DOCK_UNLOCK 12
#define FEEDBACK_DOCK_UNLOCK 22

#define USER_REQUEST_TO_UNLOCK 13
#define USER_NOT_MOUNTED_THE_BIKE_MODE 14

// LED indicators
#define LED_BLUE D4
#define RESPONSE_A D2
#define RESPONSE_B D3

ESP8266WiFiMulti WiFiMulti;

uint8_t dockIDs[] = {1, 2, 3, 4, 5, 6};
String inputString;
uint8_t serialId[4];
char cmdBuffer[16];
uint8_t dockId;

void setup() {
   Serial.begin(115200);
   while (!Serial) {;}

   Serial.println("\n\nBegin");

   WiFi.mode(WIFI_STA);
   WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

   beginGPIO();

   indicatorBlink(2);

}

void loop() {

   if (Serial.available()) {
      uint8_t command = (uint8_t)Serial.parseInt();

      if (command == DOCK_LOCK) {
         // 11 0 12 20 30 40
         dockId = (uint8_t)Serial.parseInt();

         Serial.printf("DockLock %d\n\n", dockId);
         indicatorBlink(2);

         serialId[0] =  (uint8_t)Serial.parseInt();
         serialId[1] =  (uint8_t)Serial.parseInt();
         serialId[2] =  (uint8_t)Serial.parseInt();
         serialId[3] =  (uint8_t)Serial.parseInt();

         //Serial.printf("Lock %d %X%X%X%X\n\n", dockId, serialId[0], serialId[1], serialId[2], serialId[3]);

         sprintf(cmdBuffer, "%02X%02X%02X%02X\0", serialId[0], serialId[1], serialId[2], serialId[3]);
         Serial.printf("DockLock (%s)-> %d\n", cmdBuffer, dockLock(dockId, cmdBuffer));
         Serial.flush();

      } else if (command == DOCK_UNLOCK) {
         // 12 1
         dockId = (uint8_t)Serial.parseInt();

         Serial.printf("DockUnlock %d\n\n", dockId);
         indicatorBlink(3);

         uint8_t resp = dockUnlock(dockId);
         sendSignal((resp == true) ? 1 : 0);
         Serial.printf("\nDockUnlock-> %d\n", resp);

      } else if (command == 99) {
         Serial.println("flush");
         Serial.flush();

      } else {
         Serial.println(command);
      }
   }
   delay(5);
}
