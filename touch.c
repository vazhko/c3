#include <stdlib.h>     //exit()
#include <stdio.h>
#include <signal.h>     //signal()

#include "DEV_Config.h"
#include "touch.h"
#include <time.h>

#define READ_X 0x90
#define READ_Y 0xD0

void Touch_INT_callback(void);

typedef enum {
    TOUCH_INIT  = 0,
    TOUCH_IRQ,
    TOUCH_WAIT_FOR_FREE,
} Touch_STATE;

volatile Touch_STATE flag = TOUCH_INIT;
//volatile uint8_t lock = 0;

uint8_t buff[2] = {};


/*
time_t startTime;

#include <pthread.h>
 
void *waiter(void *data) {
    static uint8_t prev_state,  state;
    prev_state = state = 1;
    while(1){
        state = TP_CS_GET();
        if(flag == TOUCH_IRQ) {
            prev_state = state = 1;
            continue;
        } else if (flag == TOUCH_WAIT_FOR_FREE){
            if(state == 0) continue;
            flag = TOUCH_INIT;
        }
        
        //DEBUG("read %d \r\n", state);
        //DEV_Delay_ms(1000);
        if( prev_state != state){
            prev_state = state;
            flag = TOUCH_IRQ;
            //lock = 1;
        }
    }

    return NULL;
}
*/



/************************************************************************/
void Touch_INT_callback(void) {
    //if (time(NULL) - startTime < 2)  return;    
    //startTime = time(NULL);
    //DEBUG("Touch_INT\n");
    flag = TOUCH_IRQ;

}

/************************************************************************/
void touchInit(void){
    wiringPiISR(TP_INT, /*INT_EDGE_BOTH*/INT_EDGE_FALLING, &Touch_INT_callback);
    //pthread_t th1;
    //pthread_create(&th1, NULL, waiter, "X");
    TP_CS_0;
    DEV_Delay_ms(1);
    //DEV_SPI1_WriteByte(0x80);  
    //DEV_SPI1_WriteByte(0x00);
    //DEV_SPI1_WriteByte(0x00);
    //startTime = time(NULL);
}

/************************************************************************/
char touchGetState(){
/*
    if (time(NULL) - startTime < 2)  {
        //flag = TOUCH_INIT;
        //return 0;
    }
*/
    //lock = 0;
    if ((flag == TOUCH_IRQ)){
        //TP_CS_0;
        //DEV_SPI1_WriteByte(READ_X);    
        //DEV_SPI1_Write_nByte(buff, 2);
        //buff[0] = DEV_SPI1_WriteByte(0); 
        //buff[1] = DEV_SPI1_WriteByte(0); 
        DEBUG("Touch_INT_callback %d %d\r\n", buff[0], buff[1]);
        flag = TOUCH_INIT;
        //DEV_Delay_ms(1);            
        //startTime = time(NULL);        
        return 1;
    }
    return 0;
}