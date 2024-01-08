#ifndef _LIBC3_H_
#define _LIBC3_H_

#ifdef __cplusplus    
    extern "C"  {
    char loadBmp(const char *path);
    char getTouch();
    void clearLcd();
    }
#else    
    char loadBmp(const char *path);
    char getTouch();
    void clearLcd();
#endif

#endif