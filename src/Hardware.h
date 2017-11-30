/*
 * Hardware.h
 *
 *  Created on: 26 lis 2017
 *      Author: lechu
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "stm32f0xx.h"

class Hardware {
public:

	static constexpr uint32_t SYSTICK_FREQUENCY_HZ = 1000;

	typedef enum{
		OK, Incident, Failure,
	}ErrorCode;
	typedef enum{
		UNKNOWN, INIT_SYSTICK, IRQ, COSTAMJESZCZE
	}ErrorSource;

	Hardware();


	static void init(){
		//		RCC->AHBENR |= RCC_APB1ENR_TIM3EN;

		// zegar timera TIM2 - 32 bit
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

		// CK_INT -> zrodlo dla PK_PSC
		// CK_PSC -> CNT counter

		TIM2->PSC = (48 - 1); // 48MHz/48 = 1MHz -> licznik co 1uS
		TIM2->CNT = 0ul;	// licznik na zero
		TIM2->CR1 = TIM_CR1_CEN;		//start licznika

		// zegar timera TIM1
		//		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

		// ustawienie Systicka
		if (SysTick_Config( SystemCoreClock / SYSTICK_FREQUENCY_HZ)) {
			errorDispatch(Hardware::ErrorCode::Failure, Hardware::ErrorSource::INIT_SYSTICK);
		}

	}

	static void errorDispatch(ErrorCode errCode, ErrorSource errSource){
		static ErrorSource source;
		source = errSource;
		switch(errCode){
		case Failure:
			while (true){;}// ToDo mruganie dioda
			break;
		case Incident:
			// Todo zasygnalizowanie
			break;
		}
	}

	static inline uint32_t getCounter_uS(){ return TIM2->CNT; }

};

#endif /* HARDWARE_H_ */
