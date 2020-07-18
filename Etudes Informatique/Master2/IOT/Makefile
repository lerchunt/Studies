SRCS = fifo_perf.cpp
EXEC = fifo_perf
OBJS = $(SRCS:.cpp=.o)
#DIR =/home/p/pierrlau/SystemC/systemc-2.3.0
DIR = /usr/systemc-2.3.1

all : $(EXEC)
	@echo Executable Produit : $(EXEC)
$(EXEC) : $(OBJS)
	g++ -L$(DIR)/lib-linux64 $(OBJS) -lsystemc -o $(EXEC)
.cpp.o :
	g++ -c -I$(DIR)/include $<
clean:
	-rm -i *.o *~
