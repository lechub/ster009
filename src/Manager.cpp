/*
 * Manager.cpp
 *
 *  Created on: 2 gru 2017
 *      Author: lechu
 */

#include "Manager.h"
#include "QuickTask.h"

Manager  manager = Manager();


void managerTask(){
	Manager * mng = Manager::getInstance();
	mng->job();
}

QuickTask mngTask = QuickTask(QuickTask::QTType::QT_PERIODIC, managerTask, 50);


Manager * Manager::getInstance(){ return &manager; }



//void Manager::job(){
//	int16_t symbol = ir->getSymbol();
//	if (symbol < 0) return;
//
//	char znak = pilot->symboltToChar(uint8_t(symbol));
//
//	if (znak == Pilot::NO_KEY) return;
//
//	sygn->beep(50);
//
//
//
//
//	Pinout::toggleWyjscie(uint8_t(znak-'0'));
//}



