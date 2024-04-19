#ifndef DESCOMPACTACAO_H
#define DESCOMPACTACAO_H

#include <string>
#include <stdio.h>

// Retorna o número de 1s e 0s adicionados ao final do texto
int NumAdicionado(std::string codigo);

// Descompacta o arquivo de entrada no arquivo de saída
void descompactar(FILE* entrada, FILE* saida);

#endif