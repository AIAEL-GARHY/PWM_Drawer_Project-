/***********************************************************************/
/***********************************************************************/
/********************  Author: Aia El-garhy    *************************/
/********************  SWC: EXTI               *************************/
/********************  LAYER: MCAL             *************************/
/********************  DATE: 1/9/2024          *************************/
/***********************************************************************/
/***********************************************************************/
#ifndef _EXTI_INTERFACE_H_
#define _EXTI_INTERFACE_H_

#define EXTI_INT0     6
#define EXTI_INT1     7
#define EXTI_INT2     5

/*SENSE_CTRL*/
#define EXTI_LOW_LEVEL      0
#define EXTI_FALLING_EDGE   1
#define EXTI_RISING_EGDE    2
#define EXTI_ON_CHANGE      3



void EXTI_Enable(u8 copy_u8IntID,u8 copy_u8SenseMode);
void EXTI_Disable(u8 copy_u8IntID);
void EXTI_callBack_INT0(void(*ptr_func)(void));
void EXTI_callBack_INT1(void(*ptr_func)(void));
void EXTI_callBack_INT2(void(*ptr_func)(void));

#endif