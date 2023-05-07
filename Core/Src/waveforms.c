/*
 * waveforms.c
 *
 *  Created on: May 2, 2023
 *      Author: colecosta7
 */


#include "waveforms.h"

int32_t* waveform(int16_t freq, int8_t wavetype, int16_t duty){
	//compute the number of samples for the given frequency
	int32_t numsamples = (SAMPLES_SEC) / (freq);
	//create an array of MAXSIZE in order to hold points
	static int32_t points[MAXSIZE] = {0};
	//the increment size for triangle and sawtooth
	int8_t inc = VOUTH/numsamples;
	//starting voltage
	int16_t vout = 0;


	//calculate a point for every sample, then convert it to a DAC value
	for(int16_t i = 0; i < numsamples; i++){
		//make the right calculation according to wavetype
		switch(wavetype){
			//uses a lookup table in order to plot sine points
			case SINE:
				if(freq == 100){
					points[i] = DAC_volt_conv(sineTable100[i]);
				}
				else if(freq == 200){
					points[i] = DAC_volt_conv(sineTable200[i]);

				}
				else if(freq == 300){
					points[i] = DAC_volt_conv(sineTable300[i]);

				}
				else if(freq == 400){
					points[i] = DAC_volt_conv(sineTable400[i]);
				}
				else{
					points[i] = DAC_volt_conv(sineTable500[i]);
				}
				break;
			//increases for half of the samples, decreases other half
			case TRIANGLE:
				if(i <= numsamples/2){
					vout += inc * 2;
					points[i] = DAC_volt_conv(vout);
				}
				else{
					vout -= inc * 2;
					points[i] = DAC_volt_conv(vout);
				}
				break;
			//increases to 3.0V per period, then back to 0V
			case SAWTOOTH:
				vout += inc;
				points[i] = DAC_volt_conv(vout);
				break;
			//high for the number of samples - the duty cycle, else low
			case SQUARE:
				if(i < (numsamples - duty)) {
					points[i] = DAC_volt_conv(VOUTH);
				}
				else {
					points[i] = DAC_volt_conv(VOUTL);
				}
				break;
		}
	}
	//return pointer to array
	return points;
}
