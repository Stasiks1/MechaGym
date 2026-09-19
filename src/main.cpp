#include <Arduino.h>
#include <M5StickCPlus.h>

int gameState = 0;
unsigned long waitStart = 0;
unsigned long randomDelay = 0;
unsigned long reactionStart = 0;

int speed = 0;

int appMode = 0;

int gymCursor = 1;

float accX, accY, accZ;

void runReactionGame() {
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
                M5.Lcd.setCursor(10, 50);
                M5.Lcd.setTextColor(WHITE, MAGENTA);
                M5.Lcd.setTextSize(3);
                M5.Lcd.print("FALSE START!");
                M5.Beep.tone(1000, 200);
                delay(1500);

                M5.Lcd.fillScreen(BLUE);
                M5.Lcd.setCursor(20, 50);
                M5.Lcd.setTextColor(WHITE, BLUE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.print("PRESS A TO START!");
                gameState = 0;
            }
            if (millis() - waitStart >= randomDelay) {
                M5.Lcd.fillScreen(GREEN);
                M5.Lcd.setCursor(10, 50);
                M5.Lcd.setTextColor(BLACK, GREEN);
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

                M5.Lcd.setCursor(10, 60);
                M5.Lcd.setTextSize(2);

                if (reactionTime < 5) {
                    M5.Lcd.setTextColor(PURPLE, BLACK);
                    M5.Lcd.print("IMPOSSIBLE! 🤖");
                } else if (reactionTime < 200) {
                    M5.Lcd.setTextColor(GREEN, BLACK);
                    M5.Lcd.print("CYBER GOD! ⚡");
                } else if (reactionTime < 320) {
                    M5.Lcd.setTextColor(CYAN, BLACK);
                    M5.Lcd.print("FAST! 🏎️");
                } else {
                    M5.Lcd.setTextColor(RED, BLACK);
                    M5.Lcd.print("TOO SLOW! 🐢");
                }

                delay(3000);

                M5.Lcd.fillScreen(BLUE);
                M5.Lcd.setCursor(20, 50);
                M5.Lcd.setTextColor(WHITE, BLUE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.print("PRESS A TO START!");
                gameState = 0;
            }
            break;
    }
}

void updateSpeedUI() {
    M5.Lcd.fillScreen(BLACK);

    if (speed >= 80) M5.Lcd.setTextColor(RED, BLACK);
    else M5.Lcd.setTextColor(GREEN, BLACK);

    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print(speed);

    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 55);

    if (speed == 0) {
        M5.Lcd.setTextColor(BLUE, BLACK);
        M5.Lcd.print("PARKED");
    } else if (speed > 0 && speed < 80) {
        M5.Lcd.setTextColor(GREEN, BLACK);
        M5.Lcd.print("DRIVE");
    } else if (speed >= 80) {
        M5.Lcd.setTextColor(RED, BLACK);
        M5.Lcd.print("OVERHEAT!");
    }
}

void runSpeedDash() {
    if (M5.BtnA.wasPressed()) {
        speed += 10;
        if (speed > 100) speed = 100;
        M5.Beep.tone(3500, 30);
        updateSpeedUI();
    }

    if (M5.BtnB.wasPressed()) {
        speed -= 10;
        if (speed < 0) speed = 0;
        M5.Beep.tone(1500, 30);
        updateSpeedUI();
    }
}

void runBubleLevel() {
    int ballX = 120 + (accX * 80);
    int ballY = 67 + (accY * 80);
    ballX = constrain(ballX, 10, 230);
    ballY = constrain(ballY, 10, 125);

    M5.Lcd.fillScreen(BLACK);

    M5.Lcd.drawCircle(120, 67, 15, GREEN);

    uint16_t ballColor = (abs(accX) < 0.08 && abs(accY) < 0.08) ? GREEN : RED;
    M5.Lcd.fillCircle(ballX, ballY, 8, ballColor);

    delay(20);
}

void drawGymMenu() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(YELLOW, BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(20, 10);
    M5.Lcd.print("=== MECHA GYM ===");

    const char* list[3] = {
        "1. SPEED DASH",
        "2. REACTION GAME",
        "3. SHAKE DICE"
    };

    for (int i = 0; i < 3; i++) {
        M5.Lcd.setCursor(15, 45 + (i * 25));
        if (gymCursor == (i + 1)) {
            M5.Lcd.setTextColor(GREEN, BLACK);
            M5.Lcd.printf("> %s", list[i]);
        } else {
            M5.Lcd.setTextColor(WHITE, BLACK);
            M5.Lcd.printf("  %s", list[i]);
        }
    }
}

void setup() {
  M5.begin();
  M5.Imu.Init();
  M5.Lcd.setRotation(3);
  drawGymMenu();
}

void loop() {
  M5.update();
  M5.Beep.update();
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  float totalAcc = abs(accX) + abs(accY) + abs(accZ);

 if (appMode != 0 && M5.BtnB.wasReleasefor(700)) {
        appMode = 0;
        drawGymMenu();
    }
switch (appMode) {
        case 0:
            if (M5.BtnB.wasPressed()) {
                gymCursor++;
                if (gymCursor > 3) gymCursor = 1;
                drawGymMenu();
            }
            if (M5.BtnA.wasPressed()) {
                appMode = gymCursor;
                M5.Lcd.fillScreen(BLACK);
                if (appMode == 1) updateSpeedUI();
                if (appMode == 2) {
                    M5.Lcd.fillScreen(BLUE);
                    M5.Lcd.setCursor(20, 50);
                    M5.Lcd.setTextColor(WHITE, BLUE);
                    M5.Lcd.setTextSize(2);
                    M5.Lcd.print("PRESS A TO START!");
                }
            }
            break;

        case 1:
            runSpeedDash();
            break;

        case 2:
            runReactionGame();
            break;

        case 3:
            runBubleLevel();
            break;
    }
}