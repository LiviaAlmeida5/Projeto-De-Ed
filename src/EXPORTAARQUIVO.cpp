// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Função para exportar as informações do arquivo binário para um csv

#include <iostream>
#include <fstream>
#include "../include/dado.h"
#include "../include/EXPORTAARQUIVO.h"

using namespace std;

void exportaArquivo()
{
    string nomeArquivo;
    dado buffer;

    cout << "Digite o nome do arquivo: ";
    cin >> nomeArquivo;
    cout << endl;

    ofstream teste(nomeArquivo);

    // escrita do cabeçaho
    teste << "Series_reference,Period,Data_value,Status,Units,Magnitude,Subject,Periodicity,Group,Series_title_1,Series_title_2,Series_title_3,Series_title_4,Series_title_5" << endl;

    ifstream in("o.bin");

    //escrita dos dados
    while (in.read((char*)(&buffer), sizeof(dado)))
    {
        teste << buffer.Series_reference << ',' << buffer.Period << ',' << buffer.Data_value << ',' << buffer.Status << ',' << buffer.Units << ',' << buffer.Magnitude << ',' << buffer.Subject << ',' << buffer.Periodicity << ',' << buffer.Group << ',' << buffer.Series_title_1 << ',' << buffer.Series_title_2 << ',' << buffer.Series_title_3 << ',' << buffer.Series_title_4 << ',' << buffer.Series_title_5 << endl;   
    }

    cout << "Arquivo criado com sucesso!" << endl << endl;

    cout << "Digite '0' para voltar ao menu inicial!" << endl;
    string voltar = "a";
    while (voltar != "0")
    {
        getline(cin, voltar);
    }
    system("clear");
}