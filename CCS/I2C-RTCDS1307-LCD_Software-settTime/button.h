#ifndef BUTTON_H                                                            
#define BUTTON_H 

extern uint8_t BUTTON_PRESSED_RELEASED_1,BUTTON_PRESSED_RELEASED_2,BUTTON_PRESSED_RELEASED_3;  /* bit:1, Aktif     */ 
extern uint8_t STATUS_B1, STATUS_B2, STATUS_B3; 
extern uint8_t bt_queue;
uint8_t button_debounce(uint8_t,uint8_t);   
uint8_t test_bit(uint8_t,uint8_t);  
  
#endif           