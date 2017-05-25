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
#include <map>
#include "Arestas.h"
#include "Graph.h"
#include "graphviewer.h"
#include "Cidade.h"
#include "Algoritmos.h"
#include "Alojamento.h"
#include "uteis.h"
#include "matcher.h"

#define NOT_DYNAMIC false
#define EDGE_COLOR "white"
#define VERTEX_COLOR "red"
#define ID_MAX 110 //mudar consoante o numero de ficheiros
#define AVERAGE_WAITING 120 //tempo de espera pelo prÃ³ximo transporte
#define VISITING_TIME 720 // tempo de visita


//Variaveis globais
Graph<Cidade> graph;
GraphViewer *gv;
std::map<int, Aresta> arestas;
std::vector<Cidade> cidadesId;  //cidades ordenadas por Id
std::vector<Cidade> cidadesNome; //cidades ordenadas por Nome

void creditos(){
	system("cls");
	titulo();
	std::cout << std::endl;
	std::cout << std::endl << "\t     Segundo projeto da cadeira 'Concepcao e Analise de Algoritmos'" << endl << endl;
	cout << "\t     Desenvolvido por:" << endl << endl;

	std::cout << "\t\t\t David Falcao       -  up201506571";
	textcolor(yellow);
	std::cout << " @ ";
	textcolor(white);
	std::cout <<"fe.up.pt" << std::endl;

	std::cout << "\t\t\t Pedro Miranda      -  up201506574";
	textcolor(yellow);
	std::cout << " @ ";
	textcolor(white);
	std::cout << "fe.up.pt" << std::endl;

	std::cout << "\t\t\t Veronica Fradique  -  up201506440";
	textcolor(yellow);
	std::cout << " @ ";
	textcolor(white);
	std::cout << "fe.up.pt" << std::endl;


	textcolor(yellow);
	std::cout << std::endl << std::endl << "\t     Prima ENTER para voltar" << std::endl;
	textcolor(white);

	std::cin.ignore();
}

void carregarArestasCusto(std::vector<std::string> vect){

	Cidade saida = pesquisaNome(cidadesNome, vect[0]);
	Cidade chegada = pesquisaNome(cidadesNome, vect[1]);

	stringstream ss1(vect[2]);
	int dia, mes;
	char nn;
	ss1 >> dia >> nn >> mes;



	for (size_t i = 0; i < cidadesId.size(); i++) {
		for(size_t k = 0; k < cidadesId[i].getNumeroDestinos(); k++)
		{
			int id_destino = cidadesId[i].getIdDestino(k);
			Cidade destino = pesquisaId(cidadesId, id_destino);

			bool visitar = false;

			if (chegada == destino)
			{
				visitar = true;
			}
			else for(size_t j=3; j< vect.size(); j++)
			{
				Cidade temp = pesquisaNome(cidadesNome, vect[j]);
				if (temp == destino)
					visitar = true;
			}

			int custo = cidadesId[i].getCustoViagem(k);

			 if(visitar){
				custo += destino.HotelMaisBarato(dia,mes)->getPreco(dia,mes); //custo viagem + custo visita
			}

			graph.addEdge(cidadesId[i], destino, custo);
		}
	}

}

void carregarArestasTempo(std::vector<std::string> vect){

	Cidade saida = pesquisaNome(cidadesNome, vect[0]);

	for (size_t i = 0; i < cidadesId.size(); i++) {
		for(size_t k = 0; k < cidadesId[i].getNumeroDestinos(); k++)
		{
			int id_destino = cidadesId[i].getIdDestino(k);
			Cidade destino = pesquisaId(cidadesId, id_destino);

			bool origem = false;
			bool visitar = false;

			if (saida == cidadesId[i])
			{
				origem = true;
			}

			for(size_t j=3; j< vect.size(); j++)
			{
				Cidade temp = pesquisaNome(cidadesNome, vect[j]);
				if (temp == destino)
					visitar = true;
			}

			int tempo = cidadesId[i].getTempoViagem(k);
			if (origem){
				// o tempo ï¿½ sï¿½ o da Viagem
			}
			else if(visitar){
				tempo += VISITING_TIME; //tempo viagem + tempo visita
			}
			else tempo += AVERAGE_WAITING; // tempo viagem + espera aeroporto


			graph.addEdge(cidadesId[i], destino, tempo);
		}
	}
}

void limparArestas(){
	for (size_t i = 0; i < cidadesId.size(); i++) {
		for(size_t k = 0; k < cidadesId[i].getNumeroDestinos(); k++)
		{
			int id_destino = cidadesId[i].getIdDestino(k);
			Cidade destino = pesquisaId(cidadesId, id_destino);
			graph.removeEdge(cidadesId[i], destino);
		}
	}
}

void carregarFichMsg(){

	gotoxy(0,21);
	textcolor(light_red);
	std::cout << "\t    Os ficheiros ja foram carregados" << std::endl;
	textcolor(white);
	Sleep(1000);
	gotoxy(0,21);
	std::cout << "\t                                    " << std::endl;

}

int carregarFicheiros() {

	int contador = 1;
	std::string path = "./res/";
	ifstream in;
	std::string nomeCidade, nomeH, nomeE, temp;
	unsigned int x, y, count, count1;

	while (contador <= ID_MAX) {
		ostringstream conversor;
		conversor << contador;
		std::string fich = path + conversor.str() + ".txt";
		const char *nomeFich;
		nomeFich = fich.c_str();

		in.open(nomeFich);

		if (!in.fail()) {
			getline(in, nomeCidade);
			getline(in, temp, ',');
			x = atoi(temp.c_str());
			getline(in, temp);
			y = atoi(temp.c_str());

			Coordenadas cords = Coordenadas(x, y);

			getline(in, temp);
			count = atoi(temp.c_str());

			//CICLO Alojamento
			std::vector<Alojamento*> hoteis;
			for (size_t i = 0; i < count; i++) {
				getline(in, nomeH);
				getline(in, temp);
				count1 = atoi(temp.c_str());

				//CICLO EPOCAS
				std::vector<Epoca*> epocas;
				for (size_t k = 0; k < count1; k++) {
					int diaI, diaF, mesI, mesF, preco;
					getline(in, nomeE);
					getline(in, temp, '-');
					diaI = atoi(temp.c_str());
					getline(in, temp, '/');
					mesI = atoi(temp.c_str());
					getline(in, temp, '-');
					diaF = atoi(temp.c_str());
					getline(in, temp);
					mesF = atoi(temp.c_str());

					getline(in, temp);
					preco = atoi(temp.c_str());

					Epoca* epoca = new Epoca(nomeE, diaI, mesI, diaF, mesF,
							preco);
					epocas.push_back(epoca);
				}

				Alojamento* hotel = new Alojamento(nomeH, epocas);
				hoteis.push_back(hotel);
			}

			getline(in, temp);
			count = atoi(temp.c_str());

			if (count == 0)
			{
				//std::cout << nomeCidade << std::endl;
			}

			//Ciclo destinos
			std::vector<int> destinos;

			for (size_t i = 0; i < count; i++) {
				getline(in, temp);
				int idD = atoi(temp.c_str());
				getline(in, temp);
				int preco = atoi(temp.c_str());
				getline(in, temp);
				int tempo = atoi(temp.c_str());

				destinos.push_back(idD);
				destinos.push_back(preco);
				destinos.push_back(tempo);
			}

			//Ciclo pontos de interesse
			std::vector<std::string> pontos;

			getline(in, temp);
			count = atoi(temp.c_str());

			for (size_t i = 0; i < count; i++) {
				getline(in, temp);
				pontos.push_back(temp);
			}

			Cidade cidade = Cidade(contador, nomeCidade, cords, hoteis, destinos);
			cidade.setPontosInteresse(pontos);

			graph.addVertex(cidade);
			cidadesId.push_back(cidade);
			cidadesNome.push_back(cidade);
			in.close();

		}

		contador++;
	}
	cidadesId = ordenarPorId(cidadesId, 0, cidadesId.size()-1);
	cidadesNome = ordenarPorNome(cidadesNome, 0, cidadesNome.size()-1);

	int id = 0;

	for(size_t i=0; i<cidadesId.size(); i++){
		for (size_t k = 0; k < cidadesId[i].getNumeroDestinos(); k++) {
			int id = cidadesId[i].getId();
			int id_destino = cidadesId[i].getIdDestino(k);
			int custo =  cidadesId[i].getCustoViagem(k);
			int tempo =  cidadesId[i].getTempoViagem(k);

			Aresta a = Aresta(id,id_destino, custo, tempo);
			arestas[id] = a;
			id++;

		}
	}

	gotoxy(0,21);
	textcolor(yellow);
	std::cout << "\t    Carregamento completo";
	textcolor(white);
	Sleep(1000);
	gotoxy(0,21);
	std::cout << "\t                         ";

	return 1;
}

void updateGViewer(){
	for (size_t i = 0; i < cidadesId.size(); i++) {
		gv->addNode(cidadesId[i].getId(), cidadesId[i].getCoordenadas().getX(), cidadesId[i].getCoordenadas().getY());
		gv->setVertexLabel(cidadesId[i].getId(), cidadesId[i].getNome());
		gv->setVertexColor(cidadesId[i].getId(), VERTEX_COLOR);
		gv->setVertexSize(cidadesId[i].getId(), 25);
	}

	int id = 0;

	for (size_t i = 0; i < cidadesId.size(); i++) {
		if (cidadesId[i].getId() != 0)
		{
			for (size_t k = 0; k < cidadesId[i].getNumeroDestinos(); k++) {
				Cidade cid = pesquisaId(cidadesId,cidadesId[i].getIdDestino(k));

				if (cid.getId() == 0) {
					std::cout << "ERRO";
				} else {
					//dest.push_back(pesquisaId(cidadesId, cidadesId[i].getIdDestino(k)));
					gv->addEdge(id, cidadesId[i].getId(), cidadesId[i].getIdDestino(k), EdgeType::DIRECTED);
					id++;
				}
			}
		}
	}

	gv->rearrange();

}

void inicializarGraphicViewer(){
	//Inicializar graphos
	gv->setBackground("background.jpg");
	gv->createWindow(1680, 1050);
	gv->defineVertexColor(VERTEX_COLOR);
	gv->defineEdgeColor(EDGE_COLOR);
	gv->defineEdgeCurved(false);
}

void abrirMapa(int opcao){

	if (opcao == 0){
		gotoxy(0,21);
		textcolor(light_red);
		std::cout << "\t    Carregue os ficheiros primeiro" << std::endl;
		textcolor(white);
		Sleep(1000);
		gotoxy(0,21);
		std::cout << "\t                                  " << std::endl;
	}
	else {
		gotoxy(0,21);
		textcolor(yellow);
		std::cout << "\t    A abrir . . ." << std::endl;

		inicializarGraphicViewer();

		gotoxy(0,21);
		textcolor(white);
		std::cout << "\t                 " << std::endl;

	}

}

void displayCaixaDestinos(int opcao, int idI, int idF){
	if (opcao == 1){
		textcolor(yellow);
	}
	else {
		textcolor(white);
	}

	int a = 186;
	char char1 = a;  //

	int b = 201;
	char char2 = b; //

	int c = 205;
	char char3 = c; //

	int d = 187;
	char char4 = d; //

	int e = 200;
	char char5 = e; //

	int f = 188;
	char char6 = f; //



	gotoxy(14,5);
	std::cout << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;

	gotoxy(14,6);
	std::cout <<char1;

	gotoxy(75,6);
	std::cout <<char1;

	gotoxy(14,7);
	std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6 << endl;

	if ((opcao == 1) && (idI != 0)){
		gotoxy(13,6);
		std::cout <<"<";
	}
	else {
		gotoxy(13,6);
		std::cout <<" ";
	}

	if ((opcao == 1) && (idF != (int)cidadesNome.size()-1)){
		gotoxy(76,6);
		std::cout <<">";
	}
	else {
		gotoxy(76,6);
		std::cout <<" ";
	}

	textcolor(white);

	gotoxy(0,21);

}

void displayBarraDestinos(int idI, int idF){

	std::string temp;
	gotoxy(15,6);
	for (size_t i = 15; i <= 74; i++) {
		std::cout << " ";
	}

	gotoxy(17,6);


	std::cout << cidadesNome[idI].getNome();


	for (int i = idI+1; i < idF; i++) {
		temp = cidadesNome[i].getNome();

		textcolor(white);
		std::cout << " - ";


		std::cout << cidadesNome[i].getNome();

	}

	textcolor(white);
	gotoxy(0,21);

}

void barraDestinos_move(int &idI, int &idF, int key){

	int tamanho = 38;
	int contador = 0;

	if (key == LEFT_KEY){
		if (idI == 0)
		{
			return;
		}
		else {
			idF = idI;

			while (1){
				if (idI == -1){
					break;
				}
				else {
					contador += cidadesNome[idI].getNome().size();
					if (contador > tamanho)
					{
						idI++;
						return;
					}
					else {
						idI--;
					}
				}
			}

			contador = 0;
			idF = 0;
			idI = 0;
			while (1){
					contador += cidadesNome[idF].getNome().size();
					if (contador > tamanho)
					{
						idF--;
						return;
					}
					else {
						idF++;
					}
			}

		}

	}
	else if (key == RIGHT_KEY){

		if (idF == (int)cidadesNome.size()-1)
		{
			return;
		}
		else {
			idI = idF;

			while (1){
				if (idF == (int)cidadesNome.size()){
					break;
				}
				else {
					contador += cidadesNome[idF].getNome().size();
					if (contador > tamanho)
					{
						idF--;
						return;
					}
					else {
						idF++;
					}
				}
			}

			contador = 0;
			idF = cidadesNome.size()-1;
			idI = cidadesNome.size()-1;
			while (1){
					contador += cidadesNome[idI].getNome().size();
					if (contador > tamanho)
					{
						idI++;
						return;
					}
					else {
						idI--;
					}
			}

		}

	}

}

void imprimir_hoteis(std::vector<std::string> vect){

	limparEcra();
	cabecalho();
	int acumulado = 0;
	int atual;

	int a = 186;
	char char1 = a;

	int b = 201;
	char char2 = b;

	int c = 205;
	char char3 = c;

	int d = 187;
	char char4 = d;

	int e = 200;
	char char5 = e;

	int f = 188;
	char char6 = f;

	int g = 203;
	char char7 = g;

	int h = 185;
	char char8 = h;

	std::string origem = vect[0];
	std::string destino = vect[1];
	std::string data = vect[2];
	int dia, mes;
	char temp;
	unsigned int i = 3;
	stringstream ss1(data);
	ss1 >> dia >> temp >>mes;

	for(; i < vect.size(); i++){
		gotoxy(14,2+i);
		textcolor(yellow);
		std::cout << char1;

		Cidade cid = pesquisaNome(cidadesNome, vect[i]);
		Alojamento* hh =  cid.HotelMaisBarato(dia,mes);

		textcolor(white);
		gotoxy(16,2+i);
		std::cout << hh->getNome();

		gotoxy(45,2+i);
		std::cout << cid.getNome();

		atual = hh->getPreco(dia,mes);
		acumulado += atual;
		gotoxy(65,2+i);
		std::cout << atual;

		gotoxy(75,2+i);
		textcolor(yellow);
		std::cout << char1;
	}

	gotoxy(14,2+i);
	textcolor(yellow);
	std::cout << char1;

	Cidade cid = pesquisaNome(cidadesNome, destino);
	Alojamento* hh =  cid.HotelMaisBarato(dia,mes);

	textcolor(white);
	gotoxy(16,2+i);
	std::cout << hh->getNome();

	gotoxy(45,2+i);
	std::cout << cid.getNome();

	atual = hh->getPreco(dia,mes);
	acumulado += atual;
	gotoxy(65,2+i);
	std::cout << atual;

	gotoxy(75,2+i);
	textcolor(yellow);
	std::cout << char1;


	i-= 2;


	textcolor(light_red);
	gotoxy(16,3);
	std::cout << "Hotel";

	gotoxy(45,3);
	std::cout << "Cidade";

	gotoxy(64,3);
	std::cout << "Custo";

	gotoxy(0,4);
	textcolor(yellow);
	cout << "\t      " << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;

	textcolor(yellow);
	gotoxy(14, 5+i);
	std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;

	gotoxy(45,5+i);
	std::cout << char7;

	gotoxy(45,6+i);
	std::cout << char1;

	gotoxy(75,6+i);
	std::cout << char1;

	gotoxy(45,7+i);
	std::cout << char5;

	for(size_t k = 46; k< 75; k++)
	{
		std::cout << char3;
	}
	std::cout << char6;

	gotoxy(48,6+i);
	textcolor(light_red);
	std::cout << "TOTAL";

	gotoxy(65, 6+i);
	std::cout << acumulado;


	textcolor(white);
	gotoxy(0,21);
}

void imprimir_custo(std::vector<std::string> vect, int opcao){
	limparEcra();
	cabecalho();
	int acumulado = 0;
	int acumulado1 = 0;

	int a = 186;
	char char1 = a;  // obter -> Ã¢â€¢â€˜

	int b = 201;
	char char2 = b; // obter -> Ã¢â€¢â€�

	int c = 205;
	char char3 = c; // obter -> Ã¢â€¢ï¿½

	int d = 187;
	char char4 = d; // obter -> Ã¢â€¢â€”

	int e = 200;
	char char5 = e; // obter -> Ã¢â€¢Å¡

	int f = 188;
	char char6 = f; // obter -> Ã¢â€¢ï¿½

	int g = 203;
	char char7 = g; // obter -> â•¦

	int h = 185;
	char char8 = h; // obter -> â•£

	std::string origem = vect[0];
	std::string destino = vect[1];
	std::string data = vect[2];

	std::vector<std::string> v1 = vect;

	int dia, mes;
	char temp;
	unsigned int i = 0;
	unsigned int counter = 0;

	vector<Cidade> caminho;

	stringstream ss1(data);
	ss1 >> dia >> temp >>mes;

	carregarArestasCusto(vect);

	if (opcao == 1){
		graph.dijkstraShortestPath(pesquisaNome(cidadesNome, origem));
		caminho = graph.getPath(pesquisaNome(cidadesNome, origem), pesquisaNome(cidadesNome, destino));
		for(; i< caminho.size(); i++)
		{
			int id = caminho[i].getId() - 1;
			textcolor(yellow);
			gotoxy(14,5+i);
			std::cout << char1;

			gotoxy(16,5+i);
			textcolor(white);
			std::cout << caminho[i].getNome();

			gotoxy(50, 5+i);
			std::cout << graph.getVertexSet()[id]->getDist() - acumulado;
			acumulado = graph.getVertexSet()[id]->getDist();

			gotoxy(65, 5+i);
			std::cout << graph.getVertexSet()[id]->getDist();

			textcolor(yellow);
			gotoxy(75,5+i);
			std::cout << char1;
		}
	}
	else {
		graph.dijkstraShortestPath(pesquisaNome(cidadesNome, origem));
		caminho = graph.getPath(pesquisaNome(cidadesNome, origem), pesquisaNome(cidadesNome, vect[3]));

		for(; i< caminho.size(); i++)
		{
			int id = caminho[i].getId() - 1;
			textcolor(yellow);
			gotoxy(14,5+i);
			std::cout << char1;

			gotoxy(16,5+i);
			textcolor(white);
			std::cout << caminho[i].getNome();

			gotoxy(50, 5+i);
			std::cout << graph.getVertexSet()[id]->getDist() - acumulado;
			acumulado = graph.getVertexSet()[id]->getDist();

			gotoxy(65, 5+i);
			std::cout << graph.getVertexSet()[id]->getDist();

			textcolor(yellow);
			gotoxy(75,5+i);
			std::cout << char1;
		}
		counter = caminho.size();
		i = counter;

		vect.erase(vect.begin());
		vect.erase(vect.begin());
		vect.erase(vect.begin());

		for(; i < vect.size()+counter; i++)
		{
			acumulado1 = 0;;

			graph.dijkstraShortestPath(pesquisaNome(cidadesNome, vect[i-counter]));
			if (i != (vect.size()+counter)-1){
				caminho = graph.getPath(pesquisaNome(cidadesNome, vect[i-counter]), pesquisaNome(cidadesNome, vect[i+1-counter]));
			}
			else {
				caminho = graph.getPath(pesquisaNome(cidadesNome, vect[i-counter]), pesquisaNome(cidadesNome, destino));
			}
			caminho.erase(caminho.begin());
			for(; i< caminho.size()+counter; i++)
			{
				int id = caminho[i-counter].getId() - 1;
				textcolor(yellow);
				gotoxy(14,5+i);
				std::cout << char1;

				gotoxy(16,5+i);
				textcolor(white);
				std::cout << caminho[i-counter].getNome();

				gotoxy(50, 5+i);
				std::cout << graph.getVertexSet()[id]->getDist() - acumulado1;
				acumulado1 = graph.getVertexSet()[id]->getDist();

				gotoxy(65, 5+i);
				std::cout << graph.getVertexSet()[id]->getDist()+acumulado;

				textcolor(yellow);
				gotoxy(75,5+i);
				std::cout << char1;

			}
			acumulado += acumulado1;
			counter += caminho.size();
			i = counter;


		}
		i--;
	}

	textcolor(light_red);
	gotoxy(16,3);
	std::cout << "Cidades";

	gotoxy(45,3);
	std::cout << "C. cidade";

	gotoxy(60,3);
	std::cout << "C. acumulado";


	gotoxy(0,4);
	textcolor(yellow);
	cout << "\t      " << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;

	textcolor(yellow);
	gotoxy(14, 5+i);
	std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;

	gotoxy(45,5+i);
	std::cout << char7;

	gotoxy(45,6+i);
	std::cout << char1;

	gotoxy(75,6+i);
	std::cout << char1;

	gotoxy(45,7+i);
	std::cout << char5;

	for(size_t k = 46; k< 75; k++)
	{
		std::cout << char3;
	}
	std::cout << char6;

	gotoxy(48,6+i);
	textcolor(light_red);
	std::cout << "TOTAL";

	gotoxy(65, 6+i);
	std::cout << acumulado;


	textcolor(white);
	gotoxy(0,21);
	system("pause");
	imprimir_hoteis(v1);
}

void imprimir_tempo(std::vector<std::string> vect, int opcao){
	limparEcra();
	cabecalho();
	int acumulado = 0;
	int acumulado1 = 0;

	int a = 186;
	char char1 = a;  // obter -> Ã¢â€¢â€˜

	int b = 201;
	char char2 = b; // obter -> Ã¢â€¢â€�

	int c = 205;
	char char3 = c; // obter -> Ã¢â€¢ï¿½

	int d = 187;
	char char4 = d; // obter -> Ã¢â€¢â€”

	int e = 200;
	char char5 = e; // obter -> Ã¢â€¢Å¡

	int f = 188;
	char char6 = f; // obter -> Ã¢â€¢ï¿½

	int g = 203;
	char char7 = g; // obter -> â•¦

	int h = 185;
	char char8 = h; // obter -> â•£

	std::string origem = vect[0];
	std::string destino = vect[1];
	std::string data = vect[2];
	int dia, mes;
	char temp;
	unsigned int i = 0;
	unsigned int counter = 0;

	vector<Cidade> caminho;

	stringstream ss1(data);
	ss1 >> dia >> temp >>mes;

	carregarArestasTempo(vect);

	if (opcao == 2){
		graph.dijkstraShortestPath(pesquisaNome(cidadesNome, origem));
		caminho = graph.getPath(pesquisaNome(cidadesNome, origem), pesquisaNome(cidadesNome, destino));
		for(; i< caminho.size(); i++)
		{
			int id = caminho[i].getId() - 1;
			textcolor(yellow);
			gotoxy(14,5+i);
			std::cout << char1;

			gotoxy(16,5+i);
			textcolor(white);
			std::cout << caminho[i].getNome();

			gotoxy(50, 5+i);
			std::cout << graph.getVertexSet()[id]->getDist() - acumulado;
			acumulado = graph.getVertexSet()[id]->getDist();

			gotoxy(65, 5+i);
			std::cout << graph.getVertexSet()[id]->getDist();

			textcolor(yellow);
			gotoxy(75,5+i);
			std::cout << char1;
		}
	}
	else {
		graph.dijkstraShortestPath(pesquisaNome(cidadesNome, origem));
		caminho = graph.getPath(pesquisaNome(cidadesNome, origem), pesquisaNome(cidadesNome, vect[3]));

		for(; i< caminho.size(); i++)
		{
			int id = caminho[i].getId() - 1;
			textcolor(yellow);
			gotoxy(14,5+i);
			std::cout << char1;

			gotoxy(16,5+i);
			textcolor(white);
			std::cout << caminho[i].getNome();

			gotoxy(50, 5+i);
			std::cout << graph.getVertexSet()[id]->getDist() - acumulado;
			acumulado = graph.getVertexSet()[id]->getDist();

			gotoxy(65, 5+i);
			std::cout << graph.getVertexSet()[id]->getDist();

			textcolor(yellow);
			gotoxy(75,5+i);
			std::cout << char1;
		}
		counter = caminho.size();
		i = counter;

		vect.erase(vect.begin());
		vect.erase(vect.begin());
		vect.erase(vect.begin());

		for(; i < vect.size()+counter; i++)
		{
			acumulado1 = 0;;

			graph.dijkstraShortestPath(pesquisaNome(cidadesNome, vect[i-counter]));
			if (i != (vect.size()+counter-1)){
				caminho = graph.getPath(pesquisaNome(cidadesNome, vect[i-counter]), pesquisaNome(cidadesNome, vect[i+1-counter]));
			}
			else {
				caminho = graph.getPath(pesquisaNome(cidadesNome, vect[i-counter]), pesquisaNome(cidadesNome, destino));
			}
			caminho.erase(caminho.begin());
			for(; i< caminho.size()+counter; i++)
			{
				int id = caminho[i-counter].getId() - 1;
				textcolor(yellow);
				gotoxy(14,5+i);
				std::cout << char1;

				gotoxy(16,5+i);
				textcolor(white);
				std::cout << caminho[i-counter].getNome();

				gotoxy(50, 5+i);
				std::cout << graph.getVertexSet()[id]->getDist() - acumulado1;
				acumulado1 = graph.getVertexSet()[id]->getDist();

				gotoxy(65, 5+i);
				std::cout << graph.getVertexSet()[id]->getDist()+acumulado;

				textcolor(yellow);
				gotoxy(75,5+i);
				std::cout << char1;

			}
			acumulado += acumulado1;
			counter += caminho.size();
			i = counter;
		}
		i--;
	}


	textcolor(light_red);
	gotoxy(16,3);
	std::cout << "Cidades";

	gotoxy(45,3);
	std::cout << "T. cidade";

	gotoxy(60,3);
	std::cout << "T. acumulado";


	gotoxy(0,4);
	textcolor(yellow);
	cout << "\t      " << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;

	textcolor(yellow);
	gotoxy(14, 5+i);
	std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;

	gotoxy(45,5+i);
	std::cout << char7;

	gotoxy(45,6+i);
	std::cout << char1;

	gotoxy(75,6+i);
	std::cout << char1;

	gotoxy(45,7+i);
	std::cout << char5;

	for(size_t k = 46; k< 75; k++)
	{
		std::cout << char3;
	}
	std::cout << char6;

	gotoxy(48,6+i);
	textcolor(light_red);
	std::cout << "TOTAL";

	gotoxy(65, 6+i);
	std::cout << acumulado;


	textcolor(white);
	gotoxy(0,21);

}

void menu_resultado(int opcao, std::vector<std::string> vect){

	if (opcao == 1 || opcao == 3){
		imprimir_custo(vect,opcao);
	}
	else imprimir_tempo(vect,opcao);

	system("pause");
}

void menu_custo_tempo_interface(int opcao, bool imprimir){


	int a = 186;
	char char1 = a;  //

	int b = 201;
	char char2 = b; //

	int c = 205;
	char char3 = c; //

	int d = 187;
	char char4 = d; //

	int e = 200;
	char char5 = e; //

	int f = 188;
	char char6 = f; //

	int g = 204;
	char char7 = g; // obter -> â• 

	int h = 185;
	char char8 = h; // obter -> â•£

	if (imprimir){
		limparEcra();
		textcolor(yellow);
		gotoxy(14,5);
		std::cout << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;


		for (size_t i = 0; i < 7; i++) {
			gotoxy(14,6+i);
			std::cout <<char1;

			gotoxy(75,6+i);
			std::cout <<char1;
		}

		gotoxy(14,7);
		std::cout << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;

		gotoxy(14,13);
		std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6 << endl;

		textcolor(white);
		gotoxy(24,6);
		std::cout << "Deseja otimizar os resultados quanto ao: ";
	}


	if (opcao == 1){
		textcolor(light_red);
	}
	else {
		textcolor(white);
	}
	gotoxy(25,9);
	std::cout << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3  << char3 << char3<< char4;
	gotoxy(25,10);
	std::cout << char1 << "  Custo";
	gotoxy(35,10);
	std::cout << char1;
	gotoxy(25,11);
	std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6;

	if (opcao == 2){
		textcolor(light_red);
	}
	else {
		textcolor(white);
	}
	gotoxy(53,9);
	std::cout << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3  << char3 << char3<< char4;
	gotoxy(53,10);
	std::cout << char1 << "  Tempo";
	gotoxy(63,10);
	std::cout << char1;
	gotoxy(53,11);
	std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6;



	textcolor(white);
	gotoxy(0,21);

}

void menu_custo_tempo(std::vector<std::string> vect){

	int tecla = 0;
	int opcao = 1;
	bool imprimir = true;

	do{
		menu_custo_tempo_interface(opcao, imprimir);
		imprimir = false;
		tecla = opcao_valida_listas(opcao,1,2);

		if (tecla != RIGHT_KEY && tecla != LEFT_KEY)
			imprimir = true;

	} while(tecla != ENTER);

	if(opcao == 1){
		if(vect.size() != 3){
			opcao = 3;
		}
	}
	else if(opcao == 2){
		if(vect.size() != 3)
		{
			opcao = 4;
		}
	}

	switch (opcao) {
		case 1:
			carregarArestasCusto(vect);
			menu_resultado(1, vect);
			limparArestas();
			break;

		case 2:
			carregarArestasTempo(vect);
			menu_resultado(2, vect);
			limparArestas();
			break;

		case 3:
			carregarArestasCusto(vect);
			menu_resultado(3, vect);
			limparArestas();
			break;

		case 4:
			carregarArestasTempo(vect);
			menu_resultado(4, vect);
			limparArestas();
			break;
	}


}

void menu_escolha_ops(int opcao, int opcao_b){
	int a = 254;
	char square = a;
	int y = 0;
	int y1 = 0;

	if (opcao_b > 5){
		y = 9 + opcao_b;
	}
	else {
		y = 8 + opcao_b;
	}

	if (opcao > 5){
		y1 = 9 + opcao;
	}
	else {
		y1 = 8 + opcao;
	}

	if (opcao_b != 1){
		gotoxy(14, y);
		textcolor(yellow);
		std::cout << " ";
		textcolor(white);
	}

	if (opcao != 1){
		gotoxy(14, y1);
		textcolor(yellow);
		std::cout << square;
		textcolor(white);
	}


	gotoxy(0, 21);
}

void pesquisa_ops(int opcao, int opcao_b, int tam){
	int a = 254;
	char square = a;
	int y = 0;
	int y1 = 0;

	if (opcao_b > tam){
		y = 4 + opcao_b;
	}
	else {
		y = 3 + opcao_b;
	}

	if (opcao > tam){
		y1 = 4 + opcao;
	}
	else {
		y1 = 3 + opcao;
	}

	gotoxy(17, y);
	textcolor(yellow);
	std::cout << " ";
	textcolor(white);

	gotoxy(17, y1);
	textcolor(yellow);
	std::cout << square;
	textcolor(white);

	gotoxy(0, 21);
}

std::vector<std::string> pesquisa(int opcao , std::vector<std::string> vect){

	limparEcra();
	int a = 205;
	char char1 = a;
	std::string cmp;
	std::vector<std::string>cidades;

	textcolor(yellow);
	gotoxy(14,1);
	std::cout << "PESQUISA:";
	gotoxy(14,2);

	for (size_t i = 0; i < 61; i++) {
		std::cout << char1;
	}
	std::cout << std::endl;
	textcolor(white);

	gotoxy(25,1);
	std::cout << "> ";
	getline(std::cin, cmp);

	std::vector<std::string> v;

	switch (opcao) {
		case 1:{
			v = pesquisaExata(cidadesId,cmp);
			break;
		}

		case 2:{
			v = pesquisaAproximada(cidadesId,cmp);
			break;
		}
	}

	textcolor(light_red);
	gotoxy(19,3);
	std::cout << "TIPO";
	gotoxy(32,3);
	std::cout << "NOME";
	gotoxy(65,3);
	std::cout << "CIDADE";
	textcolor(white);

	int k = 0;
	for (size_t i = 0; i < v.size(); i++) {
		gotoxy(19,k+4);
		std::cout << v[i];
		gotoxy(32,k+4);
		std::cout <<  v[i+1];
		gotoxy(65,k+4);
		std::cout << v[i+2] ;
		cidades.push_back(v[i+2]);
		i++;
		i++;
		k++;
	}
	k++;
	gotoxy(19,k+4);
	std::cout << "Cancelar";

	int tecla = 0;
	int opcao1 = 1;
	int opcao_b = 1;

	do{
		pesquisa_ops(opcao1, opcao_b, cidades.size());
		opcao_b = opcao1;
		tecla = opcao_valida(opcao1,1,cidades.size()+1);

	} while (tecla != ENTER);

	gotoxy(0,21);

	if(opcao1 > cidades.size()){
		//do nothing
	}
	else {
		bool existe = false;

		for (size_t i = 0; i < vect.size(); i++) {
			if (vect[i] == cidades[opcao1-1]){
				existe = true;
				break;
			}
		}
		if (!existe){
			vect.push_back(cidades[opcao1-1]);
		}
	}

	return vect;
}

void escolha_ex_apx_interface(int opcao, bool imprimir){

	int a = 186;
	char char1 = a;  //

	int b = 201;
	char char2 = b; //

	int c = 205;
	char char3 = c; //

	int d = 187;
	char char4 = d; //

	int e = 200;
	char char5 = e; //

	int f = 188;
	char char6 = f; //

	int g = 204;
	char char7 = g; // obter -> â• 

	int h = 185;
	char char8 = h; // obter -> â•£

	if (imprimir){
		limparEcra();
		textcolor(yellow);
		gotoxy(14,5);
		std::cout << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;

		for (size_t i = 0; i < 7; i++) {
			gotoxy(14,6+i);
			std::cout <<char1;

			gotoxy(75,6+i);
			std::cout <<char1;
		}

		gotoxy(14,7);
		std::cout << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;

		gotoxy(14,13);
		std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6 << endl;

		textcolor(white);
		gotoxy(24,6);
		std::cout << "\tDeseja fazer uma pesquisa: ";
	}

	if (opcao == 1){
		textcolor(light_red);
	}
	else {
		textcolor(white);
	}
	gotoxy(25,9);
	std::cout << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3  << char3 << char3<< char4;
	gotoxy(25,10);
	std::cout << char1 << "  Exata";
	gotoxy(35,10);
	std::cout << char1;
	gotoxy(25,11);
	std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6;

	if (opcao == 2){
		textcolor(light_red);
	}
	else {
		textcolor(white);
	}

	gotoxy(53,9);
	std::cout << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3  << char3 << char3 << char3 << char4;
	gotoxy(53,10);
	std::cout << char1 << "Aproximada";
	gotoxy(64,10);
	std::cout << char1;
	gotoxy(53,11);
	std::cout << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6;

	textcolor(white);
	gotoxy(0,21);
}

int escolha_ex_apx(){
	int tecla = 0;
	int opcao = 1;
	bool imprimir = true;

	do{
		escolha_ex_apx_interface(opcao, imprimir);
		imprimir = false;
		tecla = opcao_valida_listas(opcao,1,2);

		if (tecla != RIGHT_KEY && tecla != LEFT_KEY)
			imprimir = true;

	} while(tecla != ENTER);

	return opcao;
}

std::vector<std::string> menu_pesquisa_PI(std::vector<std::string> vect) {

	int opcao = escolha_ex_apx();

	/*
	* OPCAO:
	*	1 - Pesquisa exata
	*	2 - Pesquisa aproximada
	*/
	vect = pesquisa(opcao, vect);

	return vect;
}

void menu_escolha(){
	int opcao = 1, opcao_b = 1, tecla, tecla1 = 0;
	bool imprimir = true;
	int carFich = 0;
	bool updated = false;
	int idI = 0, idF = 5;
	std::vector<std::string> vect;
	std::string partida;
	std::string chegada;
	std::vector<std::string> paragens;
	std::string data;
	unsigned int dia, mes, ano;

	do
	{
		if (imprimir)
		{
			limparEcra();
			cabecalho();
			displayBarraDestinos(idI, idF);
			gotoxy(39,4);
			textcolor(light_red);
			std::cout << "DESTINOS";


			gotoxy(0,10);
			textcolor(red);
			std::cout << "\t        Partida: " << std::endl;
			textcolor(green);
			std::cout << "\t        Destino: " << std::endl;
			textcolor(light_gray);
			std::cout << "\t        Data: " << std::endl;
			textcolor(light_gray);
			std::cout << "\t        Paragens: " << std::endl << std::endl;

			textcolor(white);
			std::cout << "\t        Procurar Paragens" << std::endl;
			std::cout << "\t        Avancar" << std::endl;
			std::cout << "\t        Cancelar" << std::endl;

			imprimir = false;

			if (partida == "")
			{
				gotoxy(25,10);
				textcolor(dark_gray);
				std::cout << " (obrigatorio)";
				textcolor(white);
			}
			else {
				gotoxy(25,10);
				std::cout << partida;
			}

			if (chegada == "")
			{
				gotoxy(25,11);
				textcolor(dark_gray);
				std::cout << " (obrigatorio)";
				textcolor(white);
			}
			else {
				gotoxy(25,11);
				std::cout << chegada;
			}

			if (data == "")
			{
				gotoxy(23,12);
				textcolor(dark_gray);
				std::cout << "( DD/MM/AAAA )";
				textcolor(white);
			}
			else {
				gotoxy(23,12);
				std::cout << data;
			}

			gotoxy(0,21);

		}

		if (paragens.size() == 0)
		{
			gotoxy(27,13);
			textcolor(dark_gray);
			std::cout << "(opcional)";
			textcolor(white);
		}
		else {
			int nLetras = 0;
			gotoxy(25,13);
			textcolor(white);

			for(size_t i = 0; i < paragens.size(); i++)
			{
				if (nLetras + paragens[i].size() < 45)
				{
						std::cout << "  " << paragens[i];
						nLetras += paragens[i].size()+2;
				}
				else {
					std::cout << "...";
					break;
				}

			}
		}


		if (opcao == 1)
		{
			displayCaixaDestinos(1, idI, idF);
		}
		else if(opcao_b == 1){
			displayCaixaDestinos(0, idI, idF);
		}

		menu_escolha_ops(opcao,opcao_b);
		opcao_b = opcao;


		tecla = opcao_valida(opcao, 1, 8);
		Sleep(100);

		tecla1 = 0;
		if (tecla == ENTER)
		switch (opcao)
		{
		case 1:
			while (tecla1 != ENTER) {
				tecla1 = tecla_pressionada();
				barraDestinos_move(idI, idF, tecla1);
				displayBarraDestinos(idI, idF);
				displayCaixaDestinos(1, idI, idF);
			}
			imprimir = true;
			break;

		case 2:{
			Cidade cid = Cidade();
			while(cid.getId() == 0){
				gotoxy(25,10);
				std::cout << "                                                                ";
				gotoxy(25,10);
				getline(cin, partida);
				cid = pesquisaNome(cidadesNome, partida);
				if (cid.getId() == 0)
				{
					gotoxy(25,10);
					std::cout << "                                                                ";
					gotoxy(25,10);
					textcolor(red);
					std::cout << " Cidade nao existente";
					textcolor(white);
					Sleep(1000);
					cin.ignore(256,'\n');
				}
				}
				gotoxy(0,21);
			}
			break;

		case 3:{
			Cidade cid = Cidade();

			while(cid.getId() == 0){
					gotoxy(25,11);
					std::cout << "                                                                ";
					gotoxy(25,11);
					getline(cin, chegada);
					cid = pesquisaNome(cidadesNome, chegada);
					if (cid.getId() == 0)
					{
						gotoxy(25,11);
						std::cout << "                                                                ";
						gotoxy(25,11);
						textcolor(red);
						std::cout << " Cidade nao existente";
						textcolor(white);
						Sleep(1000);
						cin.ignore(256,'\n');
					}
				}
			gotoxy(0,21);
			}
			break;

		case 4:{
			bool avancar = false;
			char sep = '/';
			char ch1, ch2;

			while(!avancar)
			{
				gotoxy(23,12);
				std::cout << "                                                                ";
				gotoxy(25,12);
				getline(cin, data);
				stringstream ss1(data);
				ss1 >> dia >> ch1 >> mes >> ch2 >> ano;

				if ((ch1 != sep) || (ch2 != sep)){
					gotoxy(23,12);
					std::cout << "                                                                ";
					gotoxy(25,12);
					textcolor(red);
					std::cout << " Formato invalido";
					textcolor(white);
					Sleep(1000);
				} else {
					if (!dia_existe(dia,mes,ano)){
						gotoxy(23,12);
						std::cout << "                                                                ";
						gotoxy(25,12);
						textcolor(red);
						std::cout << " Data inexistente";
						textcolor(white);
						Sleep(1000);
					} else {
						avancar = true;
					}

				}

			}
			gotoxy(0,21);
		}
			break;

		case 5:
			break;

		case 6:{
			std::vector<std::string> tmp;
			tmp.push_back(partida);
			tmp.push_back(chegada);

			std::vector<std::string> v = menu_pesquisa_PI(tmp);

			if (v.size() > tmp.size()){
				paragens.push_back(v[v.size()-1]);
			}

			imprimir = true;
			opcao = 1;
			opcao_b = 1;
			break;
		}

		case 7:{

				if (partida != "")
					if (chegada != "")
						if(data != ""){
							vect.push_back(partida);
							vect.push_back(chegada);
							vect.push_back(data);

							for (size_t i = 0; i < paragens.size(); i++){
								vect.push_back(paragens[i]);
							}

							menu_custo_tempo(vect);
							imprimir = true;
							return;
						}

				gotoxy(14,21);
				textcolor(red);
				std::cout << "Preencha as informacoes obrigatorias primeiro" ;
				Sleep(1000);
				textcolor(white);
				gotoxy(14,21);
				std::cout << "                                              " ;
				gotoxy(0,21);

				break;
			}

		case 8:
			return;

		}

	} while ((opcao != 8) || (tecla != ENTER));

	std::cout << std::endl << std::endl;
}

void menu_inicial_ops(int opcao, int opcao_b){
	int a = 254;
	char square = a;

	int y = 9 + opcao_b;
	int y1 = 9 + opcao;

	gotoxy(34, y);
	textcolor(yellow);
	std::cout << " ";
	textcolor(white);

	gotoxy(34, y1);
	textcolor(yellow);
	std::cout << square;
	textcolor(white);

	gotoxy(0, 21);
}

void menu_inicial(){
	int opcao = 1, opcao_b = 1, tecla;
	bool imprimir = true;
	int carFich = 0;
	bool updated = false;

	do
	{
		if (imprimir)
		{
			titulo();
			std::cout << std::endl << std::endl;
			std::cout << "\t\t\t\t    Carregar Ficheiros" << std::endl;
			std::cout << "\t\t\t\t    Abrir Mapa" << std::endl;
			std::cout << "\t\t\t\t    Escolher viagem" << std::endl;
			std::cout << "\t\t\t\t    Sobre" << std::endl;
			std::cout << "\t\t\t\t    Sair" << std::endl;
			std::cout << std::endl << std::endl << std::endl << std::endl;
			std::cout << "\t\t\t\t\t\t\t\t" << mostrar_mes(mes_do_sistema()) << " " << ano_do_sistema();
			std::cout << std::endl << std::endl;

		}

		imprimir = false;

		menu_inicial_ops(opcao,opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 5);
		Sleep(100);


		if (tecla == ENTER)
		switch (opcao)
		{
		case 1:
			if (carFich == 0){
				carFich = carregarFicheiros();
			}
			else carregarFichMsg();
			break;

		case 2:
			if (carFich == 0){
				abrirMapa(0);
			}
			else {
				if (!updated){
					abrirMapa(1);
					updateGViewer();
					updated = true;
				}
				else abrirMapa(1);
			}
			break;

		case 3:
			if (carFich == 1){
				menu_escolha();
				imprimir = true;
			}
			else abrirMapa(0);
			break;

		case 4:
			creditos();
			imprimir = true;
			break;

		case 5:
			return;

		}

	} while ((opcao != 5) || (tecla != ENTER));

	std::cout << std::endl << std::endl;
}

int main() {
	configurar_terminal();
	gv = new GraphViewer(1680, 1050, NOT_DYNAMIC);
	menu_inicial();
	limparEcra();
	gv->closeWindow();


	gotoxy(0,0);
	return 0;
}
