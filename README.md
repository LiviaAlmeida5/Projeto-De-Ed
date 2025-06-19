Projeto Pratico de ED-UFLA-2025/01:
Manipulação e Ordenação de Arquivos Binários em Memoria Secundaria

Integrantes: Gustavo G. Ribeiro, Lívia Maria, Mauricio Sandim.

Tema: Intercalção Polifásica crescente com o arquivo CSV `'property-transfer-statistics-march-2022-quarter-csv.csv'`.

**O objetivo**

 O principal objetivo desse projeto e criar um programa capaz de ler um arquivo *CSV* com uma grande quantidade de entradas e transformá-lo em binário. A partir desse arquivo binário há a ordenação dos dados utilizado o campo Data_Value, de forma que só a memoria externa é utilizada, e, ademais, é possível manipular e alterar as informações desse arquivo.

**As Função presentes nesse projeto são**

[1] Adicionar um elemento no arquivo em uma posição específica qualquer. 

[2] Visualizar os registros entre duas posições. 

[3] Alterar os dados de um registro. 

[4] Trocar dois registros de posição no arquivo. 

[5] Visualizar todos os registros do arquivo armazenados.

[6] Exportar arquivo para CSV.

**Compilação e execução**

Para compilar o programa, abra o terminal no diretório onde está a pasta `'src'` e `'include'`, e digite:

```bash
make
```

Caso queira compilar utilizando o g++, digite o comando:

```bash
g++ src/*.cpp -Iinclude -o projeto
```

Para executá-lo, digite, na mesma pasta, o comando:

```bash
./projeto
```