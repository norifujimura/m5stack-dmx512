
#include <M5Core2.h>

int brightness = 0;
int Tx = 33;//DMXoutputPin
void setup() {
  M5.begin();
  M5.Lcd.clear(); 
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(1);
  M5.Lcd.print("M5Stack DMX512");
  //Serial2.begin(250000,SERIAL_8N2,32,33);//Grove
}
void loop() {
  M5.update(); 
  
  for (brightness = 0; brightness <= 255; brightness++) {
     writeDMX( brightness);
     delay(100);
    }

  for (brightness = 0; brightness <= 255; brightness++) {
     writeDMX(255- brightness);
     delay(100);
    }    
    delay(400);
 
}

void writeDMX(int x){
      pinMode(Tx,OUTPUT);
      digitalWrite(Tx,0);//Break as LOW
      delayMicroseconds(88);
      digitalWrite(Tx,1);//MAB as HIGH
      delayMicroseconds(8);
      Serial2.begin(250000,SERIAL_8N2,32,33);//Grove
      Serial2.write(0x0);//Start Code as 0
      Serial2.write(x);//Ch1 Data
      Serial2.end( );
 }
