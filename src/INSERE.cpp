#include "../include/INSERE.h"
#include "../include/VALIDACAO.h"
#include "../include/dado.h"
#include <iostream>
#include <fstream>
#include <cstring> // Para usar memset

using namespace std;

void inserir()
{
    // Abre arquivo para leitura + escrita
    fstream arq("o.bin", ios::in | ios::out | ios::binary);

    arq.seekg(0, ios::end);
    int total_registros = arq.tellg() / sizeof(dado);

    int pos;

    do
    {
        cout << "Em qual posição você quer inserir? (De 0 até " << total_registros << ")\n";
        cin >> pos;
        if (pos < 0 or pos > total_registros)
        {
            cout << "Posição inválida.\n";
        }
    } while (pos < 0 or pos > total_registros);

    // dados do novo registro
    dado novo;
    cout << "Escreva o novo registro:\n";
    string aux;

    cin.ignore();
    do
    {
        cout << "Escreva o novo 'Series_reference': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(20, aux))
        {
            aux.copy(novo.Series_reference, aux.size());
            novo.Series_reference[aux.size()] = '\0';
        }

    } while (aux.size() > 20 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Period'(data no formato 0000.00): ";
        getline(cin, aux);
        cout << endl;

        if (validacaoFloat(aux))
        {
            novo.Period = stof(aux);
        }
        else
        {
            cout << "======================================================================================================================" << endl
                 << endl;
            cout << "Nome inválido!!" << endl
                 << endl;
        }
    } while (not validacaoFloat(aux));

    do
    {
        cout << "Escreva o novo 'Data_value'(int): ";
        getline(cin, aux);
        cout << endl;

        if (validacaoInt(aux))
        {
            novo.Data_value = stoi(aux);
        }
        else
        {
            cout << "======================================================================================================================" << endl
                 << endl;
            cout << "Número inválido!!" << endl
                 << endl;
        };

    } while (not validacaoInt(aux) or aux.empty());

    cout << "Escreva o novo 'Status'(char): ";
    cin >> novo.Status;

    cin.ignore();
    do
    {
        cout << "Escreva o novo 'Units': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(10, aux))
        {
            aux.copy(novo.Units, aux.size());
            novo.Units[aux.size()] = '\0';
        }

    } while (aux.size() > 10 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Magnitude'(int): ";
        getline(cin, aux);
        cout << endl;

        if (validacaoInt(aux))
        {
            novo.Magnitude = stoi(aux);
        }
        else
        {
            cout << "======================================================================================================================" << endl
                 << endl;
            cout << "Número inválido!!" << endl
                 << endl;
        };

    } while (not validacaoInt(aux) or aux.empty());

    do
    {
        cout << "Escreva o novo 'Subject': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(50, aux))
        {
            aux.copy(novo.Subject, aux.size());
            novo.Subject[aux.size()] = '\0';
        }

    } while (aux.size() > 50 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Periodicity': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(10, aux))
        {
            aux.copy(novo.Periodicity, aux.size());
            novo.Periodicity[aux.size()] = '\0';
        }

    } while (aux.size() > 10 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Group': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(100, aux))
        {
            aux.copy(novo.Group, aux.size());
            novo.Group[aux.size()] = '\0';
        }

    } while (aux.size() > 100 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_1': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(70, aux))
        {
            aux.copy(novo.Series_title_1, aux.size());
            novo.Series_title_1[aux.size()] = '\0';
        }

    } while (aux.size() > 70 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_2': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(70, aux))
        {
            aux.copy(novo.Series_title_2, aux.size());
            novo.Series_title_2[aux.size()] = '\0';
        }

    } while (aux.size() > 70 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_3': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(70, aux))
        {
            aux.copy(novo.Series_title_3, aux.size());
            novo.Series_title_3[aux.size()] = '\0';
        }

    } while (aux.size() > 70 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_4': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(70, aux))
        {
            aux.copy(novo.Series_title_4, aux.size());
            novo.Series_title_4[aux.size()] = '\0';
        }

    } while (aux.size() > 70 or aux.empty());

    do
    {
        cout << "Escreva o novo 'Series_title_5': ";
        getline(cin, aux);
        cout << endl;

        if (validacao(70, aux))
        {
            aux.copy(novo.Series_title_5, aux.size());
            novo.Series_title_5[aux.size()] = '\0';
        }

    } while (aux.size() > 70 or aux.empty());

    // cin >> novo.Series_reference >> novo.Period >> novo.Data_value >> novo.Status >> novo.Units >> novo.Magnitude >> novo.Subject >> novo.Periodicity >> novo.Group >> novo.Series_title_1 >> novo.Series_title_2 >> novo.Series_title_3 >> novo.Series_title_4 >> novo.Series_title_5;

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

    cout << "Registro inserido na posição " << pos << " com sucesso!\n";

    arq.close();

    cout << "Digite '0' para voltar ao menu inicial!" << endl;
    string voltar = "a";
    while (voltar != "0")
    {
        getline(cin, voltar);
    }
    system("clear");
}