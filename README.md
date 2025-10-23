# ESP32-OLED-Menu-System
A multi-level menu system for an ESP32 with an OLED display and 4 LEDs.

# ESP32-OLED-Menu-System

This project is a comprehensive, multi-level menu system for an ESP32, using a 128x64 SSD1306 OLED display and three push-buttons for navigation. It's designed to be a robust template for controlling various outputs (like LEDs) through a clean, non-blocking interface.

This was a passion project that involved over 8 hours of coding, 2 days of UI/UX planning, and debugging over 400 lines of code.

![Demo GIF](https://i.imgur.com/your-demo.gif)
*(You can replace the link above by uploading your video or a GIF of the project!)*

---

## Features

* **Multi-Level Menu:** A clean state-machine logic allows for a Main Menu, Sub-Menus, and Action screens.
* **3-Button Navigation:** Simple and intuitive "Next," "Previous/Back," and "Enter" controls.
* **Non-Blocking Code:** The `handleActiveActions()` function runs animations and blinking without using `delay()`, so the menu is always responsive.
* **Splash Screen:** A "WELCOME" message on startup.
* **Multiple LED Modes:**
    * **Blink:** Make a single LED blink.
    * **Toggle:** Turn a single LED on or off.
    * **Animations:** Run one of four pre-programmed animations using all LEDs.

---

## Hardware Required

* 1 x ESP32 Development Board
* 1 x SSD1306 128x64 I2C OLED Display
* 4 x 5mm LEDs (I used Blue, Green, Orange, and Red)
* 3 x Tactile Push-Buttons
* 4 x 220Ω Resistors (for the LEDs)
* 1 x Breadboard
* Jumper Wires

---

## Wiring Diagram

| Component | ESP32 Pin |
| :--- | :--- |
| **OLED SCL** | GPIO 22 |
| **OLED SDA** | GPIO 21 |
| **Blue LED** | GPIO 2 |
| **Green LED** | GPIO 4 |
| **Orange LED** | GPIO 18 |
| **Red LED** | GPIO 19 |
| **Button 1 (Next)** | GPIO 27 |
| **Button 2 (Previous)** | GPIO 14 |
| **Button 3 (Enter)** | GPIO 12 |

*Note: All buttons are wired with `INPUT_PULLUP`. Connect one side of the button to the GPIO pin and the other side to **GND**.*

---

## Software & Libraries

This project was written in the Arduino C/C++ environment (using the Arduino IDE).

You will need to install the following libraries from the Arduino Library Manager:
* `Adafruit_GFX`
* `Adafruit_SSD1306`

The `Wire.h` library is built-in.

---

## How to Use

1.  **Power On:** The device will show a "WELCOME" splash screen and then load the Main Menu.
2.  **Main Menu:**
    * **Next Button:** Scrolls down (Blink -> Toggle -> Animation).
    * **Previous Button:** Scrolls up.
    * **Enter Button:** Selects the highlighted option and moves to its Sub-Menu.
3.  **Sub-Menu:**
    * **Next Button:** Scrolls down the list of options (e.g., Blue LED, Green LED, etc.).
    * **Previous Button:** Scrolls up or, if at the first item, goes back to the Main Menu.
    * **Enter Button:** Selects the highlighted action (e.g., "Blink Blue LED").
4.  **Action Screen:**
    * The selected action (blink, animation, etc.) will begin.
    * **Enter Button:** Stops the action and returns you to the previous Sub-Menu.
