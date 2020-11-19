
void beginGPIO(){
   pinMode(LED_BLUE, OUTPUT);
   pinMode(RESPONSE_A, OUTPUT);
   pinMode(RESPONSE_B, OUTPUT);

   digitalWrite(RESPONSE_A, LOW);
   digitalWrite(RESPONSE_B, LOW);
   digitalWrite(LED_BLUE, HIGH);

}
void sendSignal(uint8_t sig) {
   if (sig == 1) digitalWrite(RESPONSE_B, HIGH);  // Signal state
   else digitalWrite(RESPONSE_B, LOW);  // Signal state

   digitalWrite(RESPONSE_A , HIGH);  // Enable the line
   delay(2000);
   digitalWrite(RESPONSE_A, LOW);    // Line Enable
   digitalWrite(RESPONSE_B, LOW);    // Off the signal
   delay(500);
}

void indicatorBlink(int c) {
   for (int i = 0; i < c; i++) {
      digitalWrite(LED_BLUE , LOW);
      delay(500);
      digitalWrite(LED_BLUE, HIGH);
      delay(500);
   }
}
void ledBlink(int pin, int c) {
   for (int i = 0; i < c; i++) {
      digitalWrite(pin , LOW);
      delay(500);
      digitalWrite(pin, HIGH);
      delay(500);
   }
}
