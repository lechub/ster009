/*
 * IR1838T.h
 *
 *  Created on: 23 lis 2017
 *      Author: lechu
 */

#ifndef IR1838T_H_
#define IR1838T_H_

#include <stdint.h>
#include "Fifo.h"
#include "Hardware.h"
#include "Pinout.h"

class IR1838T {

private:
	static constexpr uint16_t FIFO_LENGTH = 20;

	uint8_t	fifoData[FIFO_LENGTH];
	Fifo fifo = Fifo(fifoData, FIFO_LENGTH);
public:
	static constexpr uint8_t START_SYMBOL = 0xFE;
	static constexpr uint8_t STOP_SYMBOL = 0xFD;

	static constexpr uint32_t LEADER_BURST_TIME_US = 9000;
	static constexpr uint32_t BURST_SPACE_TIME_US = 4500;
	static constexpr uint32_t REPEAT_SPACE_TIME_US = 2250;
	static constexpr uint32_t BIT_ON_TIME_US = 562;
	static constexpr uint32_t BIT_OFF_1_TIME_US = 1675;
	static constexpr uint32_t BIT_OFF_0_TIME_US = 562;

	IR1838T(){};
	//virtual ~IR1838T();


	int16_t getSymbol(){
		if (fifo.isEmpty()){ return -1;
		}
		return fifo.get();
	}

	typedef enum{
		SILENCE,	// oczekiwanie na LEADER-a
		LEADER,		// Poczatek transmisji - BURST
		SPACE1,		// przerwa za BURST-em
		REPEAT,		// przerwa za burstem z RepeatCode
		DATA,		// kolejne 32 bity
		VALID,		// znacznik przyjetej transmisji - gotowe do odczytu
	} CodeState;

	typedef struct{
		volatile uint32_t	dataBits;
		volatile uint32_t	repetitions;
		uint32_t lastTimeStampUs = 0;
		uint8_t bitNr = 0;
		volatile CodeState	state;
		bool lastPinLevel = true;
	}IRData;

	//extern IRData irDataIRQ, irDataPublic;

	void irqRcv(){
		static IRData ir;


		uint32_t timeUs = Hardware::getCounter_uS();
		uint32_t intervalUs = timeUs - ir.lastTimeStampUs;
		if (intervalUs > 1000000) 				// jesli nic sie nie zdarzylo przez 1 sekunde to do SILENCE
			ir.state = CodeState::SILENCE;

		bool pinState = Pinout::getIRLevel();
		if (pinState != ir.lastPinLevel){			// zmiana poziomu na IR?

			ir.lastPinLevel = pinState;
			ir.lastTimeStampUs = timeUs;

			CodeState state = ir.state;	// reakcja na zmiane
			if (pinState){	// zbocze narastajace
				switch(state){
				case CodeState::SILENCE: break;		// jakis blad, albo cos
				case CodeState::LEADER:
					if ((intervalUs > (IR1838T::LEADER_BURST_TIME_US - 3000))
							&&(intervalUs < (IR1838T::LEADER_BURST_TIME_US + 3000))){		// burst zmierzony miedzy 6 a 12 ms?
						ir.state = CodeState::SPACE1;	// prawidlowo - bedzie przerwa
					}else{
						ir.state = CodeState::SILENCE;	// zla dlugosc bursta - powrot do SILENCE
					}
					break;
				case CodeState::SPACE1: break;		//
				case CodeState::DATA:
					if (intervalUs > (2 * IR1838T::BIT_ON_TIME_US)){	// czy dlugosc bitu wieksza niz 2 x prawidlowa?
						ir.state = CodeState::SILENCE;	// za dlugo poczatek bitu to do SILENCE
					}
					if (ir.bitNr >= 8){ // przepisac
						uint8_t znak = uint8_t(ir.dataBits >> 8);
						fifo.put(znak);
						ir.state = CodeState::SILENCE;
					}
					break;
				case CodeState::REPEAT:
					if (intervalUs > (2 * IR1838T::BIT_ON_TIME_US)){	// czy dlugosc bitu wieksza niz 2 x prawidlowa?
						ir.state = CodeState::SILENCE;	// za dlugo poczatek bitu to do SILENCE
					}
					ir.repetitions++;
					if (ir.repetitions > 20){		// 108 ms miedzy RepeatCode x 15 = 2,16 sekundy
						fifo.put(uint8_t(ir.dataBits>>8));
						ir.repetitions = 0;
						ir.state = CodeState::SILENCE;
					}
					break;
				case CodeState::VALID: break;
				default: break;
				}
			}else{ // zbocze opadajace - modulacja w akcji
				switch(state){
				case CodeState::SILENCE:
					ir.repetitions = 0;
					ir.state = CodeState::LEADER; 		// poczatek LEADER-a
					break;
				case CodeState::LEADER: break;
				case CodeState::SPACE1:							// poczatek pierwszego bitu
					if ((intervalUs < (IR1838T::REPEAT_SPACE_TIME_US - 500))
							||(intervalUs > (IR1838T::BURST_SPACE_TIME_US + 1000))){
						ir.state = CodeState::SILENCE;		// zla dlugosc przerwy - powrot do SILENCE
						break;
					}
					if (intervalUs > (IR1838T::REPEAT_SPACE_TIME_US + 500)){
						ir.state = CodeState::DATA;			// beda dane - zaczyna sie pierwszy bit
						ir.bitNr = 0;									// reset znacznika bitow
					}else{
						ir.state = CodeState::REPEAT;
					}
					break;
				case CodeState::DATA:								// skonczyl sie znacznik bitu
					if (intervalUs > (IR1838T::BIT_OFF_1_TIME_US *2)){	// za dlugi odstep po znaczniku bitu - do SILENCE
						ir.state = CodeState::SILENCE;
						break;
					}
					ir.dataBits <<= 1;	// przesuniecie w lewo dla nastepnego bitu
					ir.bitNr++;					// licznik bitow +1
					if (intervalUs > (IR1838T::BIT_OFF_0_TIME_US + 200)){ // wiecej niz 762?
						ir.dataBits |= 0b01;						// przyjeto bit = 1, wiec ustawienie najmlodszego
					}
					break;
				case CodeState::REPEAT: break; //
				case CodeState::VALID: break;
				default: break;
				}
			}

		}

	}

};
#endif /* IR1838T_H_ */
