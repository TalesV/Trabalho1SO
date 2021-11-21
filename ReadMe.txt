Aluno: Tales Vinicius de Medeiros Alves
Matrícula:20200040685

Link do vídeo no Youtube:https://youtu.be/7cAMQ1zAVjU
Link do GitHub:https://github.com/TalesV/Trabalho1SO
Link do Google Drive:https://drive.google.com/drive/folders/1W7oKcRn5t6cbl6z9HhCfmJ_CzCWIbyT1?usp=sharing

** O link do google drive tem todos os arquivos resultados gerados pelos programas, como deu uns 3 gb de arquivos não deu pra colocar no github.

Além do que foi falado no vídeo ainda quero ressaltar outros pontos que não foram possíveis comentar devido ao tempo limite do vídeo.

Nos programas eu utilizei da função chrono para pegar o tempo de execução do programa no caso do programa de thread("Paralelo_Thread.cpp") por exemplo na linha 86, logo antes de criar as threads eu começo a função e assim que o processo principal espera todas as threads acabarem utilizando da função pthread_join na linha 96 e logo que acaba o *for* para esperar todas as threads acabarem vem o chrono end na linha 97 para finalizar o contagem de tempo. Esse processo é bem semelhante no programa que utiliza de mútiplos processos("Paralelo_Processos.cpp") em que começa a contagem na linha 59, logo antes de criar os múltiplos processos e acaba na linha 100 depois de esperar todos os filhos terminarem os seus processos. No programa sequencial ("Prog_Sequencial.cpp") a implementação foi bem simples, antes de começar a multiplicação de matrizes na linha 54 e assim que a acaba o for ele já termina a contagem na linha 64.

Falando um pouco mais sobre os arquivos criados pelos programas em paralelo, todos os arquivos possuem na primeira linha as dimensões da matriz resultado e a última linha o tempo de execução do processo/thread que o criou, além disso eles possuem parte dos elementos da matriz resultado, o número de elementos que cada arquivo possui é calculado seguindo a equação: (dim_n1*dim_m2)/P, em que P é o número de processos/threads do programa e dim_n1 é o número de linhas da matriz_1 e dim_m2 o número de colunas da matriz 2, matrizes essas feitas pelo programa auxiliar ("Prog_Aux.cpp"), esses arquivos podem ser encontrados na pasta "Resultados" nesse .rar.

Sobre a metodologia utilizada para adquirir os dados de tempo de cada programa encontrados no arquivo "Trabalho1SO.xlsx", para cada tamanho de matriz eu rodei cada programa 10 vezes, eu utilizei o incremento de P e dos tamanhos da matriz igual a x2, eu utilizei os seguintes códigos para criar as matrizes:
./CMatriz 100 100 100 100
./CMatriz 200 200 200 200
./CMatriz 400 400 400 400
./CMatriz 800 800 800 800
./CMatriz 1600 1600 1600 1600
./CMatriz 3200 3200 3200 3200

E para cada tamanho de matriz, excluindo a matriz 3200, eu rodei os programas:
for run in {1..10}; do ./Seq Matriz_1 Matriz_2 ; done
for run in {1..10}; do ./Proc Matriz_1 Matriz_2 2; done
for run in {1..10}; do ./Thread Matriz_1 Matriz_2 2; done
for run in {1..10}; do ./Proc Matriz_1 Matriz_2 4; done
for run in {1..10}; do ./Thread Matriz_1 Matriz_2 4; done
for run in {1..10}; do ./Proc Matriz_1 Matriz_2 8; done
for run in {1..10}; do ./Thread Matriz_1 Matriz_2 8; done
for run in {1..10}; do ./Proc Matriz_1 Matriz_2 16; done
for run in {1..10}; do ./Thread Matriz_1 Matriz_2 16; done
for run in {1..10}; do ./Proc Matriz_1 Matriz_2 32; done
for run in {1..10}; do ./Thread Matriz_1 Matriz_2 32; done

No caso da matriz 3200 eu rodei apenas uma vez cada programa porque o programa sequencial demorou mais de 10 minutos para finalizar os resultados encontrados foram bem interessantes e dentro do esperado por isso continuei utilizando dos dados mesmo com uma amostragem pequena.

Com esses dados eu peguei os valores que saiam no arquivos "Tempo.txt" e manualmente colocava no libreoffice eu utilizei a média desses tempos coletados para fazer as matrizes que foram pedidas no E1 e E2 necessárias para a discussão.

Partindo para a parte de discussão outros pontos interessantes que não pude comentar no vídeo devido ao tempo foi em como para matrizes pequenas como no caso da matriz 100x100 o tempo de execução do programa sequencial foi competitivo com o tempo de execução dos programas em paralelo princpalmente quando o P=32 em que existia uma concorrência entre esses processos relativamente pequenos e acabava mudando o cache várias vezes o que deixou o processo mais lento.
Outro ponto importante de comentar é que o número ideal de processos/threads foi igual ao número de cores que existem na máquina isso nem sempre é verdade, em processos que precisam esperar pela leitura e escrita ou que dependem de outros arquivos que podem estar em uso e ser bloquados para uso do processo naquele momento um aumento no número de threads acima da quantidade de cores na máquina pode resultar em um programa mais rápido, no nosso trabalho como cada processo/thread criava um arquivo independete dos demais não existiu uma necessidade desses processos esperarem por uma resposta do sistema operacional ou uma resposta do usuário.

Conclusão.
Esse trabalho foi bem interessante ao meu ponto de vista os resultados estavam de acordo com o que vimos nas aulas e a grande diferença no desempenho entre um processo sequencial e paralelo me deixou bem impressionado.



