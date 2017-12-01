/*
 * Sygnalizacja.h
 *
 *  Created on: 1 gru 2017
 *      Author: lechu
 */

#ifndef SYGNALIZACJA_H_
#define SYGNALIZACJA_H_

#include <stdint.h>
#include "Gpio.h"


class Sygnalizacja {
public:
	static constexpr uint32_t DEFAULT_BEEP_TIME_MS = 300;
private:
	Gpio * buzzer = nullptr;
public:
	Sygnalizacja(){}
	Sygnalizacja(Gpio * buzzerPtr){ init(buzzerPtr); }
	void init(Gpio * buzzerPtr){ buzzer = buzzerPtr; }

	void beep(uint32_t timeMs);
	void beep(){ beep(DEFAULT_BEEP_TIME_MS); }
};

#endif /* SYGNALIZACJA_H_ */
