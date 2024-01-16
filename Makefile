TARGET = libC3.so 

.PHONY: all clean install

all: $(TARGET)
	
clean:
			rm -rf $(TARGET) *.*o

$(TARGET): libC3.so 
			rm -rf *.*o
			gcc -lwiringPi -lm -D USE_WIRINGPI_LIB -g -O0 -Wall -c  -fpic *.c
			gcc -shared -o libC3.so *.o
			sudo yes | sudo cp -rf libC3.so /usr/lib
			
install:
			sudo yes | sudo cp -rf libC3.so /usr/lib


			
