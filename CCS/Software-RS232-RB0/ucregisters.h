#ifndef UCREGISTER_H
#define UCREGISTER_H
           
//Control PINS
#byte TRISB   = 0x0F93
#byte PORTB   = 0x0F81

#bit  UART_TX_DIR = TRISB.1   //TX
#bit  UART_RX_DIR = TRISB.0   //RX
                              
#bit  UART_TX = PORTB.1       //TX   
#bit  UART_RX = PORTB.0       //RX   

#bit  LED_DIR = TRISB.2       //TX   
#bit  LED = PORTB.2       //RX  
                 
                         
//OSILATOR - 8MHZ
#byte OSCCON = 0x0FD3       
#bit  IRCF2 =OSCCON.6  
#bit  IRCF1 =OSCCON.5                     
#bit  IRCF0 =OSCCON.4 
       
//TIMER1 INTERRUPT BYTE adresleri
#byte ADCON1 = 0x0FC1    
#byte INTCON = 0x0FF2  // INTCON REGISTER
#byte INTCON2=0x0FF1   //                                                                                            
                                             
#bit INTCON_INT0IF=INTCON.1      //RB0 enable  
#bit INTCON_INT0IE=INTCON.4      //RB0 enable
#bit INTCON_GIE_GIEH = INTCON.7  // Global Interrupt Enable bit  
                    
#endif UCREGISTER_H                                                                         
