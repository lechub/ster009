/*
 * Pilot.cpp
 *
 *  Created on: 28 lis 2017
 *      Author: lechu
 */

#include "Pilot.h"

Pilot::Pilot() {
	// TODO Auto-generated constructor stub

}

const uint8_t Pilot::numbers[10] = {
		152,	// 0
		162,	// 1
		98,		// 2
		226,	// 3
		34,		// 4
		2,		// 5
		194,	// 6
		224,	// 7
		168,	// 8
		144,	// 9
};

const uint8_t Pilot::symbols[8][2] = {
		{NO_KEY, 0xfe},
		{HASH, 104},
		{ASTERISK, 176},
		{'a', 24},		// up
		{'l', 16},		// left
		{'o', 56},		// ok
		{'r', 90},		// right
		{'d', 74},		// down
};

