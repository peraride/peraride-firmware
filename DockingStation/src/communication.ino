#define DOCK_LOCK 11
#define DOCK_UNLOCK 12
#define FEEDBACK_DOCK_UNLOCK 22

void sendBikeFound(int dock){

   sprintf(sBuffer, "%d %d %d %d %d %d 99\n",
   DOCK_LOCK, (dock+1), cardUID[0], cardUID[1], cardUID[2], cardUID[3]);

   Serial.println(sBuffer);
   Serial1.println(sBuffer);
}

int  sendBikeUnlock(int dock){
   //http://peraride-api.herokuapp.com/api/auth/dock/unlock?dock_id=1111.1
   sprintf(sBuffer, "%d %d 99\n", DOCK_UNLOCK, (dock+1));
   Serial.println(sBuffer);
   Serial1.println(sBuffer);

   return readSignal();
}

String inputString;

void serialEvent1(){
   while (Serial1.available()) {
      char inChar = (char)Serial1.read();
      inputString += inChar;
      if (inChar == '\n') {
         Serial.print(">> reply: ");
         Serial.print(inputString);
         inputString = "";
      }
   }
}
