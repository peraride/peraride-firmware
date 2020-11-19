
/********************************************
 Wiring the MFRC522 to ESP8266 (ESP-12)
   RST     = GPIO5   D1
   SDA(SS) = GPIO4   D2
   MOSI    = GPIO13  D7
   MISO    = GPIO12  D6
   SCK     = GPIO14  D5
   GND     = GND
   3.3V    = 3.3V
********************************************/



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

      return ((cardUID[0]+cardUID[1]+cardUID[2]+cardUID[3] )>0); // Return non-zero value

   }
   Serial.println(F("Card not detected"));
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
