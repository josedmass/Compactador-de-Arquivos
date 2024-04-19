# Compactador-de-Arquivos
Este projeto foi desenvolvido como Trabalho Prático 3 da disciplina de Estrutura de Dados da UFMG, realizado em 2023/01.

## Autor
- José Eduardo Duarte Massucato

## Descrição
O trabalho proposto tem por objetivo lidar com a compressão de arquivos, de forma que não haja perda de informações no processo. Diante desse contexto, por decisão de projeto, a compactação do arquivo foi feita por caractere, utilizando do algoritmo de Huffman. Este algoritmo baseia-se na construção de uma árvore binária que codifica os caracteres presentes no arquivo de entrada, atribuindo códigos menores aos caracteres mais recorrentes, fazendo com que eles então ocupem menos espaço no arquivo de saída.

## Funcionalidades
- Compactação de um arquivo de texto em outro de tamanho menor.
- Descompressão de um arquivo de texto, __compactado por este programa__, de volta a sua forma original.

OBS: Os detalhes da implementação, bem como as estruturas de dados utilizados e os métodos adotados, encontram-se em "Documentacao.pdf".

## Como usar
1. Navegue até a pasta TP no seu computador
```bash
cd /<caminho_para_a_pasta>/TP
```

2. Adicione um arquivo, com extensão .txt, de entrada desejado em ./TP.

3. Compile e execute o programa a partir do arquivo Makefile presente em ./TP
```bash
make run in=<entrada.txt> out=<saida.txt> opt=<opção>
```

OBS: a cada nova execução, <opção> deve ser substituído por -c, para compactar, ou por -d, para descompactar. Como explicitado anteriormente, caso a opção seja -d, o arquivo de entrada __deve__ ser um arquivo que foi compactado por este programa, senão comportamentos indeterminados ocorrerão.

4. A saída será direcionada para o arquivo de saída determinado.

5. Ao final das execuções, utilize o Makefile para limpar os arquivos gerados.
```bash
make clean
```

OBS: Um arquivo de entrada de exemplo, chamado "in.txt", foi adicionado em ./TP.