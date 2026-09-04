#include <Arduino.h>
#include <M5StickCPlus.h>

int speed = 0;
void updateDashboard() {
  M5.Lcd.fillScreen(BLACK);
  if (speed >= 80) {
    M5.Lcd.setTextColor(RED, BLACK);
  }
    else {
    M5.Lcd.setTextColor(GREEN, BLACK);
     }
  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(10,10);
  M5.Lcd.print(speed);
  if (speed == 0) {
    M5.Lcd.setTextColor(BLUE, BLACK);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(10, 50);
    M5.Lcd.print("PARKED");
  }
    else if (speed > 0 && speed < 80) {
    M5.Lcd.setTextColor(GREEN, BLACK);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(10, 50);
    M5.Lcd.print("DRIVE");
    }
    else if (speed >= 80) {
    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(10, 50);
    M5.Lcd.print("OVERHEAT!");
    }
    }

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10,10);
  M5.Lcd.print("Hello, User!");
}

void loop() {
  M5.update();
  M5.Beep.update();
  if (M5.BtnA.wasPressed()) {
      speed += 10;
      if (speed > 100) {
      speed = 100;
      }
      M5.Beep.tone(3500, 30);
      updateDashboard();
    
  }
  if (M5.BtnB.wasPressed()) {
      speed -= 10;
      if (speed < 0) {
      speed = 0;
    }
    M5.Beep.tone(1500, 30);
    updateDashboard();
  }
}

