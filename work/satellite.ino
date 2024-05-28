#include <Wire.h>
#include <AHT20.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_NeoPixel.h>

AHT20 aht20;
Adafruit_BMP280 bmp;
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
  float t  = aht20.getTemperature();
  for (int i = 0; i < 4; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
  }
  float h  = aht20.getHumidity();
  for (int i = 4; i < 8; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
  }
  float p  = bmp.readPressure();
  for (int i = 8; i < 11; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
  }
  Serial.println("온도: "+String(t)+"습도: "+String(h)+" 현재기압: "+String(p*0.01));
  Serial1.print(String(t) + '\d' + String(h) + '\t' + String(p) + '\n') ;
  if(Serial.available()) { 
  char buffer[64]; 
  int bytesRead = Serial.readBytesUntil('\n', buffer, sizeof(buffer)); 
  Serial1.write(buffer, bytesRead); 
  }
  if(Serial1.available()){
    Serial.print(Serial1.read());
  }
  delay(1500);
  strip.setPixelColor(11, strip.Color(255, 255, 255));
  strip.show();
  strip.clear();
}

