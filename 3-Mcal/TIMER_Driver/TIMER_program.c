/***********************************************************************/
/***********************************************************************/
/********************  Author: Aia El-garhy    *************************/
/********************  SWC: TIMERS             *************************/
/********************  LAYER: MCAL             *************************/
/********************  DATE: 1/9/2024          *************************/
/***********************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Error_State.h"


#include "TIMER_config.h"
#include "TIMER_private.h"
#include "TIMER_register.h"
#include "TIMER_interface.h"


static void (*ptrToFunc_ovf)(void)=NULL;
static void (*ptrToFunc_ctc)(void)=NULL;

void TIMER0_voidInit(void)
{
	#if TIMER0_WAVE_GEN_MODE == TIMER0_CTC_MODE
	/*set ctc mode */
	SET_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);

	/*set prescaler*/
	TCCR0 &= 0b11111000;
	TCCR0 |= TIMER0_PRESCALER;

	/*set compare value*/
	OCR0 = TIMER0_COMPARE_MATCH_VALUE;

	/*enable ctc interrupt*/
	SET_BIT(TIMSK,1);
	
	

	#elif TIMER0_WAVE_GEN_MODE == TIMER0_OVF_MODE


	#elif TIMER0_WAVE_GEN_MODE == TIMER0_Fast_PWM_MODE
	/*set pwm mode */
	SET_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);

	/*NON inverting mode*/
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);

	
	/*set  32us*/
	OCR0=63;
	/*set prescaler*/
	TCCR0 &= 0b11111000;
	TCCR0 |= TIMER0_PRESCALER;
	

	#elif TIMER0_WAVE_GEN_MODE == TIMER0_Phase_Correct_MODE
	
	#else
	#error "WRONG WAVE GENERATION MODE SELECT "
	#endif

}

u8 TIMER0_callBack(u8 copy_u8IntID,void (*ptrToFunc)(void))
{

	u8 Error_state=OK;

	if(ptrToFunc != NULL)
	{
		if(copy_u8IntID == TIMER_OVF_INT)
		{
			ptrToFunc_ovf=ptrToFunc;
		}
		else if(copy_u8IntID==TIMER_CTC_INT)
		{
			ptrToFunc_ctc=ptrToFunc;
		}
		else
		{
			Error_state=NOK;
		}
		
		
	}
	else
	{
		Error_state=NULL_POINTER;
	}


	return Error_state;
}
void TIMER1_voidInit(void)
{
	/*Set OC1 normal mode*/
	CLR_BIT(TIMER1_TCCR1A,TIMER1_COM1A0);
	CLR_BIT(TIMER1_TCCR1A,TIMER1_COM1A1);
	
	/*Set waveform generation mode normal */
	CLR_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
	CLR_BIT(TIMER1_TCCR1A,TIMER1_WGM11);
	CLR_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
	CLR_BIT(TIMER1_TCCR1B,TIMER1_WGM13);
	
	/*prescaler/8*/
	CLR_BIT(TIMER1_TCCR1B,0);
	SET_BIT(TIMER1_TCCR1B,1);
	CLR_BIT(TIMER1_TCCR1B,2);

}

void TIMER1_voidSetTimerValue(u16 copy_u16TimerValue)
{
	TIMER1_TCNT1=copy_u16TimerValue;
}
u16 TIMER1_voidGetTimerValue(void)
{
	return TIMER1_TCNT1;
}

void TIMER1_voidSetCompareValueChannelA(u16 copy_u16CompareValue)
{
	/*set compare value*/
	TIMER1_OCR1A=copy_u16CompareValue;
}




/*ISR CTC MODE*/
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	ptrToFunc_ctc();
}


/*ISR OVF MODE*/
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	ptrToFunc_ovf();
}
