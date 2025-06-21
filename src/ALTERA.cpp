// Nomes dos Membros do Grupo: Gustavo Gerônimo Ribeiro, Lívia Maria Almeida Silva e Maurício Vicente Sandim
// Função para alterar as informações de um determinado registro

#include "../include/VALIDACAO.h"
#include "../include/dado.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <sstream>

using namespace std;

void alterar()
{
   // variaveis da função
   dado alterado;
   string aux;
   int posição;
   int opcao;
   fstream arq("o.bin");
   if (!arq)
      throw runtime_error("Arquivo temporário inexistente");
   
   ostringstream duasCasasDecimais; // variável para permitir a saída do dado com duas casas decimais sem prejudicar as demais saídas
   
   // acesso da posição
   arq.seekg(0, arq.end);
   int tam = arq.tellg() / sizeof(dado);
   arq.seekg(0, arq.beg);

   cout << "======================================================================================================================" << endl;
   cout << endl;

   do
   {
      cout << "Digite a posição que você deseja alterar seu registro (De 0 até " << tam-1 << "): ";
      cin >> posição;
      if (posição < 0 or posição >= tam)
      {
         cout << "Posição Inválida!!" << endl;
         cout << endl;
      }
   } while (posição < 0 or posição >= tam);

   arq.seekg(posição * sizeof(dado));
   arq.read((char *)(&alterado), sizeof(dado));

   // menu de alteração
   do
   {
      duasCasasDecimais.str(""); // limpeza da variável
      duasCasasDecimais << setprecision(2) << fixed << alterado.Period;

      system("clear");
      cout << "Os dados dessa posição são:" << endl;
      cout << "Series_reference | Period | Data_value | Status | Units | Magnitude | Subject | Periodicity | Group | Series_title_1 | Series_title_2 | Series_title_3 | Series_title_4 | Series_title_5" << endl;
      cout << alterado.Series_reference << " | " << duasCasasDecimais.str() << " | " << alterado.Data_value << " | " << alterado.Status << " | " << alterado.Units << " | " << alterado.Magnitude << " | " << alterado.Subject << " | " << alterado.Periodicity << " | " << alterado.Group << " | " << alterado.Series_title_1 << " | " << alterado.Series_title_2 << " | " << alterado.Series_title_3 << " | " << alterado.Series_title_4 << " | " << alterado.Series_title_5 << endl;
      cout << endl;

      cout << "Qual parte do registro você deseja aleterar?" << endl;
      cout << endl;
      cout << "[1] Series_reference" << endl;
      cout << "[2] Period " << endl;
      cout << "[3] Data_value " << endl;
      cout << "[4] Status " << endl;
      cout << "[5] Units " << endl;
      cout << "[6] Magnitude " << endl;
      cout << "[7] Subject " << endl;
      cout << "[8] Periodicity " << endl;
      cout << "[9] Group" << endl;
      cout << "[10] Series_title_1 " << endl;
      cout << "[11] Series_title_2 " << endl;
      cout << "[12] Series_title_3 " << endl;
      cout << "[13] Series_title_4 " << endl;
      cout << "[14] Series_title_5 " << endl;
      cout << "[0] Finalizar alterações " << endl;

      cin >> opcao;

      switch (opcao)
      {
      case 1:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Series_reference': ";
            getline(cin, aux);

            if (validacao(19, aux))
            {
               aux.copy(alterado.Series_reference, aux.size());
               alterado.Series_reference[aux.size()] = '\0';
            }

         } while (aux.size() > 19 or aux.empty());

         break;
      case 2:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Period'(data no formato 0000.00): ";
            getline(cin, aux);

            if (validacaoData(aux))
            {
               alterado.Period = stof(aux);
            }
            else
            {
               cout << "======================================================================================================================" << endl;
               cout << endl;
               cout << "Valor inválido!!" << endl;
               cout << endl;
            }
         } while (not validacaoData(aux));
         break;
      case 3:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Data_value'(float): ";
            getline(cin, aux);

            if (validacaoFloat(aux))
            {
               alterado.Data_value = stof(aux);
            }
            else
            {
               cout << "======================================================================================================================" << endl;
               cout << endl;
               cout << "Valor inválido!!" << endl;
               cout << endl;
            };

         } while (not validacaoFloat(aux) or aux.empty());
         break;
      case 4:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Status'(char): ";
            getline(cin, aux);

            if (aux.size() == 1)
            {
               alterado.Status = aux[0];
            }
            else
            {
               cout << "======================================================================================================================" << endl;
               cout << endl;
               cout << "Char inválido!!" << endl;
               cout << endl;
            };

         } while (aux.size() != 1);
         break;
      case 5:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Units': ";
            getline(cin, aux);

            if (validacao(9, aux))
            {
               aux.copy(alterado.Units, aux.size());
               alterado.Units[aux.size()] = '\0';
            }

         } while (aux.size() > 9 or aux.empty());
         break;
      case 6:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Magnitude'(int): ";
            getline(cin, aux);

            if (validacaoInt(aux))
            {
               alterado.Magnitude = stoi(aux);
            }
            else
            {
               cout << "======================================================================================================================" << endl;
               cout << endl;
               cout << "Valor inválido!!" << endl;
               cout << endl;
            };

         } while (not validacaoInt(aux) or aux.empty());
         break;
      case 7:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Subject': ";
            getline(cin, aux);

            if (validacao(49, aux))
            {
               aux.copy(alterado.Subject, aux.size());
               alterado.Subject[aux.size()] = '\0';
            }

         } while (aux.size() > 49 or aux.empty());
         break;
      case 8:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Periodicity': ";
            getline(cin, aux);

            if (validacao(9, aux))
            {
               aux.copy(alterado.Periodicity, aux.size());
               alterado.Periodicity[aux.size()] = '\0';
            }

         } while (aux.size() > 9 or aux.empty());
         break;
      case 9:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Group': ";
            getline(cin, aux);

            if (validacao(99, aux))
            {
               aux.copy(alterado.Group, aux.size());
               alterado.Group[aux.size()] = '\0';
            }

         } while (aux.size() > 99 or aux.empty());
         break;
      case 10:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Series_title_1': ";
            getline(cin, aux);

            if (validacao(69, aux))
            {
               aux.copy(alterado.Series_title_1, aux.size());
               alterado.Series_title_1[aux.size()] = '\0';
            }

         } while (aux.size() > 69 or aux.empty());
         break;
      case 11:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Series_title_2': ";
            getline(cin, aux);

            if (validacao(69, aux))
            {
               aux.copy(alterado.Series_title_2, aux.size());
               alterado.Series_title_2[aux.size()] = '\0';
            }

         } while (aux.size() > 69 or aux.empty());
         break;
      case 12:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Series_title_3': ";
            getline(cin, aux);

            if (validacao(69, aux))
            {
               aux.copy(alterado.Series_title_3, aux.size());
               alterado.Series_title_3[aux.size()] = '\0';
            }

         } while (aux.size() > 69 or aux.empty());
         break;
      case 13:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Series_title_4': ";
            getline(cin, aux);

            if (validacao(69, aux))
            {
               aux.copy(alterado.Series_title_4, aux.size());
               alterado.Series_title_4[aux.size()] = '\0';
            }

         } while (aux.size() > 69 or aux.empty());
         break;
      case 14:
         cin.ignore();
         do
         {
            cout << "Escreva o alterado 'Series_title_5': ";
            getline(cin, aux);

            if (validacao(69, aux))
            {
               aux.copy(alterado.Series_title_5, aux.size());
               alterado.Series_title_5[aux.size()] = '\0';
            }

         } while (aux.size() > 69 or aux.empty());
         break;
      case 0:
         break;
      default:
         cout << "Opção inválida!!" << endl;
         break;
      };
   } while (opcao != 0);

   // substituição do dado
   arq.seekp(posição * sizeof(dado));
   arq.write((const char *)(&alterado), sizeof(dado));

   arq.seekg(posição * sizeof(dado));
   arq.read((char *)(&alterado), sizeof(dado));

   duasCasasDecimais.str(""); // limpeza da variável
   duasCasasDecimais << setprecision(2) << fixed << alterado.Period;

   cout << endl;
   cout << alterado.Series_reference << " | " << duasCasasDecimais.str() << " | " << alterado.Data_value << " | " << alterado.Status << " | " << alterado.Units << " | " << alterado.Magnitude << " | " << alterado.Subject << " | " << alterado.Periodicity << " | " << alterado.Group << " | " << alterado.Series_title_1 << " | " << alterado.Series_title_2 << " | " << alterado.Series_title_3 << " | " << alterado.Series_title_4 << " | " << alterado.Series_title_5 << endl;
   cout << endl;

   cout << "Registro guardado!!" << endl;
   cout << endl;

   cout << "Digite '0' para voltar ao menu inicial!" << endl;
   string voltar = "a";
   while (voltar != "0")
   {
      getline(cin, voltar);
   }
   system("clear");
}