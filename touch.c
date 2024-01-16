#include <stdlib.h>     //exit()
#include <stdio.h>
#include <signal.h>     //signal()

#include "DEV_Config.h"
#include "touch.h"

void Touch_INT_callback(void);

typedef enum {
    TOUCH_INIT  = 0,
    TOUCH_IRQ,
} Touch_STATE;

Touch_STATE flag = TOUCH_INIT;


/************************************************************************/
void Touch_INT_callback(void) {
    flag = TOUCH_IRQ;
}

/************************************************************************/
void touchInit(void){
    wiringPiISR(TP_INT, INT_EDGE_FALLING, &Touch_INT_callback);
    TP_CS_0;
}

/************************************************************************/
char touchGetState(){
    if (flag == TOUCH_IRQ){
        printf("Touch_INT_callback\r\n");
        flag = TOUCH_INIT;
        DEV_Delay_ms(1);
        return 1;
    }
    return 0;
}