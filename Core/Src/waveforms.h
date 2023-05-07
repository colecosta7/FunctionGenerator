/*
 * waveforms.h
 *
 *  Created on: May 2, 2023
 *      Author: colecosta7
 */

#ifndef SRC_WAVEFORMS_H_
#define SRC_WAVEFORMS_H_

#include "main.h"
#include "math.h"
#include "sin.h"
#include <stdlib.h>

#define CLOCKFREQ 32000000
#define SAMPLES_SEC 42000
#define SINE 6
#define TRIANGLE 7
#define SAWTOOTH 8
#define SQUARE 9
#define VOUTH 3000
#define VOUTL 0
#define MAXSIZE 420

int32_t* waveform(int16_t freq, int8_t wavetype, int16_t duty);

#endif /* SRC_WAVEFORMS_H_ */
