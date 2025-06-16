// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Header com a struct usada para os registros

#ifndef DADO_H
#define DADO_H

struct dado
{
    char Series_reference[20];
    float Period;
    float Data_value;
    char Status;
    char Units[10];
    int Magnitude;
    char Subject[50];
    char Periodicity[10];
    char Group[100];
    char Series_title_1[70];
    char Series_title_2[70];
    char Series_title_3[70];
    char Series_title_4[70];
    char Series_title_5[70];
};

#endif