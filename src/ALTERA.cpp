#include "../include/ALTERA.h"
#include "../include/VALIDACAO.h"
#include "../include/dado.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

void alterar()
{
   dado novo;
   string aux;
   int posição;
   int opcao;
   fstream arq("o.bin");
   string temp;

   arq.seekg(0, arq.end);
   int tam = arq.tellg() / sizeof(dado);
   arq.seekg(0, arq.beg);

   cout << "======================================================================================================================" << endl
        << endl;

   do
   {
      cout << "Digite a posição que você deseja alterar seu registro: ";
      cin >> posição;
      if (posição < 0 or posição > tam)
      {
         cout << "Posição Inválida!!" << endl
              << endl;
      }
   } while (posição < 0 or posição > tam);

   arq.seekg(posição * sizeof(dado));
   arq.read((char *)(&novo), sizeof(dado));

   do
   {
      system("clear");
      cout << "Os dados dessa posição são:" << endl;
      cout << "Series_reference | Period | Data_value | Status | Units | Magnitude | Subject | Periodicity | Group | Series_title_1 | Series_title_2 | Series_title_3 | Series_title_4 | Series_title_5" << endl;
      cout << novo.Series_reference << " | " << novo.Period << " | " << novo.Data_value << " | " << novo.Status << " | " << novo.Units << " | " << novo.Magnitude << " | " << novo.Subject << " | " << novo.Periodicity << " | " << novo.Group << " | " << novo.Series_title_1 << " | " << novo.Series_title_2 << " | " << novo.Series_title_3 << " | " << novo.Series_title_4 << " | " << novo.Series_title_5 << endl
           << endl;

      cout << "Qual parte do registro você deseja aleterar?" << endl
           << endl
           << "[1] Series_reference" << endl
           << "[2] Period " << endl
           << "[3] Data_value " << endl
           << "[4] Status " << endl
           << "[5] Units " << endl
           << "[6] Magnitude " << endl
           << "[7] Subject " << endl
           << "[8] Periodicity " << endl
           << "[9] Group" << endl
           << "[10] Series_title_1 " << endl
           << "[11] Series_title_2 " << endl
           << "[12] Series_title_3 " << endl
           << "[13] Series_title_4 " << endl
           << "[14] Series_title_5 " << endl
           << "[0] Voltar para o menu" << endl;

      cin >> opcao;

      switch (opcao)
      {
      case 1:
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

         break;
      case 2:
         cin.ignore();
         do
         {
            cout << "Escreva o novo 'Period'(data no formato 0000.00): ";
            getline(cin, aux);
            cout << endl;

            if (validacaoData(aux))
            {
               novo.Period = stof(aux);
            }
            else
            {
               cout << "======================================================================================================================" << endl
                    << endl;
               cout << "Valor inválido!!" << endl
                    << endl;
            }
         } while (not validacaoData(aux));
         break;
      case 3:
         cin.ignore();
         do
         {
            cout << "Escreva o novo 'Data_value'(float): ";
            getline(cin, aux);
            cout << endl;

            if (validacaoFloat(aux))
            {
               novo.Data_value = stof(aux);
            }
            else
            {
               cout << "======================================================================================================================" << endl
                    << endl;
               cout << "Valor inválido!!" << endl
                    << endl;
            };

         } while (not validacaoFloat(aux) or aux.empty());
         break;
      case 4:
         cin.ignore();
         do
         {
            cout << "Escreva o novo 'Status'(char): ";
            getline(cin, aux);
            cout << endl;

            if (aux.size() == 1)
            {
               novo.Status = aux[0];
            }
            else
            {
               cout << "======================================================================================================================" << endl
                    << endl;
               cout << "Char inválido!!" << endl
                    << endl;
            };

         } while (aux.size() != 1);
         break;
      case 5:
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
         break;
      case 6:
         cin.ignore();
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
               cout << "Valor inválido!!" << endl
                    << endl;
            };

         } while (not validacaoInt(aux) or aux.empty());
         break;
      case 7:
         cin.ignore();
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
         break;
      case 8:
         cin.ignore();
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
         break;
      case 9:
         cin.ignore();
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
         break;
      case 10:
         cin.ignore();
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
         break;
      case 11:
         cin.ignore();
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
         break;
      case 12:
         cin.ignore();
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
         break;
      case 13:
         cin.ignore();
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
         break;
      case 14:
         cin.ignore();
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
         break;
      case 0:
         break;
      default:
         cout << "Opção inválida!!" << endl;
         break;
      };
   } while (opcao != 0);

   arq.seekp(posição * sizeof(dado));
   arq.write((const char *)(&novo), sizeof(dado));

   arq.seekg(posição * sizeof(dado));
   arq.read((char *)(&novo), sizeof(dado));

   cout << endl
        << novo.Series_reference << " | " << novo.Period << " | " << novo.Data_value << " | " << novo.Status << " | " << novo.Units << " | " << novo.Magnitude << " | " << novo.Subject << " | " << novo.Periodicity << " | " << novo.Group << " | " << novo.Series_title_1 << " | " << novo.Series_title_2 << " | " << novo.Series_title_3 << " | " << novo.Series_title_4 << " | " << novo.Series_title_5 << endl
        << endl;

   cout << "Alterações salvas!!" << endl
        << endl;

   cout << "Digite '0' para voltar ao menu inicial!" << endl;
   string voltar = "a";
   while (voltar != "0")
   {
      getline(cin, voltar);
   }
   system("clear");
}