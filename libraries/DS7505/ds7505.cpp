/* ========================================================================== */
/*                                                                            */
/*  DS7505.cpp - Library for MAXIM DS7505 temperature sensor.                 */
/*  Created by Alexandre C, October 26, 2010.                         */
/*  Released into the public domain.                                          */
/*                                                                            */
/* ========================================================================== */

/******************************************************************************
 * Includes
 ******************************************************************************/


#include <Wire.h>
#include "ds7505.h"


/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/

DS7505::DS7505( void )
{

}

/******************************************************************************
 * User functions
 ******************************************************************************/

//todo negative temperature
int DS7505::getTemp(uint8_t ucAddress)
{
    unsigned int uiMesure = measure(ucAddress);
    unsigned long temp=((long)uiMesure*125)/320;
    return(int) temp; //return temp * 100 to avoid float values
}

uint16_t DS7505::measure(uint8_t ucAddress)
{
    unsigned char ds7505[2];
    Wire.requestFrom(DS7505_BASE+ucAddress, 2);
    char i=0;
    while(Wire.available())    // slave may send less than requested
    {
        ds7505[i++]=Wire.read();
    }
    return ((int)ds7505[0]<<8)+ds7505[1];
}

void DS7505::config(uint8_t ucAddress, uint8_t ucConfig)
{
    //ADDR_BYTE + 0x01 + DATA_CONFIG
    Wire.beginTransmission(DS7505_BASE+ucAddress);
    Wire.write(REG_CONFIG);
    Wire.write(ucConfig);
    Wire.endTransmission();
    Wire.beginTransmission(DS7505_BASE+ucAddress);
    Wire.write(REG_TEMP);
    Wire.endTransmission();
}

void DS7505::setTHyst(uint8_t ucAddress,uint16_t uiTHyst)
{
    //ADDR_BYTE + 0x01 + DATA_CONFIG
    Wire.beginTransmission(DS7505_BASE+ucAddress);
    Wire.write(REG_THYST);
    Wire.write((uint8_t)(uiTHyst>>8));
    Wire.write((uint8_t)(uiTHyst&0xFF));
    Wire.endTransmission();
    Wire.beginTransmission(DS7505_BASE+ucAddress);
    Wire.write(REG_TEMP);
    Wire.endTransmission();
}

void DS7505::setTOS(uint8_t ucAddress,uint16_t uiTOS)
{
    //ADDR_BYTE + 0x01 + DATA_CONFIG
    Wire.beginTransmission(DS7505_BASE+ucAddress);
    Wire.write(REG_TOS);
    Wire.write((uint8_t)(uiTOS>>8));
    Wire.write((uint8_t)(uiTOS&0xFF));
    Wire.endTransmission();
    Wire.beginTransmission(DS7505_BASE+ucAddress);
    Wire.write(REG_TEMP);
    Wire.endTransmission();
}

uint16_t DS7505::readReg(uint8_t ucAddress,uint8_t ucReg)
{
    uint8_t ds7505[2];
    Wire.beginTransmission(DS7505_BASE+ucAddress);
    Wire.write(ucReg);
    Wire.endTransmission();
    if(ucReg==REG_CONFIG)
        Wire.requestFrom(DS7505_BASE+ucAddress, 1);
    else
        Wire.requestFrom(DS7505_BASE+ucAddress, 2);

    uint8_t i=0;
    while(Wire.available())    // slave may send less than requested
    {
        ds7505[i++]=Wire.read();
    }
    Wire.beginTransmission(DS7505_BASE+ucAddress);
    Wire.write(REG_TEMP);
    Wire.endTransmission();
    if(i==2)
        return ((uint16_t)ds7505[0]<<8)+ds7505[1];
    else
        return ds7505[0];
}

void DS7505::recallData(uint8_t ucAddress)
{
    Wire.beginTransmission(DS7505_RECALL);
    Wire.write(ucAddress);
    Wire.endTransmission();

}

void DS7505::copyData(uint8_t ucAddress)
{
    Wire.beginTransmission(DS7505_COPY);
    Wire.write(ucAddress);
    Wire.endTransmission();
}

void DS7505::softPOR(uint8_t ucAddress)
{
    Wire.beginTransmission(DS7505_POR);
    Wire.write(ucAddress);
    Wire.endTransmission();
}


