#ifndef UCREGISTER_H
#define UCREGISTER_H

                                                      
//Analog PINS           
#byte TRISA = 0x0F92    
#byte PORTA = 0x0F80  
#bit  PORTA_DIR_0=TRISA.0 
#bit  PORTA_0=PORTA.0  
#bit  PORTA_DIR_1=TRISA.1 
#bit  PORTA_1=PORTA.1          
                      
//Control PINS
#byte TRISB = 0x0F93     
#byte PORTB = 0x0F81  
#bit  PORTB_0=PORTB.0  
#bit  PORTB_7=PORTB.7   

// LCD PINS
//#byte TRISD = 0x0F95                     
//#byte PORTD = 0x0F8C                     
//#bit  PORTD_7=PORTD.7    

//LCD Control Pins
#byte TRISE = 0x0F96     
#byte PORTE = 0x0F84                       

  
//#byte TRISC = 0x0F94 
//#byte PORTC = 0x0F82            
//#bit  TRISC_6=TRISC.6 
//#bit  TRISC_7=TRISC.7  
                           
                     

                         
//OSILATOR - 8MHZ
#byte OSCCON = 0x0FD3       
#bit  IRCF2 =OSCCON.6  
#bit  IRCF1 =OSCCON.5                     
#bit  IRCF0 =OSCCON.4 
       
//TIMER1 INTERRUPT BYTE adresleri
   
#byte RCON = 0x0FD0    // RCON REGISTER
#byte INTCON = 0x0FF2  // INTCON REGISTER 
#byte IPR1 = 0x0F9F    // Cevresel kesme onceligi                         
#byte PIR1 = 0x0F9E    // Cevresel kesme istegi (Bayrak)
#byte PIE1 = 0x0F9D    // Cevresel kesme yetkisi 
#byte T1CON  = 0x0FCD  // TIMER1 kontrol kayitcisi 
#byte TMR1H = 0x0FCF   // TIMER1'in ta;ma sayacinin son 8 biti                                     
#byte TMR1L = 0x0FCE   // TIMER1'in ta;ma sayacinin ilk 8 biti
//   #############TIMER 1########                                                           
//# RCON  :: RCON REGISTER // Bit Adresleri                                    
#bit RCON_IPEN = RCON.7        // Enable priority levels on interrupts                   
//# INTCON  :: INTCON REGISTER // Bit Adresleri      
#bit INTCON_GIE_GIEH = INTCON.7  // Global Interrupt Enable bit 
#bit INTCON_PEIE = INTCON.6      // INTCON_PEIE=1, Enables all high priority interrupts
//# IPR1  :: IPR1 REGISTER // Bit Adresleri 
#bit IPR1_TMR1IP = IPR1.0  // TMR1 Overflow Interrupt Priority bit                                        
//# PIR1  :: PIR1 REGISTER // Bit Adresleri
#bit PIR1_TMR1IF=PIR1.0    // TMR1 Overflow Interrupt Flag bit    
//# PIE1  :: PIE1 REGISTER // Bit Adresleri 
#bit PIE1_TMR1IE=PIE1.0    // TMR1 Overflow Interrupt Enable bit     
//#T0CON  :: TIMER0 CONTROL REGISTER // Bit Adresleri
#bit T1CON_RD16    = T1CON.7     // 16-bit Read/Write Mode Enable bit
#bit T1CON_T1RUN   = T1CON.6     // Timer1 System Clock Status bit
#bit T1CON_T1CKPS1 = T1CON.5     // Timer1 Input Clock Prescale Select bits                             
#bit T1CON_T1CKPS0 = T1CON.4     // Timer1 Input Clock Prescale Select bits
#bit T1CON_T1OSCEN = T1CON.3     // Timer1 Oscillator Enable bit
#bit T1CON_T1SYNC  = T1CON.2     // Timer1 External Clock Input Synchronization Select bit
#bit T1CON_TMR1CS  = T1CON.1     // Timer1 Clock Source Select bit 
#bit T1CON_TMR1ON  = T1CON.0     // Timer1 On bit         
                                                                
//   ################   RS232/EUSART   #################  //   
#byte  RCSTA   = 0x0FAB    // RCSTA: RECEIVE STATUS AND CONTROL REGISTER
#byte  BAUDCON = 0x0FB8    // BAUDCON: BAUD RATE CONTROL REGISTER                       
#byte  TXSTA   = 0x0FAC    // TXSTA: TRANSMIT STATUS AND CONTROL REGISTER 
#byte  SPBRGH  = 0x0FB0    // EUSART Baud Rate Generator Register, High Byte                         
#byte  SPBRG   = 0x0FAF    // EUSART Baud Rate Generator Register, Low Byte  
#byte  TXREG   = 0x0FAD    // EUSART Transmit Register                            
#byte  RCREG   = 0x0FAE    // EUSART Receive Register

#bit   OERR_RCSTA= RCSTA.1  // Overrun Error bit
#bit   CREN_RCSTA= RCSTA.4  // Continuous Receive Enable bit   
#bit   TXIF_PIR1 = PIR1.4   // EUSART Transmit Interrupt Flag bit
#bit   RCIF_PIR1 = PIR1.5   // EUSART Receive Interrupt Flag bit 
#bit   RCIE_PIE1 = PIE1.5   // EUSART Receive Interrupt Enable bit 
#bit   TXIE_PIE1 = PIE1.4   // EUSART Transmit Interrupt Enable bit     

// ############# GLCD 128x64 ################
//DATA
#byte TRISD = 0x0F95                     
#byte PORTD = 0x0F83  
#byte LCD_data = 0x0F8C  
//CONTROL
#byte TRISBB = 0x0F93     
#byte PORTBB = 0x0F81  
#byte LATBB  = 0x0F8A 
                              
#bit   CS1 = LATBB.0  
#bit   CS2 = LATBB.1  
#bit   RS  = LATBB.2  
#bit   RW  = LATBB.3 
#bit   EN  = LATBB.4             
#bit   RST = LATBB.5                      
                      
//################## MMC/CARD - SPI ###################
#byte TRISC = 0x0F94 
#byte PORTC = 0x0F82        
#byte LATC  = 0x0F8B                           
 
//SPI                        
#bit   CS   = PORTC.2      
#bit   CLK  = PORTC.3 
#bit   SDI  = PORTC.4   
#bit   SDO  = PORTC.5    
#bit   CS_DIR   = TRISC.2  
#bit   CLK_DIR  = TRISC.3       
#bit   SDI_DIR  = TRISC.4  
#bit   SDO_DIR  = TRISC.5  
                          
#byte SSPBUF  = 0x0FC9        // VERI GONDERIRKEN VE ALIRKEN BU 8 BITLIK REGISTER KULLANILIR  

#byte SSPSTAT = 0x0FC7        // VERI HIZI VE BF KONTROLU SAGLANIYOR                                                                 
#bit  BF      = SSPSTAT.0     // BUFFER(SSPBUF REGISTER)'IN BOS VEYA DOLU OLUP OLMADIGININ KONTROLUNU YAPAR.
#bit  CKE     = SSPSTAT.6  
#bit  SMP     = SSPSTAT.7   

#byte SSPCON1 = 0x0FC6        // SDA VE SCL'YI AKTIF EDIYORUZ || I2C'YI MASTER MODUNA ALIYORUZ()  URETECEGIMIZ SAAT FREKANSI clock = FOSC/(4 * (SSPADD + 1)) 
#bit  SSPM0     = SSPCON1.0   
#bit  SSPM1     = SSPCON1.1  
#bit  SSPM2     = SSPCON1.2  
#bit  SSPM3     = SSPCON1.3  
#bit  CKP       = SSPCON1.4  
#bit  SSPEN     = SSPCON1.5 

               
                     
#endif UCREGISTER_H                                                                         