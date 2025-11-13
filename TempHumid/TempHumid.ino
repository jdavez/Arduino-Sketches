#include <Wire.h>
//#include <ACROBOTIC_SSD1306.h>
#include <U8x8lib.h>
#include "SparkFunHTU21D.h"
#include "Adafruit_SHT31.h"

//Create an instance of the object
HTU21D htu21;
Adafruit_SHT31 sht31 = Adafruit_SHT31();
char buf[64];

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);    
// On an arduino UNO/NANO:       A4(SDA), A5(SCL)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

/*
  Wire.begin();  
  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(0,0);              // Set cursor position, start of line 0
  oled.putString("HTU21D");
  oled.setTextXY(1,0);              // Set cursor position, start of line 1
  oled.putString(" tt.t C, hh.h%");
  oled.setTextXY(2,0);              // Set cursor position, start of line 2
  oled.putString("SHT31D");
  oled.setTextXY(3,0);             // Set cursor position, line 2 10th character
  oled.putString(" TT.T C, HH.H%");
*/

  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);

  htu21.begin();
  sht31.begin(0x44);

}

void loop() {
  // put your main code here, to run repeatedly:
  float humd = htu21.readHumidity();
  float temp = htu21.readTemperature();
  //snprintf(buf, sizeof(buf), "%.1f, %.1f%%", temp, humd);
  dtostrf(temp, 6, 1, buf);
  buf[6]='C'; buf[7]='\0';
  u8x8.drawString(0, 0, buf);

  dtostrf(humd, 6, 1, &buf[8]);
  buf[14]='%';
  buf[15]='\0';
  u8x8.drawString(0, 2, &buf[8]);
  /*
  oled.setTextXY(1,0);
  oled.putString(buf);
  */
  
  u8x8.refreshDisplay();  
  
  Serial.println(buf);
  delay(1000);

  float t = sht31.readTemperature();
  float h = sht31.readHumidity();
  //snprintf(buf, sizeof(buf), "%.1f, %.1f%%", t, h);
  dtostrf(t, 6, 1, buf);
  buf[6]='C'; buf[7]=',';
  buf[7]='\n'; u8x8.drawString(0, 4, buf);
  dtostrf(h, 6, 1, &buf[8]);
  buf[14]='%';
  buf[15]='\0';
  u8x8.drawString(0, 6, &buf[8]);
  /*
  oled.setTextXY(3,0);
  oled.putString(buf);
  */
  
  u8x8.refreshDisplay();
    
  Serial.println(buf);
  delay(1000);

}
