/*
 * DAC_lib.h
 *
 *  Created on: Apr 23, 2023
 *      Author: colecosta7
 */

#ifndef SRC_DAC_LIB_H_
#define SRC_DAC_LIB_H_
#include "main.h"
//useful defines
#define AF5 5

//function declarations
void DAC_init(void);

void DAC_write(uint16_t val);

uint16_t DAC_volt_conv(uint16_t voltage);

#endif /* SRC_DAC_LIB_H_ */
