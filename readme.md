# Trabalho de AED II - 12/01/2025

## Tema do trabalho: Jogo da Forca

Jogo em que o jogador tem que acertar qual é a palavra proposta, tendo como dica
o número de letras como também uma das letras reveladas. A cada letra errada, é
desenhada uma parte do corpo do enforcado. O jogo termina ou com o acerto da
palavra ou com o término do desenho.

## Funcionamento

Inicialmente, os jogadores terão acesso a um menu onde podem ver as regras do jogo, sair ou iniciar o jogo.
Caso inicie o jogo, o Jogador 1 deverá inserir uma palavra a ser adivinhada, utilizando de apenas letras, sem acentos ou espaçamento.
Após a inserção da palavra, deve ser pressionado ENTER para que o jogo comece de fato para o jogador 2.

O jogador 2 deverá jogar então um jogo de forca tradicional, sendo a palavra certa a inserida pelo jogador 1.
O jogador 2 poderá tentar qualquer letra, caso a palavra contenha a letra inserida, todas as ocorrências da mesma na palavra serão reveladas, 
caso erre terá mais um erro adicionado, caso chegue a 5 letras erradas, o jogador 2 perderá o jogo, caso adivinhe a palavra por inteiro, o jogador 2 ganhará o jogo.

## Como Executar o Projeto

Certifique-se de ter um compilador C++ instalado.

*É necessário ter um compilador como o g++ (parte do GCC) ou equivalente.*

1. Clone o repositório

```bash
git clone https://github.com/gbfllp/forcplusplus.git # clone o repositório usando o git
cd forcplusplus # vá para o diretório contendo o projeto
```

2. Compile o arquivo principal

```bash
g++ index.cpp -o forca # compila o arquivo "index.cpp" em um executável com o nome "forca"
```

3. Execute o arquivo compilado

* Caso esteja no windows, o arquivo a ser executado será "forca.exe", no linux/macOs simplesmente "forca".

## Autores

- César Nogueira
- Gabriel Fellipe
- Gabriel Henrique
- Ian Libânio
- João Bruno
