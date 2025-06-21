// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Função para exportar as informações do arquivo binário para um csv

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "../include/dado.h"

using namespace std;

void exportaArquivo()
{
    ifstream in("o.bin");
    if (!in)
        throw runtime_error("Arquivo temporário inexistente");

    string nomeArquivo;
    dado buffer;

    cout << "Digite o nome do arquivo: ";
    cin >> nomeArquivo;
    cout << endl;

    ofstream teste(nomeArquivo);

    // escrita do cabeçaho
    teste << "Series_reference,Period,Data_value,Status,Units,Magnitude,Subject,Periodicity,Group,Series_title_1,Series_title_2,Series_title_3,Series_title_4,Series_title_5" << endl;

    // escrita dos dados
    while (in.read((char *)(&buffer), sizeof(dado)))
    {
        ostringstream duasCasasDecimais; // variável para permitir a saída do dado com duas casas decimais sem prejudicar as demais saídas
        duasCasasDecimais << setprecision(2) << fixed << buffer.Period;

        teste << buffer.Series_reference << ',' << duasCasasDecimais.str() << ',' << buffer.Data_value << ',' << buffer.Status << ',' << buffer.Units << ',' << buffer.Magnitude << ',' << buffer.Subject << ',' << buffer.Periodicity << ',' << buffer.Group << ',' << buffer.Series_title_1 << ',' << buffer.Series_title_2 << ',' << buffer.Series_title_3 << ',' << buffer.Series_title_4 << ',' << buffer.Series_title_5 << endl;
    }

    cout << "Arquivo criado com sucesso!" << endl;
    cout << endl;

    cout << "Digite '0' para voltar ao menu inicial!" << endl;
    string voltar = "a";
    while (voltar != "0")
    {
        getline(cin, voltar);
    }
    system("clear");
}