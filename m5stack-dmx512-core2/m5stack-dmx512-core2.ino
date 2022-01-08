
#include <M5Core2.h>
#include <SoftwareSerial.h>
#define swrxPin 32
#define swtxPin 33

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
    delay(400);
 
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
      mySerial.write(zero);//Start Code as 0
      mySerial.write(zero);//Ch1 Data
      mySerial.write(x);//Ch2 Data
      mySerial.end();
 }
