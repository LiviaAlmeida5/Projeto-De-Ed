// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Funções para verificar se o dado inserido pelo usuário é válido

#include <iostream>

using namespace std;

bool validacao(int tamMax, string aux)
{
    if (aux.size() <= tamMax and not aux.empty()) // verifica se o texto tem o tamanho adequado
    {
        return true;
    }
    cout << "======================================================================================================================" << endl << endl;
    cout << "Nome inválido!!" << endl << endl;
    return false;
}

bool validacaoInt(string num) // verifica se o valor é um inteiro
{
    for (int i = 0; i < num.size(); i++)
    {
        if (not isdigit(num[i]) or num.size() > 9)
        {
            return false;
        }
    }
    return true;
}

bool validacaoData(string aux) // verifica se o dado está no formato de data (0000.00)
{
    int contPonto = 0;
    if (aux.size() != 7)
    {
        return false;
    }
    if (aux[4] != '.')
    {
        return false;
    }

    for (int i = 0; i < aux.size(); i++)
    {
        if (aux[i] == '.')
        {
            contPonto++;
        }
        else if (not isdigit(aux[i]) and aux[i] != '.')
        {
            return false;
        }
    }

    if (contPonto == 1)
    {
        return true;
    }
    return false;
}

bool validacaoFloat(string aux) // verifica se o dado é um número decimal
{
    int cont = 0;
    for (int i = 0; i < aux.size(); i++)
    {
        if (aux[i] == '.')
        {
            cont++;
        }
        else if (not isdigit(aux[i]))
        {
            return false;
        }
    }

    if (cont > 1 or aux.size() == 0)
    {
        return false;
    }
    return true;
}