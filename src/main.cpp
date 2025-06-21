// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Função principal com  abertura do arquivo, ordenação e menu principal

#include <iostream>
#include "../include/MOSTRARTUDO.h"
#include "../include/ORDENA.h"
#include "../include/ALTERA.h"
#include "../include/TROCA.h"
#include "../include/INSERE.h"
#include "../include/MOSTRARPARTE.h"
#include "../include/EXPORTAARQUIVO.h"
#include "../include/dado.h"
#include <fstream>
#include <string>

using namespace std;

void menu()
{
    system("clear");

    char opcao;

    do
    {
        cout << "O que deseja fazer?" << endl;
        cout << endl;
        cout << "[1] Adicionar um elemento no arquivo em uma posição específica qualquer." << endl;
        cout << "[2] Visualizar os registros entre duas posiçôes." << endl;
        cout << "[3] Alterar os dados de um registro." << endl;
        cout << "[4] Trocar dois registros de posição no arquivo." << endl;
        cout << "[5] Visualizar todos os registros do arquivo armazenados." << endl;
        cout << "[6] Exportar arquivo para CSV." << endl;
        cout << "[0] Encerrar o programa." << endl;
        cout << endl;

        cin >> opcao;
        switch (opcao)
        {
        case '1':
            system("clear");
            inserir();
            break;
        case '2':
            system("clear");
            mostra_x_ate_y();
            break;
        case '3':
            system("clear");
            alterar();
            break;
        case '4':
            system("clear");
            trocar();
            break;
        case '5':
            system("clear");
            visualizarTudo();
            break;
        case '6':
            system("clear");
            exportaArquivo();
        case '0':
            system("clear");
            break;
        default:
            system("clear");
            cout << "======================================================================================================================" << endl;
            cout << endl;
            cout << "Opção Inaválida!!" << endl;
            cout << endl;
            break;
        }

    } while (opcao != '0');
    remove("o.bin");
}

bool LeituraArquivo(string nome)
{
    string linha;
    char lixo;

    string auxVerificaCampoVazio;
    char auxVerificaCampoComVirgula;

    dado buffer;

    ifstream arq(nome);

    // caso não consiga abrir o arquivo
    if (!arq)
    {
        throw runtime_error("Arquivo inexistente");
    }

    // leitura do csv e escrita do binario
    ofstream saida("o.bin");

    getline(arq, linha);

    int i = 0;

    while (arq.getline(buffer.Series_reference, 20, ','))
    {
        arq >> buffer.Period;

        arq >> lixo;

        // tratamento de campo
        getline(arq, auxVerificaCampoVazio, ',');

        if (not auxVerificaCampoVazio.empty())
        {
            buffer.Data_value = stof(auxVerificaCampoVazio);
        }
        else
        {
            buffer.Data_value = -1;
        }

        arq >> buffer.Status;

        arq >> lixo;

        arq.getline(buffer.Units, 10, ',');

        arq >> buffer.Magnitude;

        arq >> lixo;

        arq.getline(buffer.Subject, 50, ',');

        arq.getline(buffer.Periodicity, 10, ',');

        // tratamento de campo com ',' no texto
        arq >> auxVerificaCampoComVirgula;

        if (auxVerificaCampoComVirgula == '"')
        {
            string guarda = "\"";
            string recebe;

            getline(arq, recebe, ',');

            guarda += (recebe + ",");

            getline(arq, recebe, ',');

            guarda += recebe;

            copy(&guarda[0], &guarda[guarda.size()], buffer.Group);
            buffer.Group[guarda.size()] = '\0';
        }
        else
        {
            string guarda = "";
            guarda += auxVerificaCampoComVirgula;
            string recebe;

            getline(arq, recebe, ',');

            guarda += recebe;

            copy(&guarda[0], &guarda[guarda.size()], buffer.Group);
            buffer.Group[guarda.size()] = '\0';
        }

        arq.getline(buffer.Series_title_1, 70, ',');

        arq.getline(buffer.Series_title_2, 70, ',');

        arq.getline(buffer.Series_title_3, 70, ',');

        arq.getline(buffer.Series_title_4, 70, ',');

        arq.getline(buffer.Series_title_5, 70);

        saida.write((const char *)(&buffer), sizeof(dado));
    }
    return true;
}

int main(int argc, char const *argv[])
{
    string nome;
    bool ConseguiuLer = false;

    // abertura do arquivo
    do
    {
        cout << "Digite o nome do arquivo: ";
        cin >> nome;
        try
        {
            ConseguiuLer = LeituraArquivo(nome);
        }
        catch (const std::exception &e)
        {
            cerr << e.what() << '\n';
        }

    } while (not ConseguiuLer);

    ordenar();

    menu();
    return 0;
}
