#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- PIN DEFINITIONS ---
#define BLUE_LED   2
#define GREEN_LED  4
#define ORANGE_LED 18
#define RED_LED    19

const int buttonPin1 = 27; // NEXT
const int buttonPin2 = 14; // PREVIOUS / BACK
const int buttonPin3 = 12; // ENTER

// --- BUTTON STATE VARIABLES ---
int B1State = HIGH, lastB1State = HIGH;
int B2State = HIGH, lastB2State = HIGH;
int B3State = HIGH, lastB3State = HIGH;

// --- MENU STATE VARIABLES ---
int menuIndex = 0;
int subMenuIndex = -1;
int subSubMenuIndex = -1;

// --- MENU ITEM COUNTS ---
const int totalMenus = 3;
const int totalSubMenus = 4;

// --- NON-BLOCKING ACTION VARIABLES ---
unsigned long lastActionTime = 0;
int animationStep = 0;
bool blinkState = false;

// === FORWARD DECLARATION ===
void handleActiveActions();

// === DISPLAY FUNCTIONS (Unchanged) ===
void showMainMenu(int menuNum) {
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(ORANGE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  subMenuIndex = -1;
  subSubMenuIndex = -1;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("--- MAIN MENU ---");
  display.setCursor(20, 15);
  display.println("Blink LED");
  display.setCursor(20, 25);
  display.println("Toggle LED");
  display.setCursor(20, 35);
  display.println("Animation LED");
  switch(menuNum) {
    case 0: display.setCursor(10, 15); break;
    case 1: display.setCursor(10, 25); break;
    case 2: display.setCursor(10, 35); break;
  }
  display.println(">");
  display.display();
}

void showSubMenu(int menuNum, int subMenuNum) {
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(ORANGE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  subMenuIndex = subMenuNum;
  subSubMenuIndex = -1;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  switch(menuNum) {
    case 0: display.println("--- Blink LED ---"); break;
    case 1: display.println("--- Toggle LED ---"); break;
    case 2: display.println("--- Animation LED ---"); break;
  }
  switch(menuNum) {
    case 0: case 1:
      display.setCursor(20, 15); display.println("Blue LED");
      display.setCursor(20, 25); display.println("Green LED");
      display.setCursor(20, 35); display.println("Orange LED");
      display.setCursor(20, 45); display.println("Red LED");
      break;
    case 2:
      display.setCursor(20, 15); display.println("Scanner Animation");
      display.setCursor(20, 25); display.println("Fill Up Animation");
      display.setCursor(20, 35); display.println("Converge Animation");
      display.setCursor(20, 45); display.println("Flash Animation");
      break;
  }
  switch(subMenuNum) {
    case 0: display.setCursor(10, 15); break;
    case 1: display.setCursor(10, 25); break;
    case 2: display.setCursor(10, 35); break;
    case 3: display.setCursor(10, 45); break;
  }
  display.println(">");
  display.display();
}

void showSubSubMenu(int menuNum, int subMenuNum) {
  subSubMenuIndex = 0;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  lastActionTime = millis();
  animationStep = 0;
  blinkState = true;
  display.setCursor(0, 0);
  display.print("Action: ");
  switch(menuNum) {
    case 0: display.println("Blinking"); break;
    case 1: display.println("Toggling"); break;
    case 2: display.println("Animation"); break;
  }
  if (menuNum == 1) {
    switch(subMenuNum) {
      case 0: digitalWrite(BLUE_LED, HIGH); break;
      case 1: digitalWrite(GREEN_LED, HIGH); break;
      case 2: digitalWrite(ORANGE_LED, HIGH); break;
      case 3: digitalWrite(RED_LED, HIGH); break;
    }
  }
  String line1 = "Press Enter";
  String line2 = "to go Back";
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(line1, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, 40);
  display.println(line1);
  display.getTextBounds(line2, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, 52);
  display.println(line2);
  display.display();
}

// ==========================================================
// THIS IS THE CORRECTED AND MORE RELIABLE SETUP FUNCTION
// ==========================================================
void setup() {
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(ORANGE_LED, LOW);
  digitalWrite(RED_LED, LOW);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  Serial.begin(115200);

  // Give power a moment to stabilize before talking to the display
  delay(250); 

  // Initialize the display. Use the Serial Monitor to check for failure.
  // If it fails, try changing the I2C address from 0x3C to 0x3D.
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  
  // This sequence "wakes up" the display controller for sure.
  display.display(); // Send the empty buffer
  delay(100);
  display.clearDisplay(); // Clear it again
  display.display();
  delay(100);

  // --- SPLASH SCREEN ---
  // Now, the display is guaranteed to be ready.
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(27, 27);
  display.println("WELCOME");
  display.display();
  delay(2000);
  
  // Finally, show the main menu
  showMainMenu(menuIndex);
}

void loop() {
  B1State = digitalRead(buttonPin1);
  B2State = digitalRead(buttonPin2);
  B3State = digitalRead(buttonPin3);

  if (subSubMenuIndex != -1) {
    handleActiveActions();
    if (B3State == LOW && lastB3State == HIGH) {
      showSubMenu(menuIndex, subMenuIndex);
      delay(200);
    }
  } else if (subMenuIndex != -1) {
    if (B1State == LOW && lastB1State == HIGH) {
      subMenuIndex++;
      if (subMenuIndex >= totalSubMenus) subMenuIndex = 0;
      showSubMenu(menuIndex, subMenuIndex);
      delay(200);
    }
    if (B2State == LOW && lastB2State == HIGH) {
      if (subMenuIndex == 0) showMainMenu(menuIndex);
      else {
        subMenuIndex--;
        showSubMenu(menuIndex, subMenuIndex);
      }
      delay(200);
    }
    if (B3State == LOW && lastB3State == HIGH) {
      showSubSubMenu(menuIndex, subMenuIndex);
      delay(200);
    }
  } else {
    if (B1State == LOW && lastB1State == HIGH) {
      menuIndex++;
      if (menuIndex >= totalMenus) menuIndex = 0;
      showMainMenu(menuIndex);
      delay(200);
    }
    if (B2State == LOW && lastB2State == HIGH) {
      menuIndex--;
      if (menuIndex < 0) menuIndex = totalMenus - 1;
      showMainMenu(menuIndex);
      delay(200);
    }
    if (B3State == LOW && lastB3State == HIGH) {
      showSubMenu(menuIndex, 0);
      delay(200);
    }
  }

  lastB1State = B1State;
  lastB2State = B2State;
  lastB3State = B3State;
}

void handleActiveActions() {
  switch (menuIndex) {
    case 0:
      if (millis() - lastActionTime > 400) {
        lastActionTime = millis();
        blinkState = !blinkState;
        switch (subMenuIndex) {
          case 0: digitalWrite(BLUE_LED, blinkState); break;
          case 1: digitalWrite(GREEN_LED, blinkState); break;
          case 2: digitalWrite(ORANGE_LED, blinkState); break;
          case 3: digitalWrite(RED_LED, blinkState); break;
        }
      }
      break;
    case 2:
      if (millis() - lastActionTime > 150) {
        lastActionTime = millis();
        animationStep++;
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(ORANGE_LED, LOW);
        digitalWrite(RED_LED, LOW);
        switch (subMenuIndex) {
          case 0:
            if (animationStep > 5) animationStep = 0;
            if (animationStep == 0) digitalWrite(BLUE_LED, HIGH);
            if (animationStep == 1) digitalWrite(GREEN_LED, HIGH);
            if (animationStep == 2) digitalWrite(ORANGE_LED, HIGH);
            if (animationStep == 3) digitalWrite(RED_LED, HIGH);
            if (animationStep == 4) digitalWrite(ORANGE_LED, HIGH);
            if (animationStep == 5) digitalWrite(GREEN_LED, HIGH);
            break;
          case 1:
            if (animationStep > 4) animationStep = 0;
            if (animationStep >= 1) digitalWrite(BLUE_LED, HIGH);
            if (animationStep >= 2) digitalWrite(GREEN_LED, HIGH);
            if (animationStep >= 3) digitalWrite(ORANGE_LED, HIGH);
            if (animationStep >= 4) digitalWrite(RED_LED, HIGH);
            break;
          case 2:
            if (animationStep > 3) animationStep = 0;
            if (animationStep == 0) { digitalWrite(BLUE_LED, HIGH); digitalWrite(RED_LED, HIGH); }
            if (animationStep == 1) { digitalWrite(GREEN_LED, HIGH); digitalWrite(ORANGE_LED, HIGH); }
            if (animationStep == 2) { digitalWrite(ORANGE_LED, HIGH); digitalWrite(GREEN_LED, HIGH); }
            if (animationStep == 3) { digitalWrite(RED_LED, HIGH); digitalWrite(BLUE_LED, HIGH); }
            break;
          case 3:
            if (animationStep > 1) animationStep = 0;
            if (animationStep == 0) {
              digitalWrite(BLUE_LED, HIGH);
              digitalWrite(GREEN_LED, HIGH);
              digitalWrite(ORANGE_LED, HIGH);
              digitalWrite(RED_LED, HIGH);
            }
            break;
        }
      }
      break;
  }
}
