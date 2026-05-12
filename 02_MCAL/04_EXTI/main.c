#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "STK_interface.h"

u8 Counter = 20; 
u8 InterruptSourceIndex = 0;

int main (void)
{
	RCC_Init();
	RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
	RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
	RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
	RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);

	GPIO_voidSetPinDirection(GPIOA, 4, INPUT_PULLUP_PULLDOWN);
	GPIO_voidSetPinValue(GPIOA, 4, GPIO_HIGH);

	EXTI_voidInit(EXTI_LINE4, PA, RISING_EDGE, ButtonIncrement());
	
}

void ButtonIncrement(void)
{
	Counter++;
	if (Counter > 99)
	{
		Counter = 0;
	}
	InterruptSourceIndex = 15+10;
}