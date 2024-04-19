CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/Mapa.o $(OBJ)/ArvoreHuffman.o $(OBJ)/ConversaoBinario.o $(OBJ)/Compactacao.o $(OBJ)/Descompactacao.o
HDRS = $(INC)/Mapa.h $(INC)/ArvoreHuffman.h $(INC)/ConversaoBinario.h $(INC)/Compactacao.h $(INC)/Descompactacao.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

run: $(EXE)
	./$(EXE) $(in) $(out) $(opt)

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/Mapa.o: $(HDRS) $(SRC)/Mapa.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Mapa.o $(SRC)/Mapa.cpp

$(OBJ)/ArvoreHuffman.o: $(HDRS) $(SRC)/ArvoreHuffman.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/ArvoreHuffman.o $(SRC)/ArvoreHuffman.cpp

$(OBJ)/ConversaoBinario.o: $(HDRS) $(SRC)/ConversaoBinario.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/ConversaoBinario.o $(SRC)/ConversaoBinario.cpp

$(OBJ)/Compactacao.o: $(HDRS) $(SRC)/Compactacao.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Compactacao.o $(SRC)/Compactacao.cpp

$(OBJ)/Descompactacao.o: $(HDRS) $(SRC)/Descompactacao.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Descompactacao.o $(SRC)/Descompactacao.cpp
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out