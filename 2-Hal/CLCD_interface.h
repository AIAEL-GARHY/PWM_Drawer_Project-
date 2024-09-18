/***********************************************************************/
/***********************************************************************/
/********************  Author: Aia El-garhy    *************************/
/********************  SWC: CLCD               *************************/
/********************  LAYER: HAL              *************************/
/********************  DATE: 1/9/2024         *************************/
/***********************************************************************/
/***********************************************************************/

#ifndef _CLCD_INTERFACE_H_
#define _CLCD_INTERFACE_H_


void CLCD_voidSendCommand(u8 Copy_u8Command);         /*used to send command to lcd*/

void CLCD_voidSendData(u8 Copy_u8Data);               /*used to send data to lcd*/

void CLCD_voidInit(void);                             /*used to Initialize lcd*/

u8 CLCD_u8SendString(const u8 *copy_pu8String);       /*used to send string to lcd*/

void CLCD_writeNumber(u32 number);                    /*used to write any number to lcd*/

u8 CLCD_u8SetPostion(u8 copy_u8PosRow,u8 copy_u8PosCol); 


#endif