#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Programa responsável por criar a matriz 1 e 2
int main(int argc, char *argv[]){
  int dim_n1=atoi(argv[1]);
  int dim_m1=atoi(argv[2]);
  int dim_n2=atoi(argv[3]);
  int dim_m2=atoi(argv[4]);
  
  fstream F_m1;
  F_m1.open("Matriz_1.txt", ios::out); 
  if(F_m1.is_open()){
     F_m1<< dim_n1<<" "<< dim_m1<<std::endl;
     for(int i=0; i<dim_n1; i++){
     	for(int j=0; j<dim_m1; j++){
     	   F_m1<< "M1["<< i<<"]["<< j<<"] "<< (rand()%10 + 1)<<std::endl;
     	}
     }
     F_m1.close();
  }
  
  fstream F_m2;
  F_m2.open("Matriz_2.txt", ios::out); 
  if(F_m2.is_open()){
     F_m2<< dim_n2<<" "<< dim_m2<<std::endl;
     for(int i=0; i<dim_n2; i++){
     	for(int j=0; j<dim_m2; j++){
     	   F_m2<< "M2["<< i<<"]["<< j<<"] "<< (rand()%10 + 1)<<std::endl;
     	}
     }
     F_m2.close();
  }
  return 0;
}
