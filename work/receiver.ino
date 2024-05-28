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
  Serial.println("LABEL,Date,Time,Tem,Hum,Pres");
}

void loop() {
  if (Serial1.available()) {
    u8g2.clearBuffer();	
    String m1 = Serial1.readStringUntil('\d');
    String m2 = Serial1.readStringUntil('\t');
    String m3 = Serial1.readStringUntil('\n');

    float value1 = m1.toFloat();
    float value2 = m2.toFloat();
    float value3 = m3.toFloat();

    Serial.print("DATA,DATE,TIME,");
    Serial.print(value1); Serial.print(","); Serial.print(value2); Serial.print(","); Serial.println(value3);
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
  delay(1500);
}
