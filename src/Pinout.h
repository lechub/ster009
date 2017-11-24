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
	static constexpr uint16_t ILOSC_KEYS = 8;

private:
	static Gpio wy1, wy2, wy3, wy4, wy5, wy6, wy7, wy8, wy9, wy10,
	wy11, wy12, wy13, wy14, wy15, wy16, wy17, wy18, wy19, wy20,
	wy21, wy22, wy23, wy24, wy25, wy26, wy27, wy28, wy29, wy30,
	wy31, wy32;

	static Gpio key1, key2, key3, key4, key5, key6, key7, key8;

	static Gpio infraRed;
	static Gpio buzzer;
	static Gpio rsDir;

	static Gpio * wyjsciaTab[ILOSC_WYJSC];
	static Gpio * keyTab[ILOSC_KEYS];

	static Gpio * gpioTab[ILOSC_WYJSC];

	static Gpio irRecv(GPIOE,9);

public:

	static void init(){
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN
				| RCC_AHBENR_GPIODEN | RCC_AHBENR_GPIOEEN
				//| RCC_AHBENR_GPIOFEN
		;

		for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
			wyjsciaTab[i]->setup(Gpio::GpioMode::OUTPUT, Gpio::GpioOType::PushPull
					, Gpio::GpioPuPd::NoPull, Gpio::GpioSpeed::LowSpeed);
		}

		for (uint8_t i = 0; i < ILOSC_KEYS; i++){
			wyjsciaTab[i]->setup(Gpio::GpioMode::INPUT, Gpio::GpioOType::NoMatter
					, Gpio::GpioPuPd::PullUp, Gpio::GpioSpeed::LowSpeed);
		}

		buzzer.setup(Gpio::GpioMode::OUTPUT, Gpio::GpioOType::PushPull
							, Gpio::GpioPuPd::NoPull, Gpio::GpioSpeed::LowSpeed);

		rsDir.setup(Gpio::GpioMode::OUTPUT, Gpio::GpioOType::PushPull
				, Gpio::GpioPuPd::NoPull, Gpio::GpioSpeed::LowSpeed);

		infraRed.setup(Gpio::GpioMode::INPUT, Gpio::GpioOType::NoMatter
				, Gpio::GpioPuPd::PullUp, Gpio::GpioSpeed::MaximumSpeed);
	}

	static Gpio * getWyj(uint8_t nr){ return nr < ILOSC_WYJSC ? wyjsciaTab[nr] : wyjsciaTab[0]; }
	static Gpio * getWej(uint8_t nr){ return nr < ILOSC_KEYS ? keyTab[nr] : keyTab[0]; }

	static void buzzerSet(bool newstate){ buzzer.pinSet(newstate); }


};

#endif /* PINOUT_H_ */
