// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Função para inserir um registro em uma determinada posição

#include "../include/VALIDACAO.h"
#include "../include/dado.h"
#include <iostream>
#include <fstream>

using namespace std;

void inserir()
{
    // Abre arquivo para leitura + escrita
    fstream arq("o.bin", ios::in | ios::out | ios::binary);

    arq.seekg(0, ios::end);
    int total_registros = arq.tellg() / sizeof(dado);

    // acessa a posição
    int pos;

    do
    {
        cout << "Em qual posição você quer inserir (De 0 até " << total_registros << ")? ";
        cin >> pos;
        if (pos < 0 or pos > total_registros)
        {
            cout << "Posição inválida. " << endl;
        }

    } while (pos < 0 or pos > total_registros);

    // dados do novo registro
    dado novo;
    cout << "Escreva o novo registro: ";
    string aux;

    cin.ignore();
    do
    {
        cout << "Escreva o novo 'Series_reference': ";
        getline(cin, aux);

        if (validacao(19, aux))
        {
            aux.copy(novo.Series_reference, aux.size());
            novo.Series_reference[aux.size()] = '\0';
        }

    } while (aux.size() > 19 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Period'(data no formato 0000.00): ";
        getline(cin, aux);

        if (validacaoData(aux))
        {
            novo.Period = stof(aux);
        }
        else
        {
            cout << "======================================================================================================================" << endl;
            cout << endl;
            cout << "Valor inválido!!" << endl;
            cout << endl;
        }
    } while (not validacaoData(aux));

    do
    {
        cout << "Escreva o novo 'Data_value'(int): ";
        getline(cin, aux);

        if (validacaoFloat(aux))
        {
            novo.Data_value = stof(aux);
        }
        else
        {
            cout << "======================================================================================================================" << endl;
            cout << endl;
            cout << "Valor inválido!!" << endl;
            cout << endl;
        };

    } while (not validacaoFloat(aux) or aux.empty());

    do
    {
        cout << "Escreva o novo 'Status'(char): ";
        getline(cin, aux);

        if (aux.size() == 1)
        {
            novo.Status = aux[0];
        }
        else
        {
            cout << "======================================================================================================================" << endl;
            cout << endl;
            cout << "Char inválido!!" << endl;
            cout << endl;
        }

    } while (aux.size() != 1);

    do
    {
        cout << "Escreva o novo 'Units': ";
        getline(cin, aux);

        if (validacao(9, aux))
        {
            aux.copy(novo.Units, aux.size());
            novo.Units[aux.size()] = '\0';
        }

    } while (aux.size() > 9 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Magnitude'(int): ";
        getline(cin, aux);

        if (validacaoInt(aux))
        {
            novo.Magnitude = stoi(aux);
        }
        else
        {
            cout << "======================================================================================================================" << endl;
            cout << endl;
            cout << "Valor inválido!!" << endl;
            cout << endl;
        };

    } while (not validacaoInt(aux) or aux.empty());

    do
    {
        cout << "Escreva o novo 'Subject': ";
        getline(cin, aux);

        if (validacao(49, aux))
        {
            aux.copy(novo.Subject, aux.size());
            novo.Subject[aux.size()] = '\0';
        }

    } while (aux.size() > 49 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Periodicity': ";
        getline(cin, aux);

        if (validacao(9, aux))
        {
            aux.copy(novo.Periodicity, aux.size());
            novo.Periodicity[aux.size()] = '\0';
        }

    } while (aux.size() > 9 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Group': ";
        getline(cin, aux);

        if (validacao(99, aux))
        {
            aux.copy(novo.Group, aux.size());
            novo.Group[aux.size()] = '\0';
        }

    } while (aux.size() > 99 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_1': ";
        getline(cin, aux);

        if (validacao(69, aux))
        {
            aux.copy(novo.Series_title_1, aux.size());
            novo.Series_title_1[aux.size()] = '\0';
        }

    } while (aux.size() > 69 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_2': ";
        getline(cin, aux);

        if (validacao(69, aux))
        {
            aux.copy(novo.Series_title_2, aux.size());
            novo.Series_title_2[aux.size()] = '\0';
        }

    } while (aux.size() > 69 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_3': ";
        getline(cin, aux);

        if (validacao(69, aux))
        {
            aux.copy(novo.Series_title_3, aux.size());
            novo.Series_title_3[aux.size()] = '\0';
        }

    } while (aux.size() > 69 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_4': ";
        getline(cin, aux);

        if (validacao(69, aux))
        {
            aux.copy(novo.Series_title_4, aux.size());
            novo.Series_title_4[aux.size()] = '\0';
        }

    } while (aux.size() > 69 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_5': ";
        getline(cin, aux);

        if (validacao(69, aux))
        {
            aux.copy(novo.Series_title_5, aux.size());
            novo.Series_title_5[aux.size()] = '\0';
        }

    } while (aux.size() > 69 or aux.empty());

    // move para frente
    dado buffer;
    for (int i = total_registros - 1; i >= pos; --i)
    {
        arq.seekg(i * sizeof(dado), ios::beg);
        arq.read(reinterpret_cast<char *>(&buffer), sizeof(dado));

        arq.seekp((i + 1) * sizeof(dado), ios::beg);
        arq.write(reinterpret_cast<const char *>(&buffer), sizeof(dado));
    }

    // Inserir novo registro na posição desejada
    arq.seekp(pos * sizeof(dado), ios::beg);
    arq.write(reinterpret_cast<const char *>(&novo), sizeof(dado));

    cout << "Registro inserido na posição " << pos << " com sucesso!" << endl;

    arq.close();

    cout << "Digite '0' para voltar ao menu inicial!" << endl;
    string voltar = "a";
    while (voltar != "0")
    {
        getline(cin, voltar);
    }
    system("clear");
}