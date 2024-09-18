/***********************************************************************/
/***********************************************************************/
/********************  Author: Aia El-garhy    *************************/
/********************  SWC: TIMERS             *************************/
/********************  LAYER: MCAL             *************************/
/********************  DATE: 1/9/2024          *************************/
/***********************************************************************/
/***********************************************************************/


#ifndef _TIMER_INTERFACE_H_
#define _TIMER_INTERFACE_H_

#define TIMER_OVF_INT 0
#define TIMER_CTC_INT 1


void TIMER0_voidInit(void);                                        /*Used to Initialize Timer_0*/

u8 TIMER0_callBack(u8 copy_u8IntID,void (*ptrToFunc)(void));       /*Function Used to Set CallBack Function to Execute when Timer overflow Happen*/

void TIMER1_voidInit(void);                                        /*Used to Initialize Timer_1*/

void TIMER1_voidSetTimerValue(u16 copy_u16TimerValue);             /*Used to Set Value Timer_1*/

u16 TIMER1_voidGetTimerValue(void);                                /*Used to Get Value of Timer_1*/

#endif

