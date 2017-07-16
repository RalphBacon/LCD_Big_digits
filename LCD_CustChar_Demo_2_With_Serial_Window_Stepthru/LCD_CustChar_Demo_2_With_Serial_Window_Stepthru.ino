// 1. for I2C communication to the LCD
#include <Wire.h>

// 2. for the LCD functions
#include <LiquidCrystal_I2C.h>

// Hexadecimal address of the LCD unit
#define I2C_ADDR 0x27 //0x3F for 16 x 2 units

// Tell the LCD what type we have (eg 16 x 2 or 20 x 4)
LiquidCrystal_I2C lcd(I2C_ADDR, 20, 4);

// Define the bit patters for each of our custom chars. These
// are 5 bits wide and 8 dots deep
uint8_t custChar[8][8] = {
  {31, 31, 31, 0, 0, 0, 0, 0},      // Small top line - 0
  {0, 0, 0, 0, 0, 31, 31, 31},      // Small bottom line - 1
  { B11111,
    B00000,
    B00000,
    B00000,                         // This shows an alternative
    B00000,                         // way of defining a custome character,
    B00000,                         // a bit more 'visually' perhaps?
    B00000,
    B11111,
  },
  //{31, 0, 0, 0, 0, 0, 0, 31},     // Small lines top and bottom -2
  {0, 0, 0, 0, 0, 0,  0, 31},       // Thin bottom line - 3
  {31, 31, 31, 31, 31, 31, 15, 7},  // Left bottom chamfer full - 4
  {28, 30, 31, 31, 31, 31, 31, 31}, // Right top chamfer full -5
  {31, 31, 31, 31, 31, 31, 30, 28}, // Right bottom chamfer full -6
  {7, 15, 31, 31, 31, 31, 31, 31},  // Left top chamfer full -7
};

// Define our numbers 0 thru 9
// 254 is blank and 255 is the "Full Block"
uint8_t bigNums[10][6] = {
  {7, 0, 5, 4, 1, 6},         //0
  {0, 5, 254, 1, 255, 1},     //1
  {0, 2, 5, 7, 3, 1},         //2
  {0, 2, 5, 1, 3, 6},         //3
  {7, 3, 255, 254, 254, 255}, //4
  {7, 2, 0, 1, 3, 6},         //5
  {7, 2, 0, 4, 3, 6},         //6
  {0, 0, 5, 254, 7, 254},   //7
  {7, 2, 5, 4, 3, 6},         //8
  {7, 2, 5, 1, 3, 6},         //9
};

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

  // Test it out
  lcd.home();
  lcd.print("Hello Arduino Fans!");
  lcd.setCursor(2, 2);
  lcd.print("Large LCD fonts?");

  //Pause here until a character is sent from the Serial Monitor window
  Serial.println("Enter any character in the field above and click send!");
  while (!Serial.available()) {}
  while (Serial.available()) {Serial.read();}

  // Clear the screen
  lcd.clear();

  // Demo Part 1 - the custom characters
  // Create custom character map (8 characters only!)
  for (int cnt = 0; cnt < sizeof(custChar) / 8; cnt++) {
    lcd.createChar(cnt, custChar[cnt]);
  }

  // Print all the special chars out
  //  for (int cnt = 0; cnt < 8; cnt++) {
  //    lcd.print((char)cnt);
  //  }

  // Now print the numbers 0 to 9
  // Format is: number2print, startCol, startRow
  printBigNum(0, 0, 0);
  printBigNum(1, 4, 0);
  printBigNum(2, 8, 0);
  printBigNum(3, 12, 0);
  printBigNum(4, 16, 0);
  printBigNum(5, 0, 2);
  printBigNum(6, 4, 2);
  printBigNum(7, 8, 2);
  printBigNum(8, 12, 2);
  printBigNum(9, 16, 2);

  // Manually enter a decimal point (or whatever) at our desired location
  // using a standard built in character (not a custom character)
  // It will overwrite anything in that position on screen (in this demo
  // it is being written into a space character position)
  lcd.setCursor(8, 3);
  //lcd.print((char) 44); //46 = period , 161 = larger empty period
  lcd.print(",");

  //Pause here until a character is sent from the Serial Monitor window
  Serial.println("Enter any character in the field above and click send!");
  while (!Serial.available()) {}

  // Demo part 2 - temperature
  lcd.clear();

  lcd.print("CURRENT LOUNGE TEMP");
  lcd.setCursor(16, 2);
  lcd.print((char)161);
  lcd.setCursor(16, 3);
  lcd.print("C");
  lcd.setCursor(11, 3);
  lcd.print(",");
  printBigNum(2, 4, 2);
  printBigNum(4, 8, 2);
  printBigNum(9, 12, 2);

  while (true) {
    for (int cnt = 8; cnt >= 0; cnt--) {
      delay(1000);
      printBigNum(cnt, 12, 2);
    }

    for (int cnt = 1; cnt <= 9; cnt++) {
      delay(1000);
      printBigNum(cnt, 12, 2);
    }
  }
}

// -----------------------------------------------------------------
// Print big number over 2 lines, 3 colums per half digit
// -----------------------------------------------------------------
void printBigNum(int number, int startCol, int startRow) {

  // Position cursor to requested position (each char takes 3 cols plus a space col)
  lcd.setCursor(startCol, startRow);

  // Each number split over two lines, 3 chars per line. Retrieve character
  // from the main array to make working with it here a bit easier.
  uint8_t thisNumber[6];
  for (int cnt = 0; cnt < 6; cnt++) {
    thisNumber[cnt] = bigNums[number][cnt];
  }

  // First line (top half) of digit
  for (int cnt = 0; cnt < 3; cnt++) {
    lcd.print((char)thisNumber[cnt]);
  }

  // Now position cursor to next line at same start column for digit
  lcd.setCursor(startCol, startRow + 1);

  // 2nd line (bottom half)
  for (int cnt = 3; cnt < 6; cnt++) {
    lcd.print((char)thisNumber[cnt]);
  }
}

// -----------------------------------------------------------------
// LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP
// -----------------------------------------------------------------
void loop() {
  // Nothing to do here (compiler will probably remove this method)
}

