/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2019-07-08
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"

uint32_t fd;
int INT_PIN;

void DEV_SetBacklight(UWORD Value){	
    pwmWrite(LCD_BL,Value); 
}

/*****************************************
                GPIO
*****************************************/
void DEV_Digital_Write(UWORD Pin, UBYTE Value){
   digitalWrite(Pin, Value); 
}

UBYTE DEV_Digital_Read(UWORD Pin){
    UBYTE Read_value = 0;
    Read_value = digitalRead(Pin);

    return Read_value;
}

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode){

    if(Mode == 0 || Mode == INPUT){
        pinMode(Pin, INPUT);
        pullUpDnControl(Pin, PUD_UP);
    }else{ 
        pinMode(Pin, OUTPUT);
        // printf (" %d OUT \r\n",Pin);
    }
 
}

/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms){
    delay(xms);

}

static void DEV_GPIO_Init(void){

    DEV_GPIO_Mode(LCD_CS, 1);
    DEV_GPIO_Mode(LCD_RST, 1);
    DEV_GPIO_Mode(LCD_DC, 1);
    DEV_GPIO_Mode(LCD_BL, 1);

    DEV_GPIO_Mode(TP_INT, 0);
    DEV_GPIO_Mode(TP_CS, 1);
    
    LCD_CS_1;
	LCD_BL_1;

    TP_CS_0;
    
}
/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_ModuleInit(void){
 
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        DEBUG("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        DEBUG("set wiringPi lib success  !!! \r\n");
    }
    DEV_GPIO_Init();
    wiringPiSPISetup(SPI_CH, 32000000);
    //wiringPiSPISetupMode (0, 32000000, 3);
	//pinMode (LCD_BL, PWM_OUTPUT);
    //pwmWrite(LCD_BL,512);
    //DEV_I2C_Init(0x15);
    return 0;
}

/*****************************************************************************/
void DEV_SPI_WriteByte(uint8_t Value){
    wiringPiSPIDataRW(SPI_CH, &Value, 1);
}

/*****************************************************************************/
void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len){
    uint8_t Data[Len];
    memcpy(Data, pData,  Len);
    wiringPiSPIDataRW(SPI_CH, (unsigned char *)Data, Len);
}

/******************************************************************************
function:	I2C Function initialization and transfer
parameter:
Info:
******************************************************************************/
void DEV_I2C_Init(uint8_t Add){
    printf("WIRINGPI I2C Device\r\n");       
    fd = wiringPiI2CSetup(Add);
}

void I2C_Write_Byte(uint8_t Cmd, uint8_t value) {
	int ref;
    //wiringPiI2CWrite(fd,Cmd);
    ref = wiringPiI2CWriteReg8(fd, (int)Cmd, (int)value);
    while(ref != 0) {
        ref = wiringPiI2CWriteReg8 (fd, (int)Cmd, (int)value);
        if(ref == 0)
            break;
    }
}

int I2C_Read_Byte(uint8_t Cmd){
	int ref;
    ref = wiringPiI2CReadReg8 (fd, (int)Cmd);
    return ref;
}

int I2C_Read_Word(uint8_t Cmd){
	int ref;
    ref = wiringPiI2CReadReg16 (fd, (int)Cmd);
    return ref;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_ModuleExit(void){

}