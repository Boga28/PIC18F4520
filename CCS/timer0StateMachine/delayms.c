#include <delayms.h>            
  
void delayMsFun(uint16_t msecs)  // Delay function - generates a delay of specified msecs
{   uint16_t i,j; 
    for(i=0;i<=msecs;i++){              
      for(j=0;j<197;j++);
    }                               
}                                     