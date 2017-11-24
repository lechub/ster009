/*
 * Pinout.cpp
 *
 *  Created on: 23 lis 2017
 *      Author: lechu
 */

#include "Pinout.h"

	Gpio Pinout::wy1 = Gpio(GPIOD, 4);
	 Gpio Pinout::wy2 = Gpio(GPIOD, 3);
	 Gpio Pinout::wy3 = Gpio(GPIOD, 2);
	 Gpio Pinout::wy4 = Gpio(GPIOD, 1);
	 Gpio Pinout::wy5 = Gpio(GPIOD, 0);
	 Gpio Pinout::wy6 = Gpio(GPIOC, 12);
	 Gpio Pinout::wy7 = Gpio(GPIOC, 11);
	 Gpio Pinout::wy8 = Gpio(GPIOC, 10);
	 Gpio Pinout::wy9 = Gpio(GPIOB, 12);
	 Gpio Pinout::wy10 = Gpio(GPIOB, 13);
	 Gpio Pinout::wy11 = Gpio(GPIOB, 14);
	 Gpio Pinout::wy12 = Gpio(GPIOB, 15);
	 Gpio Pinout::wy13 = Gpio(GPIOD, 11);
	 Gpio Pinout::wy14 = Gpio(GPIOD, 12);
	 Gpio Pinout::wy15 = Gpio(GPIOD, 13);
	 Gpio Pinout::wy16 = Gpio(GPIOD, 14);
	 Gpio Pinout::wy17 = Gpio(GPIOB, 1);
	 Gpio Pinout::wy18 = Gpio(GPIOB, 0);
	 Gpio Pinout::wy19 = Gpio(GPIOC, 5);
	 Gpio Pinout::wy20 = Gpio(GPIOC, 4);
	 Gpio Pinout::wy21 = Gpio(GPIOA, 7);
	 Gpio Pinout::wy22 = Gpio(GPIOA, 6);
	 Gpio Pinout::wy23 = Gpio(GPIOA, 5);
	 Gpio Pinout::wy24 = Gpio(GPIOA, 4);
	 Gpio Pinout::wy25 = Gpio(GPIOE, 1);
	 Gpio Pinout::wy26 = Gpio(GPIOE, 0);
	 Gpio Pinout::wy27 = Gpio(GPIOB, 9);
	 Gpio Pinout::wy28 = Gpio(GPIOB, 8);
	 Gpio Pinout::wy29 = Gpio(GPIOB, 6);
	 Gpio Pinout::wy30 = Gpio(GPIOB, 5);
	 Gpio Pinout::wy31 = Gpio(GPIOB, 4);
	 Gpio Pinout::wy32 = Gpio(GPIOB, 3);

	 Gpio Pinout::key1 = Gpio(GPIOB, 11);
	 Gpio Pinout::key2 = Gpio(GPIOB, 10);
	 Gpio Pinout::key3 = Gpio(GPIOE, 15);
	 Gpio Pinout::key4 = Gpio(GPIOE, 14);
	 Gpio Pinout::key5 = Gpio(GPIOE, 13);
	 Gpio Pinout::key6 = Gpio(GPIOE, 12);
	 Gpio Pinout::key7 = Gpio(GPIOE, 11);
	 Gpio Pinout::key8 = Gpio(GPIOE, 10);

	 Gpio Pinout::infraRed = Gpio(GPIOE, 9);
	 Gpio Pinout::buzzer = Gpio(GPIOE, 8);
	 Gpio Pinout::rsDir = Gpio(GPIOD, 10);

	 Gpio * Pinout::wyjsciaTab[ILOSC_WYJSC] = {
			&wy1, &wy2, &wy3, &wy4, &wy5, &wy6, &wy7, &wy8, &wy9, &wy10,
			&wy11, &wy12, &wy13, &wy14, &wy15, &wy16, &wy17, &wy18, &wy19, &wy20,
			&wy21, &wy22, &wy23, &wy24, &wy25, &wy26, &wy27, &wy28, &wy29, &wy30,
			&wy31, &wy32
	 };

	 Gpio * Pinout::keyTab[ILOSC_KEYS] = {
			&key1, &key2, &key3, &key4, &key5, &key6, &key7, &key8
	 };


