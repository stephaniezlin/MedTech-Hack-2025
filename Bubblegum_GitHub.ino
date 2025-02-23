#include <LiquidCrystal.h>
#include <math.h>

// LCD pin configuration
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Thermistor setup
const int ThermistorPin = A0;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  // Set LCD size (16 columns, 2 rows)
}

void loop() {
  int Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;  
  T = (T * 9.0) / 5.0 + 32.0; // Convert to Fahrenheit

  // Print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" F");

  // Check if temperature is above 120°F and update LCD
  lcd.setCursor(0, 0);  // Move to first row
  if (T > 120.0) {
    lcd.print("READY         ");  // Display "READY"
  } else {
    lcd.print("NOT READY     ");  // Display "NOT READY"
  }

  // Display temperature with "Temp:" on the second line
  lcd.setCursor(0, 1);  // Move to second row
  lcd.print("Temp: ");  
  lcd.print(T);
  lcd.print(" F  ");  // Extra spaces to clear old characters

  delay(1000); // Update every second
}