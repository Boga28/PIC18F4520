#include "definitions.h" 
#include "ucregisters.h" 
#ifndef SPI_H
#define SPI_H     
              
void SPI_Master_Init();   
uint8_t SPI_transfer(uint8_t); 
void CS_ENABLE(); 
void CS_DISABLE();   


                    
#endif  //SPI_H   
