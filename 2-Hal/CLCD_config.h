/***********************************************************************/
/***********************************************************************/
/********************  Author: Aia El-garhy    *************************/
/********************  SWC: CLCD               *************************/
/********************  LAYER: HAL              *************************/
/********************  DATE: 1/9/2024         *************************/
/***********************************************************************/
/***********************************************************************/

#ifndef _CLCD_CONFIG_H_
#define _CLCD_CONFIG_H_

#define CLCD_MODE 8

#if CLCD_MODE == 4

#define CLCD_D4_PIN    DIO_PIN4
#define CLCD_D5_PIN    DIO_PIN5
#define CLCD_D6_PIN    DIO_PIN6
#define CLCD_D7_PIN    DIO_PIN7

#endif

#define CLCD_DATA_PORT   DIO_PORTA

#define CLCD_CTRL_PORT   DIO_PORTB

#define CLCD_RS   DIO_PIN0
#define CLCD_RW   DIO_PIN1
#define CLCD_E    DIO_PIN2

#endif
