CC=gcc
CFLAGS=-g 
OBJS=main.o modules/itoa.o modules/ai.o modules/pwm.o modules/gpio.o modules/gpioModule.o modules/motorCtl.o
TARGET=main.out


$(TARGET) : $(OBJS)
	$(MAKE) -C modules
	$(CC) -o $@ $(OBJS)

all : $(OBJS)

clean:
	$(MAKE) -C modules clean
	rm -f *.o
	rm -f $(TARGET)
	rm -f img/*.txt
