DIR_BIN      = ./bin
DIR_MAIN  = ./

OBJ_C = $(wildcard ${DIR_MAIN}/*.c )
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

TARGET = main

USELIB = USE_WIRINGPI_LIB

DEBUG = -D $(USELIB)
ifeq ($(USELIB), USE_BCM2835_LIB)
    LIB = -lbcm2835 -lm 
else ifeq ($(USELIB), USE_WIRINGPI_LIB)
    LIB = -lwiringPi -lm 
endif


CC = gcc
MSG = -g -O0 -Wall
CFLAGS += $(MSG) $(DEBUG)

${TARGET}:${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB)
    
${DIR_BIN}/%.o:$(DIR_MAIN)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@
    
	
clean :
	rm $(DIR_BIN)/*.* 
	rm $(TARGET) 
