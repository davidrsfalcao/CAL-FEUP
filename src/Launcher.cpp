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
		std::cout << "\t    A abir . . ." << std::endl;

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

		if (idF == cidadesNome.size()-1)
		{
			return;
		}
		else {
			idI = idF;

			while (1){
				if (idF == cidadesNome.size()){
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

void menu_resultado(std::vector<std::string> vect){
	limparEcra();


}

void menu_escolha_ops(int opcao, int opcao_b){
	int a = 254;
	char square = a;
	int y = 0;
	int y1 = 0;

	if (opcao_b > 4){
		y = 9 + opcao_b;
	}
	else {
		y = 8 + opcao_b;
	}

	if (opcao > 4){
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

	do
	{
		if (imprimir)
		{
			limparEcra();
			cabecalho();
			displayBarraDestinos(idI, idF);
			gotoxy(0,10);
			textcolor(red);
			std::cout << "\t        Partida: " << std::endl;
			textcolor(green);
			std::cout << "\t        Destino: " << std::endl;
			textcolor(light_gray);
			std::cout << "\t        Paragens: " << std::endl << std::endl;

			textcolor(white);
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

			if (paragens.size() == 0)
			{
				gotoxy(27,12);
				textcolor(dark_gray);
				std::cout << "(opcional)";
				textcolor(white);
			}

			gotoxy(0,21);

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


		tecla = opcao_valida(opcao, 1, 6);
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
					}
				}
			gotoxy(0,21);
			}
			break;

		case 4:
			break;

		case 5:{
				vect.push_back(partida);
				vect.push_back(chegada);

				for (size_t i = 0; i < paragens.size(); i++{
					vect.push_back(paragens[i]);
				}
			}
			break;

		case 6:
			return;

		}

	} while ((opcao != 6) || (tecla != ENTER));

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
			menu_escolha();
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
	configurar_terminal();
	gv = new GraphViewer(1680, 1050, NOT_DYNAMIC);
	menu_inicial();

	limparEcra();
	gv->closeWindow();

	gotoxy(0,0);
	return 0;
}
