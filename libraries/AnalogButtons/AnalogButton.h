/* ========================================================================== */
/*                                                                            */
/*  AnalogButton.h - analog button management            .                    */
/*  Created by Alexandre C., January 24, 2018.                                */
/*  Released into the public domain.                                          */
/*                                                                            */
/* ========================================================================== */


#ifndef AnalogButton_h
#define AnalogButton_h

#include "Arduino.h"

typedef enum{
    btnRIGHT=0,
    btnUP,
    btnDOWN,
    btnLEFT,
    btnSELECT,
    btnNONE,
}eBtn_t;

class AnalogButton
{
private:


public:
    AnalogButton( );
    eBtn_t eRead();
};

#endif

