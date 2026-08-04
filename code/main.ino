//AUTHOR :- Sasidu Wishshanka

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <Keypad.h>

//---------------- RFID ----------------
#define SS_PIN 5
#define RST_PIN 4
MFRC522 rfid(SS_PIN, RST_PIN);

//---------------- Servo ----------------
Servo doorServo;
#define SERVO_PIN 13

//---------------- Buzzer ----------------
#define BUZZER 15

//---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

//---------------- Keypad ----------------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {32, 33, 25, 26};
byte colPins[COLS] = {27, 14, 12, 21};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//------------- Correct UID -------------
byte correctUID[4] = {0xF9, 0x57, 0xD4, 0x11};

//------------- Password ---------------
String password = "1234";
String input = "";

//------------ Buzzer ------------------
void beep()
{
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
  delay(200);

  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
}

//----------- Door Open ----------------
void openDoor()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Door Open");

 // Slowly Open (90° -> 20°)
for (int pos = 80; pos >= 20; pos--) {
  doorServo.write(pos);
  delay(20);   
}

delay(5000);

// Slowly Close (20° -> 90°)
for (int pos = 20; pos <= 90; pos++) {
  doorServo.write(pos);
  delay(20);   
}

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Door Closed");

  delay(2000);
}

//-------------- Setup -----------------
void setup()
{
  Serial.begin(115200);

  SPI.begin(18,19,23,5);
  rfid.PCD_Init();


  Wire.begin(22,16);

  lcd.init();
  lcd.backlight();

  doorServo.attach(SERVO_PIN);
  doorServo.write(90);

  pinMode(BUZZER,OUTPUT);
  digitalWrite(BUZZER,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("System Ready");
  delay(2000);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Smart Door");
  delay(2000);

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Door Closed");
  delay(2000);
}

void loop()
{
  // Main Screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID Scan");
  lcd.setCursor(0, 1);
  lcd.print("Enter PIN");

  // ---------- RFID ----------
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    bool cardOK = true;

    for (byte i = 0; i < 4; i++)
    {
      if (rfid.uid.uidByte[i] != correctUID[i])
      {
        cardOK = false;
      }
    }

    if (cardOK)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access OK");

      openDoor();
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access Denied");

      beep();
      delay(1500);
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  // ---------- Keypad ----------
  char key = keypad.getKey();

  if (key)
  {
    if (key >= '0' && key <= '9')
    {
      input += key;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PIN:");
      lcd.setCursor(0, 1);

      for (int i = 0; i < input.length(); i++)
      {
        lcd.print("*");
      }
    }

    // Confirm PIN
    else if (key == '#')
    {
      if (input == password)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PIN OK");

        delay(1000);

        openDoor();
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong PIN");
        lcd.setCursor(0, 1);
        lcd.print("Access Denied");

        beep();

        delay(2000);
      }

      input = "";
    }

    // Clear PIN
    else if (key == '*')
    {
      input = "";

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PIN Cleared");

      delay(1000);
    }
  }

  delay(100);
}
