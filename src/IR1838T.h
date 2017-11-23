/*
 * IR1838T.h
 *
 *  Created on: 23 lis 2017
 *      Author: lechu
 */

#ifndef IR1838T_H_
#define IR1838T_H_

#include <stdint.h>

class IR1838T {

public:

	static constexpr uint32_t LEADER_BURST_TIME_US = 9000;
	static constexpr uint32_t BURST_SPACE_TIME_US = 4500;
	static constexpr uint32_t BIT_ON_TIME_US = 562;
	static constexpr uint32_t BIT_OFF_1_TIME_US = 1675;
	static constexpr uint32_t BIT_OFF_0_TIME_US = 562;

	IR1838T(){};
	virtual ~IR1838T();
};


typedef enum{
	SILENCE,	// oczekiwanie na LEADER-a
	LEADER,		// Poczatek transmisji - BURST
	SPACE1,		// przerwa za BURST-em
	DATA,		// kolejne 32 bity
	VALID,		// znacznik przyjetej transmisji - gotowe do odczytu
} CodeState;

typedef struct{
	volatile uint32_t	dataBits;
	volatile uint32_t	repetitions;
	volatile CodeState	state;
}IRData;

extern IRData irDataIRQ, irDataPublic;

void irqRcv(){
	static bool lastPinState = true;
	static uint32_t lastTimeStampUs = 0;
	static uint8_t bitNr = 0;

	bool pinState = Pinout::getIRLevel();
	if (pinState != lastPinState){
		lastPinState = pinState;
		uint32_t timeUs = getTimeUs();
		uint32_t intervalUs = timeUs - lastTimeStampUs;
		CodeState state = irDataIRQ.state;
		if (pinState){	// zbocze narastajace
			switch(state){
			case CodeState::SILENCE: break;
			case CodeState::LEADER:
				if ((intervalUs > IR1838T::LEADER_BURST_TIME_US - 1000)
						&&(intervalUs < IR1838T::LEADER_BURST_TIME_US + 1000)){
					irDataIRQ.state = CodeState::SPACE1;
				}else{
					irDataIRQ.state = CodeState::SILENCE;
				}
				break;
			case CodeState::SPACE1: break;
			case CodeState::DATA:
				if (intervalUs > 2 * IR1838T::BIT_ON_TIME_US){
					irDataIRQ.state = CodeState::SILENCE;
				}
				break;
			case CodeState::VALID: break;
			default: break;
			}
		}else{ // zbocze opadajace - nosna w akcji
			switch(state){
			case CodeState::SILENCE: irDataIRQ.state = CodeState::LEADER; break;
			case CodeState::LEADER: break;
			case CodeState::SPACE1:
				if ((intervalUs > IR1838T::BURST_SPACE_TIME_US - 500)
						&&(intervalUs < IR1838T::BURST_SPACE_TIME_US + 500)){
					irDataIRQ.state = CodeState::DATA;
					bitNr = 0;
				}else{
					irDataIRQ.state = CodeState::SILENCE;
				}
				break;
			case CodeState::DATA:
				if (intervalUs < IR1838T::BIT_OFF_0_TIME_US + 200){
					irDataIRQ.dataBits <<= 1;
					bitNr++;
					if (bitNr >= 32){ // przepisac
						// ToDo przepisac dane
						irDataIRQ.state = CodeState::SILENCE;
					}
				}
				break;
			case CodeState::VALID: break;
			default: break;
			}
		}

	}

}

#endif /* IR1838T_H_ */
