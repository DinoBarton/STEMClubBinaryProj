#include <LiquidCrystal.h>

// Define the pins for the two LCDs
const int rs1 = 7, en1 = 6, d41 = 5, d51 = 4, d61 = 3, d71 = 2; // LCD1
const int rs2 = 13, en2 = 12, d42 = 11, d52 = 10, d62 = 9, d72 = 8; // LCD2

// Create two LCD objects
LiquidCrystal lcd1(rs1, en1, d41, d51, d61, d71);
LiquidCrystal lcd2(rs2, en2, d42, d52, d62, d72);

// Define the pins for the buttons (connected to analog pins)
const int button1 = A0; // Button to append '1'
const int button0 = A1; // Button to append '0'
const int buttonTranslate = A2; // Button to translate binary

// Variables to track button states
bool button1State = false, lastButton1State = false;
bool button0State = false, lastButton0State = false;
bool translateState = false, lastTranslateState = false;

// Strings to store binary sequence and final word
String binarySequence = "";
String finalWord = "";

void setup() {
  // Initialize the LCDs
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);

  // Configure the analog buttons as inputs
  pinMode(button1, INPUT);
  pinMode(button0, INPUT);
  pinMode(buttonTranslate, INPUT);

  // Clear the LCDs and start blank
  lcd1.clear();
  lcd2.clear();
}

void loop() {
  // Read the button states
  button1State = analogRead(button1) < 512; // Assume a LOW signal when pressed
  button0State = analogRead(button0) < 512;
  translateState = analogRead(buttonTranslate) < 512;

  // Append '1' if Button 1 is pressed
  if (button1State && !lastButton1State) {
    binarySequence += "1";
    updateLCD1();
  }
  lastButton1State = button1State;

  // Append '0' if Button 0 is pressed
  if (button0State && !lastButton0State) {
    binarySequence += "0";
    updateLCD1();
  }
  lastButton0State = button0State;

  // Translate binary to character and update LCD2
  if (translateState && !lastTranslateState) {
    translateToWord();
  }
  lastTranslateState = translateState;
}

// Function to update LCD1 with the binary sequence
void updateLCD1() {
  lcd1.setCursor(0, 1);
  if (binarySequence.length() > 16) {
    // Only display the last 16 characters
    lcd1.print(binarySequence.substring(binarySequence.length() - 16));
  } else {
    lcd1.print(binarySequence);
    lcd1.print("                "); // Clear trailing characters
  }
}

// Function to translate the binary sequence and append to the final word
void translateToWord() {
  if (binarySequence.length() == 8) {
    // Convert binary string to a character
    char character = strtol(binarySequence.c_str(), nullptr, 2);

    // Append the character to the final word
    finalWord += character;

    // Clear the binary sequence
    binarySequence = "";

    // Update both LCDs
    lcd1.clear();
    lcd2.setCursor(0, 1);
    if (finalWord.length() > 16) {
      // Only display the last 16 characters of the word
      lcd2.print(finalWord.substring(finalWord.length() - 16));
    } else {
      lcd2.print(finalWord);
    }
  } else if (binarySequence.length() > 0) {
    // Show an error message on LCD1 if sequence isn't 8 bits
    lcd1.clear();
    lcd1.print("Error: Need 8");
    delay(2000); // Pause to show the error
    lcd1.clear();
    updateLCD1(); // Return to binary display
  }
}
