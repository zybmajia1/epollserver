#make file Main
svr : epollserver.o
	g++ $^ -o $@
epollserver.o : epollserver.cpp
	g++ $< -c
clean :
	rm *.o *.out
