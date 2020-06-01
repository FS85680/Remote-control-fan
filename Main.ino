#include <Arduino.h>
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
double angle_rad = PI / 180.0;
double angle_deg = 180.0 / PI;
IRrecv irrecv_12(12);
char ircode_12[64];
void setupIrReceiver(IRrecv irrecv) {
  irrecv.enableIRIn();
  irrecv.resume();
}
void charsToUpper(char * str) {
    int p = 0;
    while (str[p] != 0) {
        str[p] = toupper(str[p]);
        ++p;
    }
}
String getIrCommand(IRrecv irrecv, char * receivedCommand) {
    decode_results result;
    if (irrecv.decode( & result)) {
        ltoa(result.value, receivedCommand, 16);
        charsToUpper(receivedCommand);
        irrecv.resume();
    } else {
        receivedCommand[0] = '\0';
    }
    return String(receivedCommand);
}
byte getLCDaddress() {
    Wire.begin();
    byte LCDaddress = 0x27;
    Wire.beginTransmission(LCDaddress);
    byte resultNumber = Wire.endTransmission();
    if (resultNumber == 0) {
        return LCDaddress;
    } else {
        LCDaddress = 0x3F;
    }
    Wire.beginTransmission(LCDaddress);
    resultNumber = Wire.endTransmission();
    if (resultNumber == 0) {
        return LCDaddress;
    }
}
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
void setup() {
    setupIrReceiver(irrecv_12);
    pinMode(11, OUTPUT);
    analogWrite(11, 255);
    lcd = LiquidCrystal_I2C(getLCDaddress(), 16, 2);
    lcd.begin();
    lcd.backlight();
    lcd.clear();
    lcd.home();
    lcd.print("     Welcome");
}
void loop() {
    if (!((getIrCommand(irrecv_12, ircode_12)) == (""))) {
        lcd.clear();
        lcd.home();
        lcd.print("Status: OFF ");
        lcd.setCursor(0, 1);
        lcd.print("Speed: 0");
        analogWrite(11, 255);
    }
    if ((getIrCommand(irrecv_12, ircode_12)) == ("FF906F")) {
        lcd.clear();
        lcd.home();
        lcd.print("Status: ON  ");
        lcd.setCursor(0, 1);
        lcd.print("Speed: 1");
        analogWrite(11, 200);
        delay(0.4 * 1000);
    } else {
        if ((getIrCommand(irrecv_12, ircode_12)) == ("FFC23D")) {
            lcd.clear();
            lcd.home();
            lcd.print("Status: OFF ");
            lcd.setCursor(0, 1);
            lcd.print("Speed: 0");
            analogWrite(11, 255);
            delay(0.4 * 1000);
        }
    }
    if ((getIrCommand(irrecv_12, ircode_12)) == ("FF30CF")) {
        lcd.clear();
        lcd.home();
        lcd.print("Status: ON  ");
        lcd.setCursor(0, 1);
        lcd.print("Speed: 1");
        analogWrite(11, 200);
    } else {
        if ((getIrCommand(irrecv_12, ircode_12)) == ("FF18E7")) {
            lcd.clear();
            lcd.home();
            lcd.print("Status: ON  ");
            lcd.setCursor(0, 1);
            lcd.print("Speed: 2");
            analogWrite(11, 150);
        } else {
            if ((getIrCommand(irrecv_12, ircode_12)) == ("FF7A85")) {
                lcd.clear();
                lcd.home();
                lcd.print("Status: ON  ");
                lcd.setCursor(0, 1);
                lcd.print("Speed: 3");
                analogWrite(11, 60);
            } else {
                if ((getIrCommand(irrecv_12, ircode_12)) == ("FF10EF")) {
                    lcd.clear();
                    lcd.home();
                    lcd.print("Status: ON  ");
                    lcd.setCursor(0, 1);
                    lcd.print("Speed: 4");
                    analogWrite(11, 0);
                }
            }
        }
    }
}
