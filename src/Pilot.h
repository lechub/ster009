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
	static constexpr uint8_t HASH = '#';
	static constexpr uint8_t ASTERISK = '*';
	static constexpr uint8_t ENTER = '@';
	static constexpr uint8_t NO_KEY = 0xfe;

	Pilot();

private:
	static const uint8_t numbers[10];

	static const uint8_t symbols[8][2];

public:
	char symboltToChar(uint8_t symbol){
		for (uint8_t i = 0; i < 10; i++){
			if (numbers[i] == symbol) return i + '0';
		}
		for (uint8_t i = 0; i < 8; i++){
			if (symbols[i][0] == symbol) return symbols[i][1];
		}
		return NO_KEY;
	}

	uint8_t chartoSymbol(char znak){
		if ((znak <= '9')&&(znak >= '0')){
			return numbers[znak - '0'];
		}
		for (uint8_t i = 0; i < 8; i++){
			if (symbols[i][1] == znak) return symbols[i][0];
		}
		return NO_KEY;
	}

};

#endif /* PILOT_H_ */
