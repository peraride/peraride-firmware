




void init_RFID(){
   SPI.begin();                // Init SPI bus

   for(int i=0;i<DOCKS_COUNT;i++){
      rfid[i].PCD_Init();         // Init MFRC522 card
   }
   /*Serial.println(F("*****************************"));
   Serial.println(F("MFRC522 Digital self test"));
   Serial.println(F("*****************************"));
   rfid[i].PCD_DumpVersionToSerial();  // Show version of PCD - MFRC522 Card Reader
   Serial.println(F("-----------------------------"));
   Serial.println(F("Only known versions supported"));
   Serial.println(F("-----------------------------"));
   Serial.println(F("Performing test..."));
   bool result = rfid[i].PCD_PerformSelfTest(); // perform the test
   Serial.println(F("-----------------------------"));
   Serial.print(F("Result: "));
   if (result) Serial.println(F("OK"));
   else Serial.println(F("DEFECT or UNKNOWN"));
   Serial.println();*/

}

boolean checkRFID(uint8_t i){
   if (!rfid[i].PICC_IsNewCardPresent()) return false;
   if (!rfid[i].PICC_ReadCardSerial()) return false;

   Serial.print(F("Card UID: ("));
   Serial.print(i);
   Serial.print(F(") "));
   //dump_byte_array(rfid[i].uid.uidByte, rfid[i].uid.size);
   Serial.println();
   return true;
}

void dump_byte_array(byte *buffer, byte bufferSize) {
   for (byte i = 0; i < bufferSize; i++) {
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");

      cardUID[i] = (int)buffer[i];
      Serial.print(cardUID[i]);
   }
   Serial.print('\n');
   
}

int checkRFIDpresent(int i){
   boolean hasACard = false;
   if(rfid[i].PICC_IsNewCardPresent()==false){
      if(rfid[i].PICC_IsNewCardPresent()==true){
         hasACard=true;
      }
   }else{
      hasACard=true;
   }

   if(hasACard==true){
      Serial.println("Card detected");
      cardExist[i] = true;

      rfid[i].PICC_ReadCardSerial();
      Serial.print(F("Card UID: ("));Serial.print(i);Serial.print(F(") "));
      dump_byte_array(rfid[i].uid.uidByte, rfid[i].uid.size);
      Serial.println();
      dump_byte_array(rfid[i].uid.uidByte, rfid[i].uid.size);

      return ((cardUID[0]+cardUID[1]+cardUID[2]+cardUID[3] )>0) ;

   }
   Serial.println("Card not detected");
   return 0;
}
void scanCards(){
   for(int i=0;i<DOCKS_COUNT;i++){

      if(rfid[i].PICC_IsNewCardPresent()){

         if(cardExist[i]==false){
            Serial.println("New Card detected");
            cardExist[i] = true;

            rfid[i].PICC_ReadCardSerial();
            Serial.print(F("Card UID: ("));
            Serial.print(i);
            Serial.print(F(") "));
            dump_byte_array(rfid[i].uid.uidByte, rfid[i].uid.size);
            Serial.println();
            sendBikeFound(i);
         }
      }else{

         // No card detected
         if(cardExist[i]==true){
            Serial.print(F("Must have a card in "));
            Serial.print(i);
            Serial.println(F(", but now it is missing"));
            cardExist[i] = false;
         }
      }
   }
   delay(100);
}
