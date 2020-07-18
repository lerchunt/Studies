SRCS = ../models/pv_dma.cpp ../models/pv_memory.cpp dma_testbench.cpp main.cpp
EXEC = simudma
OBJS = $(SRCS:.cpp=.o)
FLAGS = -DPV_MEMORY_DEBUG -DPV_DMA_DEBUG -DPV_ROUTER_DEBUG -DPV_DMA_BLOCK_TRANSFER 
DIR = mettre le chemin d'acces a l'installation de SystemC 2.2
DIRTLM = mettre le chemin d'acces a l'installation TLM

all : $(EXEC)
	@echo Executable produit : $(EXEC)

$(EXEC) : $(OBJS)
	g++ -L$(DIR)/lib-linux64 $(OBJS) -lsystemc -o $(EXEC)

.cpp.o : 
	g++ -c $(FLAGS) -I$(DIR)/include -I$(DIRTLM) -I../models -I../protocol $< -o $@

clean:	
	-rm *.o *~ ../models/*.o ../models/*~
