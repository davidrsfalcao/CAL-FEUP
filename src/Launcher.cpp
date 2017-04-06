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
#include "uteis.h"

#define NOT_DYNAMIC false
#define EDGE_COLOR "white"
#define VERTEX_COLOR "red"
#define ID_MAX 110 //mudar consoante o numero de ficheiros

Graph<Cidade> graph;
GraphViewer *gv;

//Variaveis globais
std::vector<Cidade> cidadesId;  //cidades ordenadas por Id
std::vector<Cidade> cidadesNome; //cidades ordenadas por Nome

void creditos(){
	system("cls");
	titulo();
	std::cout << std::endl;
	std::cout << std::endl << "\t     Primeiro projeto da cadeira 'Concepcao e Analise de Algoritmos'" << endl << endl;
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

			Cidade cidade = Cidade(contador, nomeCidade, cords, hoteis,
					destinos);

			graph.addVertex(cidade);
			cidadesId.push_back(cidade);
			cidadesNome.push_back(cidade);
			in.close();

		}

		contador++;
	}
	cidadesId = ordenarPorId(cidadesId, 0, cidadesId.size()-1);
	cidadesNome = ordenarPorNome(cidadesNome, 0, cidadesNome.size()-1);

	gotoxy(0,21);
	textcolor(light_green);
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
				} else {
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
		std::cout << "\t    A abir . . ." << std::endl;

		inicializarGraphicViewer();

		gotoxy(0,21);
		textcolor(white);
		std::cout << "\t                 " << std::endl;

	}

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
			imprimir = true;
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
	 //configurar_terminal();
	gv = new GraphViewer(1680, 1050, NOT_DYNAMIC);
	menu_inicial();

	limparEcra();
	gv->closeWindow();

	gotoxy(0,0);
	return 0;
}
