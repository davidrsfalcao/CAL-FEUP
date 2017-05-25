/*
* Cidade.cpp
*
*  Created on: 01/04/2017
*      Author: David
*/

#include "Cidade.h"
#include "Algoritmos.h"

extern std::vector<Cidade> cidadesId;

Cidade::Cidade() {
	id = 0;
	nome = "";
	coordenadas = Coordenadas();
	hoteis = *(new std::vector<Alojamento*>());
}

Cidade::Cidade(unsigned int id, std::string nome, Coordenadas coordenadas, std::vector<Alojamento*> hoteis, std::vector<int> destinos) {
	this->id = id;
	this->nome = nome;
	this->coordenadas = coordenadas;
	this->hoteis = hoteis;
	this->destinos = destinos;
}

unsigned int Cidade::getId() {
	return id;
}

void Cidade::setId(unsigned int id){
	this->id = id;
}

std::string Cidade::getNome(){
	return nome;
}

void Cidade::setNome(std::string nome){
	this->nome = nome;
}

Coordenadas Cidade::getCoordenadas() {
	return coordenadas;
}

void Cidade::setCoordenadas(Coordenadas coOrdenadas){
	this->coordenadas = coordenadas;
}

std::vector<Alojamento*> Cidade::getTodosHoteis(){
	return hoteis;
}

Alojamento* Cidade::HotelMaisBarato(int dia, int mes) {

	std::vector<Alojamento*>::iterator it = hoteis.begin();

	Alojamento *hotel = new Alojamento();
	int preco_min = 999999999;
	int preco_temp = 0;

	for (; it != hoteis.end(); it++) {
		preco_temp = (*it)->getPreco(dia, mes);
		if (preco_temp < preco_min) {
			preco_min = preco_temp;
			hotel = (*it);
		}

	}

	return hotel;
}

std::vector<int> Cidade::getDestinos(){
	return destinos;
}

unsigned int Cidade::getNumeroDestinos(){
	return destinos.size()/3;
}

int Cidade::getIdDestino(int n){

	return destinos[n*3];
}

int Cidade::getCustoViagem(int n){

	return destinos[1+n*3];
}

int Cidade::getTempoViagem(int n){

	return destinos[2+n*3];
}

std::ostream & operator <<(std::ostream &of, const Cidade &ci){

	of << "ID: " << ci.id << std::endl;
	of << "Cidade:" << ci.nome << std::endl;
	for (size_t i = 0; i < ci.hoteis.size(); i++) {
		of << (*ci.hoteis[i]) << std::endl;
	}
	of << "Numero destinos: " << ci.destinos.size()/3 << std::endl;
	of << "Destinos: " << std::endl << std::endl;

	for (size_t i = 0; i < (ci.destinos.size()/3) ; i++) {

		unsigned int id = ci.destinos[i*3];
		Cidade cid = pesquisaId(cidadesId,id);

		of << "Cidade: " << cid.getNome() << std::endl;
		of << "Custo Viagem: " << ci.destinos[1+i*3] << std::endl;
		of << "Tempo Viagem: " << ci.destinos[2+i*3] << std::endl << std::endl;
	}

	return of;
}

bool Cidade::operator==(const Cidade &ci){

	return ci.id == id;
}

bool Cidade::operator!=(const Cidade &ci){

	return ci.id != id;
}
