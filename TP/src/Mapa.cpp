#include <iostream>

#include "Mapa.h"

Celula::Celula() {
    // Constrói uma célula vazia
    prox = NULL;
    valor = 0;
}

Mapa::Mapa() {
    // Constrói um Mapa vazio
    tam = 0;
    inicio = NULL;
}

Mapa::Mapa(const Mapa& other) {
    // Inicializa os membros de dados da nova instância
    tam = 0;
    inicio = NULL;

    // Copia os elementos da lista encadeada do objeto original
    Celula* auxOrigem = other.inicio;
    Celula* auxDestino = NULL;
    
    while (auxOrigem != NULL) {
        // Cria uma nova célula e copia os valores
        Celula* nova = new Celula();
        nova->chave = auxOrigem->chave;
        nova->valor = auxOrigem->valor;
        nova->prox = NULL;
        
        // Insere a nova célula na lista da nova instância
        if (inicio == NULL) {
            // Se é a primeira célula, atualiza o início
            inicio = nova;
            auxDestino = nova;
        } else {
            // Se não é a primeira célula, liga a célula anterior à nova
            auxDestino->prox = nova;
            auxDestino = nova;
        }

        // Atualiza os ponteiros auxiliares
        auxOrigem = auxOrigem->prox;
        tam++;
    }
}

int Mapa::GetTamanho() {
    return tam;
}

Celula* Mapa::GetInicio() {
    return inicio;
}

void Mapa::InserePosicao(char item, int pos) {

    if (pos < 0 || pos > tam) return; // EXCEÇÃO
    
    Celula* nova = new Celula();
    nova->chave = item;
    nova->valor = 1;
    nova->prox = NULL;

    if (pos == 0) {
        // Estamos inserindo no início
        nova->prox = inicio;
        inicio = nova;
    }

    else {
        // Inserindo nas demais posições
        Celula* aux = inicio;
        for(int i = 0; i < pos - 1; i++) {
            aux = aux->prox;
        }

        Celula* aux1 = aux->prox;
        aux->prox = nova;
        nova->prox = aux1; 
    }

    tam++;
}

void Mapa::IncrementaChave(char item) {

    // Busca pela chave no Mapa
    Celula* aux = inicio;

    int i = 0;
    while(i < tam) {
        // Encontramos o elemento, então incrementamos seu valor
        if(aux->chave == item) {
            aux->valor++;
            break;
        }
        aux = aux->prox;
        i++;
    }

    // Não encontramos o elemento, então o inserimos na última posição
    if(i == tam) InserePosicao(item, tam);

}

void Mapa::Limpa() {

    Celula* atual = inicio->prox;
    while(atual != NULL) {
        // Enquanto houver elementos no Mapa, os apaga
        inicio->prox = atual->prox;
        delete atual;
        atual = inicio->prox;
    }

    // Garante que o início aponte para NULL
    delete inicio;
    inicio = NULL;
    tam = 0;
}

Mapa::~Mapa() {
    // Basta chamar o método Limpa()
    if(inicio != NULL) Limpa();
}