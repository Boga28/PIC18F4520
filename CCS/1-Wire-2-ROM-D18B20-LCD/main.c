#include <18F4520.h>   //Kullanilan mikrodenetleyicinin surucusu derleyici uzerinde kaynak dosyasina tanimlanir.

/*FUSES: cihaza bagli cesitli opsiyonlari ayarlamak icin kullanilir. Mevcut ozellikleri en ustte belirtilir. 
       Konfigurasyon bileri vardir, bu komut ile mikrodenetleyicinin konfigurasyon pinleri ayarlan�r.
  Yaygin kullanilan cihaz secenekleri:
      · LP, XT, HS, RC :LP dusuk guclu kristal osilator, XT klasik kristal osilator, HS yuksek hizli kristal osilator, RC Direnc / Kondansator osilator
      · WDT, NOWDT  :Programin olasi kilitlenmelerde resetlenmesini sa�lar. WDT dersek bu mod aktif, NOWDT dersek bu mod pasiftir.     
      · PROTECT, NOPROTECT :Kod koruma, mikrokontrollerin i�ine y�kleyecegin kodlar kopyalananaz demek, NOPROTECT ise kodlar geriye okunup kopyalanabilir demektir. 
      · PUT, NOPUT (Power Up Timer) : NOPUT, zamanlayicilar kapali demek, yani timer olarak gecen zaman dongulerini kullanmayacagini belirtirsin.
      · BROWNOUT, NOBROWNOUT:Dusuk gerilimle program reset, bu ozellik gerilim seviyesi belli bir degerin altina dustugunde, mikrokontrollerin reset atmasidir,
          genelde NOBROWNOUT modunda tutulur, eyer BROWNOUT olarak kullanilirsa, ani gerilim dalgalanmalarinda sistem surrekli resetlenir.
      · INTRC: Internal, dahili osilatoru kullan anlamina gelir.    
      · NOMCLR: Master Clear functionality, MCLR girisi PIC'i resetlemek icin kullanilir. Bu fuse yoksa #FUSE MCLR ve MCLR pini 10k ile 5V a 
Tum #FUSES ozelliklerini kapatmak icin " #FUSES none" kullanilir.                              
*/                               
                                                        
#FUSES NOWDT, WDT8, NOLVP,NOCPD, NOWRT, NOMCLR, IESO, INTRC 
#use delay (internal=8MHz)                    
#use rs232(baud=9600, xmit=PIN_C6,rcv=PIN_C7)
//#use i2c(Master, Fast=100000, sda=PIN_C4, scl=PIN_C3, SMBUS)            
                                           
#include "definitions.h"                                                                                                      
#include "main.h"                                               
#include "delayms.h"                                
#include "ucregisters.h"                                    
#include "init.h"                                                                                         
#include "lcd.h" 
#include "ds1820.h" 
                                                            
#include "lcd.c"                                 
#include "delayms.c"
#include "1wire.c"
#include "ds1820.c" 
                   

                             
                                   
//TIMER1 UNION STRUCTURE AND COUNT MS
tmr1_time_t tmr1_time; 
uint16_t iSayac; 
uchar_t period; 

void setupTimerIOSC(void){         
   //Setup Osilator
   IRCF2 = 1;  
   IRCF1 = 1;
   IRCF0 = 1;                   
                        
   //D ve P portlari cikis olarak ayarlanip sifirlandi.
   TRISB = 0x00;                 
   TRISD = 0x00;
   TRISE = 0x00;      
   PORTB = 0x00;                                                      
   PORTD = 0x00;
   PORTE = 0x00;  
                                                     
   //TMR1 etkinlik bayraklari sifirlandi
   tmr1_time.all = 0;

   // Kesmelere izin verildi
   RCON_IPEN = 1;                                              
   INTCON_GIE_GIEH = 0; 
   INTCON_PEIE = 1;          
   IPR1_TMR1IP = 1; // TMR1 Overflow Interrupt Priority bit
   PIE1_TMR1IE = 1; // TMR1 Overflow Interrupt Enable bit
   PIR1_TMR1IF = 0; // TMR1 Overflow Interrupt Flag bit
                                                                                      
   //TIMER1 Konfigurasyon //50us
   T1CON_RD16 = 0; // 16 - bit Read / Write Mode Enable bit 
   T1CON_T1RUN = 0; // Timer1 System Clock Statusbit
   T1CON_T1CKPS1 = 0; // Timer1 Input Clock Prescale Select bits | 1:1 Olcekleme
   T1CON_T1CKPS0 = 0; // Timer1 Input Clock Prescale Select bits |
   T1CON_T1OSCEN = 0; // Timer1 Oscillator Enable bit
   T1CON_T1SYNC = 0; // Timer1 External Clock Input Synchronization Select bit
   T1CON_TMR1CS = 0; // Timer1 Clock Source Select bit
   TMR1H = 0xF8; //Tasma saayci|
   TMR1L = 0x30; // |||15536 decimal sayisina esit.    
   T1CON_TMR1ON = 1; // Timer1 On bit                                           
}          
                     
void printOn2x16(){                  
   delayUsFun(40);                                                                                                                                      
   twoLinesBCDMode();   
   LinesActive();  
   lcdCursorOff();
   lcdShiftRight();                     
   lcdClear();                                                   
   memcpy(strLCD, "INFORMELEKTRONIKAR-GE    STAJYER", 32); 
   countLCDChar=0;   
   LCDW1SecFlag=1;                             
}                          
                               
void I2C_Init() {    
   SCL_DIR = 1;     //Set as a digital input
   SDA_DIR = 1;     //Set as a digital input
   SSPADD  = 19; 
   SSPCON1 = 0x28;  // enable I2C pins SCL and SDA for serial communication
   //SSPCON2 = 0x00;  
   SSPSTAT = 0x80;  //slew rate disabled for high speed control      
}                                              


#INT_TIMER1                                                           
void timer1_interrupt(){ 
   TMR1H = 0xF8; //Tasma saayci|
   TMR1L = 0x30; // |||15536 decimal sayisina esit.  
   PIR1_TMR1IF = 0; // Kesme bayragi sifirlaniyor.   
   iSayac++;

   if (iSayac % 2 == 0)  //5ms  
      tmr1_time.tmr1_flags._2ms = true;  
   if (iSayac % 50 == 0)//50ms       
      tmr1_time.tmr1_flags._20ms = true;
   if(iSayac >= 1000){    //1 Second
      tmr1_time.tmr1_flags._1000ms = true; 
      iSayac = 0;             
   }                                        
}                             
                                  
#ORG 0x0100,0x0400                                                                    
void main(){          
   setupTimerIOSC();                                                     
   printOn2x16();                                                      
   //I2C_Init();       
   //DS1307_Init(); 
   period=0; 
   searchRom();  
   searchRom();
   searchRom();  
   INTCON_GIE_GIEH = 1; 
   while (TRUE){                        
     WDTreset();         
   
     if(tmr1_time.tmr1_flags._2ms){
        tmr1_time.tmr1_flags._2ms = false;                                                                                              
        if(LCDW1SecFlag){     
           LCD_String();                              
        }                 
     }                 
     if(tmr1_time.tmr1_flags._20ms){
        tmr1_time.tmr1_flags._20ms = false;     
        //ds1307_run(27,7,23,2,14,59,10);
     }                                        
     if(tmr1_time.tmr1_flags._1000ms){                      
        tmr1_time.tmr1_flags._1000ms = false;                                 
        PORTB_7=~PORTB_7;                         
        multid18b20cal();
        LCDW1SecFlag=1;
     }                 
  }  
} 
                          
void multid18b20cal(){             
   if(period<=5){                                       
      INTCON_GIE_GIEH = 0;  
      if(period==0||period==1){
         ds1820_read_from_rom(&SlaveROM[0]);
         heat1 = tempHeat; 
         if(period==1){  
         sprintf(TEMPBF,"T1 :%Ld  T2: %Ld    T3: %Ld     ",heat1,heat2,heat3); 
         memset(strLCD,0,32);
         memcpy(strLCD,TEMPBF,32);}
      }else if(period==2||period==3){
         ds1820_read_from_rom(&SlaveROM[1]); 
         heat2 = tempHeat;           
         if(period==3){  
         sprintf(TEMPBF,"T1 :%Ld  T2: %Ld    T3: %Ld     ",heat1,heat2,heat3); 
         memset(strLCD,0,32);
         memcpy(strLCD,TEMPBF,32);} 
      }else{
         ds1820_read_from_rom(&SlaveROM[2]); 
         heat3 = tempHeat;   
         if(period==5){  
         sprintf(TEMPBF,"T1 :%Ld  T2: %Ld    T3: %Ld     ",heat1,heat2,heat3); 
         memset(strLCD,0,32);
         memcpy(strLCD,TEMPBF,32);} 
      }                       
      INTCON_GIE_GIEH = 1;  
      } period++;
   if(period>=60)
      period=0;                                
}

void WDTreset(void){         
   #asm                  
   CLRWDT                          
   #endasm                                 
}           
                                       