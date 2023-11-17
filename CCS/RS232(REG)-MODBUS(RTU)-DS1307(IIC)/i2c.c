#include "i2c.h"                                                                                        
#include "definitions.h"    
#include "ucregisters.h"        

void I2C_Init(){    
   SCL_DIR = 1;     //Set as a digital input
   SDA_DIR = 1;     //Set as a digital input
   SSPADD  = 19; 
   SSPCON1 = 0x28;  // enable I2C pins SCL and SDA for serial communication
   //SSPCON2 = 0x00;  
   SSPSTAT = 0x80;  //slew rate disabled for high speed control      
}           
          
void _I2C_WAIT(){
   while ( ( SSPCON2 & 0x1F ) || ( SSPSTAT & 0x04 ) );
   // wait for any pending transfer 
}                                    
// Function Purpose: I2C_Write_Byte transfers one byte 
uchar_t _I2C_Write_Byte(uchar_t data){              
   SSPBUF = data;      // Send Byte value
   while(BF);      // Wait for it to complete 
   _I2C_WAIT();
   return ACKSTAT;     // Return ACK/NACK from slave
}                           
                                        
// Function Purpose: I2C_Read_Byte reads one byte
uchar_t _I2C_Read_Byte(uchar_t flag){    
   uchar_t receive = 0;
   RCEN = 1;                    
   while(!BF);      // Wait for it to complete         
   receive = SSPBUF;    
   if(flag==0) 
      _I2CACK();                                     
   else
      _I2CNACK(); 
   _I2C_WAIT(); 
   return receive; // Return The Received Byte  
}    
  
void _I2C_Start(void){ 
   SEN = 1;         // Start condition enabled 
   while(SEN);      // automatically cleared by hardware 
                    // wait for start condition to finish  
}  

void _I2C_ReStart(void){
   RSEN = 1;         // Send Restart bit
   while(RSEN);      // Wait for it to complete
}                    
                                           
//Function : I2C_Stop sends stop bit sequence 
void _I2C_Stop(void){     
   PEN = 1;      // Initiate Stop condition on SDA and SCL pins 
   while(PEN);   // Wait for stop condition to finish 
                     // PEN automatically cleared by hardware 
}    

void _I2CACK(void){
   ACKDT = 0; //Acknowledge Data bit  
   ACKEN = 1;  // Acknowledge Sequence Enable bit   
   while(ACKEN);      // Wait for it to complete
}       

void _I2CNACK(void){
   ACKDT = 1;   
   ACKEN = 1; 
   while(ACKEN);      // Wait for it to complete    
}      
