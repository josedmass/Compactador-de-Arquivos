#include <string.h>
#include <stdio.h>

#include "ArvoreHuffman.h"
#include "ConversaoBinario.h"
#include "Compactacao.h"

Mapa frequencia(FILE* arquivo) {
    Mapa freq;

    char caractere;
    while((caractere = fgetc(arquivo)) != EOF) {
        // Para cada caractere do arquivo de entrada, incrementa sua frequência, incluindo caracteres ' ' e '\n'
        freq.IncrementaChave(caractere);
    }

    return freq;
}

void AjustarByte(std::string& codigo, int falta) {
    int flag = 1;
        for (int i = 0; i < falta; i++) {
            // Adiciona 1s e 0s ao final da string, de forma que ela tenha comprimento em bytes
            if(flag == 0) {
                flag = 1;
                codigo += '0';
            }
            else {
                flag = 0;
                codigo += '1';
            }
        }
}

void compactar(FILE* entrada, Mapa freq, FILE* saida) {
    
    // Passo 1: Montar a árvore de Huffman
    ArvoreHuffman arv;
    arv.Constroi(freq);

    // Passo 2: Serializar a árvore, para colocá-la no arquivo de saída
    std::string serie;
    arv.Serializa(arv.GetRaiz(), serie);

    int falta = 8 - (serie.length() % 8); // Quanto falta para a ter comprimento em bytes
    if(falta < 8) AjustarByte(serie, falta);

    // Passo 3: Imprimir a árvore serilizada no arquivo de saída
    for (int i = 0; i < (int)serie.length(); i += 8) {
        // Imprimimos blocos de bits (caracteres)
        char bloco = BinToChar(serie.substr(i, 8));
        fwrite(&bloco, sizeof(char), 1, saida);
    }

    // Ao final, colocamos o número de 1s e 0s adicionados ao final da série
    char numadd = '0' + falta;
    fwrite(&numadd, sizeof(char), 1, saida);
    // Separamos a série do restante do texto com uma linha vazia
    char ch = '\n';
    fwrite(&ch, sizeof(char), 1, saida);
    fwrite(&ch, sizeof(char), 1, saida);

    // Passo 4: Compactar o conteúdo do arquivo de entrada, seguindo a árvore de Huffman
    std::string codigo;
    char caractere;
    while((caractere = fgetc(entrada)) != EOF) {
        codigo += arv.ObterCodigoHuffman(arv.GetRaiz(), caractere);
    }

    falta = 8 - (codigo.length() % 8); // Quanto falta para a ter comprimento em bytes
    if(falta < 8) AjustarByte(codigo, falta);

    for (int i = 0; i < (int)codigo.length(); i += 8) {
        // Imprimimos blocos de bits (caracteres)
        char bloco = BinToChar(codigo.substr(i, 8));
        fwrite(&bloco, sizeof(char), 1, saida);
    }

    // Ao final, colocamos o número de 1s e 0s adicionados ao final da série
    numadd = '0' + falta;
    fwrite(&numadd, sizeof(char), 1, saida);
}