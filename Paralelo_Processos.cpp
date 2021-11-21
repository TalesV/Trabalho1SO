#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
	const string File1=argv[1], File2=argv[2];
	int P=stoi(argv[3]);
	//Input da matriz 1 e 2 em um vetor de vetores
	fstream M1, M2;
	string linha, elemento;
	M1.open(File1+".txt", ios::in);
  	getline(M1, linha);
  	int dim_n1=stoi(linha);
  	int dim_m1=stoi(linha.substr(linha.find(" ")+1, linha.size()-linha.find(" ")));
  	std::vector<std::vector<int>> m1;
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
  	int dim_n2=stoi(linha);
  	int dim_m2=stoi(linha.substr(linha.find(" ")+1, linha.size()-linha.find(" ")));
	std::vector<std::vector<int>> m2;
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
	stringstream file_name;
	fstream F_res;
	int n_ele=(dim_n1*dim_m2)/P;
	pid_t pid[P-1];
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	//Uso do multiprocessamento
	for(int h=0; h<P-1; h++){
		int contador=0;
		pid[h]=fork();
		chrono::steady_clock::time_point begin = chrono::steady_clock::now();
		if(pid[h]==0){
				file_name<<dim_n1<<"_"<<dim_m2<<"_P="<<P<<"_proc"<<h<<".txt";
			F_res.open(file_name.str(), ios::out); 
			F_res<< dim_n1<<" "<< dim_m2<<std::endl;
			for(int i=0; i<dim_n1; i++){
				for(int j=0; j<dim_m2; j++){
     				int soma=0;
     				if(contador>=h*n_ele && contador< (h+1)*n_ele){
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
        exit(0);
		}
	}
	//O pai também tem que trabalhar
	int contador=0;
	file_name<<dim_n1<<"_"<<dim_m2<<"_P="<<P<<"_proc"<<P-1<<".txt";
	F_res.open(file_name.str(), ios::out); 
	F_res<< dim_n1<<" "<< dim_m2<<std::endl;
	for(int i=0; i<dim_n1; i++){
		for(int j=0; j<dim_m2; j++){
     		int soma=0;
     		if(contador>=(P-1)*n_ele && contador< P*n_ele){
     			for(int k=0; k<dim_m1; k++)
     				soma+=(m1[i][k]*m2[k][j]);
     			F_res<< "Res["<< i<<"]["<< j<<"] "<< soma<<std::endl;
     			}
     	    contador++;					
     	   }
      }
        F_res.close();
   //O pai espera o filhos acabarem
	while (wait(NULL)>0);
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	//Arq para salvar o tempo que levou do começo das criações dos processos ao fim de todas eles.
	fstream F_tempo;
	F_tempo.open("Tempo.txt", ios_base::app);
	F_tempo<<chrono::duration_cast<chrono::milliseconds>(end - begin).count()<<endl;
	F_tempo.close();
	return 0;
}

