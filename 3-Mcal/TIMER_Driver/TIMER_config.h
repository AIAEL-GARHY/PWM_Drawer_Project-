/***********************************************************************/
/***********************************************************************/
/********************  Author: Aia El-garhy    *************************/
/********************  SWC: TIMERS             *************************/
/********************  LAYER: MCAL             *************************/
/********************  DATE: 1/9/2024          *************************/
/***********************************************************************/
/***********************************************************************/

#ifndef _TIMER_CONFIG_H_
#define _TIMER_CONFIG_H_


/* options
 TIMER0_PRESCALER_STOP
 TIMER_PRESCALER_1     
 TIMER_PRESCALER_8     
 TIMER_PRESCALER_64    
 TIMER_PRESCALER_256   
 TIMER_PRESCALER_1024 
*/
#define TIMER0_PRESCALER  TIMER_PRESCALER_64
#define TIMER0_OCR0_VALUE 192
#define TIMER1_PRESCALER  TIMER_PRESCALER_64
/*
TIMER0_CTC_MODE
TIMER0_OVF_MODE
TIMER0_Fast_PWM_MODE
TIMER0_Phase_Correct_MODE
*/
#define  TIMER0_WAVE_GEN_MODE   TIMER0_Fast_PWM_MODE




#endif


