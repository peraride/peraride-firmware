

void isLimitTriggered(){

    // Is a bike inserted to the socket ?
    if( limitSW_Read() && (status_limit==0)){
        status_limit=1;

        // Visual and audio indicator
        blinkLED(PIN_LED_BLUE, 1,250);
        Serial.println("Limit switch pressed");

        if (checkRFIDpresent()){
            Serial.println("A card detected");
            //buzzer(1);

            // Send info to the server
            //sendBikeFound(i);

            sprintf(rfID_code, "%02X%02X%02X%02X", cardUID[0], cardUID[1], cardUID[2], cardUID[3]);
            int resp = dockLock(dockId, rfID_code);

            Serial.printf("response: %d\n", resp);

        }else{
            Serial.println("No card detected");
            // There is a valid RFID card at the slot.
            // Sound the buzzer and inform to the server

            blinkLED(PIN_LED_BLUE,3,150);
        }

        delay(500);

    }else if (limitSW_Read() == 0){
        status_limit=0;
        //digitalWrite(pin_rfid_led[i], LOW);
    }
    delay(500);
}


void isPushButtonPressed(){
    // Push button is pressed.
    if(digitalRead(PIN_PUSH_BUTTON) == 0){

        // Visual and audio indicator
        blinkLED(PIN_LED_BLUE, 1,250);
        Serial.println("Push Button pressed");

        if (limitSW_Read() == 1){
            // A bike attached

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
        // No bike attached
        Serial.println("No bike attached to this");
        return;
    }
    Serial.println("Please unmount the bike now");

    for(int i=15;i>0;i--){
        buzzer(1,200);
        delay(500);
        Serial.println(i);
        if (i<11 && (limitSW_Read() == 0)){
            // Successfully removed
            break;
        }
    }
    relayOff();
    Serial.println("Timeout ok");

    delay(3000);

    if (limitSW_Read() == 0){
        // Bike is removed
        Serial.println("Bike was removed.");
        buzzer(2, 500);

    }else{
        // Bike is still attached
        Serial.println("Bike is still attached");
        buzzer(3,750);

        if(checkRFIDpresent()){
            // RFID detected, lock the bike again

            sprintf(rfID_code, "%02X%02X%02X%02X", cardUID[0], cardUID[1], cardUID[2], cardUID[3]);
            int resp = dockLock(dockId, rfID_code);

            Serial.printf("response: %d\n", resp);

            // (Server will know it is attached on next limit switch scan cycle)
            status_limit = 0;

        }else{
            // Error ????
            blinkLED(PIN_LED_BLUE,3,150);
        }
    }
}
