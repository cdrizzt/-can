#ifndef __OUTPUT_H
#define __OUTPUT_H
#include "stdint.h"

extern uint8_t send_flag;
void Oscillograph_out(int16_t a[17],uint8_t num);
void Error_out(void);

#endif
