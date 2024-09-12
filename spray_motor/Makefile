CC=gcc
CFLAGS=-g 
OBJS=main.o itoa.o pwm.o gpio.o gpioModule.o timerTest.o
TARGET=main.out


$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

all : $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

