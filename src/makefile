DIRECTORY = NICK_sort_companies
EXE = main

REPODIR = ../$(DIRECTORY)
TARFILE = $(DIRECTORY).tar

FLAGS = -Wall -Wextra -g
CC = g++
BIN = ../bin
OBJ = ../obj

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/main.o $(OBJ)/jaro.o $(OBJ)/company.o
	$(CC) $(FLAGS) $(LDFLAGS) $(OBJ)/main.o $(OBJ)/jaro.o $(OBJ)/company.o -o $@

$(OBJ)/main.o: main.cpp jaro.h company.h 
	$(CC) $(FLAGS) -c main.cpp  -o $@

$(OBJ)/jaro.o: jaro.cpp jaro.h
	$(CC) $(FLAGS) -c jaro.cpp -o $@

$(OBJ)/company.o: company.cpp company.h jaro.h
	$(CC) $(FLAGS) -c company.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz
