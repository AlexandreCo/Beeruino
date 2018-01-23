/* ========================================================================== */
/*                                                                            */
/*  Hyst.h - hysteresis temperature regulation            .                   */
/*  Created by Alexandre C., January 24, 2018.                                */
/*  Released into the public domain.                                          */
/*                                                                            */
/* ========================================================================== */


#ifndef Hyst_h
#define Hyst_h

#include "Arduino.h"


class Hyst
{
private:
    int _iCsg;
    int _iTemp;
    uint8_t _uchHyst;
    bool _bOutState;
    int _iPinNumber;

public:
    Hyst( int );
    int run(int16_t);
    void setHyst(uint8_t);
    void setCsg(int16_t);
    int getCurrentCsg(void);
    bool bOutState();
    int iCsg(void);
    uint8_t uchHyst(void);

};

#endif
