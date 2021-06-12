#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#define address 0x48   //I2C address of MCP9802 
LiquidCrystal_I2C lcd(0x20,16,2);

int TempByte1, TempByte2;
 
void setup()
{
Wire.begin();
Serial.begin(9600);
lcd.init(); 
 
// Write to Configuration Register 
Wire.beginTransmission(address);
Wire.write(0x01);  // Address to Configuration register
Wire.write(0x64);  // ADC resolution: 12-bit,
Wire.endTransmission();
}
 
 
void loop()
{
 
// Read temperature 
Wire.beginTransmission(address);
Wire.write((byte)0x00);    // Pointer to temperature register
Wire.endTransmission();
 
Wire.beginTransmission(address);
Wire.requestFrom(address, 2);  // Now read two bytes of temperature data
if (Wire.available()) {
  TempByte1 = Wire.read();
  TempByte2 = Wire.read();
 
  int Temperature = ((TempByte1 << 8) | TempByte2);
  Temperature = Temperature >> 4;
  float TempC = 1.0*Temperature*0.0625;
  float TempF = TempC*1.8+32.0;
  Serial.print(" Temperature= ");
  Serial.print(TempC);
  Serial.print(" C, ");
  Serial.print(TempF);
  Serial.println(" F");
  lcd.setCursor(0, 0);
  lcd.print(TempC);
  lcd.setCursor(6, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print(TempF);
  lcd.setCursor(6, 1);
  lcd.print("F");
}
else{
  Serial.println("No response ");
}
Wire.endTransmission();
delay(1000);
}
