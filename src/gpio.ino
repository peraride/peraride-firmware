
void initGPIO(){

   pinMode(PIN_LED_BLUE, OUTPUT);
   pinMode(PIN_LIMIT, INPUT_PULLUP);
   pinMode(PIN_PUSH_BUTTON, INPUT_PULLUP);
   pinMode(PIN_RELAY, OUTPUT);
   pinMode(PIN_BUZZER, OUTPUT);

   digitalWrite(PIN_LED_BLUE, HIGH);
   relayOff();
}
/*
void indicatorBlink(int c) {
   for (int i = 0; i < c; i++) {
      digitalWrite(PIN_LED_BLUE , LOW);
      delay(500);
      digitalWrite(PIN_LED_BLUE, HIGH);
      delay(500);
   }
}
*/
/*void ledBlink(int pin, int c) {
   for (int i = 0; i < c; i++) {
      digitalWrite(pin , LOW);
      delay(500);
      digitalWrite(pin, HIGH);
      delay(500);
   }
}*/

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
   //buzzer(c, 1000);
}
void buzzer(int c, int d){
   /*c = max(c,1);
   d = min(d/c, 200);

   for(int i=0;i<c;i++){
      digitalWrite(PIN_BUZZER, HIGH);
      delay(d);
      digitalWrite(PIN_BUZZER, LOW);
      delay(d);
   }
   delay(500);
   */
}
void relayOn(){
   digitalWrite(PIN_RELAY, LOW);
}
void relayOff(){
   digitalWrite(PIN_RELAY, HIGH);
}
