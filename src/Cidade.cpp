/*
* Cidade.cpp
*
*  Created on: 01/04/2017
*      Author: David
*/

#include "Cidade.h"

Cidade::Cidade() {
	id = 999999;
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

int Cidade::getIdDestino(int n){

	return destinos[n*3];
}

int Cidade::getCustoViagemDestino(int n){

	return destinos[1+n*3];
}
