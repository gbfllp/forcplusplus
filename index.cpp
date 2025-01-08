#include <iostream>
#include <locale>
#include <unordered_set>

using namespace std;

int score = 0; // Pontuação do jogador. Quando chegar em 5, o usuário perde o jogo.

void clearConsole()
{
#ifdef _WIN32
    system("cls"); // Comando para Windows
#else
    system("clear"); // Comando para Linux/macOS
#endif
cout << "========== JOGO DA FORCA ==========" << endl; // Exibe o título do jogo após limpar o console.

}

struct Letter
{ // Estrutura para armazenar cada caractere da palavra escolhida
    char letter; // Armazena o caractere da letra.
    bool isGuessed; // Indica se a letra foi adivinhada pelo jogador.
    Letter *next; // Ponteiro para a próxima letra na lista encadeada.
};

Letter *storeWord(const string &word)
{ // Função para criar uma lista com as letras da palavra
    Letter *head = nullptr; // Ponteiro para o início da lista (primeira letra).
    Letter *tail = nullptr; // Ponteiro para o final da lista (última letra).
    for (char c : word)
    {
        Letter *newLetter = new Letter; // Alocar nova letra
        newLetter->letter = tolower(c); // Armazenar letra em minuscula
        newLetter->isGuessed = false;   // Deixa não inicializado como padrão
        newLetter->next = nullptr;      // Mostra o caminho para próxima letra

        if (head == nullptr)
        { // Verifica se a lista ainda está vazia.
            head = newLetter; // Detecta se é a primeira letra
        }
        else
        {
            tail->next = newLetter; // Se a lista não está vazia, a nova letra é adicionada ao final
        }

        tail = newLetter; // Atualiza o ponteiro `tail` para a nova letra.
    }

    return head; // Retorna o ponteiro para o início da lista encadeada.
}

void showWord(Letter *head)
{ // Função que exibe a palavra com letras adivinhadas ou espaços em branco.
    Letter *current = head; // Ponteiro para percorrer a lista de letras.
    while (current != nullptr)
    {
        if (current->isGuessed)
        { // Verifica se a letra foi adivinhada.
            cout << current->letter << " "; // Exibe a letra.
        }
        else
        {
            cout << "_ "; // Exibe um espaço em branco no lugar da letra.
        }
        current = current->next; // Avança para a próxima letra da lista.
    }
}

void showHanging()
{ // Função responsável por exibir o estado atual do boneco na forca com base na pontuação (erros).
    cout << "Tentativas restantes: " << 5 - score << endl; // Mostra o número de tentativas restantes.
    if (score == 0)
    { // Nenhum erro cometido ainda, exibe apenas a base da forca.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
    }
    else if (score == 1)
    { // Primeiro erro, exibe a cabeça do boneco.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl; // Cabeça representada por "(o-o)".
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
    }
    else if (score == 2)
    { // Segundo erro, adiciona os braços e o tronco.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl; // Cabeça.
        cout << "|    /|\\" << endl; // Braços e tronco.
        cout << "|" << endl;
        cout << "|" << endl;
    }
    else if (score == 3)
    { // Terceiro erro, adiciona a parte superior do corpo.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl; // Cabeça.
        cout << "|    /|\\" << endl; // Braços.
        cout << "|     |   " << endl; // Tronco.
        cout << "|" << endl;
    }
    else if (score == 4)
    { // Quarto erro, adiciona uma perna.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl; // Cabeça.
        cout << "|    /|\\" << endl; // Braços.
        cout << "|     |   " << endl; // Tronco.    
        cout << "|    /" << endl; // Uma perna.
    }
    else if (score == 5)
    { // Quinto erro, exibe o boneco completo e marca o fim do jogo.
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (x-x)" << endl; // Cabeça com "x-x" para indicar derrota.
        cout << "|    /|\\" << endl; // Braços.
        cout << "|     |   " << endl; // Tronco.
        cout << "|    / \\ " << endl; // Ambas as pernas.
    }
    else
    { // Caso o valor de `score` seja inválido, exibe uma mensagem de erro.
        cout << "Erro na quantidade de pontos!";
    }
}

struct MissedLetter
{ // Estrutura para armazenar cada letra errada
    char letter; // Armazena o caractere da letra errada.
    MissedLetter *next; // Ponteiro para a próxima letra errada na lista encadeada.
};

MissedLetter *storeMissedWord(const string &word)
{ // Função que armazena as letras erradas como uma lista encadeada.
    MissedLetter *head = nullptr; // Ponteiro para o início da lista (primeira letra errada).
    MissedLetter *tail = nullptr; // Ponteiro para o final da lista (última letra errada).
    for (char c : word)
    { // Percorre a string fornecida para armazenar cada letra.
        MissedLetter *newMissedLetter = new MissedLetter; // Aloca dinamicamente uma nova letra errada.
        newMissedLetter->letter = tolower(c);             // Armazenar letra em minuscula.
        newMissedLetter->next = nullptr;                  // Mostra o caminho para próxima letra e define como nulo.

        if (head == nullptr)
        { // Verifica se a lista ainda está vazia.
            head = newMissedLetter; // Detecta se é a primeira letra
        }
        else
        {
            tail->next = newMissedLetter; // Se a lista não está vazia, a nova letra é adicionada ao final
        }

        tail = newMissedLetter; // Muda a tail para a nova letra
    }

    return head; // Retorna o ponteiro para o início da lista encadeada.
}

void showMissedLetters(MissedLetter *head)
{ // Função que exibe todas as letras erradas armazenadas na lista.
    cout << "\nLetras erradas: "; // Exibe o título "Letras erradas".   
    MissedLetter *current = head; // Ponteiro para percorrer a lista de letras erradas.
    while (current != nullptr)  
    { // Percorre toda a lista.
        cout << current->letter << " "; // Exibe cada letra errada separada por espaço.
        current = current->next; // Avança para a próxima letra errada na lista.
    }
    cout << endl; // Quebra de linha após exibir todas as letras erradas.
}

bool isLetter(char letter) { // Função que verifica se o caractere fornecido é uma letra válida.
    return (std::isalpha(letter) && // Verifica se o caractere é uma letra do alfabeto.
        (letter == std::tolower(letter)) && // Garante que a letra esteja em minúscula.
        (letter >= 'a') && (letter <= 'z')) || // Verifica se está no intervalo de 'a' a 'z'.
        ((letter >= 'A') && (letter <= 'Z')); // Ou no intervalo de 'A' a 'Z'.
}

bool guessLetter(Letter *head, char guess)
{ // Função que verifica se a letra adivinhada está na palavra e marca como adivinhada se encontrada.
    Letter *current = head; // Ponteiro para percorrer a lista de letras.
    bool found = false; // Variável para indicar se a letra foi encontrada.
    while (current != nullptr) // Percorre a lista de letras e confere se tem alguma letra igual ao guess
    {
        if (current->letter == guess && !current->isGuessed)
        { // Verifica se a letra é igual à adivinhada e se ainda não foi marcada.
            current->isGuessed = true; // Marca a letra como adivinhada
            found = true; // Define `found` como verdadeiro, indicando que a letra foi encontrada.
        }
        current = current->next; // Avança para a próxima letra na lista.
    }
    return found; // Retorna se a letra foi encontrada ou não.
}

bool hasGuessedAll(Letter *head)
{ // Função que verifica se todas as letras da palavra foram adivinhadas.
    Letter *current = head; // Ponteiro para percorrer a lista de letras. 
    while (current != nullptr)
    {
        if (!current->isGuessed)
        { // Se encontrar uma letra que não foi adivinhada, retorna falso.
            return false;
        }
        current = current->next; // Avança para a próxima letra.
    }
    return true; // Retorna verdadeiro se todas as letras foram adivinhadas.
}

// Função que altera o estado isGuessed de cada letra
void updateGuessedLetters(Letter *head, char guess)
{
    Letter *current = head; // Ponteiro para percorrer a lista de letras.
    while (current != nullptr)
    {
        if (current->letter == guess)
        { // Verifica se a letra atual é igual à adivinhada.
            current->isGuessed = true; // Marca a letra como adivinhada.
        }
        current = current->next; // Avança para a próxima letra na lista.
    }
}

bool containsAccent(const string &word)
{ // Função que verifica se a palavra contém caracteres que não são letras.
    for (char c : word) { // Percorre cada caractere da palavra.
        if(!isLetter(c)) { // Verifica se o caractere não é uma letra válida.
            return true; // Retorna verdadeiro se encontrar um caractere inválido.
        };
    }
    return false; // Retorna falso se todos os caracteres forem letras.
}

void startGame(Letter *chosenWord)
{  // Função principal que controla o fluxo do jogo.
    MissedLetter *missedLetters = nullptr; // Lista encadeada para armazenar letras erradas.
    char guess; // Variável para armazenar a letra adivinhada pelo jogador.
    unordered_set<char> guessedLetters; // Conjunto para armazenar letras já tentadas
    // comparar score, se maior que 5, sai do loop e mensagem de perdeu
    while (score < 5)
    { // Loop principal do jogo que continua enquanto o jogador não perder (score < 5).
        showHanging(); // Exibe o estado atual do boneco na forca.
        showWord(chosenWord); // Exibe a palavra com as letras adivinhadas ou "_".
        showMissedLetters(missedLetters); // Exibe as letras erradas já digitadas.
        
        cout << "\nDigite uma letra: ";
        cin >> guess; // Recebe a entrada do jogador.
        if(isLetter(guess)) { // Verifica se o caractere digitado é uma letra válida.
            guess = tolower(guess); // Deixa minúscula
            
            if (guessedLetters.find(guess) != guessedLetters.end())
            { // Verifica se a letra já foi tentada anteriormente.
                clearConsole(); // Limpa o console.
                cout << "Letra repetida, tente novamente! ";
                continue; // Se já foi tentada, pede nova letra
            }
            guessedLetters.insert(guess); // Adiciona a letra ao conjunto de letras tentadas

            // Verificar se a letra está na palavra
            if (!guessLetter(chosenWord, guess))
            {
                // Se a letra não está na palavra, incrementa o score e armazena a letra errada
                MissedLetter *newMissedLetter = new MissedLetter; // Cria uma nova letra errada.
                newMissedLetter->letter = guess; // Armazena a letra errada.
                newMissedLetter->next = missedLetters; // Adiciona na lista encadeada de letras erradas.
                missedLetters = newMissedLetter; // Atualiza o ponteiro para a nova letra errada.
                score++; // Incrementa o número de erros.
            }
            if(hasGuessedAll(chosenWord)){ // Verifica se todas as letras da palavra foram adivinhadas.
                clearConsole(); // Limpa o console.
                cout<<"Palavra adivinhada! "; // Mensagem de vitória.
                break; // Sai do loop, encerrando o jogo.
            }
            clearConsole(); // Limpa o console para a próxima interação.
        }
        else { // Caso o caractere digitado não seja uma letra válida.
            clearConsole(); // Limpa o console.
            cout<<"O caractere digitado deve ser uma letra sem acento! ";// Mensagem de erro 
        }

        // quando a letra foi escolhida, verificar se ela está na palavra
        // se tiver, mudar o parametro isGuessed daquela letra pra verdadeiro

        // se resta mais chances e todos os isGuessed estão true:
        // mensagem que ganhou
        // se não, chama a função startGame(Letter *chosenWord) de novo

    if(score==5){ // Verifica se o jogador atingiu o limite de tentativas.
        cout << "Sem mais tentativas! "; // Mensagem indicando que o jogador perdeu.
    }
   }
}

void menu() { // Função para exibir o menu principal do jogo.
    cout << "1. Iniciar o jogo" << endl;
    cout << "2. Regras" << endl;
    cout << "3. Sair" << endl;
    cout << "Escolha: ";
    int choice; // Variável para armazenar a escolha do jogador no menu. 
    cin >> choice;
    switch (choice) { // Realiza uma ação com base na escolha do jogador.
    case 1:
        clearConsole(); // Limpa o console antes de iniciar o jogo.
        break;
    case 2:
        clearConsole(); // Limpa o console antes de exibir as regras.
        cout << "REGRAS DO JOGO:" << endl;
        cout << "- O JOGADOR 1 escolhe uma palavra sem caracteres especiais ou acentos.\n- O JOGADOR 2 tenta adivinhar a palavra, letra por letra.\n- Para cada erro, aparece um novo desenho complementando o boneco da forca.\n- O jogo termina quando o JOGADOR 2 adivinha a palavra ou esgota as 5 tentativas." << endl;
        cout << "Pressione ENTER para voltar ao menu..." << endl;
        cin.ignore();
        cin.get(); // Aguarda o jogador pressionar ENTER para voltar ao menu.
        clearConsole();
        menu(); // Retorna ao menu principal.
        break;
    case 3:
        clearConsole(); // Limpa o console antes de sair.
        cout << "Obrigado por jogar!" << endl;
        exit(0); // Encerra o programa.
        break;
    case 4: 
        clearConsole();
        cout<<"Obrigado pelos ensinamento :D" << endl; // Mensagem especial opcional.
        menu(); // Retorna ao menu principal.
        break;
    default:
        clearConsole(); // Limpa o console para exibir a mensagem de erro.
        cout << "Escolha de 1 a 3." << endl; // Mensagem caso o jogador insira uma opção inválida.
        menu(); // Retorna ao menu principal.
        break;
}
}

int main()
{ // Função principal do programa.
    setlocale(LC_ALL, "Portuguese"); // Configura o idioma para exibir caracteres acentuados corretamente.
    clearConsole(); // Limpa o console ao iniciar o jogo.
    menu(); // Exibe o menu principal.
    string word; // Variável para armazenar a palavra escolhida pelo jogador 1.

    do{ // Solicita uma palavra ao jogador 1, garantindo que não tenha acentos ou caracteres especiais.
        cout << "JOGADOR 1 - Escolha uma palavra a ser adivinhada (utilize apenas letras e sem acento): ";
        cin >> word;
        if(containsAccent(word)){ // Verifica se a palavra contém caracteres inválidos.
            cout << "Tente novamente com uma palavra sem acentos ou caracteres especiais." << endl;
        }
    } while(containsAccent(word)); // Repete até que o jogador 1 forneça uma palavra válida.
    
    Letter *chosenWord = storeWord(word); // Cria a lista de letras da palavra escolhida.
    cout << "JOGADOR 1 - Palavra escolhida com sucesso! Pressione ENTER para iniciar o jogo de JOGADOR 2" << endl;
    cin.ignore();
    cin.get(); // Aguarda o jogador pressionar ENTER para continuar.

    clearConsole(); // Limpa o console antes de iniciar o jogo.

    startGame(chosenWord); // Inicia o jogo, passando a palavra escolhida.
    cout << "A palavra escolhida foi " << word << "." << endl; // Exibe a palavra após o término do jogo.
}
