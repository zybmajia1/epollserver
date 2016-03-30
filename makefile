#make file Main
TARGET = server
CC = gcc
XX = g++
FLAGS = -Wall -O -g

%.o : %.c
	$(CC) -c $^ -o $@

%.o : %.cpp
	$(XX) -c $^ -o $@

SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$(TARGET) : $(OBJS)
	$(XX) $^ -o $(TARGET)
	chmod a+x $(TARGET)

info:
	@echo info:
	@echo $(SOURCES)
	@echo $(OBJS)
infoall: info

clean :
	rm *.o *.out
	
