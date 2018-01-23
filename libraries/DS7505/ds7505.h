/* ========================================================================== */
/*                                                                            */
/*  DS7505.h - Library for MAXIM DS7505 temperature sensor.                   */
/*  Created by Alexandre C, October 26, 2010.                         */
/*  Released into the public domain.                                          */
/*                                                                            */
/* ========================================================================== */


#ifndef DS7505_h
#define DS7505_h

#include "Arduino.h"



#define R09BITS  0x00	// 9 bits conversion max convertion time 25ms
#define R10BITS  0x20	// 10 bits conversion max convertion time 50ms
#define R11BITS  0x40	// 11 bits conversion max convertion time 100ms
#define R12BITS  0x60	// 12 bits conversion max convertion time 200ms

#define F1OUTOL  0x00	// 1 CONSECUTIVE OUT-OF-LIMITS CONVERSIONS TO TRIGGER O.S.
#define F2OUTOL  0x08	// 2 CONSECUTIVE OUT-OF-LIMITS CONVERSIONS TO TRIGGER O.S.
#define F4OUTOL  0x10	// 4 CONSECUTIVE OUT-OF-LIMITS CONVERSIONS TO TRIGGER O.S.
#define F6OUTOL  0x18	// 6 CONSECUTIVE OUT-OF-LIMITS CONVERSIONS TO TRIGGER O.S.

#define POL_HIGH  0x04	// Thermostat Output (O.S.) Polarity high
#define POL_LOW   0x00	// Thermostat Output (O.S.) Polarity low

#define TM_COMP  0x00	// Thermostat Operating Comparator mode
#define TM_INT   0x02	// Thermostat Operating Interrupt mode

#define SD_OFF    0x00	// Active conversion and thermostat operation
#define SD_ON     0x01	// Shutdown mode on

#define DS7505_BASE    0x48  // i2c bus base address
#define DS7505_COPY    0x48  // i2c bus copy address
#define DS7505_RECALL  0xB8  // i2c bus recall address
#define DS7505_POR     0x54  // i2c bus software por address

#define REG_TEMP    0x00  // Temperature reg address
#define REG_CONFIG  0x01  // config reg address
#define REG_THYST   0x02  // THyst reg address
#define REG_TOS     0x03  // TOs reg address

class DS7505
{
  private:


  public:
    DS7505( void );
    int getTemp(uint8_t);
    uint16_t measure(uint8_t);
    void config(uint8_t,uint8_t);
    void setTHyst(uint8_t,uint16_t);
    void setTOS(uint8_t,uint16_t);
    uint16_t readReg(uint8_t,uint8_t);
    void recallData(uint8_t);
    void copyData(uint8_t);
    void softPOR(uint8_t);
};

#endif
