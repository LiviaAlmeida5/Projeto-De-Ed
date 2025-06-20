// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Função para alterar mostrar uma determinada parte do arquivo

#include <iostream>
#include <fstream>
#include "../include/dado.h"
#include <iomanip>
#include <sstream>

using namespace std;

void mostra_x_ate_y()
{
    ifstream arq("o.bin", ios::binary);

    int x, y;

    // recepção das posições 
    arq.seekg(0, arq.end);
    int tam = arq.tellg() / sizeof(dado);
    arq.seekg(0, arq.beg);

    do
    {
        cout << "A posição inicial a qual deseja mostrar (De 0 até " << tam-1 << "): " << endl;
        cin >> x;
        if (x < 0 or x >= tam)
        {
            cout << "Posição Inválida!!" << endl;
        }

    } while (x < 0 or x >= tam);

    do
    {
        cout << "A última posição a qual deseja mostrar: (De " << x << " até " << tam-1 << ")" << endl;
        cin >> y;
        if (y < x or y >= tam)
        {
            cout << "Posição Inválida!!" << endl;
        }

    } while (y < x or y >= tam);

    // escrita dos dados no terminal
    dado aux;
    int cont = x;
    arq.seekg(x * sizeof(dado));
    while (cont <= y)
    {
        arq.read(reinterpret_cast<char *>(&aux), sizeof(dado));
        
        // Imprime o conteúdo
        ostringstream teste;
        teste << setprecision(2) << fixed << aux.Period;

        cout << cont << ": ";
        cout << aux.Series_reference << " | " << teste.str() << " | " << aux.Data_value << " | " << aux.Status << " | " << aux.Units << " | " << aux.Magnitude << " | " << aux.Subject << " | " << aux.Periodicity << " | " << aux.Group << " | " << aux.Series_title_1 << " | " << aux.Series_title_2 << " | " << aux.Series_title_3 << " | " << aux.Series_title_4 << " | " << aux.Series_title_5 << endl;
        cout << endl;
        cont++;
    }

    // finalização da função
    cout << "Digite '0' para voltar ao menu inicial!" << endl;
    string voltar = "a";
    while (voltar != "0")
    {
        getline(cin, voltar);
    }
    system("clear");
}