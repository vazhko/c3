#include "display9341.h"
#include "DEV_Config.h"

#include <stdlib.h>     //exit()
#include <stdio.h>
#include <signal.h>     //signal()

#include "colors.h"
#include "GUI_BMP.h"

static char isInit = 0;

int moduleInit();


/**********************************************************************/
void  displayEndHahdler(int signo){
    //System Exit
    printf("\r\nHandler:Program stop\r\n");     
    DEV_ModuleExit();
	exit(0);
}

/**********************************************************************/
int moduleInit(){
    signal(SIGINT, displayEndHahdler);    

	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }

    ili9341_Reset();
    ili9341_Init();


    LCD_BL_1;

    //ili9341_clear(0x2589);
    //ili9341_clear(0);
    //while (1) DEV_Delay_ms(100);

    return 0;
}

/**********************************************************************/
char loadBmp(const char *path){
    if (!isInit) {
        moduleInit();
        isInit = 1;
    }

    GUI_ReadBmp(path);

    return 0;
}

/**********************************************************************/
char getTouch(){
    if (!isInit) {
        moduleInit();
        isInit = 1;
    }
    return 0;
}

/**********************************************************************/
void clearLcd(){
    if (!isInit) {
        moduleInit();
        isInit = 1;
    }
    ili9341_clear(TFT_BLACK);
    //ili9341_clear(TFT_ORANGE);
}
