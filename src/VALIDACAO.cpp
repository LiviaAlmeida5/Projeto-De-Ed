#include <iostream>

using namespace std;


bool validacao(int tamMax, string aux)
{
    if (aux.size() <= tamMax and not aux.empty()) // verifica se o nome é válido
    {
        return true;
    }
    cout << "======================================================================================================================" << endl
         << endl;
    cout << "Nome inválido!!" << endl
         << endl;
    return false;
}

bool validacaoInt(string num)
{
    for (int i = 0; i < num.size(); i++)
    {
        if (not isdigit(num[i]) or num.size() > 9) // verifica se o caractere é um dígito e se o número é menor que 10^9
        {
            return false;
        }
    }
    return true;
}

bool validacaoData(string aux)
{
    int cont = 0;
    for (int i = 0; i < aux.size(); i++)
    {
        if (aux.size() != 7)
        {
            return false;
        }
        else if (aux[i] == '.')
        {
            cont++;
        }
        else if (not isdigit(aux[i]) and aux[i] != '.')
        {
            return false;
        }
    }

    if (cont == 1)
    {
        return true;
    }
    return false;
}

bool validacaoFloat(string aux)
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