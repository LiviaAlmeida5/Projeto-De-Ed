// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Função para trocar dois registros do arquivo

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "../include/dado.h"

using namespace std;

void trocar()
{
     dado aux1, aux2;
     int posição1, posição2;
     fstream arq("o.bin");
     if (!arq)
          throw runtime_error("Arquivo temporário inexistente");
     ostringstream duasCasasDecimais; // variável para permitir a saída do dado com duas casas decimais sem prejudicar as demais saídas

     // recepção das posições
     arq.seekg(0, arq.end);
     int tam = arq.tellg() / sizeof(dado);
     arq.seekg(0, arq.beg);

     cout << "======================================================================================================================" << endl;
     cout << endl;
     cout << "Arquivos de quais posições você deseja trocar seu registro?" << endl;

     do
     {
          cout << "Primeira posição (De 0 até " << tam-1 << "):" << endl;
          cin >> posição1;
          if (posição1 < 0 or posição1 >= tam)
          {
               cout << "Posição Inválida!!" << endl;
          }

     } while (posição1 < 0 or posição1 >= tam);

     do
     {
          cout << "Segunda posição (De 0 até " << tam-1 << "):" << endl;
          cin >> posição2;
          if (posição2 < 0 or posição2 >= tam)
          {
               cout << "Posição Inválida!!" << endl;
          }

     } while (posição2 < 0 or posição2 >= tam);

     // leitura dos dados
     arq.seekg(posição1 * sizeof(dado));
     arq.read((char *)(&aux1), sizeof(dado));

     duasCasasDecimais.str(""); // limpeza da variável
     duasCasasDecimais << setprecision(2) << fixed << aux1.Period;
     cout << "Registro na posição: " << posição1 << endl;
     cout << aux1.Series_reference << " | " << duasCasasDecimais.str() << " | " << aux1.Data_value << " | " << aux1.Status << " | " << aux1.Units << " | " << aux1.Magnitude << " | " << aux1.Subject << " | " << aux1.Periodicity << " | " << aux1.Group << " | " << aux1.Series_title_1 << " | " << aux1.Series_title_2 << " | " << aux1.Series_title_3 << " | " << aux1.Series_title_4 << " | " << aux1.Series_title_5 << endl;

     arq.seekg(posição2 * sizeof(dado));
     arq.read((char *)(&aux2), sizeof(dado));

     duasCasasDecimais.str(""); // limpeza da variável
     duasCasasDecimais << setprecision(2) << fixed << aux2.Period;
     cout << "Registro na posição: " << posição2 << endl;
     cout << aux2.Series_reference << " | " << duasCasasDecimais.str() << " | " << aux2.Data_value << " | " << aux2.Status << " | " << aux2.Units << " | " << aux2.Magnitude << " | " << aux2.Subject << " | " << aux2.Periodicity << " | " << aux2.Group << " | " << aux2.Series_title_1 << " | " << aux2.Series_title_2 << " | " << aux2.Series_title_3 << " | " << aux2.Series_title_4 << " | " << aux2.Series_title_5 << endl;
     cout << endl;

     // troca dos dados
     arq.seekp(posição1 * sizeof(dado));
     arq.write((const char *)(&aux2), sizeof(dado));

     arq.seekp(posição2 * sizeof(dado));
     arq.write((const char *)(&aux1), sizeof(dado));

     // resultado final

     cout << "Após a troca:" << endl;
     cout << endl;

     arq.seekg(posição2 * sizeof(dado));
     arq.read((char *)(&aux2), sizeof(dado));

     arq.seekg(posição1 * sizeof(dado));
     arq.read((char *)(&aux1), sizeof(dado));

     duasCasasDecimais.str(""); // limpeza da variável
     duasCasasDecimais << setprecision(2) << fixed << aux1.Period;
     cout << "Registro na posição: " << posição1 << endl;
     cout << aux1.Series_reference << " | " << duasCasasDecimais.str() << " | " << aux1.Data_value << " | " << aux1.Status << " | " << aux1.Units << " | " << aux1.Magnitude << " | " << aux1.Subject << " | " << aux1.Periodicity << " | " << aux1.Group << " | " << aux1.Series_title_1 << " | " << aux1.Series_title_2 << " | " << aux1.Series_title_3 << " | " << aux1.Series_title_4 << " | " << aux1.Series_title_5 << endl;

     duasCasasDecimais.str(""); // limpeza da variável
     duasCasasDecimais << setprecision(2) << fixed << aux2.Period;
     cout << "Registro na posição: " << posição2 << endl;
     cout << aux2.Series_reference << " | " << duasCasasDecimais.str() << " | " << aux2.Data_value << " | " << aux2.Status << " | " << aux2.Units << " | " << aux2.Magnitude << " | " << aux2.Subject << " | " << aux2.Periodicity << " | " << aux2.Group << " | " << aux2.Series_title_1 << " | " << aux2.Series_title_2 << " | " << aux2.Series_title_3 << " | " << aux2.Series_title_4 << " | " << aux2.Series_title_5 << endl;


     cout << "Alterações salvas!!" << endl;
     cout << endl;

     // finalização
     cout << "Digite '0' para voltar ao menu inicial!" << endl;
     string voltar = "a";
     while (voltar != "0")
     {
          getline(cin, voltar);
     }
     system("clear");
}