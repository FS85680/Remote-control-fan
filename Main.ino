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
