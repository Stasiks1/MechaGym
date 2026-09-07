#include <Arduino.h>
#include <M5StickCPlus.h>

int gameState = 0;
unsigned long waitStart = 0;
unsigned long randomDelay = 0;
unsigned long reactionStart = 0;

int speed = 0;


void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setTextColor(GREEN, BLUE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(20,50);
  M5.Lcd.print("PRESS A TO START!");

}

void loop() {
  M5.update();
  M5.Beep.update();
  switch (gameState) {
  case 0:
  if (M5.BtnA.wasPressed()) {
    M5.Lcd.fillScreen(RED);
    M5.Lcd.setCursor(10, 50);
    M5.Lcd.setTextColor(WHITE, RED);
    M5.Lcd.setTextSize(3);
    M5.Lcd.print("WAIT!");
    randomDelay = random(2000, 5000);
    waitStart = millis();
    gameState = 1;
  }
  break;
  case 1:{};
}
}
