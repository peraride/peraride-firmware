
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <SPI.h>
#include "MFRC522.h"

#define WIFI_SSID "******"
#define WIFI_PASSWORD "******"

#define STATION_ID 1111

#define PIN_LED_BLUE D4
#define PIN_LIMIT D3
#define PIN_PUSH_BUTTON A0
#define PIN_RELAY D0
#define PIN_BUZZER PIN_LED_BLUE

#define PIN_RST D1
#define PIN_SS	D2

ESP8266WiFiMulti WiFiMulti;
MFRC522 rfid(PIN_SS, PIN_RST);

uint8_t serialId[4];
uint8_t dockId=1;
boolean cardExist = false;
uint8_t cardUID[4] = {0,0,0,0};
char rfID_code[16];

uint8_t status_limit = 0;

void setup() {
   Serial.begin(115200);
   while (!Serial) {;}

   Serial.println("\n\nBegin");

   WiFi.mode(WIFI_STA);
   WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

   initGPIO();
   initRFID();

   blinkLED(PIN_LED_BLUE,2,200);
}

void loop() {

   //Serial.println(analogRead(PIN_PUSH_BUTTON) > 512);
   //Serial.println(digitalRead(PIN_LIMIT));

   isLimitTriggered();
   isPushButtonPressed();

   delay(50);
}
