ECHO=echo
COMP=g++
INT=main.h Requete.h Traitement.h
REAL=$(INT:.h=.cpp)
OBJ=$(REAL:.cpp=.o)
EXE=analog
RMFLAG=-f
CLEAN=efface
OPCOMP=-g -ansi -pedantic -Wall -std=c++11

cleanExec:$(EXE) $(CLEAN)

$(EXE):$(OBJ)
	$(ECHO) Edl
	$(COMP) -o $(EXE) $(OBJ) $(OPCOMP)

%.o:%.cpp
	$(ECHO) Compil de $<
	$(COMP) $(OPCOMP) -c $< 

.PHONY:$(CLEAN)
$(CLEAN):
	rm $(OBJ) $(RMFLAG) 
