CC=gcc
CFLAGS=-g 
OBJS=main.o timerTest.o pwm.o
TARGET=timerTest.out


$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

all : $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

