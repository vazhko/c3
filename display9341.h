#ifndef _DISPLAY_9341_C_
#define _DISPLAY_9341_C_
#include <stdint.h> 


void ili9341_clear(uint16_t colour);
//void ili9341_setPixel(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color);
//void ili9341_setaddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
//void ili9341_pushcolour(uint16_t colour);
void ili9341_writedataWindow(uint8_t *pData, uint16_t w, uint16_t h);

void ili9341_Reset(void);
void ili9341_Init(void);

#endif