#ifndef COMPACTACAO_H
#define COMPACTACAO_H

#include <string>
#include <stdio.h>

#include "Mapa.h"

// Retorna um Mapa das frequências de cada caractere que aparece no arquivo
Mapa frequencia(FILE* arquivo);

// Ajusta a string para que ela tenha comprimento em byte, isto é, string.lengh() % 8 = 0
void AjustarByte(std::string& codigo, int falta);

// Compacta o arquivo de entrada em um arquivo de saída
void compactar(FILE* entrada, Mapa freq, FILE* saida);

#endif