/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Pinout.h"
#include "IR1838T.h"
#include "Pilot.h"
#include "QuickTask.h"
#include "Sygnalizacja.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F0 empty sample (trace via NONE).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the NONE output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

IR1838T ir = IR1838T();
Pilot pilot = Pilot();
Sygnalizacja * sygnal;


//void dbgFunc(){
//	static uint32_t czas;
//	uint32_t czas2 = Hardware::getCounter_uS();
//	uint32_t dt = czas2 - czas;
//	czas = Hardware::getCounter_uS();
//
//	static bool state = false;
//	state = !state;
//	Pinout::buzzerSet(state);
//}
//QuickTask dbgTask = QuickTask(QuickTask::QTType::QT_ONCE, dbgFunc, 5000);
//




int main(int argc, char* argv[]){
  // At this stage the system clock should have already been configured
  // at high speed.



	Pinout::init();
	Hardware::init();
	sygnal = Sygnalizacja::getInstance(Pinout::getBuzzer());

  while (true) {

	  ir.irqRcv();	// obrobka czytanego pilota
	  QuickTask::runQuickTasks();

	  int16_t symbol = ir.getSymbol();
	  if (symbol > 0){
		  sygnal->beep(300);
		  char znak = pilot.symboltToChar(symbol);
		  //
		  Pinout::toggleWyjscie(uint8_t(znak-'0'));
	  }

    }
}





#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
