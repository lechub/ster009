/*
 * Sygnalizacja.cpp
 *
 *  Created on: 1 gru 2017
 *      Author: lechu
 */

#include "Sygnalizacja.h"
#include "QuickTask.h"


Sygnalizacja sygnalizacja = Sygnalizacja();

void beepStop(){
//	if (beeper == nullptr) return;
//	beeper->pinSetDown();
//	buzzer->pinSetDown();
	sygnalizacja.beepStop();
}

QuickTask beepTask = QuickTask(QuickTask::QTType::QT_ONCE, beepStop, 300);

void Sygnalizacja::beep(uint32_t timeMs){
//	beeper = buzzer;
	beepTask.disable();
	buzzer->pinSetUp();
	beepTask.startTask(QuickTask::QTType::QT_ONCE, timeMs);
}



Sygnalizacja * Sygnalizacja::getInstance(Gpio * buzzerPtr){
	sygnalizacja.init(buzzerPtr);
	return &sygnalizacja;
}
