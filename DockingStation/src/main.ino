#include <Arduino.h>
#include "define.h"

//RFID RC522(7, 42);

void setup() {
   Serial.begin(115200);
   Serial1.begin(115200);

   init_gpio();
   init_RFID();

}

int readSignal(){
   int val=0;

   while(digitalRead(PIN_RESPONSE_A)==LOW){
      delay(10);
   }

   for(int i=0;i<10;i++){
      val += digitalRead(PIN_RESPONSE_B);
      Serial.print(digitalRead(PIN_RESPONSE_B));
      delay(25);
   }
   Serial.println();
   return (val > 6);
}
void loop() {

//Serial.println(readSignal());
   isPushButtonPressed();
   isLimitTriggered();
   delay(200);
}

void unitTestPinout(){
   // Setting all pins as outputs
   for(int i=0;i<DOCKS_COUNT;i++){
      pinMode(pin_rfid_relay[i], OUTPUT);
      pinMode(pin_rfid_button[i], OUTPUT);
      pinMode(pin_rfid_led[i], OUTPUT);
      pinMode(pin_rfid_limit_sw[i], OUTPUT);
      pinMode(pin_rfid_rst[i], OUTPUT);
      pinMode(pin_rfid_cs[i], OUTPUT);
   }
   pinMode(PIN_MOSI, OUTPUT);
   pinMode(PIN_MISO, OUTPUT);
   pinMode(PIN_SCK, OUTPUT);

   pinMode(PIN_BUZZER, OUTPUT);

   // Blink one by one
   for(int i=0;i<DOCKS_COUNT;i++){
      Serial.print("Testing dock #");
      Serial.println(i);
      digitalWrite(pin_rfid_relay[i], HIGH);
      digitalWrite(pin_rfid_led[i],HIGH);
      digitalWrite(pin_rfid_button[i], HIGH);
      digitalWrite(pin_rfid_limit_sw[i], HIGH);
      digitalWrite(pin_rfid_rst[i], HIGH);
      digitalWrite(pin_rfid_cs[i],HIGH);
      digitalWrite(PIN_MISO, HIGH);
      digitalWrite(PIN_MOSI, HIGH);
      digitalWrite(PIN_SCK, HIGH);
      Serial.println();
      delay(2500);

      digitalWrite(pin_rfid_relay[i], LOW);
      digitalWrite(pin_rfid_led[i],LOW);
      digitalWrite(pin_rfid_button[i], LOW);
      digitalWrite(pin_rfid_limit_sw[i], LOW);
      digitalWrite(pin_rfid_rst[i], LOW);
      digitalWrite(pin_rfid_cs[i],LOW);
      digitalWrite(PIN_MISO, LOW);
      digitalWrite(PIN_MOSI, LOW);
      digitalWrite(PIN_SCK, LOW);
      delay(500);
   }

}

void unitTestPinout2(){
   // Setting all pins as outputs
   for(int i=0;i<DOCKS_COUNT;i++){
      pinMode(pin_rfid_relay[i], OUTPUT);
      pinMode(pin_rfid_button[i], OUTPUT);
      pinMode(pin_rfid_led[i], OUTPUT);
      pinMode(pin_rfid_limit_sw[i], OUTPUT);

      pinMode(pin_rfid_rst[i], OUTPUT);
      pinMode(pin_rfid_cs[i], OUTPUT);
   }
   pinMode(PIN_MOSI, OUTPUT);
   pinMode(PIN_MISO, OUTPUT);
   pinMode(PIN_SCK, OUTPUT);
   pinMode(PIN_BUZZER, OUTPUT);

   // Blink one by one

   Serial.println("Relay");
   for(int i=0;i<DOCKS_COUNT;i++){
      blinkLED(pin_rfid_relay[i], 1, 1000);
   }

   Serial.println("LED");
   for(int i=0;i<DOCKS_COUNT;i++){
      blinkLED(pin_rfid_led[i], 2, 1000);
   }

   Serial.println("Button");
   for(int i=0;i<DOCKS_COUNT;i++){
      blinkLED(pin_rfid_button[i], 3, 1000);
   }

   Serial.println("Switch");
   for(int i=0;i<DOCKS_COUNT;i++){
      blinkLED(pin_rfid_limit_sw[i], 4, 1000);
   }

   Serial.println("RFID.reset");
   for(int i=0;i<DOCKS_COUNT;i++){
      blinkLED(pin_rfid_rst[i], 5, 1000);
   }

   Serial.println("RFID.cs");
   for(int i=0;i<DOCKS_COUNT;i++){
      blinkLED(pin_rfid_cs[i], 6, 1000);
   }

   Serial.println("RFID.miso");
   for(int i=0;i<DOCKS_COUNT;i++){
      blinkLED(PIN_MISO, 2, 1000);
   }

   Serial.println("RFID.mosi");
   for(int i=0;i<DOCKS_COUNT;i++){
      blinkLED(PIN_MOSI, 2, 1000);
   }

   Serial.println("RFID.sck");
   for(int i=0;i<DOCKS_COUNT;i++){
      blinkLED(PIN_SCK, 2, 1000);
   }


}
