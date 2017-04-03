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
#include "graphviewer.h"
#include "Cidade.h"
#include "Algoritmos.h"
#include "Alojamento.h"

#define NOT_DYNAMIC false
#define EDGE_COLOR "black"
#define VERTEX_COLOR "red"
#define ID_MAX 1 //mudar consoante o numero de ficheiros
Graph<Cidade> graph;
GraphViewer *gv;

//Variaveis globais
std::vector<Cidade> cidadesId;  //cidades ordenadas por Id
std::vector<Cidade> cidadesNome; //cidades ordenadas por Nome

void carregarFicheiros() {

	int contador = 1;
	std::string path = "./res/";
	ifstream in;
	std::string nomeCidade, nomeH, nomeE, temp;
	unsigned int x, y, count, count1;

	while (contador <= ID_MAX) {
		ostringstream conversor;
		conversor << contador;
		std::string fich = path + conversor.str()+".txt";
		const char *nomeFich;
		nomeFich = fich.c_str();

		in.open(nomeFich);
		getline(in,nomeCidade);
		getline(in,temp,',');
		x = atoi(temp.c_str());
		getline(in,temp);
		y = atoi(temp.c_str());

		Coordenadas cords = Coordenadas(x,y);

		getline(in,temp);
		count = atoi(temp.c_str());

		//CICLO Alojamento
		std::vector<Alojamento*> hoteis;
		for (size_t i=0; i< count; i++){
			getline(in,nomeH);
			getline(in, temp);
			count1 = atoi(temp.c_str());

			//CICLO EPOCAS
			std::vector<Epoca*> epocas;
			for(size_t k=0; k<count1; k++){
				int diaI, diaF, mesI, mesF, preco;
				getline(in, nomeE);
				getline(in,temp,'-');
				diaI = atoi(temp.c_str());
				getline(in,temp,'/');
				mesI = atoi(temp.c_str());
				getline(in,temp,'-');
				diaF = atoi(temp.c_str());
				getline(in,temp);
				mesF = atoi(temp.c_str());

				getline(in, temp);
				preco = atoi(temp.c_str());

				Epoca* epoca = new Epoca(nomeE,diaI,mesI,diaF,mesF,preco);
				epocas.push_back(epoca);
			}

			Alojamento* hotel = new Alojamento(nomeH, epocas);
			hoteis.push_back(hotel);
		}

		getline(in,temp);
		count = atoi(temp.c_str());

		//Ciclo destinos
		std::vector<int> destinos;

		for (size_t i=0; i<count; i++){
			getline(in,temp);
			int idD = atoi(temp.c_str());
			getline(in,temp);
			int preco = atoi(temp.c_str());
			getline(in,temp);
			int tempo = atoi(temp.c_str());

			destinos.push_back(idD);
			destinos.push_back(preco);
			destinos.push_back(tempo);
		}

		Cidade cidade = Cidade(contador,nomeCidade,cords,hoteis,destinos);

		cidadesId.push_back(cidade);
		cidadesNome.push_back(cidade);

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
	cidade.setCoordenadas(Coordenadas(450,450));
	cidade.setId(12);

	gv->addNode(12, -100, 300);
	gv->setVertexLabel(12, "PORTO");
	gv->setVertexColor(12, "white");
	gv->rearrange();


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
	//imprimirId();

}

void inicializarGraphicViewer(){
	//Inicializar graphos
	gv = new GraphViewer(1024, 794, NOT_DYNAMIC);
	gv->setBackground("background.jpg");
	gv->createWindow(1024, 794);
	gv->defineVertexColor(VERTEX_COLOR);
	gv->defineEdgeColor(EDGE_COLOR);
}

int main() {
	//testes
	//std::cout << "HELLO WORLD";
	//carregarFicheiros();
	//testes();
	//Cidade cidade = pesquisaNome(cidadesNome,"Porto");

	//std::cout << std::endl << std::endl << "O id de Porto e " << cidade.getId();


	inicializarGraphicViewer();
	testes();
	getchar();

	return 0;
}
