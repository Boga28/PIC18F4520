#ifndef DS1820_H
#define DS1820_H 
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

                                       
extern uchar_t DevicesFound; // Number of devices found 
extern uchar_t queue;  
void searchRom(); 

                
void ds1820_read(); 
void ds1820_read_from_rom(uchar_t *);
void ds1820_configure(uchar_t TH, uchar_t TL, uchar_t config);  
extern uchar_t TEMPBF[32];  
extern sint16_t tempHeat;  
extern sint16_t heat1,heat2,heat3;   

                                       
                                       
 


#endif //DS1820_H
                    