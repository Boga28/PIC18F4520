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
//#use I2C(master, sda=PIN_C4, scl=PIN_C3)
                                           
#include "definitions.h"                                                                                                      
#include "main.h"                 
#include "delayms.h"                                
#include "ucregisters.h"                                    
#include "init.h"                                                                                         
#include "lcd.h"  
#include "button.h"       
#include "DS1307timeset.h" 
#include "timedate.h"
                         
#include "lcd.c"                                
#include "delayms.c"                 
#include "DS1307.c" 
#include "DS1307timeset.c"
#include "timedate.c"
#include "button.c"   
                             
                                   
//TIMER1 UNION STRUCTURE AND COUNT MS
tmr1_time_t tmr1_time; 
uint16_t iSayac;    
                                         
                      
void setupTimerIOSC(void){
   timeCounter=0;
   //Setup Osilator
   IRCF2 = 1;                           
   IRCF1 = 1;
   IRCF0 = 1; 
   ADCON1 = 0xFF; 
   CMCON  = 0x07;
                        
   //D ve P portlari cikis olarak ayarlanip sifirlandi.
   TRISB = 0x07;
   TRISD = 0x00;
   TRISE = 0x00;                  
   PORTB = 0x00;                                                      
   PORTD = 0x00;
   PORTE = 0x00;         
                                                     
   //TMR1 etkinlik bayraklari sifirlandi
   tmr1_time.all = 0;

   // Kesmelere izin verildi
   RCON_IPEN = 1;                                              
   INTCON_GIE_GIEH = 1;
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
   TMR1L = 0x30; // |||65436 decimal sayisina esit.
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
   // LCD_Custom_CHAR(7, legrandLCDCharacter);
   //LCD_Custom_CHAR(6, stickManLCDCharacter);                               
}                          
 
#INT_TIMER1                                                           
void timer1_interrupt(){ 
   TMR1H = 0xF8; //Tasma saayci|
   TMR1L = 0x30; // |||15536 decimal sayisina esit. 
   PIR1_TMR1IF = 0; // Kesme bayragi sifirlaniyor.
   iSayac++; 
   if (iSayac % 2 == 0) //2ms 
      tmr1_time.tmr1_flags._2ms = true;
   if (iSayac % 10 == 0) //20ms 
      tmr1_time.tmr1_flags._10ms = true;    
   if (iSayac % 500 == 0) //200ms 
      tmr1_time.tmr1_flags._500ms = true;
   if(iSayac > 1000){   // 1 Saniye  
      tmr1_time.tmr1_flags._1000ms = true; 
      iSayac = 0; 
      timeCounter++;
   }     
}                             
                                  
#ORG 0x0100,0x0400                                                                    
void main(){                                                        
   setupTimerIOSC();                                                     
   printOn2x16();             
   DS1307_Init();                                                                                      
   ds1307_set_date_time(31,12,22,6,23,59,55);
   getTime(); 
   runTime();
   while (TRUE){                  
     WDTreset();                                       
     if(tmr1_time.tmr1_flags._1000ms){                      
        tmr1_time.tmr1_flags._1000ms = false;                
        PORTB_7=~PORTB_7;       
        if(DATE_STATUS.X.SET==0){
           LCDW1SecFlag=1; 
           runTime();                                           
        }   
        //printf("\f\%02d:\%02d:\%02d\r\n", getHour(), getMin(),getSec()); 
        //printf("\%02d/\%02d/\%02d -->%s",day, getMonth(), getYear(), dayText);   
     } 
     if(timeCounter>=120){ 
        getTime(); 
        timeCounter=0;       
     }
     if(tmr1_time.tmr1_flags._500ms){            
        tmr1_time.tmr1_flags._500ms = false;  
        executed=1;
        if(DATE_STATUS.X.SET==1||DATE_STATUS.X.SET==2||DATE_STATUS.X.SET==3){
           setTimeCases();
           LCDW1SecFlag=1;     
           //printf("\fposition %d\r",position);
           //printf("DATE_STATUS.X.SET: %d\r",DATE_STATUS.X.SET);
        } 
     }                              
     if(tmr1_time.tmr1_flags._10ms){
        tmr1_time.tmr1_flags._10ms = false;
        if(bt_queue==0){button_debounce_1(PORTB,0); bt_queue++;}
        else if(bt_queue==1){button_debounce_2(PORTB,1); bt_queue++;} 
        else{button_debounce_3(PORTB,2); bt_queue=0;}
     } 
     if(tmr1_time.tmr1_flags._2ms){
        tmr1_time.tmr1_flags._2ms = false;   
        if(LCDW1SecFlag){     
           LCD_String();                                    
        }
     }                   
  }  
} 

void WDTreset(void){         
   #asm                  
   CLRWDT                          
   #endasm                                 
}                  
                                       