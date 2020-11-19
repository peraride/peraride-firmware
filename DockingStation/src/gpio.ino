
void init_gpio(){

   pinMode(PIN_RESPONSE_A, INPUT);
   pinMode(PIN_RESPONSE_B, INPUT);

   // Setup Pins
   for(int i=0;i<DOCKS_COUNT;i++){
      pinMode(pin_rfid_relay[i], OUTPUT);
      pinMode(pin_rfid_button[i], INPUT_PULLUP);
      pinMode(pin_rfid_led[i], OUTPUT);
      pinMode(pin_rfid_limit_sw[i], INPUT_PULLUP);

      digitalWrite(pin_rfid_relay[i], LOW);

      status_limit[i] = 1 - digitalRead(pin_rfid_limit_sw[i]);
   }

   pinMode(PIN_BUZZER, OUTPUT);

   // A little indicator on functionality -------------------
   for(int i=0;i<DOCKS_COUNT;i++){
      digitalWrite(pin_rfid_led[i], HIGH);
   }
   delay(1000);
   for(int i=0;i<DOCKS_COUNT;i++){
      digitalWrite(pin_rfid_led[i], LOW);
   }
   // --------------------------------------------------------

   Serial.println(F("GPIO \t: begin"));
}

void blinkLED(int pin, int c, int d){
   c = max(c,1);
   d = min(d/c, 200);

   for(int i=0;i<c;i++){
      digitalWrite(pin, HIGH);
      delay(d);
      digitalWrite(pin, LOW);
      delay(d);
   }
   delay(500);
}

void buzzer(int c){
   blinkLED(PIN_BUZZER, c,1000);
}
void buzzer(int c, int d){
   blinkLED(PIN_BUZZER, c,d);
}
void relayOn(int doc){
   digitalWrite(pin_rfid_relay[doc], HIGH);
}
void relayOff(int doc){
   digitalWrite(pin_rfid_relay[doc], HIGH);
}
