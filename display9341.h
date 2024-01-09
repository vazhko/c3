#ifndef _DISPLAY_9341_C_
#define _DISPLAY_9341_C_
#include <stdint.h> 


void ili9341_clear(uint16_t colour);
void ili9341_setPixel(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color);

void ili9341_Reset(void);
void ili9341_Init(void);

#endif