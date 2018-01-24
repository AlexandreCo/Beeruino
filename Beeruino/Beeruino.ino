// Beeruino
// by Alexandre C <http://www. ... .com>



#include <Wire.h>
#include <ds7505.h>
#include <hyst.h>
#include <AnalogButton.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

DS7505 ds7505 = DS7505();
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Hyst hyst(13);
AnalogButton button = AnalogButton();

typedef enum{
    eciStateInitDisplay,
    eciStateDisplay,
    eciStateInitConfigCsg,
    eciStateConfigCsg,
    eciStateInitConfigHyst,
    eciStateConfigHyst,
    eciStateInitAbout,
    eciStateAbout,
    eciStateInitEEpromRead,
    eciStateEEpromRead,
}eState_t;

eState_t eState=eciStateDisplay;
#define ciCsgMax  9900
#define ciCsgMin  1000
#define ciCsgDfg  6500
#define cuchHystDfg  100

typedef struct{
    uint16_t ushBdt;
    int iTemp;
    uint16_t ushAddrEEpromWrite;
    uint16_t ushAddrEEpromRead;
}sData_t;

sData_t sPriv;

void setup(){
    Wire.begin();        // join i2c bus (address optional for master)
    Serial.begin(9600);  // start serial for output
    ds7505.config(7, R12BITS);
    lcd.begin(16, 2);              // start the library
    lcd.clear();
    hyst.setCsg(ciCsgDfg);
    hyst.setHyst(cuchHystDfg);
    sPriv.ushAddrEEpromWrite=0;
}


void loop(){
    sPriv.ushBdt++;
    vGetTemp();
    vState();
    hyst.run(sPriv.iTemp);
    vSaveTemp(sPriv.iTemp);
    delay(50);
}

void vSaveTemp(int iTemp){
    if(!(sPriv.ushBdt%300)){
        vSerialDisplayTemp(iTemp);
        EEPROM.update(sPriv.ushAddrEEpromWrite, iTemp/100);
        sPriv.ushAddrEEpromWrite++;
        if (sPriv.ushAddrEEpromWrite >= EEPROM.length()) {
            sPriv.ushAddrEEpromWrite = 0;
        }
    }
}

void vGetTemp(){
    if(!(sPriv.ushBdt%20)){
        sPriv.iTemp=ds7505.getTemp(7);
    }
}

void vSerialDisplayTemp(int iTemp){
    Serial.print(iTemp/100,DEC);
    Serial.print(".");
    Serial.print(iTemp%100,DEC);
    Serial.println("");
}

void vLcdDisplayTemp(uint8_t uchX, uint8_t uchY, int iTemp){
    lcd.setCursor(uchX,uchY);
    lcd.print("T:");
    lcd.print(iTemp/100,DEC);
    lcd.print(".");
    lcd.print(iTemp%100,DEC);
}

void vLcdDisplayEEprom(int iIdx, int iTemp){
    lcd.setCursor(0,0);
    lcd.print("EEPROM:");
    lcd.setCursor(0,1);
    lcd.print("@:");
    lcd.print(iIdx,DEC);
    lcd.print(":");
    lcd.print(iTemp,DEC);
}


void vLcdDisplayCsg(uint8_t uchX, uint8_t uchY){
    lcd.setCursor(uchX,uchY);
    lcd.print("C:");
    lcd.print(hyst.getCurrentCsg()/100,DEC);
}

void vLcdDisplayOut(uint8_t uchX, uint8_t uchY){
    lcd.setCursor(uchX,uchY);
    if(hyst.bOutState()==true){
        lcd.print("#");
    }else{
        lcd.print(" ");
    }
}

void vLcdDisplayAbout(uint8_t uchX, uint8_t uchY){
    lcd.setCursor(uchX,uchY);
    lcd.print("Beeruino");
}

void vLcdDisplayConfigCfg(uint8_t uchX, uint8_t uchY){
    lcd.setCursor(uchX,uchY);
    lcd.print("Csg : ");
    lcd.print(hyst.iCsg()/100);
}

void vLcdDisplayConfigHyst(uint8_t uchX, uint8_t uchY){
    lcd.setCursor(uchX,uchY);
    lcd.print("Hyst : ");
    lcd.print(hyst.uchHyst()/100);
    lcd.print(".");
    lcd.print(hyst.uchHyst()%100);
}

void vLcdDisplayTime(uint8_t uchX, uint8_t uchY){
    uint32_t ultime=millis()/1000;
    uint16_t ushSec, ushMin,ushHour;
    ushSec=ultime%60;
    ushMin=(ultime/60)%60;
    ushHour=(ultime/3600);
    lcd.setCursor(uchX,uchY);
    if(ushHour<10){
        lcd.print("0");
    }
    lcd.print(ushHour);
    lcd.print(":");
    if(ushMin<10){
        lcd.print("0");
    }
    lcd.print(ushMin);
    lcd.print(":");
    if(ushSec<10){
        lcd.print("0");
    }
    lcd.print(ushSec);
}

void vState(){
    switch (eState){
    case eciStateInitDisplay:
        vInitDisplay();
        break;
    case eciStateDisplay:
        vRunDisplay();
        break;

    case eciStateInitConfigCsg:
        vInitConfigCfg();
        break;
    case eciStateConfigCsg:
        vRunConfigCfg();
        break;

    case eciStateInitConfigHyst:
        vInitConfigHyst();
        break;
    case eciStateConfigHyst:
        vRunConfigHyst();
        break;

    case eciStateInitEEpromRead:
        vInitEepromRead();
        break;
    case eciStateEEpromRead:
        vRunEepromRead();
        break;



    case eciStateInitAbout:
        vInitAbout();
        break;
    case eciStateAbout:
        vRunAbout();
        break;
    }
}

void vInitDisplay(){
    switch(button.eRead()){
    case btnNONE:
        eState=eciStateDisplay;
        lcd.clear();
        break;
    default:
        break;
    }
}

void vRunDisplay(){
    switch(button.eRead()){
    case btnRIGHT:
        eState=eciStateInitConfigCsg;
        lcd.clear();
        break;
    default:
        vLcdDisplayTemp(0,0,sPriv.iTemp);
        vLcdDisplayCsg(10,0);
        vLcdDisplayOut(10,1);
        vLcdDisplayTime(0,1);
        break;
    }
}

void vInitConfigCfg(){
    switch(button.eRead()){
    case btnNONE:
        eState=eciStateConfigCsg;
        lcd.clear();
        break;
    default:
        break;
    }
}

void vRunConfigCfg(){
    switch(button.eRead()){
    case btnLEFT:
        eState=eciStateInitDisplay;
        lcd.clear();
        break;

    case btnRIGHT:
        eState=eciStateInitEEpromRead;
        lcd.clear();
        break;

    case btnUP:
        hyst.setCsg(hyst.iCsg()+100);
        if(hyst.iCsg()>ciCsgMax){
            hyst.setCsg(ciCsgMax);
        }
        vLcdDisplayConfigCfg(0,0);
        break;

    case btnDOWN:
        hyst.setCsg(hyst.iCsg()-100);
        if(hyst.iCsg()<ciCsgMin){
            hyst.setCsg(ciCsgMin);
        }
        vLcdDisplayConfigCfg(0,0);
        break;

    case btnSELECT:
        eState=eciStateInitConfigHyst;
        lcd.clear();
        break;

    default:
        vLcdDisplayConfigCfg(0,0);
        break;
    }
}

void vInitConfigHyst(){
    switch(button.eRead()){
    case btnNONE:
        eState=eciStateConfigHyst;
        lcd.clear();
        break;
    default:
        break;
    }
}

void vRunConfigHyst(){
    switch(button.eRead()){

    case btnUP:
        hyst.setHyst(hyst.uchHyst()+1);
        if(hyst.uchHyst()>250){
            hyst.setHyst(10);
        }
        break;

    case btnDOWN:
        hyst.setHyst(hyst.uchHyst()-1);
        if(hyst.uchHyst()<10){
            hyst.setHyst(250);
        }
        vLcdDisplayConfigHyst(0,0);
        break;

    case btnRIGHT:
        eState=eciStateInitEEpromRead;
        lcd.clear();
        break;

    case btnLEFT:
    case btnSELECT:
        lcd.clear();
        eState=eciStateInitDisplay;
        break;

    default:
        vLcdDisplayConfigHyst(0,0);
        break;
    }
}

void vInitEepromRead(){
    switch(button.eRead()){
    case btnNONE:
        eState=eciStateEEpromRead;
        lcd.clear();
        sPriv.ushAddrEEpromRead=0;
        vLcdDisplayEEprom(0, 0);
        break;
    default:
        break;
    }
}

void vRunEepromRead(){

    uint8_t ushValue;

    switch(button.eRead()){

    case btnUP:
        ushValue = EEPROM.read(sPriv.ushAddrEEpromRead);
        lcd.clear();
        vLcdDisplayEEprom(sPriv.ushAddrEEpromRead, ushValue);
        sPriv.ushAddrEEpromRead--;
        if (sPriv.ushAddrEEpromRead == 0) {
            sPriv.ushAddrEEpromRead = EEPROM.length()-1;
        }
        break;

    case btnDOWN:
        lcd.clear();
        ushValue = EEPROM.read(sPriv.ushAddrEEpromRead);
        vLcdDisplayEEprom(sPriv.ushAddrEEpromRead, ushValue);
        sPriv.ushAddrEEpromRead++;
        if (sPriv.ushAddrEEpromRead >= EEPROM.length()) {
            sPriv.ushAddrEEpromRead = 0;
        }
        break;

    case btnLEFT:
        lcd.clear();
        eState=eciStateInitConfigCsg;
        break;

    case btnSELECT:
        lcd.clear();
        eState=eciStateInitDisplay;
        break;

    default:

        break;
    }
}

void vInitAbout(){
    switch(button.eRead()){
    case btnNONE:
        eState=eciStateAbout;
        lcd.clear();
        break;
    default:
        break;
    }
}


void vRunAbout(){
    switch(button.eRead()){
    case btnLEFT:
        eState=eciStateInitConfigCsg;
        lcd.clear();
        break;
    default:
        vLcdDisplayAbout(0,0);
        break;
    }
}



