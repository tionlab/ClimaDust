#include <Wire.h>
#include <AHT20.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_NeoPixel.h>
#include <TinyGPSPlus.h>

AHT20 aht20;
Adafruit_BMP280 bmp;
TinyGPSPlus gps;
Adafruit_NeoPixel strip(12, 14, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600,SERIAL_8N1,26,27);
  Serial2.begin(9600);
  Wire.begin();
  aht20.begin();
  bmp.begin();
  strip.begin();
  strip.show();
  strip.setBrightness(10);
}

void loop() {
  float t  = aht20.getTemperature(); // 온도
  float h  = aht20.getHumidity(); //습도
  for (int i = 0; i < 4; i++) { //aht20 에서 온습도를 가져오면 네오픽셀 불빛의 0~3번이 켜집니다 
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
  }
  float p  = bmp.readPressure();
  float a = bmp.readAltitude(1010.6);
  for (int i = 4; i < 8; i++) { //bmp280 에서 기압과 고도를 가져오면 네오픽셀 불빛의 4~7번이 켜집니다 
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
  }
  Serial.println("온도: "+String(t)+"습도: "+String(h)+"현재기압: "+String(p*0.01)+"고도: "+String(a));
  for (int i = 8; i < 11; i++) {  //온습도,기압,고도가 시리얼에 프린트되면 네오픽셀 불빛의 8~10번이 켜집니다 
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
  }
  
  
  Serial1.print(String(t) + '\a' + String(h) + '\t' + String(p) + '\n' + String(a) + '\p') ;
  GPS_Process();  
  if(Serial.available()) { 
  char buffer[64]; 
  int bytesRead = Serial.readBytesUntil('\n', buffer, sizeof(buffer));
  Serial1.write(buffer, bytesRead); 
  }
  if(Serial1.available()){ 
    Serial.print(Serial1.read());
  }
  delay(1000);
  strip.setPixelColor(11, strip.Color(255, 255, 255)); //수신기 시리얼에 데이터 전송을 완료하면 네오픽셀 불빛의 11번이 켜집니다
  strip.show();
  strip.clear();
}

void GPS_Process() {
  while(Serial2.available()) {
    gps.encode(Serial2.read());
  }
  
  Serial.print("Lat : ");
  Serial.print(gps.location.lat(),6);
  Serial.print("Lng : ");
  Serial.print(gps.location.lng(),6);

  Serial1.print(gps.location.lat(),6);
  Serial1.print('\v');
  Serial1.print(gps.location.lng(),6);
  Serial1.print('\b');
}

