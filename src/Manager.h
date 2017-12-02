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


class Manager {

	static constexpr uint8_t ILOSC_WYJSC = Pinout::ILOSC_WYJSC;

	Pilot * pilot = nullptr;
	IR1838T * ir = nullptr;
	Sygnalizacja * sygn = nullptr;

	int16_t	wyjscie = 0;
	bool randomMode = false;

	bool wyjTab[ILOSC_WYJSC];

public:
	Manager(){
		for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
			wyjTab[i] = false;
			Pinout::setWyjscie(i, false);
		}
	}
	//Manager(Pilot * pilotPtr, IR1838T * irPtr, Sygnalizacja sygnPtr){ init(pilotPtr, irPtr, sygnPtr); }

	static Manager * getInstance();

	static Manager * getInstance(Pilot * pilotPtr, IR1838T * irPtr, Sygnalizacja * sygnPtr){
		getInstance()->init(pilotPtr, irPtr, sygnPtr);
	}


	void init(Pilot * pilotPtr, IR1838T * irPtr, Sygnalizacja * sygnPtr){
		pilot = pilotPtr;
		ir = irPtr;
		sygn = sygnPtr;
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

	void randomFunc(){
		// ToDo dorobic losowe
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

		if ((znak >= '0')&&(znak <='9')){
			wyjscie *= 10;
			wyjscie += znak - '0';
			return;
		}

//		wyjscie = 0;	// skasowac numer
		Pilot::Key key = Pilot::Key(znak);
		switch(key){
		case Pilot::Key::ONOFF:		// gasi wwszystkie jesli cokolwiek swieci i swieci wszystkie gdy wszystkie zgasly
		{
			randomMode = false;
			wyjscie = 0;

			bool swieca = false;
			for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
				if (wyjTab[i] != true) swieca = true;
			}

			swieca = !swieca;

			for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
				wyjTab[i] = swieca;
			}
		}
		break;
		case Pilot::Key::MENU: // losowo zaswieca i gasi kanaly
		{
			randomMode = false;
			wyjscie = 0;

			//uint32_t tmp = Hardware::getCounter_uS();
			uint32_t tmp = random();
			tmp = tmp xor Hardware::getCounter_uS();

			for (uint8_t i = 0; i < ILOSC_WYJSC; i++){
				wyjTab[i] = tmp & 1ul <<i;
			}

		}
		break;
		case Pilot::Key::TEST:
		{
				randomMode = true;
				wyjscie = 0;
		}
			break;
		case Pilot::Key::PLUS:
			if (wyjscie < ILOSC_WYJSC) wyjscie++;
			else wyjscie = 1;
			break;
		case Pilot::Key::MINUS:		// wybiera kanal nizej
			if (wyjscie > 1) wyjscie--;
			else wyjscie = ILOSC_WYJSC;
			break;
		case Pilot::Key::BACK: 		// tylko wylacza tryb losowy
			randomMode = false;
			break;
		case Pilot::Key::FBACK:		// gasi kolejne kanaly
		{
			randomMode = false;
			setWyj(wyjscie - 1, false);
			wyjscie++;
			if (wyjscie > ILOSC_WYJSC) wyjscie = 0;
		}
		break;
		case Pilot::Key::FFORW:		// zapala kolejne kanaly
		{
			randomMode = false;
			setWyj(wyjscie - 1, true);
			wyjscie--;
			if (wyjscie < 1) wyjscie = ILOSC_WYJSC;
		}
		break;
		case Pilot::Key::PLAY:		// zmienia stan kanalu na odwrotny
			randomMode = false;
			setWyj(wyjscie -1, !getWyj(wyjscie -1));
			break;
		case Pilot::Key::CKEY: 		// wylacza tryb losowy
			randomMode = false;
			break;
		case Pilot::Key::NO_KEY: break;
		default: return;
		}

	}


};

#endif /* MANAGER_H_ */
