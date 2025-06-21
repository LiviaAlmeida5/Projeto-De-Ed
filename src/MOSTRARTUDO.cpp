// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Função para mostrar todos os resgistros do arquivo

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "../include/dado.h"

using namespace std;

void visualizarTudo()
{
    ifstream arq("o.bin", ios::binary);
    if (!arq)
        throw runtime_error("Arquivo temporário inexistente");
    dado aux;
    int cont = 0;
    bool mostraDeUmaVez = false;

    while (arq.read(reinterpret_cast<char *>(&aux), sizeof(dado)))
    {
        ostringstream duasCasasDecimais; // variável para permitir a saída do dado com duas casas decimais sem prejudicar as demais saídas
        duasCasasDecimais << setprecision(2) << fixed << aux.Period;

        // Imprime o conteúdo
        cout << cont << ": ";
        cout << aux.Series_reference << " | " << duasCasasDecimais.str() << " | " << aux.Data_value << " | " << aux.Status << " | " << aux.Units << " | " << aux.Magnitude << " | " << aux.Subject << " | " << aux.Periodicity << " | " << aux.Group << " | " << aux.Series_title_1 << " | " << aux.Series_title_2 << " | " << aux.Series_title_3 << " | " << aux.Series_title_4 << " | " << aux.Series_title_5 << endl;
        cout << endl;
        cont++;

        // controle da saída (de 100 em 100 ou todos de uma vez)
        bool controle = true;
        while (!mostraDeUmaVez and controle and (cont % 100 == 0))
        {
            cout << "Digite '0' para mostrar o arquivo de uma vez ou '1' para mostrar mais 100 registros: ";

            int escolha;

            cin >> escolha;

            if (escolha == 0)
            {
                mostraDeUmaVez = !mostraDeUmaVez;
            }
            else if (escolha == 1)
            {
                controle = !controle;
            }
        }
    }

    // finalização
    cout << "Digite '0' para voltar ao menu inicial!" << endl;
    string voltar = "a";
    while (voltar != "0")
    {
        getline(cin, voltar);
    }
    system("clear");
}