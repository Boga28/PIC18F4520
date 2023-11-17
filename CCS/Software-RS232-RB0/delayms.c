
#include "definitions.h" 
#include "delayms.h"
  
void delayMsFun(uint16_t msecs)  // Delay function - generates a delay of specified msecs
{   uint16_t i,j; 
    for(i=0;i<=msecs;i++){              
      for(j=0;j<197;j++);
    }                               
} 
void delayUsFun(uint32_t us)  // Delay function -  //1 tanesi 2.6us   
{   uint32_t i; 
    uchar_t j;       
    for(i=0;i<=us;i++){
    }                               
}  

