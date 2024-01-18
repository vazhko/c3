#include "../display9341.h"
#include "../GUI_BMP.h"
#include "../libC3.h"

#include <math.h>
#include <stdlib.h>     //exit()
#include <stdio.h>

int main(int argc, char **argv){

    char i;

    const char *path1 = "../generatedQrCode.bmp";
    const char *path2 = "../f16.bmp";
    
    //clearLcd();
    
    if( argc == 2 ) {
        loadBmp(argv[1]);
    } else { 
        clearLcd();
    }

    

    while (1){
        
        if(getTouch()){
            switch (i){
                case 0:
                    loadBmp(path1);
                    break;
                case 1:
                    loadBmp(path2);
                    break;  
                case 2:
                    clearLcd();
                    break;                  
            }
            i++;
            if(i > 2) i = 0; 
            DEV_Delay_ms(1000);           
        }
    }
    return 0;
}