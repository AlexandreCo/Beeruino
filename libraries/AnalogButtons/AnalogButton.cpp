/* ========================================================================== */
/*                                                                            */
/*  AnalogButton.h - analog button management            .                    */
/*  Created by Alexandre C., January 24, 2018.                                */
/*  Released into the public domain.                                          */
/*                                                                            */
/* ========================================================================== */

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "AnalogButton.h"


/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/

AnalogButton::AnalogButton(){

}

/******************************************************************************
 * User functions
 ******************************************************************************/
// read the buttons
eBtn_t AnalogButton::eRead()
{
    int iAdcKeyIn  = 0;
    iAdcKeyIn = analogRead(0);
    Serial.print(iAdcKeyIn,DEC);
    Serial.println("");
    if (iAdcKeyIn > 1000) return btnNONE;
    if (iAdcKeyIn < 50)   return btnRIGHT;
    if (iAdcKeyIn < 250)  return btnUP;
    if (iAdcKeyIn < 450)  return btnDOWN;
    if (iAdcKeyIn < 650)  return btnLEFT;
    if (iAdcKeyIn < 850)  return btnSELECT;

    return btnNONE;  // when all others fail, return this...
}



