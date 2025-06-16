Projeto Pratico de ED-UFLA-2025/01:
Manipulação e Ordenação de Arquivos Binários em Memoria Secundaria
Integrantes: Gustavo G. Ribeiro, Lívia Maria, Mauricio Sandim:

**O objetivo**

 O principal objetivo desse projeto e criar um programa capaz de ler um arquivo *CSV* com uma grande quantidade de entradas e transforma-lo em binário, a partir desse arquivo binário há ordenação dos dados utilizado o campo Data_Value de forma a qual só a memoria externa e utilizada, e, ademais, ser possível manipular e alterar as informações desse arquivo.**

**As Função presentes nesse projeto são**

[1] Adicionar um elemento no arquivo em uma posição específica qualquer. *No caso de ordenar novamente o arquivo, a posição no arquivo e alterada

[2] Visualizar os registros entre duas posições. *As posições devem ser compatíveis com o tamanho do arquivo e logica, no caso de tentar visualizar um posição inexistente o programa mostrara um mensagem de posição invalida*

[3] Alterar os dados de um registro. *Caso alterada a entrada semelhantemente ao adicionar em posição especifica, após a ordenação a posição no arquivo e alterada*

[4] Trocar dois registros de posição no arquivo. *Após a ordenação os arquivo voltam para posição de origem, desfazendo a troca*

[5] Visualizar todos os registros do arquivo armazenados.

[6] Exportar arquivo para CSV.

**Compilação e execução**

Para compilar o programa, abra o terminal no diretório onde está a pastar 'src' e 'include', e digite:

```bash
$ make

