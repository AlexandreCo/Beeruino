#include <ds7505.h>

// DS7505 
// by Alexandre Coffignal <http://www. ... .com>

// Demonstrates use of the DS7505 library
// Reads data from an I2C/TWI DS7505 slave device

// Created 26 October 2010

#include <Wire.h>

DS7505 ds7505 = DS7505();

void setup()
{
    Wire.begin();        // join i2c bus (address optional for master)
    Serial.begin(9600);  // start serial for output
    ds7505.config(7, R12BITS);
}

void loop()
{
    int iTemp = ds7505.getTemp(7);
    Serial.print(iTemp/100,DEC);
    Serial.print(".");
    Serial.print(iTemp%100,DEC);
    unsigned int uiReg=ds7505.readReg(7, REG_TEMP);
    Serial.print(" ");
    Serial.print(uiReg);
    uiReg=ds7505.readReg(7, REG_CONFIG);
    Serial.print(" ");
    Serial.print(uiReg,HEX);
    uiReg=ds7505.readReg(7, REG_THYST);
    Serial.print(" ");
    Serial.print(uiReg);
    uiReg=ds7505.readReg(7, REG_TOS);
    Serial.print(" ");
    Serial.println(uiReg);

    ds7505.setTHyst(7, 12345);

    ds7505.setTOS(7, 9876);

    delay(500);

}

