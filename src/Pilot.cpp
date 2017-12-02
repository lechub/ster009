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


const uint8_t Pilot::symbols[KEY_COUNT+1][2] = {
		{'0', 22},
		{'1', 12},
		{'2', 24},
		{'3', 94},
		{'4', 8},
		{'5', 28},
		{'6', 90},
		{'7', 66},
		{'8', 82},
		{'9', 74},
		{ONOFF, 69},
		{MENU, 71},
		{TEST, 68},
		{PLUS, 64},
		{MINUS, 25},
		{BACK, 67},
		{FBACK, 7},
		{FFORW, 9},
		{PLAY, 21},
		{CKEY, 13},
		{NO_KEY, NO_KEY},
};

