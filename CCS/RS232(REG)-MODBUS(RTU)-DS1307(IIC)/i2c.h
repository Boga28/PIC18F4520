#include "definitions.h" 

#ifndef I2C_H
#define I2C_H     

void I2C_Init();           
void _I2C_Start(void);       
void _I2C_ReStart(void);    
void _I2C_Stop(void);              
void _I2CACK(void);  
void _I2CNACK(void);
void _I2C_WAIT(void);
uchar_t _I2C_Write_Byte(uchar_t);  
uchar_t _I2C_Read_Byte(uchar_t);           
              
#endif //I2C_H     
