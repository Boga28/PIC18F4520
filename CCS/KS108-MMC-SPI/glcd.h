#include "definitions.h"    
#include "ucregisters.h" 
#include "fonts.h"  
#ifndef GLCD_H       
#define GLCD_H   
//EARTH ANIMATION SDCARD POSITION                             
const uint8_t startSector = 39;
const uint16_t sectorSize = 397; 
extern uint16_t sectorPosition;  
// BUFFER FOR DISPLAY                                       
extern uchar_t GLCD_BUFFER[512]; 


// DISPALY IMAGE FUNCTION                        
void GLCD_DrawTop(); 
void GLCD_DrawBottom(); 

// DISPLAY CHAR
void GLCD_StringChar(uint8_t); 
                                    
// WRITE COUNTRY NAME  
void GLCD_StringCenterOfDisp(uint8_t *, uchar_t); 

// CONTROL METHODS   
void GLCD_Init();   
void GLCD_Command(uchar_t cmd);
void GLCD_Char(uchar_t data);
void GLCD_Clear();
void CS1FUN();
void CS2FUN();
                 
void NOP();      
#endif //GLCD_H                           
