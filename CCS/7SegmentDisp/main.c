#include <18F4520.h>   //Kullanilan mikrodenetleyicinin surucusu derleyici uzerinde kaynak dosyasina tanimlanir.

/**FUSES: cihaza bagli cesitli opsiyonlari ayarlamak icin kullanilir. Mevcut ozellikleri en ustte belirtilir. 
       Konfigurasyon bileri vardir, bu komut ile mikrodenetleyicinin konfigurasyon pinleri ayarlan�r.
  Yaygin kullanilan cihaz secenekleri:
      ·   LP, XT, HS, RC     :LP dusuk guclu kristal osilator, XT klasik kristal osilator, HS yuksek hizli kristal osilator, RC Direnc/Kondansator osilator
      ·   WDT, NOWDT         :Programin olasi kilitlenmelerde resetlenmesini sa�lar. WDT dersek bu mod aktif, NOWDT dersek bu mod pasiftir.                    
      ·   PROTECT, NOPROTECT :Kod koruma, mikrokontrollerin i�ine y�kleyecegin kodlar kopyalananaz demek, NOPROTECT ise kodlar geriye okunup kopyalanabilir demektir.   
      ·   PUT, NOPUT   (Power Up Timer): NOPUT, zamanlayicilar kapali demek, yani timer olarak gecen zaman dongulerini kullanmayacagini belirtirsin.
      ·   BROWNOUT, NOBROWNOUT:Dusuk gerilimle program reset, bu ozellik gerilim seviyesi belli bir degerin altina dustugunde, mikrokontrollerin reset atmasidir,
          genelde NOBROWNOUT modunda tutulur , eyer BROWNOUT olarak kullanilirsa, ani gerilim dalgalanmalarinda sistem surrekli resetlenir.
      ·   INTRC: Internal, dahili osilatoru kullan anlam�na gelir.                
      ·   NOMCLR: Master Clear functionality, MCLR girisi PIC'i resetlemek icin kullanilir. Bu fuse yoksa #FUSE MCLR ve MCLR pini 10k ile 5V a 
Tum #FUSES ozelliklerini kapatmak icin " #FUSES none" kullanilir.                              
*/                                                                           
#FUSES NOWDT,INTRC,NOMCLR               
                       
#include "definitions.h"                                                                                                      
#include "main.h"      
#include "delayms.c"
#include "ucregisters.h" //State machine    
                                                                                      
int8_t iSevenSegDispArr[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};   
                          
void main(){                   
   int8_t iNumb=0;                                                                                        
                                                                                                                           
   TRISD=0x00;                                           
   PORTD=0x00;
   
   while(1){                                                                 
      PORTD=iSevenSegDispArr[iNumb]; 
      delayMsFun(DELAY);                                                                                     
      iNumb++;  
      if(iNumb==10)                                             
         iNumb=0; 
   }                                                         
}          