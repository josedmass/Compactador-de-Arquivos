#include "ConversaoBinario.h"

std::string CharToBin(char caractere) {
    std::string bin;
    for(int i = 7; i >= 0; i--) {
        // Percorremos cada bit do caractere, transcrevendo-os para a string
        char bit = (caractere & (1 << i)) ? '1' : '0';
        bin += bit;
    }

    return bin;
}

char BinToChar(std::string bin) {
    char caractere = 0;  // Representação binária: 00000000
    for (int i = 0; i < 8; i++) {
        // Percorremos cada caractere da string bin (cada bit), colocando-os no caractere
        caractere <<= 1;
        if (bin[i] == '1') {
            caractere |= 1;
        }
    }
    return caractere;
}