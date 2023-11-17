#ifndef INITS_H
#define INITS_H      

extern uint16_t iSayac; 
typedef union{  
   uint8_t  all;      // Type  kayitciya erismek icin
   struct{
      uint8_t _2ms    : 1;  //bit:0, 2ms 
      uint8_t _20ms   : 1;  //bit:1, 20ms 
      uint8_t _50ms   : 1;  //bit:2, 50ms 
      uint8_t _100ms  : 1;  //bit:3, 100ms    
      uint8_t _200ms  : 1;  //bit:4, 200ms                  
      uint8_t _500ms  : 1;  //bit:5, 500ms 
      uint8_t _1000ms : 1;  //bit:6, 1000ms 
      uint8_t _500us  : 1;  //bit:7, 500us
   }tmr1_flags;                    
}tmr1_time_t;   
extern tmr1_time_t tmr1_time;    




                                               
#endif //INIT_H                              
