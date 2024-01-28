TARGET = test 

.PHONY: all clean

all: $(TARGET)
	
clean:
			rm -rf $(TARGET) *.*o

$(TARGET):  
			rm -rf *.*o
			g++ -lwiringPi -lm  -g -O0 -Wall -c  test.cpp
			g++ -L../ -g -O0 -Wall -o test test.o -lC3 -lwiringPi -lm
	

