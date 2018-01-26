ECHO=echo
COMP=g++
INT=main.h Requete.h
REAL=$(INT:.h=.cpp)
OBJ=$(REAL:.cpp=.o)
EXE=LogApache
RMFLAG=-f
CLEAN=efface
OPCOMP=-g -ansi -pedantic -Wall -std=c++11

$(EXE):$(OBJ)
	$(ECHO) Edl
	$(COMP) -o $(EXE) $(OBJ) $(OPCOMP)

%.o: %.cpp
	$(ECHO) Compil de $<
	$(COMP) $(OPCOMP) -c $< 

$(CLEAN):
	rm $(OBJ) $(RMFLAG) 
