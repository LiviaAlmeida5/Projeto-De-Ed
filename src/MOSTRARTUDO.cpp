#include <iostream>
#include <fstream>
#include "../include/MOSTRARTUDO.h"
#include "../include/dado.h"

using namespace std;

void visualizarTudo()
{
    ifstream arq("o.bin", ios::binary);
    dado aux;
    int cont = 0;

    while (arq.read(reinterpret_cast<char *>(&aux), sizeof(dado)))
    {
        // Imprime o conteúdo
        cout << cont << ": ";
        cout << aux.Series_reference << " | " << aux.Period << " | " << aux.Data_value << " | " << aux.Status << " | " << aux.Units << " | " << aux.Magnitude << " | " << aux.Subject << " | " << aux.Periodicity << " | " << aux.Group << " | " << aux.Series_title_1 << " | " << aux.Series_title_2 << " | " << aux.Series_title_3 << " | " << aux.Series_title_4 << " | " << aux.Series_title_5 << endl
             << endl;
        cont++;
    }

    cout << "Digite '0' para voltar ao menu inicial!" << endl;
    string voltar = "a";
    while (voltar != "0")
    {
        getline(cin, voltar);
    }
    system("clear");
}