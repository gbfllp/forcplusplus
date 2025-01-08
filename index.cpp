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
// -------------------------------------------------------------------------------------------Comentários até aqui
void showHanging()
{
    cout << "Tentativas restantes: " << 5 - score << endl;
    if (score == 0)
    {
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
    }
    else if (score == 1)
    {
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
    }
    else if (score == 2)
    {
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl;
        cout << "|    /|\\" << endl;
        cout << "|" << endl;
        cout << "|" << endl;
    }
    else if (score == 3)
    {
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl;
        cout << "|    /|\\" << endl;
        cout << "|     |   " << endl;
        cout << "|" << endl;
    }
    else if (score == 4)
    {
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (o-o)" << endl;
        cout << "|    /|\\" << endl;
        cout << "|     |   " << endl;
        cout << "|    /" << endl;
    }
    else if (score == 5)
    {
        cout << "_______" << endl;
        cout << "|     |" << endl;
        cout << "|   (x-x)" << endl;
        cout << "|    /|\\" << endl;
        cout << "|     |   " << endl;
        cout << "|    / \\ " << endl;
    }
    else
    {
        cout << "Erro na quantidade de pontos!";
    }
}

struct MissedLetter
{ // Estrutura para armazenar cada letra errada
    char letter;
    MissedLetter *next;
};

MissedLetter *storeMissedWord(const string &word)
{ // Lista com as letras erradas
    MissedLetter *head = nullptr;
    MissedLetter *tail = nullptr;
    for (char c : word)
    {
        MissedLetter *newMissedLetter = new MissedLetter; // Alocar nova letra
        newMissedLetter->letter = tolower(c);             // Armazenar letra em minuscula
        newMissedLetter->next = nullptr;                  // Mostra o caminho para próxima letra

        if (head == nullptr)
        {
            head = newMissedLetter; // Detecta se é a primeira letra
        }
        else
        {
            tail->next = newMissedLetter; // Se a lista não está vazia, a nova letra é adicionada ao final
        }

        tail = newMissedLetter; // Muda a tail para a nova letra
    }

    return head;
}

void showMissedLetters(MissedLetter *head)
{
    cout << "\nLetras erradas: ";
    MissedLetter *current = head;
    while (current != nullptr)
    {
        cout << current->letter << " ";
        current = current->next;
    }
    cout << endl;
}

bool isLetter(char letter) {
    return (std::isalpha(letter) && (letter == std::tolower(letter)) && (letter >= 'a') && (letter <= 'z')) || ((letter >= 'A') && (letter <= 'Z'));
}

bool guessLetter(Letter *head, char guess)
{
    Letter *current = head;
    bool found = false;
    while (current != nullptr) // Percorre a lista de letras e confere se tem alguma letra igual ao guess
    {
        if (current->letter == guess && !current->isGuessed)
        {
            current->isGuessed = true; // Marca a letra como adivinhada
            found = true;
        }
        current = current->next;
    }
    return found;
}

bool hasGuessedAll(Letter *head)
{
    Letter *current = head;
    while (current != nullptr)
    {
        if (!current->isGuessed)
        {
            return false;
        }
        current = current->next;
    }
    return true;
}

// Função que altera o estado isGuessed de cada letra
void updateGuessedLetters(Letter *head, char guess)
{
    Letter *current = head;
    while (current != nullptr)
    {
        if (current->letter == guess)
        {
            current->isGuessed = true;
        }
        current = current->next;
    }
}

bool containsAccent(const string &word)
{
    for (char c : word) {
        if(!isLetter(c)) {
            return true;
        };
    }
    return false;
}

void startGame(Letter *chosenWord)
{   
    MissedLetter *missedLetters = nullptr;
    char guess;
    unordered_set<char> guessedLetters; // Conjunto para armazenar letras já tentadas
    // comparar score, se maior que 5, sai do loop e mensagem de perdeu
    while (score < 5)
    {
        showHanging();
        showWord(chosenWord);
        showMissedLetters(missedLetters);

        
        cout << "\nDigite uma letra: ";
        cin >> guess;
        if(isLetter(guess)) {
            guess = tolower(guess); // Deixa minúscula
            
            if (guessedLetters.find(guess) != guessedLetters.end())
            {
                clearConsole();
                cout << "Letra repetida, tente novamente! ";
                continue; // Se já foi tentada, pede nova letra
            }
            guessedLetters.insert(guess); // Adiciona a letra ao conjunto de letras tentadas

            // Verificar se a letra está na palavra
            if (!guessLetter(chosenWord, guess))
            {
                // Se a letra não está na palavra, incrementa o score e armazena a letra errada
                MissedLetter *newMissedLetter = new MissedLetter;
                newMissedLetter->letter = guess;
                newMissedLetter->next = missedLetters;
                missedLetters = newMissedLetter;
                score++;
            }
            if(hasGuessedAll(chosenWord)){
                clearConsole();
                cout<<"Palavra adivinhada! ";
                break;
            }
            clearConsole();
        }
        else {
            clearConsole();
            cout<<"O caractere digitado deve ser uma letra sem acento! ";// Mensagem de erro 
        }

        // quando a letra foi escolhida, verificar se ela está na palavra
        // se tiver, mudar o parametro isGuessed daquela letra pra verdadeiro

        // se resta mais chances e todos os isGuessed estão true:
        // mensagem que ganhou
        // se não, chama a função startGame(Letter *chosenWord) de novo
    
    if(score==5){
        cout << "Sem mais tentativas! ";
    }
   }
}

void menu() {
    cout << "1. Iniciar o jogo" << endl;
    cout << "2. Regras" << endl;
    cout << "3. Sair" << endl;
    cout << "Escolha: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        clearConsole();
        break;
    case 2:
        clearConsole();
        cout << "REGRAS DO JOGO:" << endl;
        cout << "- O JOGADOR 1 escolhe uma palavra sem caracteres especiais ou acentos.\n- O JOGADOR 2 tenta adivinhar a palavra, letra por letra.\n- Para cada erro, aparece um novo desenho complementando o boneco da forca.\n- O jogo termina quando o JOGADOR 2 adivinha a palavra ou esgota as 5 tentativas." << endl;
        cout << "Pressione ENTER para voltar ao menu..." << endl;
        cin.ignore();
        cin.get();
        clearConsole();
        menu();
        break;
    case 3:
        clearConsole();
        cout << "Obrigado por jogar!" << endl;
        exit(0);
        break;
    case 4: 
        clearConsole();
        cout<<"Obrigado pelos ensinamento :D" << endl;
        menu();
        break;
    default:
        clearConsole();
        cout << "Escolha de 1 a 3." << endl;
        menu();
        break;
}
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    clearConsole();
    menu();
    string word;

    do{
        cout << "JOGADOR 1 - Escolha uma palavra a ser adivinhada (utilize apenas letras e sem acento): ";
        cin >> word;
        if(containsAccent(word)){
            cout << "Tente novamente com uma palavra sem acentos ou caracteres especiais." << endl;
        }
    } while(containsAccent(word));
    
    Letter *chosenWord = storeWord(word);
    cout << "JOGADOR 1 - Palavra escolhida com sucesso! Pressione ENTER para iniciar o jogo de JOGADOR 2" << endl;
    cin.ignore();
    cin.get();

    clearConsole();

    startGame(chosenWord);
    cout << "A palavra escolhida foi " << word << "." << endl;
}
