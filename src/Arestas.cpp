/*
* Cidade.cpp
*
*  Created on: 08/04/2017
*      Author: David
*/

#include "Arestas.h"

Aresta::Aresta(unsigned int id_origem, unsigned int id_destino){
	this->id_origem = id_origem;
	this->id_destino = id_destino;
}

unsigned int Aresta::getIdOrigem(){
	return id_origem;
}

unsigned int Aresta::getIdDestino(){
	return id_destino;
}
