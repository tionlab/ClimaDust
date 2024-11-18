#include <U8g2lib.h>
#include <Wire.h>
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 26, 27);
  while (!Serial) delay(100);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  Serial.println("CLEARSHEET");
  Serial.println("LABEL,Date,Time,Tem,Hum,Pres,Alti,Lat,Lng");
}

void loop() {
  if (Serial1.available()) {
    u8g2.clearBuffer();	
    String m1 = Serial1.readStringUntil('\a'); //온도
    String m2 = Serial1.readStringUntil('\t'); //습도
    String m3 = Serial1.readStringUntil('\n'); //기압
    String m4 = Serial1.readStringUntil('\p'); //고도
    String m5 = Serial1.readStringUntil('\n'); //Lat
    String m6 = Serial1.readStringUntil('\p'); //Lng

    float value1 = m1.toFloat();
    float value2 = m2.toFloat();
    float value3 = m3.toFloat();
    float value4 = m4.toFloat();
    float value5 = m5.toFloat();
    float value6 = m6.toFloat();

    Serial.print("DATA,DATE,TIME,");
    Serial.print(value1); Serial.print(","); Serial.print(value2); Serial.print(","); Serial.println(value3); Serial.print(","); Serial.println(value4); Serial.print(","); Serial.println(value5); Serial.print(","); Serial.println(value6);
    u8g2.setCursor(0,15);
    u8g2.print("Temperature : " + m1);
    u8g2.setCursor(0,30);
    u8g2.print("Humidity : " + m2);
    u8g2.setCursor(0,45);
    u8g2.print("Pressure : " + m3);
    u8g2.setCursor(15,60);
    u8g2.print("Tion Satellite");
  }
  u8g2.sendBuffer();
  delay(1000);
}
