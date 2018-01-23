/* ========================================================================== */
/*                                                                            */
/*  Hyst.h - hysteresis temperature regulation            .                   */
/*  Created by Alexandre C., January 24, 2018.                                */
/*  Released into the public domain.                                          */
/*                                                                            */
/* ========================================================================== */

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "hyst.h"


/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/

Hyst::Hyst( int uchPinNumber ){
    _iPinNumber=uchPinNumber;
    pinMode(_iPinNumber, OUTPUT);
    _bOutState=false;
}

/******************************************************************************
 * User functions
 ******************************************************************************/
int Hyst::run(int16_t iTemp){
    _iTemp=iTemp;

    if(_bOutState==true){
        digitalWrite(_iPinNumber, HIGH);
        //en chauffe
        if(_iTemp>(_iCsg+_uchHyst)){
            _bOutState=false;
        }
    }else{
        // pas de chauffe
        digitalWrite(_iPinNumber, LOW);
        if(_iTemp<(_iCsg-_uchHyst)){
            _bOutState=true;
        }
    }
    return _bOutState;
}

void Hyst::setHyst(uint8_t uchHyst){
    _uchHyst=uchHyst;
}

void Hyst::setCsg(int16_t iCsg){
    _iCsg=iCsg;
}

int Hyst::getCurrentCsg(void){
    if(_bOutState==true){
        return _iCsg+_uchHyst;
    }else{
        return _iCsg-_uchHyst;
    }
}

bool Hyst::bOutState(void){
    return _bOutState;
}

uint8_t Hyst::uchHyst(void){
    return _uchHyst;
}

int Hyst::iCsg(void){
    return _iCsg;
}

