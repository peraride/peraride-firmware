
void initGPIO(){

    pinMode(PIN_LED_BLUE, OUTPUT);
    pinMode(PIN_LIMIT, INPUT_PULLUP);
    pinMode(PIN_PUSH_BUTTON, INPUT_PULLUP);
    pinMode(PIN_BUZZER, OUTPUT);

    digitalWrite(PIN_LED_BLUE, HIGH);
    lockClose();

    // Use Solonoid to control the lock
    // pinMode(PIN_RELAY, OUTPUT);

    // Use Servo motor to control the lock
    lockServo.attach(PIN_SERVO, 500, 2400);
}

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
    // c = max(c,1);
    // d = min(d/c, 200);
    //
    // for(int i=0;i<c;i++){
    //     digitalWrite(PIN_BUZZER, HIGH);
    //     delay(d);
    //     digitalWrite(PIN_BUZZER, LOW);
    //     delay(d);
    // }
    // delay(500);
}

void lockOpen(){
    // digitalWrite(PIN_RELAY, LOW);
    lockServo.write(SERVO_UNLOCK_POSITION);
    delay(500);
}
void lockClose(){
    // digitalWrite(PIN_RELAY, HIGH);
    lockServo.write(SERVO_LOCK_POSITION);
    delay(500);
}

boolean limitSW_Read(){
    return (analogRead(PIN_LIMIT) < 512);
}
