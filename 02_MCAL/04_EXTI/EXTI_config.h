/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXTI_config.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/9/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

//==============================================================================================================

/*
 $ Options :- بطيخة
			EXTI_LINE0
			EXTI_LINE1
			EXTI_LINE2
			.
			.
			.
			EXTI_LINE15

*/
//#define	EXTI_LINE			EXTI_LINE0

//==============================================================================================================

/*
 $ Options :-
			FALLING_EDGE
			RISING_EDGE
			ON_CHANGE
*/
#define	EXTI_SENSE_MODE		FALLING_EDGE

//==============================================================================================================

#endif