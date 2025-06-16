// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Função para trocar dois registros do arquivo

#include "../include/TROCA.h"
#include "../include/dado.h"
#include <iostream>
#include <fstream>

using namespace std;

void trocar()
{
     dado aux1, aux2;
     int posição1, posição2;
     fstream arq("o.bin");

     // recepção das posições
     arq.seekg(0, arq.end);
     int tam = arq.tellg() / sizeof(dado);
     arq.seekg(0, arq.beg);

     cout << "======================================================================================================================" << endl
          << endl;
     cout << "Arquivos de quais posições você deseja trocar seu registro?" << endl;

     do
     {
          cout << "Primeira posição:" << endl;
          cin >> posição1;
          if (posição1 < 0 or posição1 > tam)
          {
               cout << "Posição Inválida!!" << endl;
          }
     } while (posição1 < 0 or posição1 > tam);

     do
     {
          cout << "Segunda posição:" << endl;
          cin >> posição2;
          if (posição1 < 0 or posição1 > tam)
          {
               cout << "Posição Inválida!!" << endl;
          }
     } while (posição2 < 0 or posição2 > tam);

     // leitura dos dados
     arq.seekg(posição1 * sizeof(dado));
     arq.read((char *)(&aux1), sizeof(dado));

     cout << "Registro na posição: " << posição1 << endl
          << aux1.Series_reference << " | " << aux1.Period << " | " << aux1.Data_value << " | " << aux1.Status << " | " << aux1.Units << " | " << aux1.Magnitude << " | " << aux1.Subject << " | " << aux1.Periodicity << " | " << aux1.Group << " | " << aux1.Series_title_1 << " | " << aux1.Series_title_2 << " | " << aux1.Series_title_3 << " | " << aux1.Series_title_4 << " | " << aux1.Series_title_5 << endl;

     arq.seekg(posição2 * sizeof(dado));
     arq.read((char *)(&aux2), sizeof(dado));

     cout << "Registro na posição: " << posição2 << endl
          << aux2.Series_reference << " | " << aux2.Period << " | " << aux2.Data_value << " | " << aux2.Status << " | " << aux2.Units << " | " << aux2.Magnitude << " | " << aux2.Subject << " | " << aux2.Periodicity << " | " << aux2.Group << " | " << aux2.Series_title_1 << " | " << aux2.Series_title_2 << " | " << aux2.Series_title_3 << " | " << aux2.Series_title_4 << " | " << aux2.Series_title_5 << endl
          << endl;

     // troca dos dados
     arq.seekp(posição1 * sizeof(dado));
     arq.write((const char *)(&aux2), sizeof(dado));

     arq.seekp(posição2 * sizeof(dado));
     arq.write((const char *)(&aux1), sizeof(dado));

     arq.seekg(posição2 * sizeof(dado));
     arq.read((char *)(&aux2), sizeof(dado));

     // resultado final
     cout << "Após a troca:" << endl
          << endl;

     cout << "Registro na posição: " << posição2 << endl
          << aux2.Series_reference << " | " << aux2.Period << " | " << aux2.Data_value << " | " << aux2.Status << " | " << aux2.Units << " | " << aux2.Magnitude << " | " << aux2.Subject << " | " << aux2.Periodicity << " | " << aux2.Group << " | " << aux2.Series_title_1 << " | " << aux2.Series_title_2 << " | " << aux2.Series_title_3 << " | " << aux2.Series_title_4 << " | " << aux2.Series_title_5 << endl;

     arq.seekg(posição1 * sizeof(dado));
     arq.read((char *)(&aux1), sizeof(dado));

     cout << "Registro na posição: " << posição1 << endl
          << aux1.Series_reference << " | " << aux1.Period << " | " << aux1.Data_value << " | " << aux1.Status << " | " << aux1.Units << " | " << aux1.Magnitude << " | " << aux1.Subject << " | " << aux1.Periodicity << " | " << aux1.Group << " | " << aux1.Series_title_1 << " | " << aux1.Series_title_2 << " | " << aux1.Series_title_3 << " | " << aux1.Series_title_4 << " | " << aux1.Series_title_5 << endl;

     cout << "Alterações salvas!!" << endl
          << endl;

     // finalização
     cout << "Digite '0' para voltar ao menu inicial!" << endl;
     string voltar = "a";
     while (voltar != "0")
     {
          getline(cin, voltar);
     }
     system("clear");
}