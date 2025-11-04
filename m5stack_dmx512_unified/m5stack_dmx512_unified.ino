
//#include <M5Core2.h>
#include <M5Unified.h>
#include <SoftwareSerial.h>
#define swrxPin 33 //coreS3+DMXUnit+120OhmOn:16 AtomS3+DMXUnit+120OhmOn:1 seedStudio+core2: 32. seedStudio+AtomS3 2 DMXUnit:33?   m5go-bottom G17
#define swtxPin 32 //coreS3DMXUnit++120ohmOn:17 AtomS3+DMXUnit+120OhmOn:2 cseedStudio+core2: 33 seedStudio+AtomS3 1 m5go-bottom G16

SoftwareSerial mySerial;

int brightness = 0;
void setup() {
  auto cfg = M5.config();
  cfg.output_power = true;        // ✅ 電源ICの出力ON
  cfg.internal_imu = false;       // IMU未使用ならfalseに
  cfg.internal_spk = false;       // スピーカー未使用ならfalseに
  cfg.external_imu = false;

  M5.begin(cfg);                  // ✅ 安定化のため明示設定
  M5.Display.setBrightness(200); // 明るさ設定（0〜255）
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
      uint8_t half = 127;
      uint8_t full= 255;
      mySerial.write(zero);//Start Code as 0

      mySerial.write(zero);//Ch1 pan
      mySerial.write(zero);//Ch2 tilt
      mySerial.write(zero);//Ch3 speed
      mySerial.write(full);//Ch4 dim
      mySerial.write(zero);//Ch5 strobe
      mySerial.write(zero);//Ch6 r
      mySerial.write(zero);//Ch7 g
      mySerial.write(zero);//Ch8 b
      mySerial.write(zero);//Ch9 w
      mySerial.write(zero);//Ch10 or
      mySerial.write(zero);//Ch11 uv
      /*
      mySerial.write(full);//Ch1 pan
      mySerial.write(half);//Ch2 tilt
      mySerial.write(zero);//Ch3 speed
      mySerial.write(full);//Ch4 dim
      mySerial.write(zero);//Ch5 strobe
      mySerial.write(zero);//Ch6 r
      mySerial.write(zero);//Ch7 g
      mySerial.write(zero);//Ch8 b
      mySerial.write(full);//Ch9 w
      mySerial.write(zero);//Ch10 or
      mySerial.write(zero);//Ch11 uv
      */
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
