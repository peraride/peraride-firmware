
#include <SPI.h>
#include <MFRC522.h>

#define HAS_BIKE 0
#define No_BIKE 1

#define DOCKS_COUNT 6

#define PIN_BUZZER 29
#define PIN_MISO 50
#define PIN_MOSI 51
#define PIN_SCK 52

#define PIN_RESPONSE_A 38
#define PIN_RESPONSE_B 36

const uint8_t pin_rfid_rst[DOCKS_COUNT] = {42, 40, 41, 43, 45, 47};
const uint8_t pin_rfid_cs[DOCKS_COUNT] = {7,6,5,4,3,2};

const uint8_t pin_rfid_relay[DOCKS_COUNT] = {17,12,11,10,9,8};
const uint8_t pin_rfid_button[DOCKS_COUNT] = {A0,A1,A2,A3,A4,A5};
const uint8_t pin_rfid_led[DOCKS_COUNT] = {26,24,22,23,25,27};
const uint8_t pin_rfid_limit_sw[DOCKS_COUNT] = {34,32,30,31,33,35};

uint8_t status_limit[DOCKS_COUNT] = {0,0,0,0,0,0}; // Triggered == 1

long rfid_serialNo = 0;

MFRC522 rfid[6] ={
   MFRC522(pin_rfid_cs[0], pin_rfid_rst[0]),
   MFRC522(pin_rfid_cs[1], pin_rfid_rst[1]),
   MFRC522(pin_rfid_cs[2], pin_rfid_rst[2]),
   MFRC522(pin_rfid_cs[3], pin_rfid_rst[3]),
   MFRC522(pin_rfid_cs[4], pin_rfid_rst[4]),
   MFRC522(pin_rfid_cs[5], pin_rfid_rst[5])
};

boolean cardExist[DOCKS_COUNT] = {false,false,false,false,false,false};
int cardUID[4] = {0,0,0,0};

char sBuffer[256];
