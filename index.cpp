#include <iostream>
#include <locale>

using namespace std;

int score = 0; // Quando chegar em 5, o usuário deve perder

void clearConsole()
{
#ifdef _WIN32
    system("cls"); // Comando para Windows
#else
    system("clear"); // Comando para Linux/macOS
#endif
}

struct Letter
{ // Estrutura para armazenar cada caractere da palavra escolhida
    char letter;
    bool isGuessed;
    Letter *next;
};

Letter *storeWord(const string &word)
{ // Função para criar uma lista com as letras da palavra
    Letter *head = nullptr;
    Letter *tail = nullptr;
    for (char c : word)
    {
        Letter *newLetter = new Letter; // Alocar nova letra
        newLetter->letter = tolower(c); // Armazenar letra em minuscula
        newLetter->isGuessed = false;   // Deixa não inicializado como padrão
        newLetter->next = nullptr;      // Mostra o caminho para próxima letra

        if (head == nullptr)
        {
            head = newLetter; // Detecta se é a primeira letra
        }
        else
        {
            tail->next = newLetter; // Se a lista não está vazia, a nova letra é adicionada ao final
        }

        tail = newLetter; // Muda a tail para a nova letra
    }

    return head;
}

void showWord(Letter *head)
{
    Letter *current = head;
    while (current != nullptr)
    {
        if (current->isGuessed)
        {
            cout << current->letter << " ";
        }
        else
        {
            cout << "_ ";
        }
        current = current->next;
    }
}

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
    cout << "Letras erradas: ";
    MissedLetter *current = head;
    while (current != nullptr)
    {
        cout << current->letter << " ";
        current = current->next;
    }
    cout << endl;
}

bool isLetter(char letter) {
        return std::isalpha(letter) && (letter == std::tolower(letter)) && (letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z');
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

void startGame(Letter *chosenWord)
{   
    MissedLetter *missedLetters = nullptr;
    char guess;
    // comparar score, se maior que 5, sai do loop e mensagem de perdeu
    while (score < 5)
    {
        showHanging();
        showWord(chosenWord);
        showMissedLetters(missedLetters);

        if(hasGuessedAll(cho))

        cout << "\nDigite uma letra!" << endl;
        cin >> guess;
        if(isLetter(guess)) {
            guess = tolower(guess); // Deixa minúscula
            clearConsole();
        } else {
            clearConsole();
            cout<<"O caractere digitado deve ser uma letra sem acento! ";// Mensagem de erro 
        }

        

        // quando a letra foi escolhida, verificar se ela está na palavra
        // se tiver, mudar o parametro isGuessed daquela letra pra verdadeiro

        // se resta mais chances e todos os isGuessed estão true:
        // mensagem que ganhou
        // se não, chama a função startGame(Letter *chosenWord) de novo
    }

    cout << "Sem mais tentativas! A palavra era: ";
    Letter *current = chosenWord;
    while (current != nullptr)
    {
        cout << current->letter;
        current = current->next;
    }
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    cout << "========== JOGO DA FORCA ==========" << endl;

    string word;
    cout << "JOGADOR 1 - Escolha uma palavra a ser adivinhada (utilize apenas letras e sem acento): ";
    cin >> word;

    Letter *chosenWord = storeWord(word);
    cout << "JOGADOR 1 - Palavra escolhida com sucesso! Pressione ENTER para iniciar o jogo de JOGADOR 2" << endl;
    cin.ignore();
    cin.get();

    clearConsole();

    startGame(chosenWord);
}