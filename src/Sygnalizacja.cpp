/*
 * Sygnalizacja.cpp
 *
 *  Created on: 1 gru 2017
 *      Author: lechu
 */

#include "Sygnalizacja.h"
#include "QuickTask.h"


Gpio * beeper;

void beepStop(){
	beeper->pinSetDown();
}

QuickTask beepTask = QuickTask(QuickTask::QTType::QT_ONCE, beepStop, 300);

void Sygnalizacja::beep(uint32_t timeMs){
	beeper = buzzer;
	beepTask.disable();
	beeper->pinSetUp();
	beepTask.startTask(QuickTask::QTType::QT_ONCE, timeMs);
}

