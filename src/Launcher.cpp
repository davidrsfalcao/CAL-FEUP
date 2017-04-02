/*
* Launcher.cpp
*
*  Created on: 01/04/2017
*      Author: David
*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <vector>
#include "Graph.h"
#include "Cidade.h"
#include "Algoritmos.h"
#include "Alojamento.h"

#define ID_MAX 1

//Variaveis globais
std::vector<Cidade> cidadesId;  //cidades ordenadas por Id
std::vector<Cidade> cidadesNome; //cidades ordenadas por Nome

void carregarFicheiros() {

	int contador = 1;
	std::string path = "./res/";
	ifstream in;

	while (contador <= ID_MAX) {
		ostringstream conversor;
		conversor << contador;
		std::string fich = path + conversor.str()+".txt";
		const char *nomeFich;
		nomeFich = fich.c_str();

		in.open(nomeFich);
		if (in.fail()){
			std::cout << "Ficheiro nao existe.";
		}
		else std::cout << "Ficheiro existe.";

		contador++;
	}

}

void imprimirId(){

	std::cout << "Ordenadas por Id:" << endl << endl;
	for(size_t i = 0; i< cidadesId.size(); i++){
		std::cout << cidadesId[i].getId() << " - " << cidadesId[i].getNome()<< endl;
	}


	std::cout << "\n\nOrdenadas por Nome:" << endl << endl;
	for(size_t i = 0; i< cidadesNome.size(); i++){
		std::cout << cidadesNome[i].getNome() <<" - "<<cidadesNome[i].getId() << endl;
	}



}

void testes(){

	Cidade cidade = *(new Cidade());
	cidade.setNome("Porto");
	cidade.setId(12);

	cidadesId.push_back(cidade);
	cidadesNome.push_back(cidade);

	cidade.setNome("Lisboa");
	cidade.setId(1);

	cidadesId.push_back(cidade);
	cidadesNome.push_back(cidade);

	cidade.setNome("Barcelona");
	cidade.setId(34);

	cidadesId.push_back(cidade);
	cidadesNome.push_back(cidade);

	cidade.setNome("Pequim");
	cidade.setId(2);

	cidadesId.push_back(cidade);
	cidadesNome.push_back(cidade);

	cidade.setNome("Toquio");
	cidade.setId(21);

	cidadesId.push_back(cidade);
	cidadesNome.push_back(cidade);

	cidade.setNome("Bruxelas");
	cidade.setId(13);

	cidadesId.push_back(cidade);
	cidadesNome.push_back(cidade);

	cidadesId = ordenarPorId(cidadesId, 0, cidadesId.size()-1);
	cidadesNome = ordenarPorNome(cidadesNome, 0, cidadesNome.size()-1);
	imprimirId();

}

int main() {
	//std::cout << "HELLO WORLD";
	//carregarFicheiros();
	testes();
	Cidade cidade = pesquisaNome(cidadesNome,"Porto");

	std::cout << std::endl << std::endl << "O id de Porto e " << cidade.getId();

	return 0;
}
