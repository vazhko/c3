#include <stdlib.h>     //exit()
#include <stdio.h>
#include <signal.h>     //signal()

#include "DEV_Config.h"

void  Handler_1IN28_LCD(int signo);

int main(){
    printf("ura!!!\n");
    signal(SIGINT, Handler_1IN28_LCD);
    
    /* Module Init */
	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }
    LCD_BL_1;
    return 0;
}


void  Handler_1IN28_LCD(int signo){
    //System Exit
    printf("\r\nHandler:Program stop\r\n");     
    DEV_ModuleExit();
	exit(0);
}