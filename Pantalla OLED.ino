#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>


#define OLED_RESET 4
Adafruit_SSD1306 display (OLED_RESET);
void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
 
}

void loop() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("FUIMOS POR ONIGIRIS");
  display.display();
  
}
