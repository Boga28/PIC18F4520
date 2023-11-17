#ifndef MAIN_H     
#define MAIN_H 
#define DELAY 500 
 
//Display Video Animation
void displayVideoAnimation();

// SD CARD MANAGMENTS 
void readSectorData();              
void initMMC(); 
    

// INITILAZITIONS
void timer1_interrupt();
void setupTimerIOSC(void);
void WDTreset(void);  
                    
#endif //MAIN_H                                

                                                                                                              
                              
