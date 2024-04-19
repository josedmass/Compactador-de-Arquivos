#ifndef ARVOREHUFFMAN_H
#define ARVOREHUFFMAN_H

#include <iostream>

#include "Mapa.h"

// Trata-se de uma árvore binária de células, para armazenar os códigos reduzidos dos caracteres do texto

class No {
    public:
        // Construtores
        No();
        No(char ch, int freq);
    private:
        // Variáveis do No (item e apontadores para a direita e para a esquerda do nó)
        Celula item;
        No* esq;
        No* dir;
    friend class ArvoreHuffman;
};

class ArvoreHuffman {
    public: 
        // Construtor
        ArvoreHuffman();
        // Funções para igualar árvores
        No* CopiaArvore(const No* r);
        ArvoreHuffman(const ArvoreHuffman& other);
        // Função auxiliar que retorna a raíz da árvore
        No* GetRaiz();
        // Converte a árvore para sua forma serializada
        void Serializa(const No* r, std::string& serie);
        // Constrói a árvore a partir de um Mapa
        void Constroi(Mapa freq);
        // Constrói a árvore a partir de uma série
        void ConstroiSerie(const std::string& serie, No*& atual, int& i);
        // Funções para obter os códigos dos caracteres armazenados
        bool BuscarCodigoHuffman(No* no, char ch, std::string& codigo, std::string caminho);
        std::string ObterCodigoHuffman(No* r, char caractere);
        // Função para encontrar a mensagem relativa à um código
        std::string ObterMensagem(std::string codigo);
        // Funções para limpar a árvore
        void LimpaRecursivo(No* r);
        void Limpa();
        // Destrutor
        ~ArvoreHuffman();
    private:
        // Raíz da Árvore
        No* raiz;
        // Número de caracteres armazenados
        int tam;
};

#endif