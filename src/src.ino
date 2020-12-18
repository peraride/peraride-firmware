
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <SPI.h>
#include "MFRC522.h"

#include "config.h" // Sample File: config.sample.h

#define STATION_ID 1111
#define AUTH_KEY "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiI1ZTVmYmFkMDRmOTAyNDAwMDQ3NWY1Y2QiLCJpYXQiOjE2MDgzMDIzOTN9.pLRQCKJMfVuBLXT-UBvABGZupESD6YtEbpmY9M0sl5E"

#define PIN_LED_BLUE D4         // GPIO 2
#define PIN_LIMIT D3            // GPIO 0
#define PIN_PUSH_BUTTON A0
#define PIN_RELAY D0            // GPIO 16
#define PIN_BUZZER PIN_LED_BLUE

#define PIN_RST D1              // GPIO 5
#define PIN_SS	D2              // GPIO 4

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
    //Serial.println();
    //delay(500);

    isLimitTriggered();
    isPushButtonPressed();

    delay(50);
}
