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
  case 1:
  if (M5.BtnA.wasPressed()) {
    M5.Lcd.fillScreen(MAGENTA);
    M5.Lcd.setCursor(10,50);
    M5.Lcd.setTextColor(RED, MAGENTA);
    M5.Lcd.setTextSize(3);
    M5.Lcd.print("FALSE START!");
    M5.Beep.tone(1000, 200);
    delay(1500);
    gameState = 0;
  }
  if (millis() - waitStart >= randomDelay){
    M5.Lcd.fillScreen(GREEN);
    M5.Lcd.setCursor(10,50);
    M5.Lcd.setTextColor(RED, GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.print("FIRE! PRESS A!");
    M5.Beep.tone(4000, 60);
    reactionStart = millis();
    gameState = 2;
  }
  break;
  case 2:
  if (M5.BtnA.wasPressed()) {
    unsigned long reactionTime = millis() - reactionStart;
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(YELLOW, BLACK);
    M5.Lcd.printf("%lu ms", reactionTime);
  
  if (reactionTime < 200) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 50);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(GREEN, BLACK);
    M5.Lcd.print("CYBER GOD!");
  }
  else if (reactionTime < 320 && reactionTime > 200) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 50);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(YELLOW, BLACK);
    M5.Lcd.print("FAST!");
  }
  else {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 50);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.print("TOO SLOW!");
  }
  gameState = 0;
  }
break;
}
}
