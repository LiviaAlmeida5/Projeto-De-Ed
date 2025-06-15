#include <iostream>
#include <fstream>
#include <algorithm>
#include "../include/dado.h"
#include "../include/ORDENA.h"

using namespace std;

const char carregamento[] = {
    '|',
    '/',
    '-',
    '\\',
};

bool operator<(dado d1, dado d2)
{
    return d1.Data_value < d2.Data_value;
}

bool operator>(dado d1, dado d2)
{
    return d1.Data_value > d2.Data_value;
}

bool operator<=(dado d1, dado d2)
{
    return d1.Data_value <= d2.Data_value;
}

bool operator>=(dado d1, dado d2)
{
    return d1.Data_value >= d2.Data_value;
}

class MinHeap
{
private:
    // atributos
    dado *heap;
    int capacidade;
    int tamanho;

    // modulos privados
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i);
    void corrigeDescendo(int i);
    void heapfy();

public:
    MinHeap(int cap, ifstream &entrada);
    ~MinHeap();
    dado retiraRaiz();
    dado retiraRaizCedo(dado novo);
    bool vazia() { return tamanho == 0; }
};

MinHeap::MinHeap(int cap, ifstream &entrada)
{
    heap = new dado[cap];
    capacidade = cap;
    tamanho = cap;

    entrada.read((char *)(&heap[0]), cap * sizeof(dado));

    heapfy();
}

MinHeap::~MinHeap()
{

    delete[] heap;
}

int MinHeap::pai(int i)
{
    return (i - 1) / 2;
}

int MinHeap::esquerdo(int i)
{
    return 2 * i + 1;
}

int MinHeap::direito(int i)
{
    return 2 * i + 2;
}

void MinHeap::corrigeDescendo(int i)
{
    int esq = esquerdo(i);
    int dir = direito(i);
    int menor = i;
    int final = tamanho - 1;

    if ((esq <= final) and (heap[esq] < heap[menor]))
    {
        menor = esq;
    }

    if ((dir <= final) and (heap[dir] < heap[menor]))
    {
        menor = dir;
    }

    if (menor != i)
    {
        swap(heap[menor], heap[i]);
        corrigeDescendo(menor);
    }
}

void MinHeap::heapfy()
{
    for (int i = (tamanho / 2) - 1; i >= 0; i--)
    {
        corrigeDescendo(i);
    }
}

dado MinHeap::retiraRaiz()
{
    if (tamanho == 0)
        throw runtime_error("Erro ao retirar raiz");

    int inicio = 0;
    int final = tamanho - 1;

    dado aux = heap[inicio];

    swap(heap[inicio], heap[final]);

    tamanho--;

    corrigeDescendo(inicio);

    return aux;
}

dado MinHeap::retiraRaizCedo(dado novo)
{
    int inicio = 0;

    dado aux = heap[inicio];

    heap[inicio] = novo;

    heapfy();

    return aux;
}

void criaBlocos()
{

    ifstream entrada("o.bin");

    entrada.seekg(0, entrada.end);

    const int capacidade = 400;
    int i = 0;

    entrada.seekg(0, entrada.beg);
    dado aux1;
    dado aux2;

    ofstream fita1("fita1.bin");
    MinHeap heap(capacidade, entrada);

    cout << "Carregando  ";

    while (entrada.read((char *)(&aux1), sizeof(dado)))
    {
        cout << '\b' << carregamento[i / 1000 % 4];
        cout.flush();
        i++;

        aux2 = heap.retiraRaizCedo(aux1);

        fita1.write((const char *)(&aux2), sizeof(dado));
    }

    ofstream fita2("fita2.bin");

    while (!heap.vazia())
    {
        aux1 = heap.retiraRaiz();
        fita2.write((const char *)(&aux1), sizeof(dado));
    }
}

void intercala()
{
    ifstream fita1("fita1.bin");

    dado anterior;
    dado compara1;

    fita1.read((char *)(&compara1), sizeof(dado));
    anterior = compara1;
    bool alterna = true;
    int i = 0;

    while (!fita1.eof())
    {
        cout << '\b' << carregamento[i / 100 % 4];
        cout.flush();
        i++;

        if (alterna)
        {
            alterna = !alterna;

            ifstream fita2("fita2.bin");
            ofstream fita3("fita3.bin");

            dado compara2;
            fita2.read((char *)(&compara2), sizeof(dado));

            while (!fita2.eof())
            {
                if (fita1.eof() or compara1 < anterior)
                {
                    fita3.write((const char *)(&compara2), sizeof(dado));
                    fita2.read((char *)(&compara2), sizeof(dado));
                }
                else if (compara1 < compara2)
                {
                    anterior = compara1;
                    fita3.write((const char *)(&compara1), sizeof(dado));
                    fita1.read((char *)(&compara1), sizeof(dado));
                }
                else
                {
                    fita3.write((const char *)(&compara2), sizeof(dado));
                    fita2.read((char *)(&compara2), sizeof(dado));
                }
            }

            while (compara1 >= anterior and !fita1.eof())
            {
                fita3.write((const char *)(&compara1), sizeof(dado));
                anterior = compara1;
                fita1.read((char *)(&compara1), sizeof(dado));
            }

            anterior = compara1;
        }

        else
        {
            alterna = !alterna;

            ifstream fita2("fita3.bin");
            ofstream fita3("fita2.bin");

            dado compara2;
            fita2.read((char *)(&compara2), sizeof(dado));

            while (!fita2.eof())
            {
                if (fita1.eof() or compara1 < anterior)
                {
                    fita3.write((const char *)(&compara2), sizeof(dado));
                    fita2.read((char *)(&compara2), sizeof(dado));
                }
                else if (compara1 < compara2)
                {
                    anterior = compara1;
                    fita3.write((const char *)(&compara1), sizeof(dado));
                    fita1.read((char *)(&compara1), sizeof(dado));
                }
                else
                {
                    fita3.write((const char *)(&compara2), sizeof(dado));
                    fita2.read((char *)(&compara2), sizeof(dado));
                }
            }

            while (compara1 >= anterior and !fita1.eof())
            {
                fita3.write((const char *)(&compara1), sizeof(dado));
                anterior = compara1;
                fita1.read((char *)(&compara1), sizeof(dado));
            }

            anterior = compara1;
        }
    }

    remove("fita1.bin");

    if (alterna)
    {
        remove("fita3.bin");
        rename("fita2.bin", "o.bin");
    }
    else
    {
        remove("fita2.bin");
        rename("fita3.bin", "o.bin");
    }
}

void ordenar()
{
    system("clear");
    criaBlocos();
    intercala();
    system("clear");
}
