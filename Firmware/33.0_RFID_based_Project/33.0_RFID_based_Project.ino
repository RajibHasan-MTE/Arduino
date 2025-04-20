#include <SPI.h>
#include <MFRC522.h>


#define SS_PIN 10
#define RST_PIN 9
#define LED1 8
#define LED2 7


MFRC522 mfrc522(SS_PIN, RST_PIN);
String tag_UID1 = "93EED4A0";
String tag_UID2 = "0326B50E";

boolean ledState1 = 1;
boolean ledState2 = 1;
void setup(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
}

int readID(){
  if(!mfrc522.PICC_IsNewCardPresent()){
    Serial.println("Please panch the card");
    return false;
  }
  if(!mfrc522.PICC_ReadCardSerial()){
    Serial.println("unknow card");
    return false;
  }

  //read the UID
  String tagID = "";
  for(uint8_t i=0; i<mfrc522.uid.size; i++){
    tagID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tagID.toUpperCase();

  mfrc522.PICC_HaltA(); //stop reading
  if(tagID == tag_UID1){
    Serial.println("person 1");
    return 1;
     
  }
  if(tagID == tag_UID2){
    Serial.println("person 2");
    return 2;
  }

}


void loop(){
  int val = readID();
  digitalWrite(LED1, ledState1);
  digitalWrite(LED2, ledState2);
  if(val == 1){
    ledState1 = !ledState1;
  }
  if(val == 2){
    ledState2 = !ledState2;
  }


delay(100);

}