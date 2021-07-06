#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>

#include <SPI.h>
#include "MFRC522.h"

#include "pins.h"
#include "config.h" // Sample File: config.sample.h

ESP8266WiFiMulti WiFiMulti;
MFRC522 rfid(PIN_SS, PIN_RST);
Servo lockServo;

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

    //Serial.println(analogRead(PIN_PUSH_BUTTON));
    //Serial.println(digitalRead(PIN_LIMIT));
    //Serial.println();
    //delay(500);

    isLimitTriggered();
    isPushButtonPressed();
    //checkRFID();

    delay(50);
}
