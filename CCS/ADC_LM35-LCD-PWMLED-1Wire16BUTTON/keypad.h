#ifndef KEYPAD_H                                                                                               
#define KEYPAD_H           
const uint8_t ROWS = 4; //four rows
const uint8_t COLS = 4; //four columns 
const uint8_t sizeKEYPAD = ROWS*COLS; 
extern uchar_t keyPress;  
extern uchar_t keyStartFlag;  
extern uchar_t keyCounter;  
extern uint16_t keypadADCValue;    
                                                                               
const uchar_t keypadChar[] = {'1','2','3','4','5','6','7','8','9','0','.',35 ,13 , 8, 12, '%'}; 
const uint16_t tresholdL[] = {870,715,580,440,390,355,275,255,239,205,197,185,515,325,225,175};
const uint16_t tresholdH[] = {900,745,620,455,420,370,299,270,252,220,204,195,545,345,237,184};  

#endif //KEYPAD_H                                              // ROW RES(0,1k,2.2k,3.3k)  COL RES(0,280,480,680)
                                                                       //       L     H           -READ
                                                                       //1     870 - 900           890
                                                                       //2     715 - 745           731
                                                                       //3     580 - 620           604  
                                                                       //4     440 - 455           448 
                                                                       //5     390 - 420           404 
                                                                       //6     355 - 370           362
                                                                       //7     275 - 299           282 
                                                                       //8     255 - 270           264
                                                                       //9     239 - 252           245 
                                                                       //0     205 - 220           210
                                                                       //.     197 - 204           200
                                                                       //#(35) 185 - 195           189
                                                                       //13  ENTER     515 - 540   533
                                                                       //127 DELETE    325 - 345   336
                                                                       //12  CLEAR ALL 225 - 237   233
                                                                       //%             175 - 184   182 