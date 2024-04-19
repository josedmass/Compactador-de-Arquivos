#include "ArvoreHuffman.h"
#include "ConversaoBinario.h"

No::No() {
    // Constrói um nó vazio
    esq = NULL;
    dir = NULL;
}

No::No(char ch, int freq) {
    // Constrói um nó com chave ch e valor freq
    item.chave = ch;
    item.valor = freq;
    esq = NULL;
    dir = NULL;
}

ArvoreHuffman::ArvoreHuffman() {
    // Constrói uma árvore vazia
    raiz = NULL;
    tam = 0;
}

No* ArvoreHuffman::CopiaArvore(const No* r) {
    if (r == NULL) {
        return NULL;
    }

    // Cria um novo nó com os mesmos valores do nó original
    No* novo = new No(r->item.chave, r->item.valor);
    novo->esq = CopiaArvore(r->esq);
    novo->dir = CopiaArvore(r->dir);

    return novo;
}

ArvoreHuffman::ArvoreHuffman(const ArvoreHuffman& other) {
    // Verifica se a outra árvore está vazia
    if (other.raiz == NULL) {
        raiz = NULL;
        tam = 0;
        return;
    }

    // Realiza uma cópia da árvore original
    raiz = CopiaArvore(other.raiz);
    tam = other.tam;
}

No* ArvoreHuffman::GetRaiz() {
    // Retorna a raíz da árvore
    return raiz;
}

void ArvoreHuffman::Serializa(const No* r, std::string& serie) {
    // Análogo ao percorrimento pré-ordem
    if(r == NULL) return;

    if(r->esq != NULL && r->dir != NULL) {
        // Trata-se de um nó interno, então colocamos o bit 0 e serializamos pra esquerda e depois pra direita
        serie += '0';
        Serializa(r->esq, serie);
        Serializa(r->dir, serie);
    }
    
    else {
        // Trata-se de um nó folha, então colocamos o bit 1 e os 8 bits subsequentes representam o caractere
        serie += '1';
        serie += CharToBin(r->item.chave);
    }
}

void ArvoreHuffman::Constroi(Mapa freq) {

    Limpa();

    tam = freq.GetTamanho();

    int tamaux = freq.GetTamanho();
    Celula* aux = freq.GetInicio();

    // Vetor de nós criados para iterarmos com o HuffmanCode
    No** nos = new No*[tamaux];

    for(int i = 0; i < tamaux; i++) {
        // Inicializamos esse vetor com os valores do mapa
        nos[i] = new No(aux->chave, aux->valor);
        aux = aux->prox;
    }

    while (tamaux > 1) {
        // Passo 1: encontrar os dois nós com as menores frequências
        int min1 = 0;
        int min2 = 1;

        if(nos[min1]->item.valor > nos[min2]->item.valor) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        // garante que min1 e min2 são os dois menores
        for(int i = 2; i < tamaux; i++) {
            if(nos[i]->item.valor < nos[min1]->item.valor) {
                min2 = min1;
                min1 = i;
            } else if(nos[i]->item.valor < nos[min2]->item.valor) min2 = i;
        }

        // Passo 2: cria um nó pai com os dois nós com menores frequências como filhos
        No* pai = new No('\0', nos[min1]->item.valor + nos[min2]->item.valor);
        pai->esq = nos[min1];
        pai->dir = nos[min2];

        // Passo 3: removemos os elementos utilizados no mapa e colocamos o pai
        nos[min1] = pai;
        nos[min2] = nos[tamaux-1];
        raiz = pai;
        tamaux--;
    }

    if(tam == 1) {
        raiz = new No();
        raiz->esq = new No(nos[0]->item.chave, nos[0]->item.valor);
        raiz->dir = new No();
    }

    delete[] nos;

}

void ArvoreHuffman::ConstroiSerie(const std::string& serie, No*& atual, int& i) {
    if (i >= (int)serie.length()) {
        return;
    }

    char bit = serie[i++];
    if (bit == '0') {
        // Se o bit for 0, significa que é um nó interno
        No* novo = new No();
        if (raiz == NULL) {
            raiz = novo;
        }
        atual = novo;
        // Construímos a sub-árvore à esquerda e à direita desse nó
        ConstroiSerie(serie, atual->esq, i);
        ConstroiSerie(serie, atual->dir, i);
    } else if (bit == '1') {
        // Se o bit for 1, significa que é um nó folha e os 8 bits subsequentes representam o caractere desta folha
        char caractere = BinToChar(serie.substr(i, 8));
        i += 8;
        No* novo = new No(caractere, 0);
        tam++;
        atual = novo;
    }
}

bool ArvoreHuffman::BuscarCodigoHuffman(No* no, char ch, std::string& codigo, std::string caminho) {

    if (no == NULL) return false; // Não achou
    
    if (no->item.chave == ch) {
        // Achou o caractere
        codigo = caminho;
        return true;
    }

    // Busca na sub-árvore à esquerda, adicionando um "0"
    if (BuscarCodigoHuffman(no->esq, ch, codigo, caminho + "0")) return true;
    
    // Busca na sub-árvore à direita, adicionando um "1"
    if (BuscarCodigoHuffman(no->dir, ch, codigo, caminho + "1")) return true;
    
    // Não está na sub-árvore
    return false;

}

std::string ArvoreHuffman::ObterCodigoHuffman(No* r, char caractere) {
    
    if (r == NULL) return "";
    
    if (r->item.chave == caractere) return "";
    
    std::string codigo;
    // Buscamos na sub-árvore à esquerda. Se o elemento estiver lá, retornamos o caminho percorrido para chegar nele
    if (BuscarCodigoHuffman(r->esq, caractere, codigo, "0")) return codigo;
    // Buscamos na sub-árvore à direita. Se o elemento estiver lá, retornamos o caminho percorrido para chegar nele
    if (BuscarCodigoHuffman(r->dir, caractere, codigo, "1")) return codigo;

    return ""; // Não achamos o caractere

}

std::string ArvoreHuffman::ObterMensagem(std::string codigo) {

    No* atual = raiz;
    std::string original;

    for(char bit : codigo) {
        // Para cada caractere da string codigo, percorremos na árvore
        if(atual != NULL) {
            if(bit == '0') atual = atual->esq;          // bit 0: deslocamos para a esquerda
            else if(bit == '1') atual = atual->dir;     // bit 1: deslocamos para a direita

            if(atual != NULL) { // Evita acessos incorretos na memória
                if(atual->esq == NULL && atual->dir == NULL) {
                    // Chegamos em um nó folha. Ou seja, o sub-código de um caractere acabou e se iniciará o do próximo
                    original += atual->item.chave;
                    atual = raiz;
                } 
            }
        }
    }

    // A mensaegm original é retornada
    return original;
}

void ArvoreHuffman::LimpaRecursivo(No* r){
    if(r != NULL) {
        // Enquanto houver elementos na árvore, apagamos recursivamente os nós alocados, a partir da raiz No* r
        LimpaRecursivo(r->esq);
        LimpaRecursivo(r->dir);
        delete r;
    }
}

void ArvoreHuffman::Limpa() {
    // Usa o LimpaRecursivo(raiz) para limpar toda a árvore e então deixa raiz = NULL e tam = 0
    LimpaRecursivo(raiz);
    raiz = NULL;
    tam = 0;
}

ArvoreHuffman::~ArvoreHuffman() {
    // Basta chamar o método Limpa()
    Limpa();
}