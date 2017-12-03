/*
 * Manager.h
 *
 *  Created on: 2 gru 2017
 *      Author: lechu
 */


#ifndef MANAGER_H_
#define MANAGER_H_

#include "Pilot.h"
#include "IR1838T.h"
#include "Sygnalizacja.h"
#include "stdlib.h"
#include "QuickTask.h"
#include "Fifo.h"

class Manager {

	static constexpr uint8_t ILOSC_WYJSC = Pinout::ILOSC_WYJSC;
	static constexpr uint32_t MAX_RANDOM_TIME_MS = 10000;
	static constexpr uint32_t MIN_RANDOM_TIME_MS = 2000;

	Pilot * pilot = nullptr;
	IR1838T * ir = nullptr;
	Sygnalizacja * sygn = nullptr;

	uint32_t randomTime = 0;
	bool randomMode = false;

	uint8_t cyfra = 0;
	int16_t	wyjscie = 0;

	bool wyjTab[ILOSC_WYJSC];

public:
	Manager(){ }
	//Manager(Pilot * pilotPtr, IR1838T * irPtr, Sygnalizacja sygnPtr){ init(pilotPtr, irPtr, sygnPtr); }

	static Manager * getInstance();

	static Manager * getInstance(Pilot * pilotPtr, IR1838T * irPtr, Sygnalizacja * sygnPtr){
		getInstance()->init(pilotPtr, irPtr, sygnPtr);
		return getInstance();
	}


	void init(Pilot * pilotPtr, IR1838T * irPtr, Sygnalizacja * sygnPtr){
		pilot = pilotPtr;
		ir = irPtr;
		sygn = sygnPtr;
		for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
			wyjTab[i] = false;
			Pinout::setWyjscie(i, false);
		}

	}

	void setWyj(uint8_t nr, bool stan){
		if (nr >= ILOSC_WYJSC) return;
		wyjTab[nr] = stan;
		Pinout::setWyjscie(nr, stan);
	}

	bool getWyj(uint8_t nr){
		if (nr >= ILOSC_WYJSC) return false;
		return wyjTab[nr];
	}

	void toggleWyj(uint8_t nr){
		if (nr >= ILOSC_WYJSC) return;
		setWyj(nr, !getWyj(nr));
	}


	void randomFunc(){
		if ((randomTime >= MIN_RANDOM_TIME_MS)&&(randomTime <= MAX_RANDOM_TIME_MS)){
			randomTime += QuickTask::DEFAULT_TICK_INTERVAL_MILIS;
			return;
		}

		// przeladowanie licznika losowego czasu
		uint32_t rnd = random() % (MAX_RANDOM_TIME_MS - MIN_RANDOM_TIME_MS);

		randomTime = MIN_RANDOM_TIME_MS + rnd;

		rnd = random() % (ILOSC_WYJSC);

		toggleWyj(uint8_t(rnd));	// toggle wyjscie rnd
	}

	void job(){
		if (ir == nullptr) return;
		if (pilot == nullptr) return;

		int16_t symbol = ir->getSymbol();
		if (symbol < 0){
			if(randomMode) randomFunc();
			return;
		}

		char znak = pilot->symboltToChar(uint8_t(symbol));

		if (znak == Pilot::NO_KEY) return;

		if (sygn != nullptr)
			sygn->beep(50);

		Pilot::Key key = Pilot::Key(znak);
		if (key != Pilot::Key::TEST) randomMode = false;

		if ((znak >= '0')&&(znak <='9')){
			cyfra++;
			if (cyfra >= 2){
				wyjscie = uint8_t(wyjscie * 10);
				wyjscie = uint8_t(wyjscie + znak - '0');
				toggleWyj(uint8_t(wyjscie-1));
				cyfra = 0;
			}else{
				wyjscie = uint8_t(znak - '0');
			}
			return;
		}

		cyfra = 0;

		//		wyjscie = 0;	// skasowac numer

		switch(key){
		case Pilot::Key::ONOFF:		// gasi wwszystkie jesli cokolwiek swieci i swieci wszystkie gdy wszystkie zgasly
		{
			wyjscie = 0;

			bool swieca = false;
			for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
				if (getWyj(i)) swieca = true;
			}

			swieca = !swieca;

			for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
				setWyj(i,swieca);
			}
		}
		break;
		case Pilot::Key::MENU: // losowo zaswieca i gasi kanaly
		{
			wyjscie = 0;

			//uint32_t tmp = Hardware::getCounter_uS();
			uint32_t tmp = random();
			tmp = tmp xor Hardware::getCounter_uS();

			for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
				setWyj(i, tmp & 1ul << i);
			}

		}
		break;
		case Pilot::Key::TEST:		// uruchamia tryb symulacji
		{
			wyjscie = 0;
		}
		break;
		case Pilot::Key::PLUS:
		{
			setWyj(uint8_t(wyjscie - 1), true);
			wyjscie++;
			if (wyjscie > ILOSC_WYJSC) wyjscie = 1;
		}
		break;
		case Pilot::Key::MINUS:		// wybiera kanal nizej
		{
			setWyj(uint8_t(wyjscie - 1), false);
			wyjscie++;
			if (wyjscie > ILOSC_WYJSC) wyjscie = 1;
		}
		break;
		case Pilot::Key::FBACK:		// gasi kolejne kanaly
			if (wyjscie > 1) wyjscie--;
			else wyjscie = ILOSC_WYJSC;
			break;
		case Pilot::Key::FFORW:		// zapala kolejne kanaly
			if (wyjscie < ILOSC_WYJSC) wyjscie++;
			else wyjscie = 1;
			break;
		case Pilot::Key::PLAY:		// zmienia stan kanalu na odwrotny
			toggleWyj(uint8_t(wyjscie -1));
			break;
		case Pilot::Key::BACK: 		// inwersja - włącza wyłączone i wyłącza właczone
			for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
				toggleWyj(uint8_t(i+1));
			}
			break;
		case Pilot::Key::CKEY: 		// wylacza tryb losowy
		case Pilot::Key::NO_KEY: break;
		default: return;
		}

	}


};

extern QuickTask mngTask;

//----------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//----------------------------------------------------

void managerTask();

//----------------------------------------------------
#ifdef __cplusplus
}
#endif
//----------------------------------------------------


#endif /* MANAGER_H_ */
