#ifndef MAPA_H
#define MAPA_H

// Trata-se de um TAD que mapeia os caracteres (chaves) às suas frequências no texto (valor)

class Celula {
    public:
        // Construtor
        Celula();
        // Chave e valor da chave
        char chave;
        int valor;
        Celula* prox;
};

class Mapa {
    public: 
        // Construtor
        Mapa();
        // Função para copiar Mapas
        Mapa(const Mapa& other);
        // Função auxiliar que retorna o tamanho do Mapa
        int GetTamanho();
        // Função auxiliar que retorna a célula inicial do Mapa
        Celula* GetInicio();
        // Insere um elemento em uma determinada posição do Mapa
        void InserePosicao(char item, int pos);
        // Encontra determinada chave no Mapa e incrementa seu valor
        void IncrementaChave(char chave);
        // Limpa o Mapa
        void Limpa();
        // Destrutor
        ~Mapa();
    private:
        // Início do Mapa
        Celula* inicio;
        // Tamanho do Mapa
        int tam;
};

#endif