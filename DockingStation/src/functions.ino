
void isPushButtonPressed(){
   for(int i=0;i<DOCKS_COUNT;i++){
      // Push button is pressed.
      if((digitalRead(pin_rfid_button[i]) == LOW)){
         //buzzer(1);
         Serial.print(i);
         Serial.println(" : Push Button pressed");

         if (digitalRead(pin_rfid_limit_sw[i]) == LOW){
            // A bike attached

            uint8_t response = sendBikeUnlock(i);
            Serial.print("API response: ");
            Serial.print(response);

            if(response == 1){
               buzzer(1,200);
               unmountBike(i);

            }else{
               buzzer(3,200);
            }
         }
      }
   }
}


void unmountBike(int dock){
   relayOn(dock);

   if (digitalRead(pin_rfid_limit_sw[dock]) == HIGH){
      // No bike attached
      Serial.println("No bike attached to this");
      return;
   }
   Serial.println("Please unmount the bike now");

   for(int i=15;i>0;i--){
      buzzer(1,200);
      delay(500);
      Serial.println(i);
      if (i<11 && digitalRead(pin_rfid_limit_sw[dock]) == HIGH){
         // Successfully removed
         break;
      }
   }
   relayOff(dock);
   Serial.println("Timeout ok");

   delay(3000);

   if (digitalRead(pin_rfid_limit_sw[dock]) == HIGH){
      // Bike is removed
      Serial.println("Bike was removed.");
      buzzer(2, 500);

   }else{
      // Bike is still attached
      Serial.println("Bike is still attached");
      buzzer(3,750);

      // (Server will know it is attached on next limit switch scan cycle)
      status_limit[dock] = 0;

      // sendBikeFound(dock); // Mount again
      // Send an API call to server
      // Send a LOCK request to the server
   }

}

void isLimitTriggered(){
   for(int i=0;i<DOCKS_COUNT;i++){

      // Is a bike inserted to the socket ?
      if((digitalRead(pin_rfid_limit_sw[i]) == LOW) && status_limit==0){
         status_limit[i]=1;

         Serial.print(i);Serial.println(" : Limit switch pressed");

         // Visual and audio indicators
         //blinkLED(pin_rfid_led[i], 2, 1000);

         //if (checkRFID(i)==true){
         if (checkRFIDpresent(i)){
            Serial.println("A card detected");
            // Found a valid RFID card on the slot.
            buzzer(1);

            // Send info to the server
            sendBikeFound(i);

         }else{
            Serial.println("No card detected");
            // There is a valid RFID card at the slot.
            // Sound the buzzer and inform to the server

            buzzer(3);
         }

         delay(500);

      }else if (digitalRead(pin_rfid_limit_sw[i]) == HIGH){
         status_limit[i]=0;
         digitalWrite(pin_rfid_led[i], LOW);
      }
   }
   delay(500);
}
