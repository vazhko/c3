#include <stdlib.h>     //exit()
#include <stdio.h>
#include <signal.h>     //signal()

#include "DEV_Config.h"

#define ILI9341_TFTWIDTH   320
#define ILI9341_TFTHEIGHT  240

volatile uint16_t LCD_W=ILI9341_TFTWIDTH;
volatile uint16_t LCD_H=ILI9341_TFTHEIGHT;

void ili9341_Reset(void);
void ili9341_writecommand8(UBYTE Reg);
void ili9341_writedata8(UBYTE Data);
void ili9341_writedata16(UWORD Data);
void ili9341_Init(void);



/**********************************************************************/
void ili9341_Init(void){
    ili9341_writecommand8(0x01);
    DEV_Delay_ms(1000);

    	//power control A
	ili9341_writecommand8(0xCB);
	ili9341_writedata8(0x39);
	ili9341_writedata8(0x2C);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x34);
	ili9341_writedata8(0x02);

	//power control B
	ili9341_writecommand8(0xCF);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0xC1);
	ili9341_writedata8(0x30);

	//driver timing control A
	ili9341_writecommand8(0xE8);
	ili9341_writedata8(0x85);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x78);

	//driver timing control B
	ili9341_writecommand8(0xEA);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x00);

	//power on sequence control
	ili9341_writecommand8(0xED);
	ili9341_writedata8(0x64);
	ili9341_writedata8(0x03);
	ili9341_writedata8(0x12);
	ili9341_writedata8(0x81);

	//pump ratio control
	ili9341_writecommand8(0xF7);
	ili9341_writedata8(0x20);

	//power control,VRH[5:0]
	ili9341_writecommand8(0xC0);
	ili9341_writedata8(0x23);

	//Power control,SAP[2:0];BT[3:0]
	ili9341_writecommand8(0xC1);
	ili9341_writedata8(0x10);

	//vcm control
	ili9341_writecommand8(0xC5);
	ili9341_writedata8(0x3E);
	ili9341_writedata8(0x28);

	//vcm control 2
	ili9341_writecommand8(0xC7);
	ili9341_writedata8(0x86);

	//memory access control
	ili9341_writecommand8(0x36);
	ili9341_writedata8(0x48);

	//pixel format
	ili9341_writecommand8(0x3A);
	ili9341_writedata8(0x55);

	//frameration control,normal mode full colours
	ili9341_writecommand8(0xB1);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x18);

	//display function control
	ili9341_writecommand8(0xB6);
	ili9341_writedata8(0x08);
	ili9341_writedata8(0x82);
	ili9341_writedata8(0x27);

	//3gamma function disable
	ili9341_writecommand8(0xF2);
	ili9341_writedata8(0x00);

	//gamma curve selected
	ili9341_writecommand8(0x26);
	ili9341_writedata8(0x01);

	//set positive gamma correction
	ili9341_writecommand8(0xE0);
	ili9341_writedata8(0x0F);
	ili9341_writedata8(0x31);
	ili9341_writedata8(0x2B);
	ili9341_writedata8(0x0C);
	ili9341_writedata8(0x0E);
	ili9341_writedata8(0x08);
	ili9341_writedata8(0x4E);
	ili9341_writedata8(0xF1);
	ili9341_writedata8(0x37);
	ili9341_writedata8(0x07);
	ili9341_writedata8(0x10);
	ili9341_writedata8(0x03);
	ili9341_writedata8(0x0E);
	ili9341_writedata8(0x09);
	ili9341_writedata8(0x00);

	//set negative gamma correction
	ili9341_writecommand8(0xE1);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x0E);
	ili9341_writedata8(0x14);
	ili9341_writedata8(0x03);
	ili9341_writedata8(0x11);
	ili9341_writedata8(0x07);
	ili9341_writedata8(0x31);
	ili9341_writedata8(0xC1);
	ili9341_writedata8(0x48);
	ili9341_writedata8(0x08);
	ili9341_writedata8(0x0F);
	ili9341_writedata8(0x0C);
	ili9341_writedata8(0x31);
	ili9341_writedata8(0x36);
	ili9341_writedata8(0x0F);

	//exit sleep
	ili9341_writecommand8(0x11);
	DEV_Delay_ms(120);
	//display on
	ili9341_writecommand8(0x29);

}

/**********************************************************************/
void ili9341_Reset(void){
    LCD_RST_1;
    DEV_Delay_ms(100);
    LCD_RST_0;
    DEV_Delay_ms(100);
    LCD_RST_1;
    DEV_Delay_ms(100);
}

/**********************************************************************/
void ili9341_writecommand8(UBYTE Reg){
    LCD_DC_0;
    LCD_CS_0;
    DEV_SPI_WriteByte(Reg);
    //LCD_CS_1;
}

/**********************************************************************/
void ili9341_writedata8(UBYTE Data){
    LCD_DC_1;
    LCD_CS_0;
    DEV_SPI_WriteByte(Data);
    //LCD_CS_1;
}

/**********************************************************************/
void ili9341_writedata16(UWORD Data){
    LCD_DC_1;
    LCD_CS_0;
    DEV_SPI_WriteByte(Data >> 8);
    DEV_SPI_WriteByte(Data);
    //LCD_CS_1;	
}

/**********************************************************************/
//set colour for drawing
void ili9341_pushcolour(uint16_t colour){
	ili9341_writedata8(colour>>8);
	ili9341_writedata8(colour);
}

//set coordinate for print or other function
void ili9341_setaddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2){

	ili9341_writecommand8(0x2A);
	ili9341_writedata8(x1>>8);
	ili9341_writedata8(x1);
	ili9341_writedata8(x2>>8);
	ili9341_writedata8(x2);

	ili9341_writecommand8(0x2B);
	ili9341_writedata8(y1>>8);
	ili9341_writedata8(y1);
	ili9341_writedata8(y2);
	ili9341_writedata8(y2);

	ili9341_writecommand8(0x2C);//meory write
}

/**********************************************************************/
//clear lcd and fill with colour
void ili9341_clear(uint16_t colour){
	uint16_t i,j;
	ili9341_setaddress(0,0,LCD_W-1,LCD_H-1);

	for(i=0;i<LCD_W;i++)
	{
		for(j=0;j<LCD_H;j++)
		{
			ili9341_pushcolour(colour);
		}
	}
}


