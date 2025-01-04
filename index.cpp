#include <iostream>
#include <locale>

using namespace std;

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
        newLetter->letter = c;          // Armazenar letra
        newLetter->isGuessed = false;   // Deixa não inicializado como padrão
        newLetter->next = nullptr;      // Mostra o caminho para próxima letr

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

/*void showAvatar()
{
    cout << "_______" << endl;
    cout << "|     |" << endl;
    cout << "|   (o-o)" << endl;  // errou aqui
    cout << "|    /|\\" << endl; // depois aqui mostrando
    cout << "|     |   " << endl;
    cout << "|    / \\ " << endl;
}
*/

/*void menu()
{
    int opcao;
    do{
        cout<<"0 - Digitar palavra a ser adivinhada"<<endl;
        cout <<"1 - Advinhar a palavra" << endl;
        cout <<"2 - Estado atual do Avatar" << endl;
        cout <<"3 - Letras usada" << endl;
        cout <<"4 - Encerrar programa"<<endl;
        cin>>opcao; //Palavra escolhida

        switch(opcao){
            case 0:
            digitarpalavra();
            break;
            case 1:
            advinharpalavra();
            break;
            case 2:
            showAvatar();
            break;
            case 3:
            showLetrasUsadas();
            break;
            default:
            cout<<"opção invalida!"<<endl;
            break;
        }
    while(opcao != 4);
   }

}*/

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    string word;
    cout << "JOGADOR 1 - Escolha uma palavra a ser adivinhada (utilize apenas letras e sem acento): " << endl;
    cin >> word;

    Letter *chosenWord = storeWord(word);
    showWord(chosenWord);
}