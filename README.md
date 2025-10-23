# ESP32-OLED-Menu-System

This is a comprehensive, multi-level menu system for an ESP32, using a 128x64 SSD1306 OLED display and three push-buttons for navigation. It's designed as a robust template for controlling various outputs (like LEDs) through a clean, non-blocking interface.

This was a passion project that involved over 8 hours of coding, 2 days of UI/UX planning, and debugging over 400 lines of code to create a responsive and intuitive user experience.

https://www.linkedin.com/posts/iftikar-ju-etce_esp32-embeddedsystems-oled-activity-7386785487140859904-PD82?utm_source=share&utm_medium=member_desktop&rcm=ACoAAFehdUwBalCtYFh_MA3MIl1WJ41eG5qRr-4

---

## Features

* **Multi-Level Menu:** A clean state-machine logic allows for a Main Menu, Sub-Menus, and Action screens.
* **3-Button Navigation:** Simple and intuitive "Next," "Previous/Back," and "Enter" controls.
* **Non-Blocking Code:** The `handleActiveActions()` function runs animations and blinking using `millis()`, ensuring the user interface is always responsive.
* **Splash Screen:** A custom "WELCOME" message on startup.
* **Multiple LED Control Modes:**
    * **Blink:** Make a selected LED blink at a set interval.
    * **Toggle:** Turn a selected LED on (and off when backing out).
    * **Animations:** Run one of four pre-programmed animations using all four LEDs:
        1.  **Scanner:** A "Cylon" or "Knight Rider" style scanner.
        2.  **Fill Up:** LEDs light up one by one and stay on.
        3.  **Converge:** LEDs light up from the outside in.
        4.  **Flash:** All LEDs flash on and off together.

---

## Hardware Required

* 1 x ESP32 Development Board
* 1 x SSD1306 128x64 I2C OLED Display
* 4 x 5mm LEDs (Blue, Green, Orange, Red)
* 3 x Tactile Push-Buttons
* 4 x 220Ω Resistors (for the LEDs, one for each)
* 1 x Breadboard
* Jumper Wires

---

## Wiring Diagram

This code uses the default I2C pins for the ESP32.

| Component | ESP32 Pin |
| :--- | :--- |
| **OLED SCL** | GPIO 22 |
| **OLED SDA** | GPIO 21 |
| **Blue LED** | GPIO 2 |
| **Green LED** | GPIO 4 |
| **Orange LED**| GPIO 18 |
| **Red LED** | GPIO 19 |
| **Button 1 (Next)** | GPIO 27 |
| **Button 2 (Previous)** | GPIO 14 |
| **Button 3 (Enter)** | GPIO 12 |

**Button Wiring:** The buttons are configured with `INPUT_PULLUP`. Connect one side of each button to its corresponding GPIO pin and the other side to **GND**.

---

## Software & Libraries

This project was written in the Arduino C/C++ environment (using the Arduino IDE or PlatformIO).

You will need to install the following libraries from the Arduino Library Manager:
* `Adafruit_GFX`
* `Adaidfruit_SSD1306`

The `Wire.h` library (for I2C communication) is built-in with the ESP32 core.

---

## How to Use

1.  **Power On:** The device will show a "WELCOME" splash screen and then load the Main Menu.
2.  **Main Menu:**
    * **Next Button:** Scrolls down (Blink -> Toggle -> Animation).
    * **Previous Button:** Scrolls up.
    * **Enter Button:** Selects the highlighted option and moves to its Sub-Menu.
3.  **Sub-Menu:**
    * **Next Button:** Scrolls down the list of options (e.g., Blue LED, Green LED, etc., or Scanner, Fill Up, etc.).
    * **Previous Button:** Scrolls up. If at the first item, pressing "Previous" goes back to the Main Menu.
    * **Enter Button:** Selects the highlighted action and moves to the Action Screen.
4.  **Action Screen:**
    * The selected action (blink, animation, or toggle) will begin immediately.
    * The screen displays "Press Enter to go Back."
    * **Enter Button:** Stops the action, turns off all LEDs, and returns you to the previous Sub-Menu.
