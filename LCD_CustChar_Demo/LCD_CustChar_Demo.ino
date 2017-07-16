// 1. for I2C communication to the LCD
#include <Wire.h>

// 2. for the LCD functions
#include <LiquidCrystal_I2C.h>

// Hexadecimal address of the LCD unit
#define I2C_ADDR 0x3F

// Tell the LCD what type we have (eg 16 x 2 or 20 x 4)
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

// 5 bits wide x 8 bits high
uint8_t custChar[8] = {
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

uint8_t testChar[8] = {0x8,0xf4,0x8,0x43,0x4,0x4,0x43,0x0};

// ------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------
void setup()
{
  // Serial monitoring on PC (debug only)
  Serial.begin(9600);

  // Initialise the LCD: turn on backlight and ensure cursor top left
  lcd.begin();
  lcd.backlight();
  delay(500);

  // Create char map
  lcd.createChar(0, testChar);

  // Test it out
  lcd.home();
  lcd.print("Temp: 24");
  lcd.print((char)0);
}

void loop()
{

}

