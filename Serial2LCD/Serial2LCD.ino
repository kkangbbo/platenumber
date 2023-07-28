#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
char plate[5];
void setup() {
  // initialize serial:
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("plate number");
  
  lcd.setCursor(0,1);

  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(20);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.println(inputString);
    /**************************************/
    if(inputString.substring(0,3)=="num")
    {
      String plate = inputString.substring(3);
      Serial.println(plate);
      lcd.print(plate);
      lcd.setCursor(3,1);
      lcd.print(" ");
      lcd.setCursor(0,1);

    }
    /*else
    {
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
    }*/
    /**************************************/
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
