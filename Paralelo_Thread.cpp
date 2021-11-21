#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
using namespace std;
//Variaveis globais
std::vector<std::vector<int>> m1;
std::vector<std::vector<int>> m2;
int thread_i = 0;
int dim_n1;
int dim_m1;
int dim_n2;
int dim_m2;
int n_ele;
int P;
void* multiplicacao(void* arg)
{
	int thread_n=thread_i++;
	fstream F_res;
	stringstream file_name;
	int contador=0;
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	file_name<<dim_n1<<"_"<<dim_m2<<"_P="<<P<<"_thread"<<thread_n<<".txt";
	F_res.open(file_name.str(), ios::out); 
	F_res<< dim_n1<<" "<< dim_m2<<std::endl;
		for(int i=0; i<dim_n1; i++){
			for(int j=0; j<dim_m2; j++){
   			int soma=0;
   			if(contador>=(thread_n)*n_ele && contador< (thread_n+1)*n_ele){
   				for(int k=0; k<dim_m1; k++)
   					soma+=(m1[i][k]*m2[k][j]);
   				F_res<< "Res["<< i<<"]["<< j<<"] "<< soma<<std::endl;
   				}
       		contador++;					
       	}
		}
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	F_res<<chrono::duration_cast<chrono::milliseconds>(end - begin).count()<<endl;
	F_res.close();
	pthread_exit(NULL);
}
 
int main(int argc, char *argv[]){
	const string File1=argv[1], File2=argv[2];
	P=stoi(argv[3]);
	//Input da matriz 1 e 2 em um vetor de vetores
	fstream M1, M2;
	string linha, elemento;
	M1.open(File1+".txt", ios::in);
  	getline(M1, linha);
	dim_n1=stoi(linha);
  	dim_m1=stoi(linha.substr(linha.find(" ")+1, linha.size()-linha.find(" ")));
  	for(int i=0; i<dim_n1; i++){
		m1.push_back(vector<int>());
		for(int j=0; j<dim_m1; j++){
			getline(M1, linha);
			elemento=linha.back();
			if(elemento=="0")
				elemento="10";
			m1[i].push_back(stoi(elemento));
		}
	}
	M1.close();
		
	M2.open(File2+".txt", ios::in);
	getline(M2, linha);
  	dim_n2=stoi(linha);
  	dim_m2=stoi(linha.substr(linha.find(" ")+1, linha.size()-linha.find(" ")));
	for(int i=0; i<dim_n2; i++){
		m2.push_back(vector<int>());
		for(int j=0; j<dim_m2; j++){
			getline(M2, linha);
			elemento=linha.back();
			if(elemento=="0")
				elemento="10";
			m2[i].push_back(stoi(elemento));
		}
	}
   M2.close();
	n_ele=(dim_n1*dim_m2)/P;
 //Criação das threads
   pthread_t threads[P];
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    for (int i = 0; i < P-1; i++) {
        int* ponteiro;
        pthread_create(&threads[i], NULL, multiplicacao, (void*)(ponteiro));
    }
   //O "pai" também tem que trabalhar
	int* ponteiro;
        pthread_create(&threads[P-1], NULL, multiplicacao, (void*)(ponteiro));
	//A thread principal espera as outras acabarem
    for (int i = 0; i < P; i++)
        pthread_join(threads[i], NULL);   
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	//Arq para salvar o tempo que levou do começo das criações das threads ao fim de todas elas.
	fstream F_tempo;
	F_tempo.open("Tempo.txt", ios_base::app);
	F_tempo<<chrono::duration_cast<chrono::milliseconds>(end - begin).count()<<endl;
	F_tempo.close();
    return 0;
}
