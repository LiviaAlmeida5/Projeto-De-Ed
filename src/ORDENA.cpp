// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Funções utilizadas para ordenar o arquivo com base no campo Data_Value utilizando intercalação polifásica

#include <iostream>
#include <fstream>
#include <algorithm>
#include "../include/dado.h"
#include "../include/ORDENA.h"

using namespace std;

// consnte auxiliar usada na mensagem de carregamento
const char carregamento[] = {
    '|',
    '/',
    '-',
    '\\',
};

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

// classe heap auxiliar para criação dos blocos ordenados
class MinHeap
{
private:
    // atributos
    const int capacidade = 1000;
    dado heap[1000];
    int tamanho;

    // modulos privados
    inline int pai(int i); // acha o pai do valor
    inline int esquerdo(int i); // acha o filho esquerdo do valor
    inline int direito(int i); // acha o filho direito do valor
    void corrigeDescendo(int i); 
    void heapfy(); // controi o heap

public:
    MinHeap(ifstream &entrada);
    dado retiraRaiz(); // retira a raiz quando não há mais elementos no arquivo csv
    dado retiraRaizCedo(dado novo); // retira a raiz quando há mais elementos no arquivo csv que precisam entrar no heap
    bool vazia() { return tamanho == 0; } // verifica se o heap está vazio
};

MinHeap::MinHeap(ifstream &entrada)
{
    entrada.seekg(0, entrada.end);
    int tamanhoArquivo = entrada.tellg()/sizeof(dado);
    entrada.seekg(0, entrada.beg);
    
    if (tamanhoArquivo <= 1000)
    {
        tamanho = tamanhoArquivo;
        entrada.read((char *)(heap), tamanhoArquivo * sizeof(dado));
    }
    else
    {
        tamanho = capacidade;
        entrada.read((char *)(heap), capacidade * sizeof(dado));
    }

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

    // substitui raiz por um novo dado e reconstroi o heap
    heap[inicio] = novo;

    heapfy();

    return aux;
}

void criaBlocos()
{
    ifstream entrada("o.bin");

    int i = 0;

    dado aux1;
    dado aux2;

    ofstream fita1("fita1.bin");
    MinHeap heap(entrada);

    cout << "Carregando  ";

    // controi a fita 1 de forma assimétrica enquanto o o.bin não foi lido por completo
    while (entrada.read((char *)(&aux1), sizeof(dado)))
    {
        cout << '\b' << carregamento[i / 1000 % 4];
        cout.flush();
        i++;

        aux2 = heap.retiraRaizCedo(aux1);

        fita1.write((const char *)(&aux2), sizeof(dado));
    }

    ofstream fita2("fita2.bin");

    // controi a fita 2 com o último bloco
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
