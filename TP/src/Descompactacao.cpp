#include <string.h>
#include <stdio.h>

#include "ArvoreHuffman.h"
#include "ConversaoBinario.h"
#include "Descompactacao.h"

int NumAdicionado(std::string codigo) {
    char ch = BinToChar(codigo);
    int numadd = (int)ch - '0';
    return numadd;
}

void descompactar(FILE* entrada, FILE* saida) {

    // Passo 1: pegar a árvore serializada, armazenada antes de uma linha vazia
    std::string serie;
    int fim = 0;
    char cha = fgetc(entrada);

    while(!feof(entrada)) {
        if(cha == '\n') {
            if(fim > 0) break;
            else {
                serie += cha;
                fim++;
                cha = fgetc(entrada);
                continue;
            }
        }
        serie += cha;
        fim = 0;
        cha = fgetc(entrada);
    }

    serie = serie.substr(0, serie.length() - 1); // Retira o últino \n da serie, que foi adicionado artificialmente

    std::string codserie;
    for (char caractere : serie) {
        codserie += CharToBin(caractere);
    }

    int numadd = NumAdicionado(codserie.substr(codserie.length() - 8, 8));
    
    // codserie fica igual à serie antes de se adicionar 1s e 0s
    if (numadd < 8) codserie = codserie.substr(0, codserie.length() - 8 - numadd);
    else codserie = codserie.substr(0, codserie.length() - 8); // Se for igual a 8, então nada foi adicionado

    // Passo 2: remontar a árvore
    ArvoreHuffman arv;
    int i = 0;
    No* raiz = arv.GetRaiz();
    arv.ConstroiSerie(codserie, raiz, i);

    // Passo 3: para as demais linhas, remontar o texto original
    std::string codlinha;

    cha = fgetc(entrada);
    while(!feof(entrada)) {
        //std::cout << cha;
        codlinha += CharToBin(cha);
        cha = fgetc(entrada);
    }
    
    numadd = NumAdicionado(codlinha.substr(codlinha.length() - 8, 8));

    // codlinha fica igual à serie antes de se adicionar 1s e 0s
    if (numadd < 8) codlinha = codlinha.substr(0, codlinha.length() - 8 - numadd);
    else codlinha = codlinha.substr(0, codlinha.length() - 8); // Se for igual a 8, então nada foi adicionado

    // Encontramos o texto original
    std::string original = arv.ObterMensagem(codlinha);

    // Passo 4: colocar a mensagem original no arquivo de saída
    fwrite(original.c_str(), sizeof(char), original.length(), saida);
}