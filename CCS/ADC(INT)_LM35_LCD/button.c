
#include "definitions.h" 
#include "button.h"
uint8_t BUTTON_PRESSED_RELEASED;
uint8_t STATUS=0;            

uint8_t test_bit(uint8_t valueOfInput, uint8_t bits){ 
   return ((valueOfInput & (1<<bits)) != 0);
}                            
 
uint8_t button_debounce(uint8_t valueOfInput, uint8_t bit){
   if(!test_bit(valueOfInput,bit)){
      BUTTON_PRESSED_RELEASED<<=1;
   }else{                       
      BUTTON_PRESSED_RELEASED<<=1;                       
      BUTTON_PRESSED_RELEASED|=1;          
   }  
   if((BUTTON_PRESSED_RELEASED & 0x07)==0x07){ 
      STATUS = 1;
      return true;  
   }else if((BUTTON_PRESSED_RELEASED  & 0x07)==0x00){ 
      STATUS = 0;
      return false;
   }else{ 
      return STATUS;
   }
}        
