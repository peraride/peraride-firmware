# 1 "C:\\Users\\Nuwan\\AppData\\Local\\Temp\\tmpbxw3k0ex"
#include <Arduino.h>
# 1 "D:/Projects/CE-PeraRide/peraride-firmware/src/src.ino"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <SPI.h>
#include "MFRC522.h"

#include "pins.h"
#include "config.h"

ESP8266WiFiMulti WiFiMulti;
MFRC522 rfid(PIN_SS, PIN_RST);

uint8_t serialId[4];
uint8_t dockId=1;
boolean cardExist = false;
uint8_t cardUID[4] = {0,0,0,0};
char rfID_code[16];

uint8_t status_limit = 0;
void setup();
void loop();
void initRFID();
boolean checkRFID();
uint8_t checkRFIDpresent();
void dump_byte_array(byte *buffer, byte bufferSize);
void isLimitTriggered();
void isPushButtonPressed();
void unmountBike();
void initGPIO();
void blinkLED(int pin, int c, int d);
void buzzer(int c);
void buzzer(int c, int d);
void relayOn();
void relayOff();
boolean limitSW_Read();
boolean dockUnlock(uint8_t dockId);
boolean dockLock(uint8_t dockId, char* rfidCode);
#line 24 "D:/Projects/CE-PeraRide/peraride-firmware/src/src.ino"
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






    isLimitTriggered();
    isPushButtonPressed();


    delay(50);
}
# 1 "D:/Projects/CE-PeraRide/peraride-firmware/src/RFID.ino"
# 15 "D:/Projects/CE-PeraRide/peraride-firmware/src/RFID.ino"
void initRFID(){
    SPI.begin();
    rfid.PCD_Init();
}

boolean checkRFID(){
    if (!rfid.PICC_IsNewCardPresent()) return false;
    if (!rfid.PICC_ReadCardSerial()) return false;

    Serial.print(F("Card UID: "));
    dump_byte_array(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    return true;
}

uint8_t checkRFIDpresent(){

    boolean hasACard = false;
    if(rfid.PICC_IsNewCardPresent()==false){
        if(rfid.PICC_IsNewCardPresent()==true){
            hasACard=true;
        }
    }else{
        hasACard=true;
    }

    if(hasACard==true){
        Serial.println("Card detected");
        cardExist = true;

        rfid.PICC_ReadCardSerial();
        Serial.print(F("Card UID: "));
        dump_byte_array(rfid.uid.uidByte, rfid.uid.size);
        Serial.println();

        return ((cardUID[0]+cardUID[1]+cardUID[2]+cardUID[3] )>0);

    }else{
        Serial.println(F("Card not detected"));
    }

    return 0;
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");

        cardUID[i] = (int)buffer[i];
        Serial.print(cardUID[i]);
    }
    Serial.print('\n');

}
# 1 "D:/Projects/CE-PeraRide/peraride-firmware/src/functions.ino"


void isLimitTriggered(){


    if( limitSW_Read() && (status_limit==0)){
        status_limit=1;


        blinkLED(PIN_LED_BLUE, 1,250);
        Serial.println("Limit switch pressed");

        if (checkRFIDpresent()){
            Serial.println("A card detected");





            sprintf(rfID_code, "%02X%02X%02X%02X", cardUID[0], cardUID[1], cardUID[2], cardUID[3]);
            int resp = dockLock(dockId, rfID_code);

            Serial.printf("response: %d\n", resp);

        }else{
            Serial.println("No card detected");



            blinkLED(PIN_LED_BLUE,3,150);
        }

        delay(500);

    }else if (limitSW_Read() == 0){
        status_limit=0;

    }
    delay(500);
}


void isPushButtonPressed(){

    if(digitalRead(PIN_PUSH_BUTTON) == 0){


        blinkLED(PIN_LED_BLUE, 1,250);
        Serial.println("Push Button pressed");

        if (limitSW_Read() == 1){


            uint8_t resp = dockUnlock(dockId);

            Serial.printf("API response: %d\n", resp);

            if(resp == 1){
                buzzer(1,200);
                unmountBike();

            }else{
                buzzer(3,200);
            }
        }else{
            Serial.println(F("No bike attached"));
        }
        delay(2000);
    }
}

void unmountBike(){
    relayOn();

    if (limitSW_Read() == 0){

        Serial.println("No bike attached to this");
        return;
    }
    Serial.println("Please unmount the bike now");

    for(int i=15;i>0;i--){
        buzzer(1,200);
        delay(500);
        Serial.println(i);
        if (i<11 && (limitSW_Read() == 0)){

            break;
        }
    }
    relayOff();
    Serial.println("Timeout ok");

    delay(3000);

    if (limitSW_Read() == 0){

        Serial.println("Bike was removed.");
        buzzer(2, 500);

    }else{

        Serial.println("Bike is still attached");
        buzzer(3,750);

        if(checkRFIDpresent()){


            sprintf(rfID_code, "%02X%02X%02X%02X", cardUID[0], cardUID[1], cardUID[2], cardUID[3]);
            int resp = dockLock(dockId, rfID_code);

            Serial.printf("response: %d\n", resp);


            status_limit = 0;

        }else{

            blinkLED(PIN_LED_BLUE,3,150);
        }
    }
}
# 1 "D:/Projects/CE-PeraRide/peraride-firmware/src/gpio.ino"

void initGPIO(){

   pinMode(PIN_LED_BLUE, OUTPUT);
   pinMode(PIN_LIMIT, INPUT_PULLUP);
   pinMode(PIN_PUSH_BUTTON, INPUT_PULLUP);
   pinMode(PIN_RELAY, OUTPUT);
   pinMode(PIN_BUZZER, OUTPUT);

   digitalWrite(PIN_LED_BLUE, HIGH);
   relayOff();
}
# 32 "D:/Projects/CE-PeraRide/peraride-firmware/src/gpio.ino"
void blinkLED(int pin, int c, int d){
   c = max(c,1);
   d = min(d/c, 200);

   for(int i=0;i<c;i++){
      digitalWrite(pin, LOW);
      delay(d);
      digitalWrite(pin, HIGH);
      delay(d);
   }
   delay(500);
}


void buzzer(int c){

}
void buzzer(int c, int d){
# 61 "D:/Projects/CE-PeraRide/peraride-firmware/src/gpio.ino"
}
void relayOn(){
   digitalWrite(PIN_RELAY, LOW);
}
void relayOff(){
   digitalWrite(PIN_RELAY, HIGH);
}

boolean limitSW_Read(){
    return (analogRead(PIN_LIMIT) < 512);
}
# 1 "D:/Projects/CE-PeraRide/peraride-firmware/src/http.ino"
char url[256];
char body[256];

boolean dockUnlock(uint8_t dockId) {

   if ((WiFiMulti.run() == WL_CONNECTED)) {
      WiFiClient client;
      HTTPClient http;

      sprintf(url, "http://peraride-api.herokuapp.com/api/auth/dock/unlock?dock_id=%d.%d", STATION_ID, dockId);
      Serial.printf(">> GET: %s\n", url);

      for(int i=0;i<5;i++){


         if (http.begin(client, url)) {
            http.addHeader("Content-Type", "application/json");
            http.addHeader("Authorization: Bearer", AUTH_KEY);

            int httpCode = http.GET();

            if (httpCode > 0) {
               Serial.printf("GET - %d\n", httpCode);

               if (httpCode == 406) {
                  Serial.println("Not accepted");



                  return false;

               } else if (httpCode == 404) {
                  Serial.println("Dock is empty");


                  return false;

               } else if (httpCode == 202) {
                  Serial.println("Access granted");


                  return true;

               } else {

                  return false;
               }
            } else {
               Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
               return false;
            }
            http.end();
         } else {
            Serial.printf("[HTTP} Unable to connect\n");
            ESP.restart();
            return false;
         }
      }
   }else{
      Serial.printf("[HTTP} Unable to connect\n");
      ESP.restart();
      return false;
   }
   return false;
}

boolean dockLock(uint8_t dockId, char* rfidCode) {

   if ((WiFiMulti.run() == WL_CONNECTED)) {
      WiFiClient client;
      HTTPClient http;

      sprintf(url, "http://peraride-api.herokuapp.com/api/auth/dock/lock");
      sprintf(body, "{\"dock_id\": \"%d.%d\",\"rfid_code\": \"%s\"}", STATION_ID, dockId, rfidCode);
      Serial.printf(">> POST: %s >\n\t%s\n", url, body);

      for(int i=0;i<5;i++){


         if (http.begin(client, url)) {
            http.addHeader("Content-Type", "application/json");
            http.addHeader("Authorization: Bearer", AUTH_KEY);

            int httpCode = http.POST(body);

            if (httpCode > 0) {
               Serial.printf("POST - %d\n", httpCode);

               if (httpCode == 404) {

                  return false;

               } else if (httpCode == 200) {

                  return true;

               } else {

                  return false;
               }
            } else {
               Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
               return false;
            }

            http.end();
         } else {
            Serial.printf("[HTTP} Unable to connect\n");
            ESP.restart();
            return false;
         }
      }
   }
   return false;
}