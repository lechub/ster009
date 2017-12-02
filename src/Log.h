/*
 * Log.h
 *
 *  Created on: 2 gru 2017
 *      Author: lechu
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdint.h>

class Log {
	static constexpr uint32_t LOG_LENGTH = 10;
public:
	Log();

	static uint32_t logTable[LOG_LENGTH];
	static uint32_t logIndex;


	static void event(uint32_t eventNr){
#ifdef DEBUG

		logIndex++;
		if (logIndex >= LOG_LENGTH){
			logIndex = 0;
		}
		logTable[logIndex] = eventNr;

#endif
	}

};

#endif /* LOG_H_ */
