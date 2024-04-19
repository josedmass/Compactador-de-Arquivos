#include <iostream>
#include <stdlib.h>

#include "ArvoreHuffman.h"
#include "Mapa.h"
#include "ConversaoBinario.h"
#include "Compactacao.h"
#include "Descompactacao.h"

// argv[1]: arquivo de entrada
// argv[2]: arquivo de saída
// argv[3]: -c (compactação) / -d (descompactação)

int main(int argc, char* argv[]) {

    switch (argc) { 
        // Caso o usuário não tenha passado adequadamente os parâmetros de entrada
        case 0 || 1:
            std::cout << "ERRO: NÃO PASSOU O NOME DO ARQUIVO DE ENTRADA" << std::endl;
            return 1;
        case 2:
            std::cout << "ERRO: NÃO PASSOU O NOME DO ARQUIVO DE SAÍDA" << std::endl;
            return 1;
        case 3: 
            std::cout << "ERRO: NÃO PASSOU O COMANDO -c ou -d" << std::endl;
            return 1;
    }
    
    std::string opt = argv[3];

    FILE* infile = NULL;
    FILE* outfile = NULL;

    if(opt == "-c") {
        // Selecionou a opção de compactar
        std::string infile_nome = argv[1];
        infile = fopen(infile_nome.c_str(), "r");

        // Caso o arquivo não tenha sido aberto corretamente
        if (infile == NULL) {
            std::cout << "ERRO: NÃO FOI POSSÍVEL ABRIR O ARQUIVO DE ENTRADA" << std::endl;
            return 1;
        }

        Mapa freq = frequencia(infile);
        fclose(infile);

        // Caso o arquivo esteja vazio
        if(freq.GetTamanho() == 0) {
            std::cout << "ERRO: O ARQUIVO ESTÁ VAZIO" << std::endl;
            return 1;
        }

        infile = fopen(infile_nome.c_str(), "r");
        std::string outfile_nome = argv[2];
        outfile = fopen(outfile_nome.c_str(), "wb");

        compactar(infile, freq, outfile);

    } 
    
    else if (opt == "-d") {
        // Selecionou a opção de descompactar
        std::string infile_nome = argv[1];
        infile = fopen(infile_nome.c_str(), "rb");

        // Caso o arquivo não tenha sido aberto corretamente
        if (infile == NULL) {
            std::cout << "ERRO: NÃO FOI POSSÍVEL ABRIR O ARQUIVO DE ENTRADA" << std::endl;
            return 1;
        }

        std::string outfile_nome = argv[2];
        outfile = fopen(outfile_nome.c_str(), "w");

        descompactar(infile, outfile);

    }

    else {
        // O usuário digitou algo diferente de -c ou -d
        std::cout << "ERRO: '" << opt << "' É UM COMANDO INVÁLIDO" << std::endl << "OS COMANDOS VÁLIDOS SÃO: -c (para compactar) / -d (para descompactar)" << std::endl;
    }

    if (infile != NULL) fclose(infile);
    if (outfile != NULL) fclose(outfile);

    return 0;

}