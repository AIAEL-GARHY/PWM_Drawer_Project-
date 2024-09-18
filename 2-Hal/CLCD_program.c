/***********************************************************************/
/***********************************************************************/
/********************  Author: Aia El-garhy    *************************/
/********************  SWC: CLCD               *************************/
/********************  LAYER: HAL              *************************/
/********************  DATE: 1/9/2024          *************************/
/***********************************************************************/
/***********************************************************************/
#define F_CPU 16000000
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Error_State.h"

#include "DIO_interface.h"

#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"

/*static void CLCD_send4Bits(u8 copy_u8Value)
{
	u8 Local_u8Bit;
	
	Local_u8Bit=GET_BIT(copy_u8Value,0);
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN,Local_u8Bit);
	
	Local_u8Bit=GET_BIT(copy_u8Value,1);
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN,Local_u8Bit);
	
	Local_u8Bit=GET_BIT(copy_u8Value,2);
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN,Local_u8Bit);
	
	Local_u8Bit=GET_BIT(copy_u8Value,3);
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN,Local_u8Bit);
}*/


void CLCD_voidSendCommand(u8 copy_u8Command)
{
	/*CTRL PINS*/
	/*RS command=0 data=1*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS,DIO_PIN_LOW);
	/*RW read=1  write=0*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW,DIO_PIN_LOW);
	#if CLCD_MODE ==8
	/*send Command before enable pulse*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8Command);
	SendFallingEdge();
	
	#elif CLCD_MODE == 4
	CLCD_send4Bits(copy_u8Command>>4);
	SendFallingEdge();
	CLCD_send4Bits(copy_u8Command);
	SendFallingEdge();
	#endif
}


static void SendFallingEdge(void)  /*to send data after data*/
{
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E,DIO_PIN_LOW);
}

void CLCD_voidInit(void)
{
	//1-delay more than 30ms
	_delay_ms(40);
	
	#if CLCD_MODE ==8
	
	//2-sendCommand N=1-> 2 lines ,F=0 ->5*7   0b0011NFXX = 0b00111000
	CLCD_voidSendCommand(0b00111000);
	_delay_ms(1);
	//3-Display ON/OFF D=1   C =0  B=0  0b00001100
	CLCD_voidSendCommand(0b00001100);
	_delay_ms(1);
	//4-clr display 1
	CLCD_voidSendCommand(1);
	_delay_ms(2);
	CLCD_voidSendCommand(0b00000110);
	
	#elif CLCD_MODE == 4
	//2-sendCommand N=1-> 2 lines ,F=0 ->5*7   0b0011NFXX = 0b00111000
	CLCD_send4Bits(0b0010);
	SendFallingEdge();
	CLCD_send4Bits(0b0010);
	SendFallingEdge();
	CLCD_send4Bits(0b1000);
	SendFallingEdge();
	_delay_ms(1);
	
	/*3-DISPLAY ON/OFF D=1-> DISPLAY ON ,C=0 -> BLINKING OFF , B=0 -> BLINKING OFF*/
	CLCD_send4Bits(0b0000);
	SendFallingEdge();
	CLCD_send4Bits(0b1100);
	SendFallingEdge();
	/*delay more than 30us*/
	_delay_ms(1);
	
	/*4- DISPLAY CLEAR 1 */
	CLCD_send4Bits(0b0000);
	SendFallingEdge();
	CLCD_send4Bits(0b0001);
	SendFallingEdge();
	/*delay more than 1.53ms*/
	_delay_ms(2);
	
	/*5-ENTRY MODE I/D->1 SH ->0*/
	CLCD_send4Bits(0b0000);
	SendFallingEdge();
	CLCD_send4Bits(0b0110);
	SendFallingEdge();
	#endif
	
	
	
}
void CLCD_voidSendData(u8 copy_u8Data)
{
	/*CTRL PINS*/
	/*RS command=0 data=1*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS,DIO_PIN_HIGH);
	/*RW read=1  write=0*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW,DIO_PIN_LOW);
	#if CLCD_MODE == 8
	/*send data before enable pulse*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8Data);
	SendFallingEdge();
	
	#elif CLCD_MODE == 4
	CLCD_send4Bits(copy_u8Data>>4);
	SendFallingEdge();
	CLCD_send4Bits(copy_u8Data);
	SendFallingEdge();

	#endif

}

u8 CLCD_u8SendString(const u8 *copy_pu8String)
{
	u8 local_u8ErrorStatus=OK;
	u8 local_u8Counter=0;
	if(copy_pu8String != NULL)
	{
		while(copy_pu8String[local_u8Counter] != '\0')
		{
			CLCD_voidSendData(copy_pu8String[local_u8Counter]);
			local_u8Counter++;
		}
	}
	else
	{
		
		local_u8ErrorStatus=NOK;
		
	}
	return local_u8ErrorStatus;
	
}

void CLCD_writeNumber(u32 number)
{
	u32 Local_reversed = 1;
	if (number ==0)
	{
		CLCD_voidSendData('0');
	}
	else
	{
		// Reverse Number
		while (number != 0)
		{
			Local_reversed = Local_reversed*10 + (number%10); /*storing number like stack starting with 1*/
			number /= 10;
		}
		
		do
		{
			CLCD_voidSendData((Local_reversed%10)+'0'); /*printing out number like stack, Last in First out */
			Local_reversed /= 10;
		}while (Local_reversed!=1);
	}
}

u8 CLCD_u8SetPos(u8 copy_u8PosRow,u8 copy_u8PosCol)
{
	u8 local_u8ErrorStatus=OK;
	u8 local_u8DDRAM=0;
	if(copy_u8PosCol<=15)
	{
		switch(copy_u8PosRow)
	{
		case 0: local_u8DDRAM=copy_u8PosCol;  break; 
		case 1:local_u8DDRAM=copy_u8PosCol+64;break;
		default:local_u8ErrorStatus=NOK; break;
	}
	
	SET_BIT(local_u8DDRAM,7);
	CLCD_voidSendCommand(local_u8DDRAM);
	}
	else
	{
		local_u8ErrorStatus=NOK;
	}
	
	
	return local_u8ErrorStatus;
}