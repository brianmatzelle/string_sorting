DIRECTORY = NICK_sort_companies
EXE = sort

REPODIR = ../$(DIRECTORY)
TARFILE = $(DIRECTORY).tar

FLAGS = -Wall -Wextra -g
CC = g++
BIN = ../bin
OBJ = ../obj

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/main.o $(OBJ)/jaro.o $(OBJ)/company.o $(OBJ)/misc.o
	$(CC) $(FLAGS) $(LDFLAGS) $(OBJ)/main.o $(OBJ)/jaro.o $(OBJ)/company.o $(OBJ)/misc.o -o $@

$(OBJ)/main.o: main.cpp jaro.h company.h misc.h
	$(CC) $(FLAGS) -c main.cpp  -o $@

$(OBJ)/jaro.o: jaro.cpp jaro.h
	$(CC) $(FLAGS) -c jaro.cpp -o $@

$(OBJ)/company.o: company.cpp company.h jaro.h
	$(CC) $(FLAGS) -c company.cpp -o $@

$(OBJ)/misc.o: misc.cpp company.h jaro.h
	$(CC) $(FLAGS) -c misc.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz
