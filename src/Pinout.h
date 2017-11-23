/*
 * Pinout.h
 *
 *  Created on: 23 lis 2017
 *      Author: lechu
 */

#ifndef PINOUT_H_
#define PINOUT_H_

#include <stdint.h>
#include <stm32f0xx.h>
#include "Gpio.h"


class Pinout {

public:
	static constexpr uint16_t ILOSC_WYJSC = 32;

private:
	static Gpio wy1, wy2, wy3, wy4, wy5, wy6, wy7, wy8, wy9, wy10,
	wy11, wy12, wy13, wy14, wy15, wy16, wy17, wy18, wy19, wy20,
	wy21, wy22, wy23, wy24, wy25, wy26, wy27, wy28, wy29, wy30,
	wy31, wy32;

//	static Gpio wy1 = Gpio(GPIOD, 4);
//	static Gpio wy2 = Gpio(GPIOD, 3);
//	static Gpio wy3 = Gpio(GPIOD, 2);
//	static Gpio wy4 = Gpio(GPIOD, 1);
//	static Gpio wy5 = Gpio(GPIOD, 0);
//	static Gpio wy6 = Gpio(GPIOC, 12);
//	static Gpio wy7 = Gpio(GPIOC, 11);
//	static Gpio wy8 = Gpio(GPIOC, 10);
//	static Gpio wy9 = Gpio(GPIOB, 12);
//	static Gpio wy10 = Gpio(GPIOB, 13);
//	static Gpio wy11 = Gpio(GPIOB, 14);
//	static Gpio wy12 = Gpio(GPIOB, 15);
//	static Gpio wy13 = Gpio(GPIOD, 11);
//	static Gpio wy14 = Gpio(GPIOD, 12);
//	static Gpio wy15 = Gpio(GPIOD, 13);
//	static Gpio wy16 = Gpio(GPIOD, 14);
//	static Gpio wy17 = Gpio(GPIOB, 1);
//	static Gpio wy18 = Gpio(GPIOB, 0);
//	static Gpio wy19 = Gpio(GPIOC, 5);
//	static Gpio wy20 = Gpio(GPIOC, 4);
//	static Gpio wy21 = Gpio(GPIOA, 7);
//	static Gpio wy22 = Gpio(GPIOA, 6);
//	static Gpio wy23 = Gpio(GPIOA, 5);
//	static Gpio wy24 = Gpio(GPIOA, 4);
//	static Gpio wy25 = Gpio(GPIOE, 1);
//	static Gpio wy26 = Gpio(GPIOE, 0);
//	static Gpio wy27 = Gpio(GPIOB, 9);
//	static Gpio wy28 = Gpio(GPIOB, 8);
//	static Gpio wy29 = Gpio(GPIOB, 6);
//	static Gpio wy30 = Gpio(GPIOB, 5);
//	static Gpio wy31 = Gpio(GPIOB, 4);
//	static Gpio wy32 = Gpio(GPIOB, 3);
//
//	static Gpio * gpioTab[ILOSC_WYJSC] = {
//			&wy1, &wy2, &wy3, &wy4, &wy5, &wy6, &wy7, &wy8, &wy9, &wy10,
//			&wy11, &wy12, &wy13, &wy14, &wy15, &wy16, &wy17, &wy18, &wy19, &wy20,
//			&wy21, &wy22, &wy23, &wy24, &wy25, &wy26, &wy27, &wy28, &wy29, &wy30,
//			&wy31, &wy32
//	};

	static Gpio * gpioTab[ILOSC_WYJSC];

	static Gpio irRecv(GPIOE,9);

public:

	static void init(){
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN
				| RCC_AHBENR_GPIODEN | RCC_AHBENR_GPIOEEN
				//| RCC_AHBENR_GPIOFEN
		;

		for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
			gpioTab[i]->setup(Gpio::GpioMode::OUTPUT, Gpio::GpioOType::PushPull
					, Gpio::GpioPuPd::NoPull, Gpio::GpioSpeed::LowSpeed);
		}
	}

	static Gpio * getWy(uint8_t nr){ return nr < ILOSC_WYJSC ? gpioTab[nr] : gpioTab[0]; }


};

#endif /* PINOUT_H_ */
