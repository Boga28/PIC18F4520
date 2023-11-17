#ifndef ADC_H                                                                                               
#define ADC_H           

extern uint8_t preChannel; 
                       
void adcSetup();         
uint8_t ADC_Read(uint8_t); 
uint8_t is_ADC_Busy();

#endif //ADC_H  
