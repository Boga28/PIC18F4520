#ifndef DS1820_C
#define DS1820_C  

#include "1wire.h" 
#include "1wire.c" 

/*#define Input           1
#define Output          0
#define ReadROM         0x33
#define MatchROM        0x55
#define SkipROM         0xCC
#define SearchROM       0xF0
#define AlarmSearch     0xEC
#define ConvertT        0x44
#define ReadScratchpad  0xBE
#define WriteScratchpad 0x4E
#define CopyScratchpad  0x48
#define RecallEE        0xB8                                 
#define ReadPowerSupply 0xB4
#define DevicesNumber   1 */ 

void ds1820_read(); 
void ds1820_configure(uchar_t TH, uchar_t TL, uchar_t config);
uchar_t TEMPBF[10];  
uchar_t period;   //10s period
  
                                   
                                                  
/*
 * ds1820_read()             
 * Description: reads the ds18x20 device on the 1-wire bus and returns
 *              the temperature                                                  
 */

void ds1820_read() {                                       
    uint8_t busy=0, temp1, temp2;
    sint16_t temp3; 
                 
    //ds1820_configure(0x00, 0x00, 0x00);     //9 bit resolution

    onewire_reset();                     
    onewire_write(0xCC);            //Skip ROM, address all devices
    onewire_write(0x44);            //Start temperature conversion

    while(busy == 0)                //Wait while busy (bus is low)
        busy = onewire_read();    
                  
    onewire_reset();
    onewire_write(0xCC);            //Skip ROM, address all devices
    onewire_write(0xBE);            //Read scratchpad     
    
      
    temp1 = onewire_read();         
    temp2 = onewire_read(); 
                        
    temp3 = temp2;
    temp3 = temp1 + (temp3 << 8);
    temp3 = (sint16_t) temp3 / 16;
    //result = (float) temp3 / 2.0;   //Calculation for DS18S20 with 0.5 deg C resolution
    sprintf(TEMPBF,"TEMP :%Ld",temp3); 
    memset(strLCD,0,32);
    memcpy(strLCD,TEMPBF,9); 
    period=0;                  
}
    
/*
 * ds1820_configure(int8 TH, int8 LH, int8 config)
 * Description: writes configuration data to the DS18x20 device
 * Arguments: alarm trigger high, alarm trigger low, configuration
 */                                                                               

void ds1820_configure(int8 TH, int8 TL, int8 config) {
    onewire_reset();
    onewire_write(0xCC);            //Skip ROM, address all devices
    onewire_write(0x4E);            //Write to scratchpad
    onewire_write(TH);
    onewire_write(TL);
    onewire_write(config);
}


#endif /*DS1820_C*/                              
