//For more information about this library please visit us at
//http://www.arduino.cc/en/Reference/SD
#include <SD.h>  // Tested OK with 8Gb SD Card
// file is part of the ATMEL AVR-UC3-SoftwareFramework-1.7.0 Release
// SPI driver for AVR32 UC3
#include <SPI.h>
#define pinSD 10     // pin for SD card

//Arduino library for asynchronous playback of PCM/WAV files direct from SD card
//Utilizes standard Arduino SD library, SD card and output device (Speaker, Headphones, Amplifier, etc)
//Documentation is available on the Wiki: https://github.com/TMRh20/TMRpcm/wiki
#include <TMRpcm.h>  
#define Speaker 9     // pin for speaker
TMRpcm tmrpcm;   // object for TMRpcm library

// RFID -  https://travis-ci.org/miguelbalboa/rfid
#include <MFRC522.h>
#define RST_PIN  4    //Pin 9, 4 para el reset del RC522
#define SS_PIN  7   //Pin 10, 7 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // object for RC522 library 

byte ActualUID[4]; // Storage of RFID TAG code readed
byte CodeID1[4]= {0xD4, 0x2B, 0x3F, 0xC5} ; // RFID code to play audio1
byte CodeID2[4]= {0xC9, 0x2E, 0x9A, 0x34} ; // RFID code to play audio2
byte CodeID3[4]= {0x45, 0x18, 0xA6, 0x76} ; // RFID code to play audio3
// ... you can add others ...

// Audio Files:  WAV / PCM 1 channel (mono) / 16KHz / 8 bits sample
char *audio1 = "audio1.wav";
const int timeAudio1 = 5 ; // seconds of Audio 1
char *audio2 = "audio2.wav";
const int timeAudio2 = 2 ; // seconds of Audio 2
char *audio3 = "audio3.wav";
const int timeAudio3 = 2 ; // seconds of Audio 3
// ... you can add others ...

//LEDs
#define redLED 5     // pin definition for RED eyes

void setup(){

Serial.begin(9600); // serial for PC only
SPI.begin();        //Init Bus SPI

// Lector RFID
  mfrc522.PCD_Init(); // Init   MFRC522
  Serial.println("Ready for RFID...");  
  pinMode(SS_PIN,OUTPUT);
  
// Altavoz  
tmrpcm.speakerPin = Speaker; //Se define el pin en el que está conectada la bocina
pinMode(Speaker,OUTPUT);

// Leer SD
pinMode(pinSD,OUTPUT);
//  Serial.begin(9600);    //Se inicia la comunicación serial
  if (!SD.begin(pinSD)) {  // see if the card is present and can be initialized:
    Serial.println("Fallo en la tarjeta SD");  // something is wrong
    return;   // do nothing
  }

//LED
pinMode(redLED,OUTPUT);

}

void loop(){

delay (200);

  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
      // read RFID
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Send RFID UID
                  Serial.print(F("Card UID:"));
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                          ActualUID[i]=mfrc522.uid.uidByte[i];          
                  } 
                  Serial.print("     ");                 
                  // UID check with our RFIDs  
                  if(compareArray(ActualUID,CodeID1)){
                    Serial.println(audio1);
                   TurnOnLED() ;
                    tmrpcm.play(audio1);    
                    delay(timeAudio1*1000); // Required time of audio
                   }
                  else if(compareArray(ActualUID,CodeID2)){
                    Serial.println(audio2);
                   TurnOnLED() ;
                    tmrpcm.play(audio2);    
                    delay(timeAudio2*1000); // Required time of audio
                  }
                  else if(compareArray(ActualUID,CodeID3)){
                    Serial.println(audio3);
                   TurnOnLED() ;
                    tmrpcm.play(audio3);    
                    delay(timeAudio3*1000); // Required time of audio
                 }
                  else {
                    Serial.println("Nooooo...");
                  }
                  
                  // End of check
                  delay(2000);
                  Serial.println("RFID reset... Ready for RFID...");
                  mfrc522.PICC_HaltA();
          
            }
      
  }

delay (100);
}

// function to compare two vectors
 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}

  
 void TurnOnLED() {

        for (int a=0; a <= 2; a++){

        for (int i=0; i <= 255; i++){
      analogWrite(redLED, i);
      delay(3);
      }
     for (int i=0; i <= 255; i++){
      analogWrite(redLED, 255-i);
      delay(3);
      }
        }
    analogWrite (redLED, 0);  

 }
  
