// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Funções utilizadas para ordenar o arquivo com base no campo Data_Value utilizando intercalação polifásica

#include <iostream>
#include <fstream>
#include <algorithm>
#include "../include/dado.h"

using namespace std;

// consnte auxiliar usada na mensagem de carregamento
const char carregamento[] = {'|', '/', '-', '\\'};

// sobrecarga de operador de comparação
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

struct marca
{
    dado registro;
    bool marcado;
};

bool operator<(marca d1, marca d2)
{
    if (d1.marcado == d2.marcado)
    {
        return d1.registro.Data_value < d2.registro.Data_value;
    }

    return !d1.marcado; // não marcados tem preferencia
}

// classe heap auxiliar para criação dos blocos ordenados
class MinHeap
{
private:
    // atributos
    const int capacidade = 10000;
    marca heap[10000];
    int tamanho;

    // modulos privados
    inline int pai(int i);      // acha o pai do valor
    inline int esquerdo(int i); // acha o filho esquerdo do valor
    inline int direito(int i);  // acha o filho direito do valor
    void corrigeDescendo(int i);
    
    public:
    void heapfy(); // constroi o heap
    MinHeap(ifstream &entrada);
    dado retiraRaiz();              // retira a raiz quando não há mais elementos no arquivo csv
    dado retiraRaizCedo(dado novo); // retira a raiz quando há mais elementos no arquivo csv que precisam entrar no heap
    void resetaMarca();
    bool vazia() { return tamanho == 0; } // verifica se o heap está vazio
};

MinHeap::MinHeap(ifstream &entrada)
{
    int i = 0;
    dado aux;
    while (entrada.read((char *)(&aux), sizeof(dado)) and i < capacidade)
    {
        heap[i].registro = aux;
        heap[i].marcado = false;
        i++;
    }

    if(!entrada.eof())
        entrada.seekg(sizeof(dado)*capacidade);

    tamanho = i;

    heapfy();
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

void MinHeap::resetaMarca()
{
    for (int i = 0; i < tamanho; i++)
    {
        heap[i].marcado = false;
    }
}

dado MinHeap::retiraRaiz()
{
    if (tamanho == 0)
        throw runtime_error("Erro ao retirar raiz");

    int inicio = 0;
    int final = tamanho - 1;

    dado aux = heap[inicio].registro;

    swap(heap[inicio], heap[final]);

    tamanho--;

    corrigeDescendo(inicio);

    return aux;
}

dado MinHeap::retiraRaizCedo(dado novo)
{
    int inicio = 0;

    dado aux = heap[inicio].registro;
    
    marca substitui;
    substitui.registro = novo;
    substitui.marcado = false;

    if (novo < aux)
        substitui.marcado = true;

    // substitui raiz por um novo dado e reconstroi o heap
    heap[inicio] = substitui;

    heapfy();

    if (heap[inicio].marcado)
    {
        resetaMarca();
    }

    return aux;
}

void criaBlocos()
{
    ifstream entrada("o.bin");

    int i = 0;

    dado recebeDoArquivo;
    dado recebeRaiz;

    ofstream fita1("fita1.bin");
    ofstream fita2("fita2.bin");

    cout << "Carregando  ";
    MinHeap heap(entrada);

    // constroi a fita 1 de forma assimétrica enquanto o o.bin não foi lido por completo
    while (entrada.read((char *)(&recebeDoArquivo), sizeof(dado)))
    {
        cout << '\b' << carregamento[i / 1000 % 4];
        cout.flush();
        i++;

        recebeRaiz = heap.retiraRaizCedo(recebeDoArquivo);
        fita1.write((const char *)(&recebeRaiz), sizeof(dado));
    }

    heap.resetaMarca();
    heap.heapfy();

    while (!heap.vazia())
    {
        recebeRaiz = heap.retiraRaiz();
        fita2.write((const char *)(&recebeRaiz), sizeof(dado));
    }

    rename("o.bin", "guarda.bin");
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
        // mensagem de carrregamento
        cout << '\b' << carregamento[i / 10 % 4];
        cout.flush();
        i++;

        // fita 3 sendo escrita
        if (alterna)
        {
            alterna = !alterna;

            ifstream fita2("fita2.bin");
            ofstream fita3("fita3.bin");

            dado compara2;
            fita2.read((char *)(&compara2), sizeof(dado));

            while (!fita2.eof())
            {
                // caso bloco ou arquivo tenha terminado
                if (fita1.eof() or compara1 < anterior)
                {
                    fita3.write((const char *)(&compara2), sizeof(dado));
                    fita2.read((char *)(&compara2), sizeof(dado));
                }
                // dado da fita 1 menor que o da fita 2
                else if (compara1 < compara2)
                {
                    anterior = compara1;
                    fita3.write((const char *)(&compara1), sizeof(dado));
                    fita1.read((char *)(&compara1), sizeof(dado));
                }
                // dado da fita 2 menor que o da fita 1
                else
                {
                    fita3.write((const char *)(&compara2), sizeof(dado));
                    fita2.read((char *)(&compara2), sizeof(dado));
                }
            }

            // finaliza escrita do bloco caso fita 2 tenha terminado
            while (compara1 >= anterior and !fita1.eof())
            {
                fita3.write((const char *)(&compara1), sizeof(dado));
                anterior = compara1;
                fita1.read((char *)(&compara1), sizeof(dado));
            }

            anterior = compara1;
        }

        // fita 2 sendo escrita
        else
        {
            alterna = !alterna;

            ifstream fita2("fita3.bin");
            ofstream fita3("fita2.bin");

            dado compara2;
            fita2.read((char *)(&compara2), sizeof(dado));

            while (!fita2.eof())
            {
                // caso bloco ou arquivo tenha terminado
                if (fita1.eof() or compara1 < anterior)
                {
                    fita3.write((const char *)(&compara2), sizeof(dado));
                    fita2.read((char *)(&compara2), sizeof(dado));
                }
                // dado da fita 1 menor que o da fita 3
                else if (compara1 < compara2)
                {
                    anterior = compara1;
                    fita3.write((const char *)(&compara1), sizeof(dado));
                    fita1.read((char *)(&compara1), sizeof(dado));
                }
                // dado da fita 3 menor que o da fita 1
                else
                {
                    fita3.write((const char *)(&compara2), sizeof(dado));
                    fita2.read((char *)(&compara2), sizeof(dado));
                }
            }

            // finaliza escrita do bloco caso fita 3 tenha terminado
            while (compara1 >= anterior and !fita1.eof())
            {
                fita3.write((const char *)(&compara1), sizeof(dado));
                anterior = compara1;
                fita1.read((char *)(&compara1), sizeof(dado));
            }

            anterior = compara1;
        }
    }

    // remoção de arquivos temporários
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
