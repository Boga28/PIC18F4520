#ifndef USART_RS232_H                                                                                               
#define USART_RS232_H   
 
extern uchar_t rxData[32];
extern uchar_t txData[32];
extern uchar_t data_in;
extern uint8_t rxData_count;
extern uchar_t terminal_text1[15];                
extern uchar_t terminal_text2[27];                              
extern uchar_t terminal_text3[17];      
extern uint8_t terminal_text1_Count,terminal_text2_Count,terminal_text3_Count,terminal_text4_Count;
extern uint8_t terminal_text1_size,terminal_text2_size ,terminal_text3_size,terminal_text4_size; 
extern uint8_t noKbHit_count;  
extern uint8_t switchTerminal_position;  
extern uint8_t UART_BUSY;

                                  
typedef union{                 
   uint8_t  all;      // Type  kayitciya erismek icin
   struct{ 
      uint8_t noKbhit              : 1;  //bit:0, no data for 5 seconds  
      uint8_t enter_flag           : 1;  //bit:1, Text executed / Texts are cleared,                                    
      uint8_t recieve_exceed       : 1;  //bit:2, LCD- character exceed / 1-Exceed
      uint8_t terminal_text1_flag  : 1;  //bit:3, Text 1 write / 1-DONE  //MEVCUT YAZI 
      uint8_t terminal_text2_flag  : 1;  //bit:4, Text 2 write / 1-DONE  //Lutfen bir yazi giriniz:            
      uint8_t terminal_text3_flag  : 1;  //bit:5, Text 3 write / 1-DONE  //Limit Asildi!!!
      uint8_t terminal_text4_flag  : 1;  //bit:6, Text 4 write / 1-DONE  //LCD
      uint8_t terminal_text_done   : 1;  //bit:6, Texts are DONE / 1-DONE     
   }stUSARTF;                                      
}unUSARTF_t;   
extern unUSARTF_t unUSARTF;    

uchar_t USART_RxCharBuffer();
void USART_TxCharBuffer();
void USART_Init();
void rs232t();    
                                                  
#endif  //USART_RS232_H
                 