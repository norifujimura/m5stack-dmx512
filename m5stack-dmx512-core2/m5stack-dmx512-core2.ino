
//#include <M5Core2.h>
#include <M5Unified.h>
#include <SoftwareSerial.h>
#define swrxPin 32 //core2+official DMX: 33. core2+Seedstudio: 32. AtomS 2
#define swtxPin 33 //core2+official DMX: 32. core2+Seedstudio: 33 AtomS 1

SoftwareSerial mySerial;

int brightness = 0;
void setup() {
  M5.begin();
  M5.Lcd.clear(); 
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(1);
  M5.Lcd.print("M5Stack DMX512");
}
void loop() {
  M5.update(); 
  
  for (brightness = 0; brightness <= 255; brightness++) {
     writeDMX( brightness);
     delay(10);
    }

  for (brightness = 0; brightness <= 255; brightness++) {
     writeDMX(255- brightness);
     delay(10);
    }    
    //delay(400);
 
}

void writeDMX(int x){
      pinMode(swtxPin,OUTPUT);

      
      digitalWrite(swtxPin,0);//Break as LOW
      delayMicroseconds(88);
      digitalWrite(swtxPin,1);//MAB as HIGH
      delayMicroseconds(8);
      

      mySerial.begin(250000, SWSERIAL_8N2, swrxPin, swtxPin , false, 256);
      mySerial.enableIntTx(true);
      uint8_t zero = 0;
      uint8_t half = 127;
      uint8_t full= 255;
      mySerial.write(zero);//Start Code as 0

      mySerial.write(zero);//Ch1 pan
      mySerial.write(half);//Ch2 tilt
      mySerial.write(half);//Ch3 speed
      mySerial.write(full);//Ch4 dim
      mySerial.write(zero);//Ch5 strobe
      mySerial.write(zero);//Ch6 r
      mySerial.write(zero);//Ch7 g
      mySerial.write(zero);//Ch8 b
      mySerial.write(zero);//Ch9 w
      mySerial.write(zero);//Ch10 or
      mySerial.write(full);//Ch11 uv
      /*
      mySerial.write(full);//Ch1 Data
      mySerial.write(zero);//Ch2 Data
      mySerial.write(64);//Ch3 Data
      mySerial.write(zero);//Ch4 Data
      mySerial.write(zero);//Ch5 Data
      mySerial.write(full);//Ch6 Data
      mySerial.write(zero);//Ch7 Data
      mySerial.write(x);//Ch8 Data
      mySerial.write(x);//Ch9 Data
      mySerial.write(x);//Ch9 Data
      mySerial.write(x);//Ch9 Data
      */
      mySerial.end();
 }
