🔐 Smart Door Lock System using ESP32

A secure Smart Door Lock System built with ESP32, RFID RC522, 4x4 Keypad, 16x2 I2C LCD, SG90 Servo Motor, and Buzzer. The system allows authorized users to unlock the door using either a registered RFID card or a PIN code.

---

📌 Features

- 🔑 RFID card authentication
- 🔢 4x4 Keypad password authentication
- 📺 16×2 I2C LCD status display
- 🚪 Automatic door lock/unlock using SG90 Servo
- 🔔 Buzzer alerts for unauthorized access
- ✅ Correct RFID card grants access
- ✅ Correct PIN ("1234#") grants access
- ❌ Wrong card or PIN displays Access Denied and activates the buzzer
- 🔄 Door automatically closes after a few seconds

---

🛠️ Components Used

- ESP32 DevKit V1
- MFRC522 RFID Reader
- RFID Card / Tag
- 4×4 Matrix Keypad
- 16×2 I2C LCD Display
- SG90 Servo Motor
- Active Buzzer
- External 5V Power Supply (Recommended for Servo)
- Jumper Wires
- Breadboard

---

🔌 Pin Connections

RFID RC522

RC522 Pin| ESP32 Pin
SDA (SS)| GPIO 5
SCK| GPIO 18
MOSI| GPIO 23
MISO| GPIO 19
RST| GPIO 4
3.3V| 3.3V
GND| GND

Servo Motor

Servo Pin| ESP32
Signal| GPIO 13
VCC| External 5V
GND| GND (Common Ground)

Buzzer

Buzzer| ESP32
+| GPIO 15
-| GND

4×4 Keypad

Keypad Pin| ESP32
R1| GPIO 32
R2| GPIO 33
R3| GPIO 25
R4| GPIO 26
C1| GPIO 27
C2| GPIO 14
C3| GPIO 12
C4| GPIO 21

I2C LCD

LCD Pin| ESP32
SDA| GPIO 22
SCL| GPIO 16
VCC| 5V
GND| GND

---

🔄 System Workflow

1. LCD displays System Ready.
2. LCD displays Smart Door.
3. LCD displays Door Closed.
4. User can:
   - Scan an RFID card, or
   - Enter a PIN using the keypad.
5. If the RFID UID matches the registered card:
   - LCD shows Access OK.
   - Door opens.
   - After 5 seconds, the door closes automatically.
6. If the RFID card is invalid:
   - LCD shows Access Denied.
   - Buzzer beeps twice.
7. If the entered PIN is 1234#:
   - LCD shows PIN OK.
   - Door opens.
8. If the PIN is incorrect:
   - LCD shows Wrong PIN and Access Denied.
   - Buzzer beeps twice.

---

📚 Arduino Libraries

Install the following libraries before uploading the code:

- MFRC522
- SPI
- ESP32Servo
- Keypad
- LiquidCrystal_I2C
- Wire

---

🚀 Future Improvements

- Store multiple RFID cards.
- Change PIN using the keypad.
- Firebase or Blynk integration.
- Mobile notifications.
- Access log with date and time.
- Fingerprint sensor support.
- Wi-Fi remote monitoring.

---

👨‍💻 Author

Sasidu Wishshanka

GitHub: https://github.com/Sasidu-Tech
