#include <iostream>
#include <locale>
#include <unordered_set>

using namespace std;

int score = 0; // Pontuação do jogador. Quando chegar em 5, o usuário perde o jogo.

// Função para limpar o console, compatível com Windows e Linux/macOS
void clearConsole() {
#ifdef _WIN32
    system("cls"); // Comando para Windows
#else
    system("clear"); // Comando para Linux/macOS
#endif
    cout << "========== JOGO DA FORCA ==========" << endl; // Exibe o título do jogo após limpar o console.
}

// Estrutura para armazenar cada caractere da palavra escolhida
struct Letter {
    char letter; // Armazena o caractere da letra.
    bool isGuessed; // Indica se a letra foi adivinhada pelo jogador.
    Letter *next; // Ponteiro para a próxima letra na lista encadeada.
};

// Função para criar uma lista com as letras da palavra escolhida
Letter *storeWord(const string &word) {
    Letter *head = nullptr; // Ponteiro para o início da lista (primeira letra).
    Letter *tail = nullptr; // Ponteiro para o final da lista (última letra).

    // Para cada caractere da palavra, cria uma nova letra e adiciona na lista
    for (char c: word) {
        Letter *newLetter = new Letter; // Alocar nova letra
        newLetter->letter = tolower(c); // Armazenar letra em minúscula
        newLetter->isGuessed = false; // Deixa não adivinhado como falso por padrão
        newLetter->next = nullptr; // Inicializa o ponteiro para a próxima letra como nullptr

        // Verificar se a lista ainda está vazia.
        if (head == nullptr) {
            head = newLetter; // Define o ponteiro da letra de início da lista encadeada como a nova letra.
        } else {
            tail->next = newLetter; // Se a lista não está vazia, a nova letra é adicionada ao final
        }

        tail = newLetter; // Atualiza o ponteiro do fim da lista encadeada para a nova letra.
    }

    return head; // Retorna o ponteiro para o início da lista encadeada.
}

// Função que exibe a palavra com letras adivinhadas ou espaços em branco.
void showWord(Letter *head) {
    Letter *current = head; // Ponteiro para percorrer a lista de letras.

    while (current != nullptr) {
        // Verifica se a letra foi adivinhada.
        if (current->isGuessed) {
            cout << current->letter << " "; // Exibe a letra.
        } else {
            cout << "_ "; // Exibe um espaço em branco no lugar da letra.
        }

        current = current->next; // Avança para a próxima letra da lista.
    }
}

// Função responsável por exibir o estado atual do boneco na forca com base na pontuação (erros).
void showHanging() {
    cout << "Tentativas restantes: " << 5 - score << endl; // Mostra o número de tentativas restantes.

    // Nenhum erro cometido ainda, exibe apenas a base da forca.
    if (score == 0) {
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
    } else if (score == 1) {
        // Primeiro erro, exibe a cabeça do boneco.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl; // Cabeça representada por "(o-o)".
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
    } else if (score == 2) {
        // Segundo erro, adiciona os braços e o tronco.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl; // Cabeça.
        cout << "|    /|\\" << endl; // Braços e tronco.
        cout << "|" << endl;
        cout << "|" << endl;
    } else if (score == 3) {
        // Terceiro erro, adiciona a parte superior do corpo.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl; // Cabeça.
        cout << "|    /|\\" << endl; // Braços.
        cout << "|     |   " << endl; // Tronco.
        cout << "|" << endl;
    } else if (score == 4) {
        // Quarto erro, adiciona uma perna.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl; // Cabeça.
        cout << "|    /|\\" << endl; // Braços.
        cout << "|     |   " << endl; // Tronco.
        cout << "|    /" << endl; // Uma perna.
    } else if (score == 5) {
        // Quinto erro, exibe o boneco completo e marca o fim do jogo.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (x-x)" << endl; // Cabeça com "x-x" para indicar derrota.
        cout << "|    /|\\" << endl; // Braços.
        cout << "|     |   " << endl; // Tronco.
        cout << "|    / \\ " << endl; // Ambas as pernas.
    } else {
        // Caso o valor de `score` seja inválido, exibe uma mensagem de erro.
        cout << "Erro na quantidade de pontos!";
    }
}

// Estrutura para armazenar cada letra errada
struct MissedLetter {
    char letter; // Armazena o caractere da letra errada.
    MissedLetter *next; // Ponteiro para a próxima letra errada na lista encadeada.
};

// Função que armazena as letras erradas como uma lista encadeada.
MissedLetter *storeMissedWord(const string &word) {
    MissedLetter *head = nullptr; // Ponteiro para o início da lista (primeira letra errada).
    MissedLetter *tail = nullptr; // Ponteiro para o final da lista (última letra errada).

    // Percorre a string fornecida para armazenar cada letra.
    for (char c: word) {
        MissedLetter *newMissedLetter = new MissedLetter; // Aloca dinamicamente uma nova letra errada.
        newMissedLetter->letter = tolower(c); // Armazenar letra em minuscula.
        newMissedLetter->next = nullptr; // Inicializa o ponteiro para a próxima letra errada como nullptr

        // Verifica se a lista ainda está vazia.
        if (head == nullptr) {
            head = newMissedLetter;
            // Define o ponteiro da letra de início da lista encadeada como a letra errada criada.
        } else {
            tail->next = newMissedLetter; // Se a lista não está vazia, a nova letra é adicionada ao final
        }

        tail = newMissedLetter; // Atualiza o ponteiro do fim da lista encadeada para a nova letra.
    }

    return head; // Retorna o ponteiro para o início da lista encadeada.
}

// Função que exibe todas as letras erradas armazenadas na lista.
void showMissedLetters(MissedLetter *head) {
    cout << "\nLetras erradas: "; // Exibe o título "Letras erradas".
    MissedLetter *current = head; // Ponteiro para percorrer a lista de letras erradas.

    // Percorre toda a lista.
    while (current != nullptr) {
        cout << current->letter << " "; // Exibe cada letra errada separada por espaço.
        current = current->next; // Avança para a próxima letra errada na lista.
    }

    cout << endl; // Quebra de linha após exibir todas as letras erradas.
}

// Função que verifica se o caractere fornecido é uma letra válida.
bool isLetter(char letter) {
    return (std::isalpha(letter) && // Verifica se o caractere é uma letra do alfabeto.
            (letter == std::tolower(letter)) && // Garante que a letra esteja em minúscula.
            (letter >= 'a') && (letter <= 'z')) || // Verifica se está no intervalo de 'a' a 'z'.
           ((letter >= 'A') && (letter <= 'Z')); // Ou no intervalo de 'A' a 'Z'.
}

// Função que verifica se a letra adivinhada está na palavra e marca como adivinhada se encontrada.
bool guessLetter(Letter *head, char guess) {
    Letter *current = head; // Ponteiro para percorrer a lista de letras.
    bool found = false; // Variável para indicar se a letra foi encontrada.

    // Percorre a lista de letras e confere se tem alguma letra igual ao guess
    while (current != nullptr) {
        // Verifica se a letra é igual à adivinhada e se ainda não foi marcada.
        if (current->letter == guess && !current->isGuessed) {
            current->isGuessed = true; // Marca a letra como adivinhada
            found = true; // Define `found` como verdadeiro, indicando que a letra foi encontrada.
        }

        current = current->next; // Avança para a próxima letra na lista.
    }
    return found; // Retorna se a letra foi encontrada ou não.
}

// Função que verifica se todas as letras da palavra foram adivinhadas.
bool hasGuessedAll(Letter *head) {
    Letter *current = head; // Ponteiro para percorrer a lista de letras.

    // Percorre a lista de letras.
    while (current != nullptr) {
        // Se encontrar uma letra que não foi adivinhada, retorna falso.
        if (!current->isGuessed) {
            return false;
        }
        current = current->next; // Avança para a próxima letra.
    }

    return true; // Retorna verdadeiro se todas as letras foram adivinhadas.
}

// Função que altera o estado isGuessed de cada letra
void updateGuessedLetters(Letter *head, char guess) {
    Letter *current = head; // Ponteiro para percorrer a lista de letras.

    // Percorre a lista de letras.
    while (current != nullptr) {
        // Verifica se a letra atual é igual à adivinhada.
        if (current->letter == guess) {
            current->isGuessed = true; // Marca a letra como adivinhada.
            break; // Interrompe o loop após encontrar a letra.
        }

        current = current->next; // Avança para a próxima letra na lista.
    }
}

// Função que verifica se a palavra contém caracteres que não são letras.
bool containsAccent(const string &word) {
    // Percorre cada caractere da palavra.
    for (char c: word) {
        // Verifica se o caractere não é uma letra válida.
        if (!isLetter(c)) {
            return true; // Retorna verdadeiro se encontrar um caractere inválido.
        };
    }

    return false; // Retorna falso se todos os caracteres forem letras.
}

// Função principal que controla o fluxo do jogo.
void startGame(Letter *chosenWord) {
    MissedLetter *missedLetters = nullptr; // Lista encadeada para armazenar letras erradas.
    char guess; // Variável para armazenar a letra adivinhada pelo jogador.
    unordered_set<char> guessedLetters; // Conjunto para armazenar letras já tentadas

    // Loop principal do jogo que continua enquanto o jogador não perder (score < 5).
    while (score < 5) {
        showHanging(); // Exibe o estado atual do boneco na forca.
        showWord(chosenWord); // Exibe a palavra com as letras adivinhadas ou "_".
        showMissedLetters(missedLetters); // Exibe as letras erradas já digitadas.

        cout << "\nDigite uma letra: ";
        cin >> guess; // Recebe a entrada do jogador.

        // Verifica se o caractere digitado é uma letra válida.
        if (isLetter(guess)) {
            guess = tolower(guess); // Deixa minúscula

            // Verifica se a letra já foi tentada anteriormente.
            if (guessedLetters.find(guess) != guessedLetters.end()) {
                clearConsole(); // Limpa o console.
                cout << "Letra repetida, tente novamente! ";
                continue; // Se já foi tentada, pede nova letra
            }

            guessedLetters.insert(guess); // Adiciona a letra ao conjunto de letras tentadas

            // Verificar se a letra está na palavra
            // Se a letra não está na palavra, incrementa o score e armazena a letra errada
            if (!guessLetter(chosenWord, guess)) {
                MissedLetter *newMissedLetter = new MissedLetter; // Cria uma nova letra errada.
                newMissedLetter->letter = guess; // Armazena a letra errada.
                newMissedLetter->next = missedLetters; // Adiciona na lista encadeada de letras erradas.
                missedLetters = newMissedLetter; // Atualiza o ponteiro para a nova letra errada.
                score++; // Incrementa o número de erros.
            }

            // Verifica se todas as letras da palavra foram adivinhadas.
            if (hasGuessedAll(chosenWord)) {
                clearConsole(); // Limpa o console.
                cout << "Palavra adivinhada! "; // Mensagem de vitória.
                break; // Sai do loop, encerrando o jogo.
            }

            clearConsole(); // Limpa o console para a próxima interação.
        } else {
            // Caso o caractere digitado não seja uma letra válida.
            clearConsole(); // Limpa o console.
            cout << "O caractere digitado deve ser uma letra sem acento! "; // Mensagem de erro
        }

        // Verifica se o jogador atingiu o limite de tentativas.
        if (score == 5) {
            cout << "Sem mais tentativas! "; // Mensagem indicando que o jogador perdeu.
        }
    }
}

// Função para exibir o menu principal do jogo.
void menu() {
    cout << "1. Iniciar o jogo" << endl;
    cout << "2. Regras" << endl;
    cout << "3. Sair" << endl;
    cout << "Escolha: ";
    int choice; // Variável para armazenar a escolha do jogador no menu.
    cin >> choice;

    // Realiza uma ação com base na escolha do jogador.
    switch (choice) {
        // Caso o jogador insira o número 1, inicia o jogo.
        case 1:
            clearConsole(); // Limpa o console antes de iniciar o jogo.
            break;
        // Caso o jogador insira o número 2, exibe as regras do jogo.
        case 2:
            clearConsole(); // Limpa o console antes de exibir as regras.
            cout << "REGRAS DO JOGO:" << endl;
            cout <<
                    "- O JOGADOR 1 escolhe uma palavra sem caracteres especiais ou acentos.\n- O JOGADOR 2 tenta adivinhar a palavra, letra por letra.\n- Para cada erro, aparece um novo desenho complementando o boneco da forca.\n- O jogo termina quando o JOGADOR 2 adivinha a palavra ou esgota as 5 tentativas."
                    << endl;
            cout << "Pressione ENTER para voltar ao menu..." << endl;
            cin.ignore();
            cin.get(); // Aguarda o jogador pressionar ENTER para voltar ao menu.
            clearConsole();
            menu(); // Retorna ao menu principal.
            break;
        // Caso o jogador insira o número 3, encerra o programa.
        case 3:
            clearConsole(); // Limpa o console antes de sair.
            cout << "Obrigado por jogar!" << endl;
            exit(0); // Encerra o programa.
        // Easter egg para os mais testadores.
        case 4:
            clearConsole();
            cout << "Obrigado pelos ensinamentos :D" << endl;
            menu(); // Retorna ao menu principal.
            break;
        // Caso o jogador insira um número inválido, exibe uma mensagem de erro.
        default:
            clearConsole(); // Limpa o console para exibir a mensagem de erro.
            cout << "Escolha de 1 a 3." << endl; // Mensagem caso o jogador insira uma opção inválida.
            menu(); // Retorna ao menu principal.
            break;
    }
}

string chooseWord(Letter *&chosenWord) {
    string word;

    do {
        cout << "JOGADOR 1 - Escolha uma palavra a ser adivinhada (utilize apenas letras e sem acento): ";
        cin >> word;
        if (containsAccent(word)) {
            // Verifica se a palavra contém caracteres inválidos.
            cout << "Tente novamente com uma palavra sem acentos ou caracteres especiais." << endl;
        }
    } while (containsAccent(word)); // Repete até que o jogador 1 forneça uma palavra válida.

    chosenWord = storeWord(word); // Cria a lista de letras da palavra escolhida.
    cout << "JOGADOR 1 - Palavra escolhida com sucesso! Pressione ENTER para iniciar o jogo de JOGADOR 2" << endl;
    cin.ignore();
    cin.get(); // Aguarda o jogador pressionar ENTER para continuar.

    clearConsole(); // Limpa o console antes de iniciar o jogo.

    return word; // Retorna a palavra escolhida pra função da main.
}

int main() {
    setlocale(LC_ALL, "Portuguese"); // Configura o idioma para exibir caracteres acentuados corretamente.
    clearConsole(); // Limpa o console ao iniciar o jogo.
    menu(); // Exibe o menu principal.

    Letter *chosenWord = nullptr; // Pré-aloca memória para a palavra escolhida.
    string word = chooseWord(chosenWord); // Solicita uma palavra ao jogador 1, garantindo que não tenha acentos ou caracteres especiais.
    startGame(chosenWord); // Inicia o jogo, passando a palavra escolhida.

    cout << "A palavra escolhida foi " << word << "." << endl; // Exibe a palavra após o término do jogo.
    return 0;
}
