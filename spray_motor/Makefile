CC=gcc
CFLAGS=-g 
OBJS=main.o itoa.o pwm.o gpio.o gpioModule.o motorCtl.o
TARGET=main.out


$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

all : $(TARGET)

clean:
	rm -f *.jpg
	rm -f *.o
	rm -f $(TARGET)
	rm -f img/*.txt

