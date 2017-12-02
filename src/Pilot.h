/*
 * Pilot.h
 *
 *  Created on: 28 lis 2017
 *      Author: lechu
 */

#ifndef PILOT_H_
#define PILOT_H_

#include <stdint.h>

class Pilot {
public:
	static constexpr uint8_t KEY_COUNT = 20;

	typedef enum{
		ONOFF = '!',
		MENU = 'M',
		TEST = 'T',
		PLUS = '+',
		MINUS = '-',
		BACK = 'B',
		FBACK = '<',
		FFORW = '>',
		PLAY = 'P',
		CKEY = 'C',
		NO_KEY = 0x0fe,
	}Key;

//	static constexpr char ONOFF = '!';
//	static constexpr char MENU = 'M';
//	static constexpr char TEST = 'T';
//	static constexpr char PLUS = '+';
//	static constexpr char MINUS = '-';
//	static constexpr char BACK = 'B';
//	static constexpr char FBACK = '<';
//	static constexpr char FFORW = '>';
//	static constexpr char PLAY = 'P';
//	static constexpr char CKEY = 'C';
//	static constexpr uint8_t NO_KEY = 0x0fe;

	Pilot();

private:
//	static const uint8_t numbers[10];

	static const uint8_t symbols[KEY_COUNT+1][2];	// dodatkowy na NO_KEY

public:
	char symboltToChar(uint8_t symbol){
		for (uint8_t i = 0; i < KEY_COUNT; i++){
			if (symbols[i][1] == symbol) return symbols[i][0];
		}
		return NO_KEY;
	}

	uint8_t chartoSymbol(char znak){
		for (uint8_t i = 0; i < KEY_COUNT; i++){
			if (symbols[i][0] == znak) return symbols[i][1];
		}
		return NO_KEY;
	}

};

#endif /* PILOT_H_ */
